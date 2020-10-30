# EasyMenu_OLED
Librería para la implementación sencilla de menús y tablas en pantallas OLED, en conjunto con la libreria Adafruit_SSD1306 y  Adafruit_GFX.
Diseñada para acelerar la creación e menus básicos, despliegues de tablas y datos

## ¿Cómo utilizar?

```c++
/*Crear un Menú de la pantalla completa*/
EasyMenu Menu(&display, SCREEN_WIDTH, SCREEN_HEIGHT);

/*Crear un menú en una seccion de la pantalla*/
EasyMenu canvas(&display, 80, 50, 48, 7);
/*          |       |       |   |   |  |--------> Cordenada de origen en Y del canvas
            |       |       |   |   |-----------> Cordenada de origen en X del canvas
            |       |       |   |---------------> Alto del canvas del canvas
            |       |       |-------------------> Ancho del canvas del canvas
            |       |---------------------------> Apuntador al display
            |-----------------------------------> ID del canvas
*/

/******************************************************************************************************/
```

```c++
/*Dibujar un Menú básico*/
char* muenuOpciones[4] = {"   CONFIGURACION", "     OPCIONES", "     AVANZADO", "      SALIR"}; //char* array con la lista de opciones que aparecerán en el menú

Menu.clearDisplay(); //Borrar pantalla

Menu.drawMenu(muenuOpciones, 4, opcionIndex); 
/*                 |         |       |-----------> Opción seleccionada
                   |         |-------------------> Cantidad de opciones
                   |-----------------------------> Lista de etiquetas de opciones
*/
Menu.display(); //Mostrar en pantalla

/******************************************************************************************************/
```
![](https://github.com/IsraelBarreras/EasyMenu_OLED/blob/master/img/Menu.png)


```c++
/*Dibujar una tabla vacía o cuadrícula*/
Menu.clearDisplay();
Menu.drawGrill(FILAS, COLUMNAS); 
Menu.display();
```
![](https://github.com/IsraelBarreras/EasyMenu_OLED/blob/master/img/tabla.png)


```c++
/*Dibular una tabla que contenga texto*/
    char* textos[16] = {          //Array de etiquetas
        "A0", "B0", "C0", "D0",
        "A1", "B1", "C1", "D1",
        "A2", "B2", "C2", "D2",
        "A3", "B3", "C3", "D3"
    };

    Menu.clearDisplay();

    Menu.drawTable(4, 4, textos); //Tabla de 4x4 con contenido que ocupara todo el largo y ancho del canvas
                //(Filas, Columnas, list);
    Menu.display();
```
![](https://github.com/IsraelBarreras/EasyMenu_OLED/blob/master/img/TablaTexto.png)


```c++
/*Dibujar una tabla de parámetros*/
    double temperatura = 30.05;                             //Aqui solo declaro parámetros de ejemplo
    double humedad = 66;                                    //          
    double rpm = 2500;                                      //
    char* item_labels[3] = {"TEMP:", "HUM:", "RPM:"};       //    Etiquetas del lado izquierdo de la tabla
    double* item_values[3] = {&temperatura, &humedad, &rpm};//    parámetros o valores del lado derecho
    
    Menu.clearDisplay(); 
    Menu.drawParameterTable(3, item_labels, item_values, 0); //Aquí dibujamos la tabla
/*                          |      |             |       |---------------> parametro seleccionado
                            |      |             | ----------------------> Array de apuntadores a los valores de los parámetros
                            |      |-------------------------------------> Lista de nombres de cada parámetro
                            |--------------------------------------------> Numero de parámetros

*/
    Menu.display();
```
![](https://github.com/IsraelBarreras/EasyMenu_OLED/blob/master/img/tablaParametros.png)
