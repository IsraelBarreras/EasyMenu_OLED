#include "EasyMenu.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH    128 // OLED display ancho en pixeles
#define SCREEN_HEIGHT   64 // OLED display alto en pixeles
#define OLED_RESET      4 // Reset pin # (or -1 if sharing Arduino reset pin)

#define IZQUIERDA   A3
#define DERECHA     A0 
#define ARRIBA      A1
#define ABAJO       A2
#define ACEPTAR     2
#define CANCELAR    3
#define NUM_BOTONES 6

/*Configuración de menus */
#define PRINCIPAL_ITEMS 3
#define OPTIONS_ITEMS   4
#define CONFIG_ITEMS    5
#define LECTURAS_ITEMS  3
#define DISPLAY_REFRESH_TIME    100u

/*funciones estáticas*/
static void menuPrincipal(void);
static void menuOpciones(void);
static void menuConfig(void);
static void menuLecturas(void);

static int isPressAnyButton(void);
static void botonera(byte itemsNum);

/*Variables glovales */
uint16_t displayPontiers[4] = {&menuPrincipal, &menuOpciones, &menuConfig, menuLecturas};
byte displaySelec = 0;
int  selItem = -1;
unsigned long lastRefresh = 0;

/*Variables a monitorear */
double temperatura = 25.32;
double humedad = 89.50;
double rpm = 4500;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

EasyMenu Menu(&display, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

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
    pinMode(ARRIBA, INPUT);
    pinMode(ABAJO, INPUT);
    pinMode(IZQUIERDA, INPUT);
    pinMode(DERECHA, INPUT);
    pinMode(ACEPTAR, INPUT);

}

int cont = 0;
void loop() 
{
    Menu.clearDisplay();
    //display.setCursor(0,0);
   // Menu.drawGrill(2,++cont);
    
    void (*current_display)(void) = displayPontiers[displaySelec];
    (*current_display)();

    Menu.display();
}



/*FUNCIONES PARA CADA MENU */
static void menuPrincipal(void)
{
    char* items[PRINCIPAL_ITEMS] = {"    OPCIONES", "  CONFIGURACION", "    LECTURAS"};
    
    Menu.drawMenu(items, PRINCIPAL_ITEMS, selItem); /*Dibujamos el menu con los items declarados*/
    
    botonera(PRINCIPAL_ITEMS);
}

static void menuOpciones(void)
{
    char* items[OPTIONS_ITEMS] = {"Opcion 1", "Opcion 2", "Opcion 3", "Opcion 4"};
    
    Menu.drawMenu(items, OPTIONS_ITEMS, selItem); /*Dibujamos el menu con los items declarados*/

    botonera(OPTIONS_ITEMS);
}

/*FAKE PARÁMETROS */
double  maxTemp = 30.5;
double  minTemp = 15;
double  maxHum  = 99;
double  minHum  = 50;
double  lecTime = 5000;

static void menuConfig(void)
{ 
    char* item_labels[CONFIG_ITEMS] = {"MaxTemp: C", "MinTemp: C", "Max Hum: %", "Min Hum: %", "Time:   ms"};
    double* item_values[CONFIG_ITEMS] = {&maxTemp, &minTemp, &maxHum, &minHum, &lecTime};
    
    Menu.drawParameterTable(CONFIG_ITEMS, item_labels, item_values, selItem); /*Dibujamos el menu con los items declarados*/

    botonera(CONFIG_ITEMS);
}


static void menuLecturas(void)
{
    char* item_labels[LECTURAS_ITEMS] = {"TEMP:", "HUM:", "RPM:"};
    double* item_values[LECTURAS_ITEMS] = {&temperatura, &humedad, &rpm};
    
    display.setTextSize(2); 
    Menu.drawParameterTable(LECTURAS_ITEMS, item_labels, item_values, selItem); /*Dibujamos el menu con los items declarados*/

    botonera(LECTURAS_ITEMS);

    /*   SIMULACIÓN  LECTURAS RANDOM       */
    if(millis() % 5000 < 100)
    {
        temperatura = random(2000, 3000) / 100;
        humedad = random(5000, 9900) / 100;
        rpm =  random(2000, 5000);
    }
}

static void botonera(byte itemsNum)
{
    /*LOGICA PARA BOTONERA*/
    if(millis() - lastRefresh >= DISPLAY_REFRESH_TIME)
    {
        if(int pressButon = isPressAnyButton())
        {
            switch(pressButon)
            {
                case ARRIBA:
                            selItem = (selItem > 0) ? selItem - 1 : itemsNum - 1;
                            break;

                case ABAJO:
                            selItem = (selItem < itemsNum - 1) ? selItem + 1 : 0;
                            break;

                case ACEPTAR:
                            if(displaySelec == 0)
                            {
                                displaySelec = selItem + 1;
                                selItem = 0;
                            }
                            break;

                case CANCELAR:
                            display.setTextSize(1.5); 
                            displaySelec = 0;
                            selItem = 0;
                            break;

                case IZQUIERDA:
                case DERECHA:
                            break;
            }

        }

        lastRefresh = millis();
    }
    /*END BOTONERA*/
}

static int isPressAnyButton(void)
{
     int botones[NUM_BOTONES] = {ARRIBA, ABAJO, DERECHA, IZQUIERDA, ACEPTAR, CANCELAR};
    
    for(int i = 0; i < NUM_BOTONES; i++)
    {
        if(digitalRead(botones[i]))
            return botones[i];
    }

    return 0;
}