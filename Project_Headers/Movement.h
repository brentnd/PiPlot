#ifndef COMPUTE_H_
#define COMPUTE_H_

#include <math.h>

#define CANVAS_WIDTH   4000 // MM
#define CANVAS_HEIGHT  4000 // MM
#define MOTOR_RADIUS   3 // MM

#define HOME_POS       (uint32_t)(0.7071*CANVAS_WIDTH)

void MovementGoto(uint32_t x, uint32_t y);

#endif /* COMPUTE_H_ */
