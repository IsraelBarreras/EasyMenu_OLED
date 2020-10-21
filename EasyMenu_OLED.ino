#include "EasyMenu.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // OLED display ancho en pixeles
#define SCREEN_HEIGHT 64 // OLED display alto en pixeles
#define IZQUIERDA A3
#define DERECHA A0 
#define ARRIBA A1
#define ABAJO A2
#define ACEPTAR 2
#define CANCELAR 3

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



void setup() 
{
  Serial.begin(9600); //Inicializamos el puerto serie
  Wire.begin(); //Inicializacmos la comunicación I2C
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Inicializamos el display con ndirección 0x3C
    Serial.println(F("SSD1306 NO SE PUDO ENCONTRAR"));
    for(;;); // Loop infinito
  }
  
    display.clearDisplay();
    display.display();
    display.clearDisplay();
    display.setTextSize(1.5); 
    display.setTextColor(WHITE);        
    display.setCursor(0,0);
    display.clearDisplay();
    pinMode(ARRIBA, INPUT);
    pinMode(ABAJO, INPUT);
    pinMode(IZQUIERDA, INPUT);
    pinMode(DERECHA, INPUT);
    pinMode(ACEPTAR, INPUT);

}



void loop() 
{

}