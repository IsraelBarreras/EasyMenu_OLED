#include "Arduino.h"
#include "EasyMenu.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

EasyMenu::EasyMenu(Adafruit_SSD1306 *displayPointer, int width, int height)
{
  display = displayPointer;
  displayWidth = width;
  displayHeight = height;
  ORIGIN_X = 0;
  ORIGIN_Y = 0;
}

EasyMenu::EasyMenu(Adafruit_SSD1306 *displayPointer, int canvasWidth, int canvasHeight, int xOrigin, int yOrigin)
{
  display = displayPointer;
  displayWidth = canvasWidth;
  displayHeight = canvasHeight;
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
  int rowSpace = displayHeight/rows;
  int columSpace = displayWidth/colums;


  this->drawGrill(rows, colums);

  for(actualColum = 0; actualColum < colums; actualColum++)
  {
    
    for(actualRow = 0; actualRow < rows; actualRow++)
    {
      if(selCol == actualColum && selRow == actualRow)
      {
            display->fillRect(ORIGIN_X + (columSpace * actualColum), ORIGIN_Y + (rowSpace * actualRow), columSpace, rowSpace,1);
            display->setTextColor(0);
      }
      display->setCursor(ORIGIN_X + 2 + (columSpace * actualColum), ORIGIN_Y + 2 + (rowSpace * actualRow));
      display->print(labels[actualRow*colums + actualColum]);
      display->setTextColor(1);
    }
    
  }

  display->display();

  return true;
}   

boolean EasyMenu::drawGrill(byte rows, byte colums)
{
  byte actualColum = 0;
  byte actualRow = 0;
  int rowSpace = displayHeight/rows;
  int columSpace = displayWidth/colums;

  /*display->drawLine(0, 0, displayWidth, 0, 1);
  display->drawLine(0, 0, 0, displayHeight, 1);

  display->drawLine(0, displayHeight - 1, displayWidth, displayHeight - 1, 1);
  display->drawLine(displayWidth - 1, 0, displayWidth - 1, displayHeight, 1);*/

  for(actualColum = 0; actualColum <= colums; actualColum++)
  {
    display->drawLine(ORIGIN_X + (columSpace * actualColum), ORIGIN_Y, ORIGIN_X + (columSpace * actualColum), ORIGIN_Y + displayHeight, 1);
  }

  for(actualRow = 0; actualRow <= rows; actualRow++)
  {
     display->drawLine(ORIGIN_X, ORIGIN_Y + (rowSpace * (actualRow)), ORIGIN_X + displayWidth, ORIGIN_Y + (rowSpace * actualRow), 1);
  }

  display->display();

  return true;
} 

boolean EasyMenu::drawMenu(char *items[], byte numItems, int selectItem)
{
  int rowSpace = displayHeight/numItems;

  this->drawGrill(numItems, 1);

  for(int actualItem = 0; actualItem < numItems; actualItem++)
  {
    if(actualItem == selectItem)
    {
      display->fillRect(ORIGIN_X, ORIGIN_Y + (rowSpace * actualItem), displayWidth, rowSpace,1);
      display->setTextColor(0);  
    }

    display->setCursor(ORIGIN_X + 10, ORIGIN_Y + 5 + (rowSpace * actualItem));
    display->print(items[actualItem]);
    display->setTextColor(WHITE);
  }

  display->display();

  return true;
}

boolean EasyMenu::drawParameterTable(byte numItems, char* itemLabels[], double* itemValues[], int selectItem)
{
  int rowSpace = displayHeight/numItems;

  this->drawGrill(numItems, 2);

  for(int actualItem = 0; actualItem < numItems; actualItem++)
  {
    display->setCursor(ORIGIN_X + 2 , ORIGIN_Y + 2 + (rowSpace * actualItem));
    display->print(itemLabels[actualItem]);

    if(actualItem == selectItem)
    {
      display->fillRect(ORIGIN_X + displayWidth/2, ORIGIN_Y + (rowSpace * actualItem), ORIGIN_X + displayWidth, ORIGIN_Y + rowSpace, 1);
      display->setTextColor(0);  
    }

    display->setCursor(ORIGIN_X + displayWidth/2 + 2, ORIGIN_Y + 2 + rowSpace * actualItem);
    display->print(*itemValues[actualItem]);
    display->setTextColor(WHITE);
  }

  display->display();

  return true;

}
