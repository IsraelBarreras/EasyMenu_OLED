#ifndef EasyMenu_h
#define EasyMenu_h

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
 
class EasyMenu
{
  private:
    Adafruit_SH1106 *disp;
    int dispWidth;
    int dispHeight;
    int ORIGIN_X;
    int ORIGIN_Y;
    
  public:
    EasyMenu(Adafruit_SH1106 *dispPointer, int width, int height);
    EasyMenu(Adafruit_SH1106 *dispPointer, int canvasWidth, int canvasHeight, int xOrigin, int yOrigin);
    boolean drawTable(byte rows, byte colums, char* labels[]);
    boolean drawTable(byte rows, byte colums, char* labels[], int selRow, int selCol);
    boolean drawGrill(byte rows, byte colums);
    boolean drawMenu(const char *items[], byte numItems, int selectItem);
    boolean drawParameterTable(byte numItems, char* itemLabels[], double* itemValues[], int selectItem);
    void    clearDisplay(void);
    void    display(void);
    
};

#endif
