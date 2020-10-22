#include "Arduino.h"
#include "EasyMenu.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

EasyMenu::EasyMenu(Adafruit_SSD1306 *dispPointer, int width, int height)
{
  disp = dispPointer;
  dispWidth = width;
  dispHeight = height;
  ORIGIN_X = 0;
  ORIGIN_Y = 0;
}

EasyMenu::EasyMenu(Adafruit_SSD1306 *dispPointer, int canvasWidth, int canvasHeight, int xOrigin, int yOrigin)
{
  disp = dispPointer;
  dispWidth = canvasWidth;
  dispHeight = canvasHeight;
  ORIGIN_X = xOrigin;
  ORIGIN_Y = yOrigin;
}

boolean EasyMenu::drawTable(byte rows, byte colums, char* labels[])
{
    this->drawTable(rows, colums, labels, -1, -1);
}

boolean EasyMenu::drawTable(byte rows, byte colums, char* labels[], int selRow, int selCol)
{
  byte actualColum = 0;
  byte actualRow = 0;
  int rowSpace = dispHeight/rows;
  int columSpace = dispWidth/colums;


  this->drawGrill(rows, colums);

  for(actualColum = 0; actualColum < colums; actualColum++)
  {
    
    for(actualRow = 0; actualRow < rows; actualRow++)
    {
      if(selCol == actualColum && selRow == actualRow)
      {
            disp->fillRect(ORIGIN_X + (columSpace * actualColum), ORIGIN_Y + (rowSpace * actualRow), columSpace, rowSpace,1);
            disp->setTextColor(0);
      }
      disp->setCursor(ORIGIN_X + 2 + (columSpace * actualColum), ORIGIN_Y + 2 + (rowSpace * actualRow));
      disp->print(labels[actualRow*colums + actualColum]);
      disp->setTextColor(1);
    }
    
  }

  return true;
}   

boolean EasyMenu::drawGrill(byte rows, byte colums)
{
  byte actualColum = 0;
  byte actualRow = 0;
  int rowSpace = dispHeight/rows;
  int columSpace = dispWidth/colums;

  /*disp->drawLine(0, 0, dispWidth, 0, 1);
  disp->drawLine(0, 0, 0, dispHeight, 1);

  disp->drawLine(0, dispHeight - 1, dispWidth, dispHeight - 1, 1);
  disp->drawLine(dispWidth - 1, 0, dispWidth - 1, dispHeight, 1);*/

  for(actualColum = 0; actualColum <= colums; actualColum++)
  {
    disp->drawLine(ORIGIN_X + (columSpace * actualColum), ORIGIN_Y, ORIGIN_X + (columSpace * actualColum), ORIGIN_Y + dispHeight, 1);
  }

  for(actualRow = 0; actualRow <= rows; actualRow++)
  {
     disp->drawLine(ORIGIN_X, ORIGIN_Y + (rowSpace * (actualRow)), ORIGIN_X + dispWidth, ORIGIN_Y + (rowSpace * actualRow), 1);
  }

  return true;
} 

boolean EasyMenu::drawMenu(char *items[], byte numItems, int selectItem)
{
  int rowSpace = dispHeight/numItems;

  this->drawGrill(numItems, 1);

  for(int actualItem = 0; actualItem < numItems; actualItem++)
  {
    if(actualItem == selectItem)
    {
      disp->fillRect(ORIGIN_X, ORIGIN_Y + (rowSpace * actualItem), dispWidth, rowSpace,1);
      disp->setTextColor(0);  
    }

    disp->setCursor(ORIGIN_X + 10, ORIGIN_Y + 5 + (rowSpace * actualItem));
    disp->print(items[actualItem]);
    disp->setTextColor(WHITE);
  }

  return true;
}

boolean EasyMenu::drawParameterTable(byte numItems, char* itemLabels[], double* itemValues[], int selectItem)
{
  int rowSpace = dispHeight/numItems;

  this->drawGrill(numItems, 2);

  for(int actualItem = 0; actualItem < numItems; actualItem++)
  {
    disp->setCursor(ORIGIN_X + 2 , ORIGIN_Y + 2 + (rowSpace * actualItem));
    disp->print(itemLabels[actualItem]);

    if(actualItem == selectItem)
    {
      disp->fillRect(ORIGIN_X + dispWidth/2, ORIGIN_Y + (rowSpace * actualItem), ORIGIN_X + dispWidth, ORIGIN_Y + rowSpace, 1);
      disp->setTextColor(0);  
    }

    disp->setCursor(ORIGIN_X + dispWidth/2 + 2, ORIGIN_Y + 2 + rowSpace * actualItem);
    disp->print(*itemValues[actualItem]);
    disp->setTextColor(WHITE);
  }

  return true;

}


void EasyMenu::clearDisplay(void)
{
    disp->clearDisplay();
}

void EasyMenu::display(void)
{
    disp->display();
}