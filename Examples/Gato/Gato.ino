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

EasyMenu canvas1(&display, 127, 20, 0, 0);
EasyMenu canvas2(&display, 100, 40, 13, 20);

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
    display.print(F("Ingeniate..."));
    display.display();
    delay(2000);
    display.clearDisplay();
    pinMode(ARRIBA, INPUT);
    pinMode(ABAJO, INPUT);
    pinMode(IZQUIERDA, INPUT);
    pinMode(DERECHA, INPUT);
    pinMode(ACEPTAR, INPUT);

}

#define NUM_ITEMS 9
int GATO_X = 0;
int GATO_Y = 0;
char* X_O[2] = {"  X", "  O"};
byte selJugador = 0;

char* gato[NUM_ITEMS] ={
      " ", " ", " ",
      " ", " ", " ",
      " ", " ", " "
  };

  char* labels[3] = {"   EL GATO VOLADOR", "GAME OVER > X < WINS", "GAME OVER > O < WINS"};

void loop() 
{
  display.clearDisplay();
  canvas1.drawTable(1,1,labels);
  
  canvas2.drawTable(3,3, gato, GATO_Y, GATO_X);
  
  if(int boton = isPressButton())
  {
      switch(boton)
      {
          case ARRIBA:
                        GATO_Y = (GATO_Y > 0) ? GATO_Y - 1 : 2;
                        break;
          case ABAJO:
                        GATO_Y = (GATO_Y < 2) ? GATO_Y + 1 : 0;
                        break;
          case IZQUIERDA:
                        GATO_X = (GATO_X > 0) ? GATO_X - 1 : 2;
                        break;
          case DERECHA:
                        GATO_X = (GATO_X < 2) ? GATO_X + 1 : 0;
                        break;
          case ACEPTAR:
                        if(gato[(GATO_Y * 3) + GATO_X] == " ")
                        {
                            gato[(GATO_Y * 3) + GATO_X] = X_O[selJugador];
                            
                            isGameOver();
                            
                            selJugador =  (selJugador == 1) ? 0 : 1;
                        }
                        break; 
      }
      delay(200);
  }

  display.display();
 
}

#define NUM_BOTONES 5
int isPressButton()
{
    int botones[NUM_BOTONES] = {ARRIBA, ABAJO, DERECHA, IZQUIERDA, ACEPTAR};
    
    for(int i = 0; i < NUM_BOTONES; i++)
    {
        if(digitalRead(botones[i]))
            return botones[i];
    }

    return 0;
}

void isGameOver(void)
{
    int NUMERO_CONVINACIONES = 8;
    int convinacion[NUMERO_CONVINACIONES][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}
    };

    for(int i = 0; i < NUMERO_CONVINACIONES; i++)
    {
        int puntos = 0;

        if(gato[convinacion[i][0]] == X_O[selJugador])
            puntos++;
        
        if(gato[convinacion[i][1]] == X_O[selJugador])
            puntos++;

        if(gato[convinacion[i][2]] == X_O[selJugador])
            puntos++;
        
 
        while(puntos == 3)
        {
            display.clearDisplay();
            labels[0] = (selJugador) ? labels[2] : labels[1];
            canvas1.drawTable(1,1,labels);
            canvas2.drawTable(3,3, gato, (int)(convinacion[i][0] / 3), (int)(convinacion[i][0] % 3));
            canvas2.drawTable(3,3, gato, (int)(convinacion[i][1] / 3), (int)(convinacion[i][1] % 3));
            canvas2.drawTable(3,3, gato, (int)(convinacion[i][2] / 3), (int)(convinacion[i][2] % 3));
            display.display();
         }
            
    }

}

/*
0 1 2
3 4 5
6 7 8
 */