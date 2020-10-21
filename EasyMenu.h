#ifndef EasyMenu_h
#define EasyMenu_h

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
class EasyMenu
{
  private:
    Adafruit_SSD1306 *display;
    int displayWidth;
    int displayHeight;
    int ORIGIN_X;
    int ORIGIN_Y;
    
  public:
    EasyMenu(Adafruit_SSD1306 *displayPointer, int width, int height);
    EasyMenu(Adafruit_SSD1306 *displayPointer, int canvasWidth, int canvasHeight, int xOrigin, int yOrigin);
    boolean EasyMenu::drawTable(byte rows, byte colums, char* labels[]);
    boolean drawTable(byte rows, byte colums, char* labels[], int selRow, int selCol);
    boolean drawGrill(byte rows, byte colums);
    boolean drawMenu(char *items[], byte numItems, int selectItem);
    boolean drawParameterTable(byte numItems, char* itemLabels[], double* itemValues[], int selectItem);
    
};

#endif
