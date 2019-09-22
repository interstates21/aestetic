
/* Define window size */
#define W 608
#define H 480
/* Define various vision related constants */
#define EyeHeight 6      // Camera height from floor when standing
#define DuckHeight 2.5   // And when crouching
#define HeadMargin 1     // How much room there is above camera before the head hits the ceiling
#define KneeHeight 2     // How tall obstacles the player can simply walk over without jumping
#define HFOV (0.73f * H) // Affects the horizontal field of vision
#define VFOV (.2f * H)   // Affects the vertical field of vision

#define min(a, b) (((a) < (b)) ? (a) : (b))               // min: Choose smaller of two scalars.
#define max(a, b) (((a) > (b)) ? (a) : (b))               // max: Choose greater of two scalars.
#define clamp(a, mi, ma) min(max(a, mi), ma)              // clamp: Clamp value into set range.
#define cross(x0, y0, x1, y1) ((x0) * (y1) - (x1) * (y0)) // cross: Vector cross product
// Overlap:  Determine whether the two number ranges overlap.
#define Overlap(a0, a1, b0, b1) (min(a0, a1) <= max(b0, b1) && min(b0, b1) <= max(a0, a1))
// IntersectBox: Determine whether two 2D-boxes intersect.
#define IntersectBox(x0, y0, x1, y1, x2, y2, x3, y3) (Overlap(x0, x1, x2, x3) && Overlap(y0, y1, y2, y3))
// PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
#define PointSide(px, py, x0, y0, x1, y1) cross((x1) - (x0), (y1) - (y0), (px) - (x0), (py) - (y0))
// Intersect: Calculate the point of intersection between two lines.
#define Intersect(x1, y1, x2, y2, x3, y3, x4, y4) ((t_v2f){                                                                                    \
    cross(cross(x1, y1, x2, y2), (x1) - (x2), cross(x3, y3, x4, y4), (x3) - (x4)) / cross((x1) - (x2), (y1) - (y2), (x3) - (x4), (y3) - (y4)), \
    cross(cross(x1, y1, x2, y2), (y1) - (y2), cross(x3, y3, x4, y4), (y3) - (y4)) / cross((x1) - (x2), (y1) - (y2), (x3) - (x4), (y3) - (y4))})
