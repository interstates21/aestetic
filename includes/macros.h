#ifndef MACROS_H
#define MACROS_H

#define MAX(a, b) ((a < b) ? b : a)
#define MIN(a, b) ((a > b) ? b : a)
#define CLAMP(x, a, b) (((x) > (b)) ? (b) : (((x) < (a)) ? (a) : (x)))
#endif // !MACROS_H