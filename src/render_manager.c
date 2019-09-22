#include "alt.h"

// #define NEAR_Z 1e-4f
// #define NEAR_X 1e-5f
// #define FAR_Z 5
// #define FAR_X 20.f

// #define START 0
// #define END WIDTH - 1
// #define YAW(y, z) (y + z * 1) // player->yaw

// #define MAX_QUEUE 32

// void handleHiddenWall(t_vt *p1, t_vt *p2)
// {
//     t_v2f i1;
//     t_v2f i2;

//     i1 = Intersect(p1->x, p1->z, p2->x, p2->z, -NEAR_X, NEAR_Z, -FAR_Z, FAR_Z);
//     i2 = Intersect(p1->x, p1->z, p2->x, p2->z, NEAR_X, NEAR_Z, FAR_Z, FAR_Z);

//     if (p1->z < NEAR_Z)
//     {
//         if (i1.y > 0)
//         {
//             p1->x = i1.x;
//             p1->z = i1.y;
//         }
//         else
//         {
//             p1->x = i2.x;
//             p1->z = i2.y;
//         }
//     }
//     if (p2->z < NEAR_Z)
//     {
//         if (i1.y > 0)
//         {
//             p2->x = i1.x;
//             p2->z = i1.y;
//         }
//         else
//         {
//             p2->x = i2.x;
//             p2->z = i2.y;
//         }
//     }
// }

// void transformPerspective(t_vt *p1, t_vt *p2, t_cam *cam)
// {
//     cam->camSpace1.x = cam->hfov / p1.z;
//     cam->camSpace1.y = cam->vfov / p1.z;

//     cam->camSpace2.x = cam->hfov / p2.z;
//     cam->camSpace2.y = cam->vfov / p2.z;

//     p1->x = WIDTH / 2 - -(int)(p1->x * cam->camSpace1.x);
//     p2->x = WIDTH / 2 - (int)(p2->x * cam->camSpace2.x);
// }

// void translatePairVertices(t_vt *p1, t_vt *p2, const t_player player)
// {
//     p1->x = p1->x - player.pos.x;
//     p1->z = p1->y - player.pos.y;
//     p1->y = 0;

//     p2->x = p2->x - player.pos.x;
//     p2->z = p2->y - player.pos.y;
//     p2->y = 0;
// }

// void rotatePairVerices(t_vt *p1, t_vt *p2, const t_player player)
// {
//     const t_vt temp1 = *p1;
//     const t_vt temp2 = *p2;

//     //Y rotation matrix
//     p1->x = temp1.x * player.anglesin - temp1.z * player.anglecos;
//     p1->z = temp1.x * player.anglecos + temp1.z * player.anglesin;

//     p2->x = temp2.x * player.anglesin - temp2.z * player.anglecos;
//     p2->z = temp2.x * player.anglecos + temp2.z * player.anglesin;
// }

// void projectFloor(double *floor, double *portalFloor, int portalIndex, const t_scene *scene)
// {
//     t_vt playerPos;

//     playerPos = scene->player.pos;
//     *floor = *floor - playerPos.z;
//     *portalFloor = portalIndex >= 0 ? scene->sectors[portalIndex].floor - playerPos.z : 0;
// }

// void projectCeil(double *ceil, double *portalCeil, int portalIndex, const t_scene *scene)
// {
//     t_vt playerPos;

//     playerPos = scene->player.pos;
//     *ceil = *ceil - playerPos.z;
//     *portalCeil = portalIndex >= 0 ? scene->sectors[portalIndex].ceil - playerPos.z : 0;
// }

// void renderFloorCeil(t_vt p1, t_vt p2, int currentIndex, t_scene *scene)
// {
//     const t_sector currentSector = scene->sectors[currentIndex];
//     double floor;
//     double ceil;

//     double portalFloor;
//     double portalCeil;

//     t_range screen1Y;
//     t_range screen2Y;
//     t_range screen1PY;
//     t_range screen2PY;

//     floor = currentSector.floor;
//     ceil = currentSector.ceil;
//     portalFloor = 0;
//     portalCeil = 0;

//     projectFloor(&(floor), &(portalFloor), currentIndex, scene);
//     projectCeil(&(ceil), &(portalCeil), currentIndex, scene);

//     screen1Y.min = HEIGHT / 2 - (int)(YAW(ceil, p1.z) * camSpace1.y),
//     screen1Y.max = HEIGHT / 2 - (int)(YAW(floor, p1.z) * camSpace1.y),
//     screen2Y.min = HEIGHT / 2 - (int)(YAW(ceil, p2.z) * camSpace2.y),
//     screen2Y.max = HEIGHT / 2 - (int)(YAW(floor, p2.z) * camSpace2.y),

//     screen1PY.min = HEIGHT / 2 - (int)(YAW(ceil, p1.z) * camSpace1.y),
//     screen1PY.max = HEIGHT / 2 - (int)(YAW(floor, p1.z) * camSpace1.y),
//     screen2PY.min = HEIGHT / 2 - (int)(YAW(ceil, p2.z) * camSpace2.y),
//     screen2PY.max = HEIGHT / 2 - (int)(YAW(floor, p2.z) * camSpace2.y),
// }

// void renderSector(t_scene *scene, const t_sector currentSector)
// {
//     int i;
//     t_vt p1;
//     t_vt p2;

//     i = 0;
//     while (i < currentSector.npoints - 1)
//     {
//         p1 = currentSector.walls[i];
//         p2 = currentSector.walls[i + 1];
//         translatePairVertices(&(p1), &(p2), scene->player);
//         rotatePairVerices(&(p1), &(p2), scene->player);

//         if (p1.z <= 0 && p2.z <= 0)
//             continue;
//         if (p1.z <= 0 || p2.z <= 0)
//             handleHiddenWall(&(p1), &(p2));

//         transformPerspective(&(p1), &(p2), scene->cam);
//         if (p1.x >= p2.x || p2.x < START || p1.x > END)
//             continue;

//         renderFloorCeil(currentSector);

//         i++;
//     }
// }

// // renderLine() {
// // for (int x = beginx; x <= endx; ++x)
// // {
// //     /* Calculate the Z coordinate for this point. (Only used for lighting.) */
// //     int z = ((x - x1) * (tz2 - tz1) / (x2 - x1) + tz1) * 8;
// //     /* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
// //     int ya = (x - x1) * (y2a - y1a) / (x2 - x1) + y1a, cya = clamp(ya, ytop[x], ybottom[x]); // top
// //     int yb = (x - x1) * (y2b - y1b) / (x2 - x1) + y1b, cyb = clamp(yb, ytop[x], ybottom[x]); // bottom

// //     /* Render ceiling: everything above this sector's ceiling height. */
// //     vline(scene, x, ytop[x], cya - 1, 0x111111, 0x222222, 0x111111);
// //     /* Render floor: everything below this sector's floor height. */
// //     vline(scene, x, cyb + 1, ybottom[x], 0x0000FF, 0x0000AA, 0x0000FF);

// //     /* Is there another sector behind this edge? */
// //     if (neighbor >= 0)
// //     {
// //         /* Same for _their_ floor and ceiling */
// //         int nya = (x - x1) * (ny2a - ny1a) / (x2 - x1) + ny1a, cnya = clamp(nya, ytop[x], ybottom[x]);
// //         int nyb = (x - x1) * (ny2b - ny1b) / (x2 - x1) + ny1b, cnyb = clamp(nyb, ytop[x], ybottom[x]);
// //         /* If our ceiling is higher than their ceiling, render upper wall */
// //         unsigned r1 = 0x010101 * (255 - z), r2 = 0x040007 * (31 - z / 8);
// //         vline(scene, x, cya, cnya - 1, 0, x == x1 || x == x2 ? 0 : r1, 0); // Between our and their ceiling
// //         ytop[x] = clamp(max(cya, cnya), ytop[x], HEIGHT - 1);              // Shrink the remaining window below these ceilings
// //         /* If our floor is lower than their floor, render bottom wall */
// //         vline(scene, x, cnyb + 1, cyb, 0, x == x1 || x == x2 ? 0 : r2, 0); // Between their and our floor
// //         ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]);                 // Shrink the remaining window above these floors
// //     }
// //     else
// //     {
// //         /* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
// //         unsigned r = 0x010101 * (255 - z);
// //         vline(scene, x, cya, cyb, 0, x == x1 || x == x2 ? 0 : r, 0);
// //     }
// // }
// // }

// void render(t_scene *scene)
// {
//     // draw_test_square(scene);
//     int yBottom[WIDTH];
//     int yTop[WIDTH] = {0};
//     int renderSectors[WIDTH];
//     int i;

//     t_queue queue[MAX_QUEUE];
//     t_queue *tail = queue;
//     t_queue *head = queue;

//     int renderSectors[scene->n_sectors];

//     for (unsigned x = 0; x < WIDTH; ++x)
//         yBottom[x] = HEIGHT - 1;
//     for (int n = 0; n < scene->n_sectors; ++n)
//         renderSectors[n] = 0;

//     t_queue b =
//     {
//         scene->player.sector, 0, WIDTH - 1
//     };

//     *head = b;

//     if (++head == queue + MAX_QUEUE)
//         head = queue;

//     i = 0;

//     // t_sector currentSector = scene->sectors[scene->player.sector];
//     do
//     {
//         t_queue this = *tail;
//         if (++tail == queue + MAX_QUEUE)
//             tail = queue;

//         if (renderSectors[this.nSector] & 0x21)
//             continue;
//         ++renderSectors[this.nSector];

//         const t_sector current = scene->sectors[this.nSector];

//         renderSector(scene, current);
//     } while (head != tail);
// }

void render(t_scene *scene)
{
    // paint_screen(scene);
    DrawScreen(scene);
}