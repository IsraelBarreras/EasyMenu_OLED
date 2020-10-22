#include "EasyMenu.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH    128 // OLED display ancho en pixeles
#define SCREEN_HEIGHT   64 // OLED display alto en pixeles
#define OLED_RESET      4 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

EasyMenu Menu(&display, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1); //Canvas con origen en X = 0 y Y = 0
EasyMenu canvas1(&display, 48, 64, 0, 0);
EasyMenu canvas2(&display, 80, 50, 48, 7);
/*          |       |       |   |   |  |--------> Cordenada de origen en Y del canvas
            |       |       |   |   |-----------> Cordenada de origen en X del canvas
            |       |       |   |---------------> Alto del canvas del canvas
            |       |       |-------------------> Ancho del canvas del canvas
            |       |---------------------------> Apuntador al display
            |-----------------------------------> ID del canvas
*/

void setup() 
{
  Serial.begin(9600); //Inicializamos el puerto serie
  Wire.begin(); //Inicializacmos la comunicación I2C
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Inicializamos el display con ndirección 0x3C
    Serial.println(F("SSD1306 NO SE PUDO ENCONTRAR"));
    for(;;); // Loop infinito
  }
  
    
    display.setTextSize(1.5); 
    display.setTextColor(WHITE);        
    display.setCursor(0,0);
    display.clearDisplay();

}


void loop() 
{
    display.setTextSize(1.5); 

    /*dibujar un Menú con 4 opciones */
    char* muenuOpciones[4] = {"   CONFIGURACION", "     OPCIONES", "     AVANZADO", "      SALIR"};
    
    for(int opcionIndex = 0; opcionIndex < 4; opcionIndex++)
    {
        Menu.clearDisplay();
        Menu.drawMenu(muenuOpciones, 4, opcionIndex); //Tabla de 4x4 con contenido que ocupara todo el largo y ancho del display o canvas
        Menu.display();
        delay(500);
    }

    /**************************************************************************************************** */
    /*Dibujar un grill o tabla vacía */
    for(int i = 1; i < 20; i++)
    {
        Menu.clearDisplay();
        Menu.drawGrill(i,i); //Tabla de ixi que ocupara todo el largo y ancho del display o canvas
        Menu.display();
        delay(100);
    }
    

    /******************************************************************************************/

    /*Dibular una tabla que contenga texto*/
    char* textos[16] = {
        "A0", "B0", "C0", "D0",
        "A1", "B1", "C1", "D1",
        "A2", "B2", "C2", "D2",
        "A3", "B3", "C3", "D3"
    };

    Menu.clearDisplay();

    Menu.drawTable(4, 4, textos); //Tabla de 4x4 con contenido que ocupara todo el largo y ancho del display o canvas

    Menu.display();

    delay(200);

    /*Seleccionar una celda */
    Menu.clearDisplay();

    Menu.drawTable(4, 4, textos, 1, 3); //Tabla de 4x4 con contenido seleccionado la fila 1 y columna 3

    Menu.display();

    delay(2000);

    /**********************************************************************************************************/

    /*TABLA DE PARAMETROS */
    double temperatura = 30.05;
    double humedad = 66;
    double rpm = 2500;
    char* item_labels[3] = {"TEMP:", "HUM:", "RPM:"};
    double* item_values[3] = {&temperatura, &humedad, &rpm};
    
    Menu.clearDisplay();
    display.setTextSize(2); 
    Menu.drawParameterTable(3, item_labels, item_values, 0); //Tabla con parámetros
    Menu.display();
    delay(3000);

    /********************************************************************************/

    /*Uso de canvas*/
    /*Se puede dividir la pantalla en diferentes secciones declarando varios objetos
    de dimensiones diferentes y con diferentes puntos de origen */
    char* items_canvas1[3] = {"M1", "M2", "M3"};
    char* items_canvas2[2] = {"ON", "OFF"};

    Menu.clearDisplay();
    canvas1.drawMenu(items_canvas1, 3, 0);             //Dibujar en canvas 1
    canvas2.drawTable(1, 2, items_canvas2, 0, 1);      //Dibujar en canvas 2
    Menu.display();
    delay(1000);

    Menu.clearDisplay();
    canvas1.drawMenu(items_canvas1, 3, 0); 
    canvas2.drawTable(1, 2, items_canvas2, 0, 0); //Cambiar seleccion
    Menu.display();

    delay(5000);

}

