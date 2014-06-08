#ifndef COMPUTE_H_
#define COMPUTE_H_

#include <math.h>

#define CANVAS_WIDTH   4000 // MM
#define CANVAS_HEIGHT  4000 // MM
#define MOTOR_RADIUS   3 // MM

#define HOME_POS       (uint32_t)(0.7071*CANVAS_WIDTH)

/* Public prototypes */
void MoveInit();
void MoveSetZero();
void MoveToAbsolute(uint32_t x, uint32_t y);
void MoveToRelative(uint32_t x_delta, uint32_t y_delta);
void MoveX(int32_t delta);
void MoveY(int32_t delta);
void MoveHome();
void MoveSetZero();

void DrawCircle(int radius);

#endif /* COMPUTE_H_ */
