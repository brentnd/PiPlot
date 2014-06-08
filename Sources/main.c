#include "Config.h"

#define MOVE_DIST 100

void terminal()
{
  char c = 48;
  for(;;)
  {
    LINEFEED;
    UART_putchar('>');
    while(UART_getchar_present() == 0);
    c = UART_getchar();
    
    switch(c)
    {
    case 'w':
      PRINTLN("Moving UP");
      MoveY(-MOVE_DIST);
      break;
    case 's':
      PRINTLN("Moving DOWN");
      MoveY(MOVE_DIST);
      break;
    case 'a':
      PRINTLN("Moving LEFT");
      MoveX(-MOVE_DIST);
      break;
    case 'd':
      PRINTLN("Moving RIGHT");
      MoveX(MOVE_DIST);
      break;
    case 'h':
      PRINTLN("Going Home...");
      MoveHome();
      break;
    case 'z':
      PRINTLN("Zeroed at current position.");
      MoveSetZero();
      break;
    }
  }
  
}

/*
 * Future main method for Pythagorian Plotter
 */
int main(void)
{
  ConfigInitialize();
  printf("Pythagorian Plotter v1.0\n\n");
  printf("Initialized...\n");
  ConfigStart();
  printf("Started...\n");
  MoveSetZero();
  printf("Zeroed...\n");
  
  // Start terminal loop
  terminal();
  
  return 0;
}
