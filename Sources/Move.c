#include "Config.h"


/* Local variables */
int x_pos,y_pos;

/* Private method prototypes */
void GotoXY(double x, double y);
void SetLengths(double l0, double l1);

/* Public implementations */
void MoveInit()
{
  x_pos = (CANVAS_WIDTH/2);
  y_pos = (CANVAS_WIDTH/2);
}

void MoveHome()
{
  MoveToAbsolute((CANVAS_WIDTH/2),(CANVAS_WIDTH/2));
}

void MoveSetZero()
{
  StepperSetZero(p_Motor0);
  StepperSetZero(p_Motor1);
  MoveInit();
}

void MoveToAbsolute(uint32_t x, uint32_t y)
{
  double i,distance;
  
  double x_int, y_int;
  uint32_t x_old, y_old;
  
  x_old = x_pos; y_old = y_pos;
  
  distance = sqrt((x-x_pos)*(x-x_pos) + (y-y_pos)*(y-y_pos));
  for(i=0.0; i<distance; i+=INTERP_STEP)
  {
    x_int = x_old + (i/distance) * (int)(x-x_old);
    y_int = y_old + (i/distance) * (int)(y-y_old);
    GotoXY(x_int, y_int);
  }
}

void DrawCircle(int radius)
{
  int x,y;
  uint32_t r2 = radius * radius;
  
  uint32_t x_cen, y_cen;
  x_cen = x_pos;
  y_cen = y_pos;
  
  // Bottom half
  for(x=-radius; x<radius; x++)
  {
    y = (int) (sqrt(r2 - x*x) + 0.5);
    GotoXY(x_cen + x, y_cen + y);
  }
  // Top half
  for(x=-radius; x<radius; x++)
  {
    y = (int) (sqrt(r2 - x*x) + 0.5);
    GotoXY(x_cen - x, y_cen - y);
  }
  GotoXY(x_cen, y_cen);
}

void MoveToRelative(uint32_t x_delta, uint32_t y_delta)
{
  MoveToAbsolute(x_pos+x_delta, y_pos+y_delta);
}

void MoveX(int32_t delta)
{
  MoveToAbsolute(x_pos+delta, y_pos);
}
void MoveY(int32_t delta)
{
  MoveToAbsolute(x_pos, y_pos + delta);
}

void GotoXY(double x, double y)
{
  double l0, l1;
  // Translate X, Y coords into lengths 
  // for each stepper motor.
  l0 = (double) (sqrt(x*x + y*y));
  l1 = (double) (sqrt(y*y + (CANVAS_WIDTH-x)*(CANVAS_WIDTH-x)));
  
  // Update stepper motors to those lengths
  SetLengths(l0, l1);
 
  while(StepperMoving());
  x_pos = x;
  y_pos = y;
}

void SetLengths(double l0, double l1)
{
  uint32_t steps0, steps1;
  
  steps0 = (uint32_t) (l0 / LENGTH_PER_STEP);
  steps1 = (uint32_t) (l1 / LENGTH_PER_STEP);
  
  StepperSetPosition(p_Motor0, steps0);
  StepperSetPosition(p_Motor1, steps1);
}
