#ifndef EasyTable_h
#define EasyTable_h

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
class EasyTable
{
  private:
    Adafruit_SSD1306 *display;
    int displayWidth;
    int displayHeight;
    int ORIGIN_X;
    int ORIGIN_Y;
    
  public:
    EasyTable(Adafruit_SSD1306 *displayPointer, int width, int height);
    EasyTable(Adafruit_SSD1306 *displayPointer, int canvasWidth, int canvasHeight, int xOrigin, int yOrigin);
    boolean EasyTable::drawTable(byte rows, byte colums, char* labels[]);
    boolean drawTable(byte rows, byte colums, char* labels[], int selRow, int selCol);
    boolean drawGrill(byte rows, byte colums);
    boolean drawMenu(char *items[], byte numItems, int selectItem);
    boolean drawParameterTable(byte numItems, char* itemLabels[], double* itemValues[], int selectItem);
    
};

#endif
