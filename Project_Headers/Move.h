#ifndef COMPUTE_H_
#define COMPUTE_H_

#include <math.h>

#define CANVAS_WIDTH        400 // MM
#define CANVAS_HEIGHT       400 // MM

#define M_PI                3.14159265358979323846
#define LENGTH_PER_STEP     (0.085) // MM per step
#define INTERP_STEP         1.0

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
