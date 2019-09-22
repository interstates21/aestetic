#include "alt.h"
static void vline(t_scene *scene, int x, int y1, int y2, int top, int middle, int bottom)
{
    y1 = clamp(y1, 0, HEIGHT - 1);
    y2 = clamp(y2, 0, HEIGHT - 1);
    if (y2 == y1)
        sdl_put_pix(&(scene->pixels), x, y1, middle);
    else if (y2 > y1)
    {
        sdl_put_pix(&(scene->pixels), x, y1, top);
        for (int y = y1 + 1; y < y2; ++y)
            sdl_put_pix(&(scene->pixels), x, y, middle);
        sdl_put_pix(&(scene->pixels), x, y2, bottom);
    }
}

void DrawScreen(t_scene *scene)
{
    t_player player = scene->player;

    player.pos.z = 5; // ghost#hardcoded

    enum
    {
        MaxQueue = 32
    }; // maximum number of pending portal renders
    struct item
    {
        int sectorno, sx1, sx2;
    } queue[MaxQueue], *head = queue, *tail = queue;
    int ytop[WIDTH] = {0}, ybottom[WIDTH], renderedsectors[scene->n_sectors];
    for (unsigned x = 0; x < WIDTH; ++x)
        ybottom[x] = HEIGHT - 1;
    for (unsigned n = 0; n < scene->n_sectors; ++n)
        renderedsectors[n] = 0;

    /* Begin whole-screen rendering from pos the player is. */
    *head = (struct item){player.sector, 0, WIDTH - 1};
    if (++head == queue + MaxQueue)
        head = queue;

    do
    {
        /* Pick a sector & slice from the queue to draw */
        const struct item now = *tail;
        if (++tail == queue + MaxQueue)
            tail = queue;

        if (renderedsectors[now.sectorno] & 0x21)
            continue; // Odd = still rendering, 0x20 = give up
        ++renderedsectors[now.sectorno];
        t_sector *sect;
        sect = &(scene->sectors)[now.sectorno];
        /* Render each walls of this sector that is facing towards player. */
        for (unsigned s = 0; s < sect->npoints; ++s)
        {
            /* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
            float vx1 = sect->walls[s + 0].x - player.pos.x, vy1 = sect->walls[s + 0].y - player.pos.y;
            float vx2 = sect->walls[s + 1].x - player.pos.x, vy2 = sect->walls[s + 1].y - player.pos.y;
            /* Rotate them around the player's view */
            float pcos = player.anglecos, psin = player.anglesin;
            float tx1 = vx1 * psin - vy1 * pcos, tz1 = vx1 * pcos + vy1 * psin;
            float tx2 = vx2 * psin - vy2 * pcos, tz2 = vx2 * pcos + vy2 * psin;
            /* Is the walls at least partially in front of the player? */
            if (tz1 <= 0 && tz2 <= 0)
                continue;
            /* If it's partially behind the player, clip it against player's view frustrum */
            if (tz1 <= 0 || tz2 <= 0)
            {
                float nearz = 0.001, farz = 5, nearside = 0.001, farside = 20.f;
                // Find an intersection between the walls and the approximate edges of player's view
                t_v2f i1 = Intersect(tx1, tz1, tx2, tz2, -nearside, nearz, -farside, farz);
                t_v2f i2 = Intersect(tx1, tz1, tx2, tz2, nearside, nearz, farside, farz);
                if (tz1 < nearz)
                {
                    if (i1.y > 0)
                    {
                        tx1 = i1.x;
                        tz1 = i1.y;
                    }
                    else
                    {
                        tx1 = i2.x;
                        tz1 = i2.y;
                    }
                }
                if (tz2 < nearz)
                {
                    if (i1.y > 0)
                    {
                        tx2 = i1.x;
                        tz2 = i1.y;
                    }
                    else
                    {
                        tx2 = i2.x;
                        tz2 = i2.y;
                    }
                }
            }
            /* Do perspective transformation */
            float xscale1 = HFOV / tz1, yscale1 = VFOV / tz1;
            int x1 = WIDTH / 2 - (int)(tx1 * xscale1);
            float xscale2 = HFOV / tz2, yscale2 = VFOV / tz2;
            int x2 = WIDTH / 2 - (int)(tx2 * xscale2);
            if (x1 >= x2 || x2 < now.sx1 || x1 > now.sx2)
                continue; // Only render if it's visible
            /* Acquire the floor and ceiling heights, relative to pos the player's view is */
            float yceil = sect->ceil - player.pos.z;
            float yfloor = sect->floor - player.pos.z;
            /* Check the edge type. neighbor=-1 means walls, other=boundary between two scene->sectors. */
            int neighbor = sect->portals[s];
            float nyceil = 0, nyfloor = 0;
            if (neighbor >= 0) // Is another sector showing through this portal?
            {
                nyceil = scene->sectors[neighbor].ceil - player.pos.z;
                nyfloor = scene->sectors[neighbor].floor - player.pos.z;
            }
            /* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
#define Yaw(y, z) (y + z * player.yaw)
            int y1a = HEIGHT / 2 - (int)(Yaw(yceil, tz1) * yscale1), y1b = HEIGHT / 2 - (int)(Yaw(yfloor, tz1) * yscale1);
            int y2a = HEIGHT / 2 - (int)(Yaw(yceil, tz2) * yscale2), y2b = HEIGHT / 2 - (int)(Yaw(yfloor, tz2) * yscale2);
            /* The same for the neighboring sector */
            int ny1a = HEIGHT / 2 - (int)(Yaw(nyceil, tz1) * yscale1), ny1b = HEIGHT / 2 - (int)(Yaw(nyfloor, tz1) * yscale1);
            int ny2a = HEIGHT / 2 - (int)(Yaw(nyceil, tz2) * yscale2), ny2b = HEIGHT / 2 - (int)(Yaw(nyfloor, tz2) * yscale2);

            /* Render the walls. */
            int beginx = max(x1, now.sx1), endx = min(x2, now.sx2);
            for (int x = beginx; x <= endx; ++x)
            {
                /* Calculate the Z coordinate for this point. (Only used for lighting.) */
                int z = ((x - x1) * (tz2 - tz1) / (x2 - x1) + tz1) * 8;
                /* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
                int ya = (x - x1) * (y2a - y1a) / (x2 - x1) + y1a, cya = clamp(ya, ytop[x], ybottom[x]); // top
                int yb = (x - x1) * (y2b - y1b) / (x2 - x1) + y1b, cyb = clamp(yb, ytop[x], ybottom[x]); // bottom

                /* Render ceiling: everything above this sector's ceiling height. */
                vline(scene, x, ytop[x], cya - 1, 0x111111, 0x222222, 0x111111);
                /* Render floor: everything below this sector's floor height. */
                vline(scene, x, cyb + 1, ybottom[x], 0x0000FF, 0x0000AA, 0x0000FF);

                /* Is there another sector behind this edge? */
                if (neighbor >= 0)
                {
                    /* Same for _their_ floor and ceiling */
                    int nya = (x - x1) * (ny2a - ny1a) / (x2 - x1) + ny1a, cnya = clamp(nya, ytop[x], ybottom[x]);
                    int nyb = (x - x1) * (ny2b - ny1b) / (x2 - x1) + ny1b, cnyb = clamp(nyb, ytop[x], ybottom[x]);
                    /* If our ceiling is higher than their ceiling, render upper walls */
                    unsigned r1 = 0x010101 * (255 - z), r2 = 0x040007 * (31 - z / 8);
                    vline(scene, x, cya, cnya - 1, 0, x == x1 || x == x2 ? 0 : r1, 0); // Between our and their ceiling
                    ytop[x] = clamp(max(cya, cnya), ytop[x], HEIGHT - 1);              // Shrink the remaining window below these ceilings
                    /* If our floor is lower than their floor, render bottom walls */
                    vline(scene, x, cnyb + 1, cyb, 0, x == x1 || x == x2 ? 0 : r2, 0); // Between their and our floor
                    ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]);                 // Shrink the remaining window above these floors
                }
                else
                {
                    /* There's no neighbor. Render walls from top (cya = ceiling level) to bottom (cyb = floor level). */
                    unsigned r = 0x010101 * (255 - z);
                    vline(scene, x, cya, cyb, 0, x == x1 || x == x2 ? 0 : r, 0);
                }
            }
            /* Schedule the neighboring sector for rendering within the window formed by this walls. */
            if (neighbor >= 0 && endx >= beginx && (head + MaxQueue + 1 - tail) % MaxQueue)
            {
                *head = (struct item){neighbor, beginx, endx};
                if (++head == queue + MaxQueue)
                    head = queue;
            }
        } // for s in sector's edges
        ++renderedsectors[now.sectorno];
    } while (head != tail); // render any other queued scene->sectors
}
