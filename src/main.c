#include "../includes/alt.h"
#include "../includes/functions.h"

// todo: resize window

// SDL_Texture   *load_sur(SDL_Renderer *ren) {
//     SDL_Texture *tex = NULL;

//     SDL_Surface *sur = SDL_LoadBMP("src/0.bmp");
//     if (sur == NULL) {
//         ft_putstr(SDL_GetError());
//         exit(1);
//     }

//      tex = SDL_CreateTextureFromSurface(ren, sur);

//      SDL_FreeSurface(sur);

//      return (tex);
// }

static void LoadData()
{

    FILE* fp = fopen("map-clear.txt", "rt");
    if(!fp) { perror("map-clear.txt"); exit(1); }
    char Buf[256], word[256], *ptr;
    struct xy* vert = NULL, v;
    int n, m, NumVertices = 0;
    while(fgets(Buf, sizeof Buf, fp))
        switch(sscanf(ptr = Buf, "%32s%n", word, &n) == 1 ? word[0] : '\0')
        {
            case 'v': // vertex
                for(sscanf(ptr += n, "%f%n", &v.y, &n); sscanf(ptr += n, "%f%n", &v.x, &n) == 1; )
                    { vert = realloc(vert, ++NumVertices * sizeof(*vert)); vert[NumVertices-1] = v; }
                break;
            case 's': // sector
                sectors = realloc(sectors, ++NumSectors * sizeof(*sectors));
                struct sector* sect = &sectors[NumSectors-1];
                int* num = NULL;
                sscanf(ptr += n, "%f%f%n", &sect->floor,&sect->ceil, &n);
                for(m=0; sscanf(ptr += n, "%32s%n", word, &n) == 1 && word[0] != '#'; )
                    { num = realloc(num, ++m * sizeof(*num)); num[m-1] = word[0]=='x' ? -1 : atoi(word); }
                sect->npoints   = m /= 2;//уууух, сука
                sect->neighbors = malloc( (m  ) * sizeof(*sect->neighbors) );
                sect->vertex    = malloc( (m+1) * sizeof(*sect->vertex)    );
                for(n=0; n<m; ++n) sect->neighbors[n] = num[m + n];
                for(n=0; n<m; ++n) sect->vertex[n+1]  = vert[num[n]]; // TODO: Range checking
                sect->vertex[0] = sect->vertex[m]; // Ensure the vertexes form a loop
                free(num);
                break;
            case 'p':; // player
                float angle;
                sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle,&n);
                player = (struct player) { {v.x, v.y, 0}, {0,0,0}, angle,0,0,0, n }; // TODO: Range checking
                player.where.z = sectors[player.sector].floor + EyeHeight;
        }
    fclose(fp);
    free(vert);
}
static void UnloadData()
{
    for(unsigned a=0; a<NumSectors; ++a) free(sectors[a].vertex);
    for(unsigned a=0; a<NumSectors; ++a) free(sectors[a].neighbors);
    free(sectors);
    sectors    = NULL;
    NumSectors = 0;
}


Uint32 *get_screen_pixels(void)
{
    Uint32 *pixels;

    if (!(pixels = (Uint32 *)malloc(WIDTH * HEIGHT * sizeof(Uint32)))) // todo: make sure we don't need 1 extra memory cell
        print_err("allocating pixels failed.");
    memset(pixels, 0, WIDTH * HEIGHT * sizeof(Uint32));
    return (pixels);
}

/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
static void vline(t_scene* scene, int x, int y1,int y2, int top,int middle,int bottom)
{
    y1 = clamp(y1, 0, HEIGHT-1);
    y2 = clamp(y2, 0, HEIGHT-1);
    if(y2 == y1)
        sdl_put_pix(&(scene->pixels), x, y1, middle);
    else if(y2 > y1)
    {
         sdl_put_pix(&(scene->pixels), x, y1, top);
        for(int y=y1+1; y<y2; ++y)
            sdl_put_pix(&(scene->pixels), x, y, middle);
        sdl_put_pix(&(scene->pixels), x, y2, bottom);
    }
}

/* MovePlayer(dx,dy): Moves the player by (dx,dy) in the map, and
 * also updates their anglesin/anglecos/sector properties properly.
 */
static void MovePlayer(float dx, float dy)
{
    float px = player.where.x, py = player.where.y;
    /* Check if this movement crosses one of this sector's edges
     * that have a neighboring sector on the other side.
     * Because the edge vertices of each sector are defined in
     * clockwise order, PointSide will always return -1 for a point
     * that is outside the sector and 0 or 1 for a point that is inside.
     */
    const struct sector* const sect = &sectors[player.sector];
    const struct xy* const vert = sect->vertex;
    for(unsigned s = 0; s < sect->npoints; ++s)
        if(sect->neighbors[s] >= 0
        && IntersectBox(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
        && PointSide(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
        {
            player.sector = sect->neighbors[s];
            break;
        }

    player.where.x += dx;
    player.where.y += dy;
    player.anglesin = sinf(player.angle);
    player.anglecos = cosf(player.angle);
}

static void DrawScreen(t_scene *scene)
{
    enum { MaxQueue = 32 };  // maximum number of pending portal renders
    struct item { int sectorno,sx1,sx2; } queue[MaxQueue], *head=queue, *tail=queue;
    int ytop[WIDTH]={0}, ybottom[WIDTH], renderedsectors[NumSectors];
    for(unsigned x=0; x<WIDTH; ++x) ybottom[x] = HEIGHT-1;
    for(unsigned n=0; n<NumSectors; ++n) renderedsectors[n] = 0;

    /* Begin whole-screen rendering from where the player is. */
    *head = (struct item) { player.sector, 0, WIDTH-1 };
    if(++head == queue+MaxQueue) head = queue;

    do {
    /* Pick a sector & slice from the queue to draw */
    const struct item now = *tail;
    if(++tail == queue+MaxQueue) tail = queue;

    if(renderedsectors[now.sectorno] & 0x21) continue; // Odd = still rendering, 0x20 = give up
    ++renderedsectors[now.sectorno];
    const struct sector* const sect = &sectors[now.sectorno];
    /* Render each wall of this sector that is facing towards player. */
    for(unsigned s = 0; s < sect->npoints; ++s)
    {
        /* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
        float vx1 = sect->vertex[s+0].x - player.where.x, vy1 = sect->vertex[s+0].y - player.where.y;
        float vx2 = sect->vertex[s+1].x - player.where.x, vy2 = sect->vertex[s+1].y - player.where.y;
        /* Rotate them around the player's view */
        float pcos = player.anglecos, psin = player.anglesin;
        float tx1 = vx1 * psin - vy1 * pcos,  tz1 = vx1 * pcos + vy1 * psin;
        float tx2 = vx2 * psin - vy2 * pcos,  tz2 = vx2 * pcos + vy2 * psin;
        /* Is the wall at least partially in front of the player? */
        if(tz1 <= 0 && tz2 <= 0) continue;
        /* If it's partially behind the player, clip it against player's view frustrum */
        if(tz1 <= 0 || tz2 <= 0)
        {
            float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
            // Find an intersection between the wall and the approximate edges of player's view
            struct xy i1 = Intersect(tx1,tz1,tx2,tz2, -nearside,nearz, -farside,farz);
            struct xy i2 = Intersect(tx1,tz1,tx2,tz2,  nearside,nearz,  farside,farz);
            if(tz1 < nearz) { if(i1.y > 0) { tx1 = i1.x; tz1 = i1.y; } else { tx1 = i2.x; tz1 = i2.y; } }
            if(tz2 < nearz) { if(i1.y > 0) { tx2 = i1.x; tz2 = i1.y; } else { tx2 = i2.x; tz2 = i2.y; } }
        }
        /* Do perspective transformation */
        float xscale1 = hfov / tz1, yscale1 = vfov / tz1;    int x1 = WIDTH/2 - (int)(tx1 * xscale1);
        float xscale2 = hfov / tz2, yscale2 = vfov / tz2;    int x2 = WIDTH/2 - (int)(tx2 * xscale2);
        if(x1 >= x2 || x2 < now.sx1 || x1 > now.sx2) continue; // Only render if it's visible
        /* Acquire the floor and ceiling heights, relative to where the player's view is */
        float yceil  = sect->ceil  - player.where.z;
        float yfloor = sect->floor - player.where.z;
        /* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
        int neighbor = sect->neighbors[s];
        float nyceil=0, nyfloor=0;
        if(neighbor >= 0) // Is another sector showing through this portal?
        {
            nyceil  = sectors[neighbor].ceil  - player.where.z;
            nyfloor = sectors[neighbor].floor - player.where.z;
        }
        /* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
        #define Yaw(y,z) (y + z*player.yaw)
        int y1a  = HEIGHT/2 - (int)(Yaw(yceil, tz1) * yscale1),  y1b = HEIGHT/2 - (int)(Yaw(yfloor, tz1) * yscale1);
        int y2a  = HEIGHT/2 - (int)(Yaw(yceil, tz2) * yscale2),  y2b = HEIGHT/2 - (int)(Yaw(yfloor, tz2) * yscale2);
        /* The same for the neighboring sector */
        int ny1a = HEIGHT/2 - (int)(Yaw(nyceil, tz1) * yscale1), ny1b = HEIGHT/2 - (int)(Yaw(nyfloor, tz1) * yscale1);
        int ny2a = HEIGHT/2 - (int)(Yaw(nyceil, tz2) * yscale2), ny2b = HEIGHT/2 - (int)(Yaw(nyfloor, tz2) * yscale2);

        /* Render the wall. */
        int beginx = max(x1, now.sx1), endx = min(x2, now.sx2);
        for(int x = beginx; x <= endx; ++x)
        {
            /* Calculate the Z coordinate for this point. (Only used for lighting.) */
            int z = ((x - x1) * (tz2-tz1) / (x2-x1) + tz1) * 8;
            /* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
            int ya = (x - x1) * (y2a-y1a) / (x2-x1) + y1a, cya = clamp(ya, ytop[x],ybottom[x]); // top
            int yb = (x - x1) * (y2b-y1b) / (x2-x1) + y1b, cyb = clamp(yb, ytop[x],ybottom[x]); // bottom

            /* Render ceiling: everything above this sector's ceiling height. */
            vline(scene, x, ytop[x], cya-1, 0x111111 ,0x222222,0x111111);
            /* Render floor: everything below this sector's floor height. */
            vline(scene, x, cyb+1, ybottom[x], 0x0000FF,0x0000AA,0x0000FF);

            /* Is there another sector behind this edge? */
            if(neighbor >= 0)
            {
                /* Same for _their_ floor and ceiling */
                int nya = (x - x1) * (ny2a-ny1a) / (x2-x1) + ny1a, cnya = clamp(nya, ytop[x],ybottom[x]);
                int nyb = (x - x1) * (ny2b-ny1b) / (x2-x1) + ny1b, cnyb = clamp(nyb, ytop[x],ybottom[x]);
                /* If our ceiling is higher than their ceiling, render upper wall */
                unsigned r1 = 0x010101 * (255-z), r2 = 0x040007 * (31-z/8);
                vline(scene, x, cya, cnya-1, 0, x==x1||x==x2 ? 0 : r1, 0); // Between our and their ceiling
                ytop[x] = clamp(max(cya, cnya), ytop[x], HEIGHT-1);   // Shrink the remaining window below these ceilings
                /* If our floor is lower than their floor, render bottom wall */
                vline(scene, x, cnyb+1, cyb, 0, x==x1||x==x2 ? 0 : r2, 0); // Between their and our floor
                ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]); // Shrink the remaining window above these floors
            }
            else
            {
                /* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
                unsigned r = 0x010101 * (255-z);
                vline(scene, x, cya, cyb, 0, x==x1||x==x2 ? 0 : r, 0);
            }
        }
        /* Schedule the neighboring sector for rendering within the window formed by this wall. */
        if(neighbor >= 0 && endx >= beginx && (head+MaxQueue+1-tail)%MaxQueue)
        {
            *head = (struct item) { neighbor, beginx, endx };
            if(++head == queue+MaxQueue) head = queue;
        }
    } // for s in sector's edges
    ++renderedsectors[now.sectorno];
    } while(head != tail); // render any other queued sectors
}

void shitty_controller(t_controller *controller, bool *end, t_sdl sdl) {

 float eyeheight =controller->ducking ? DuckHeight : EyeHeight;
       controller->ground= !controller->falling;
        if(controller->falling)
        {
            player.velocity.z -= 0.05f; /* Add gravity */
            float nextz = player.where.z + player.velocity.z;
            if(player.velocity.z < 0 && nextz  < sectors[player.sector].floor + eyeheight) // When going down
            {
                /* Fix tocontroller.ground*/
                player.where.z    = sectors[player.sector].floor + eyeheight;
                player.velocity.z = 0;
                controller->falling = 0;
               controller->ground = 1;
            }
            else if(player.velocity.z > 0 && nextz > sectors[player.sector].ceil) // When going up
            {
                /* Prevent jumping above ceiling */
                player.velocity.z = 0;
                controller->falling = 1;
            }
            if(controller->falling)
            {
                player.where.z += player.velocity.z;
                controller->moving = 1;
            }
        }
        /* Horizontal collision detection */
        if(controller->moving)
        {
            float px = player.where.x,    py = player.where.y;
            float dx = player.velocity.x, dy = player.velocity.y;

            const struct sector* const sect = &sectors[player.sector];
            const struct xy* const vert = sect->vertex;
            /* Check if the player is about to cross one of the sector's edges */
            for(unsigned s = 0; s < sect->npoints; ++s)
                if(IntersectBox(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
                && PointSide(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
                {
                    /* Check where the hole is. */
                    float hole_low  = sect->neighbors[s] < 0 ?  9e9 : max(sect->floor, sectors[sect->neighbors[s]].floor);
                    float hole_high = sect->neighbors[s] < 0 ? -9e9 : min(sect->ceil,  sectors[sect->neighbors[s]].ceil );
                    /* Check whether we're bumping into a wall. */
                    if(hole_high < player.where.z+HeadMargin
                    || hole_low  > player.where.z-eyeheight+KneeHeight)
                    {
                        /* Bumps into a wall! Slide along the wall. */
                        /* This formula is from Wikipedia article "vector projection". */
                        float xd = vert[s+1].x - vert[s+0].x, yd = vert[s+1].y - vert[s+0].y;
                        dx = xd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                        dy = yd * (dx*xd + yd*dy) / (xd*xd + yd*yd);
                        controller->moving = 0;
                    }
                }
            MovePlayer(dx, dy);
            controller->falling = 1;
        }

        keyboard_input(&player, end, controller);
        /* mouse aiming */
        mouse_aiming(&player, controller);
        MovePlayer(0,0);

        float move_vec[2] = {0.f, 0.f};
        if(controller->move_forw) { move_vec[0] += player.anglecos*0.2f; move_vec[1] += player.anglesin*0.2f; }
        if(controller->move_back) { move_vec[0] -= player.anglecos*0.2f; move_vec[1] -= player.anglesin*0.2f; }
        if(controller->rot_left) { move_vec[0] += player.anglesin*0.2f; move_vec[1] -= player.anglecos*0.2f; }
        if(controller->rot_right) { move_vec[0] -= player.anglesin*0.2f; move_vec[1] += player.anglecos*0.2f; }
        int pushing = controller->move_forw || controller->move_back || controller->rot_left || controller->rot_right;
        float acceleration = pushing ? 0.4 : 0.2;

        player.velocity.x = player.velocity.x * (1-acceleration) + move_vec[0] * acceleration;
        player.velocity.y = player.velocity.y * (1-acceleration) + move_vec[1] * acceleration;

        if(pushing) controller->moving = 1;

        SDL_Delay(10);
}

void init_controller(t_controller *controller) {
    controller->move_forw = false;
    controller->move_back = false;
    controller->rot_left = false;
    controller->rot_right = false;
    controller->falling = true;
    controller->ground = false;
    controller->moving = false;
    controller->ducking = false;
    controller->yaw = 0;
}

int main()
{
    t_sdl           sdl;
    t_scene         scene;
    t_controller    controller;
    bool            end;

//!
	scene.sectors = NULL;
//!
  load_data("map-clear.txt", &scene);
//	LoadData();

    int r = -1;
    while (++r < scene.n_sectors)
	{
    	int y = -1;
    	printf("sector %d:\n\tfloor = %f, ceil = %f\nvertices:\n", r, scene.sectors[r].ceil, scene.sectors[r].floor);
    	while (++y < scene.sectors[r].npoints)
    		printf("\t(%f, %f)\n", scene.sectors[r].vertex[y].x, scene.sectors[r].vertex[y].y);
	}
    printf("player:\n\t(%f, %f)\tang = %f\tsect = %d\n", scene.player.pos.x, scene.player.pos.y, scene.player.angle, scene.player.sector);
exit(1);
    end = false;
    sdl_init(&sdl);
    sdl_init_renderer(&sdl);
    scene.pixels = get_screen_pixels();

    init_controller(&controller);
    //     init_render(scene);
    //     init_contols(scene);
    //     init_textures(scene);
    SDL_SetRelativeMouseMode(SDL_TRUE);
    while (!end)
    {

        DrawScreen(&scene);
		//printf("x-x dead\n");
        SDL_UpdateTexture(sdl.texture, NULL, scene.pixels, WIDTH * sizeof(Uint32));
        SDL_RenderCopy(sdl.renderer, sdl.texture, NULL, NULL);
        SDL_RenderPresent(sdl.renderer);
        sdl_clear_texture(&(scene.pixels));
        SDL_RenderClear(sdl.renderer);

        //listen_controls()
        //apply_controls()
        shitty_controller(&controller, &end, sdl);

    }
    UnloadData();
    SDL_Quit();
    return 0;
}


// bool validate_arg(char **argv)
// {
//     if (argv)
//         return (true);
//     return (true);
// }



// int main(int argc, char **argv)
// {
//     t_sdl sdl;
//     t_scene scene;

//     if (argc != 2)
//         print_err("Usage: ./doom [mapname]");
//     if (!validate_arg(argv))
//         print_err("Wrong arg.");
//     parse_manager(&scene, argv[1]);
//     sdl_init(&sdl);
//     sdl_init_renderer(&sdl);
//     scene.pixels = get_screen_pixels();
//     run(&sdl, &scene);
//     sdl_clean(&sdl);
//     return 0;
// }
