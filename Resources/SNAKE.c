/*

    SNAKE.h

*/

#include "SNAKE.h"

Player Jugador;
Snake_Body Food;
Snake_Body *Body; // Debe ser del mismo tipo a la memoria dinamica
uint8_t Frame_Vel=0, Flag_Game_Over = 0, Aleatorio=0;
uint16_t Body_Pos=0;

const uint16_t Manzana[]={
  5, 8, 0x78, 0xFC, 0x7E, 0xFD, 0x79
};

/***************************************************************
*   @fn SNAKE_Init
*   Inicializa los valores de la serpiente
****************************************************************/
void SNAKE_Init(void){
    /* INICIALIZACION DE JUGADOR */
    Jugador = (Player){{120, 31}, {-4, 0}, 4, 0};
    Food =  (Snake_Body){{20, 10}, 1};
    
    Body = calloc(Width_Snake, sizeof(Snake_Body)); // Crea n datos en ram de tipo entero sin signo
    for (uint16_t i = 0; i<Width_Snake; i++) {
        Body[i].Posicion.X = Jugador.Posicion.X + Jugador.L + 2 * (1 + (i * 2));
        Body[i].Posicion.Y = Jugador.Posicion.Y + 2;
        Body[i].Activo = 0;
    }
}

/***************************************************************
*   @fn SNAKE_Dibujar
*   Envia los datos al buffer para posteriormente enviarse al OLED
****************************************************************/
void SNAKE_Dibujar(void){
    /* ASIGNA EN BUFFER EL CONTORNO */
    OLED_Cuadrado(0, 0, Width-1, Height-1 );

    /* REINICIO DE VARIABLES */
    if (Flag_Game_Over == 1) {
        Flag_Game_Over = 0;
        OLED_Clear();
        OLED_Print_Str(20,24,"FIN DEL JUEGO :C");
        OLED_Print_Str(20,40,"PUNTAJE: ");
        OLED_Print_Char(74,40, '0'+ Jugador.Score / 100 );
        OLED_Print_Char(81,40, '0'+ (Jugador.Score % 100) % 10 );
        OLED_Print_Char(88,40, '0'+ (Jugador.Score % 100) / 10  );
        OLED_Print_Buffer();
        Delay_Ms(1000);

        Jugador.Posicion.Y = 32;
        for (uint16_t i = 0; i<Width_Snake; i++) {
            Body[i].Activo = 0;
        }
        Body_Pos =0;
    }
    else {
        /* ASIGNA EN BUFFER LA CABEZA DE LA SERPIENTE */
        OLED_Cuadrado(Jugador.Posicion.X, Jugador.Posicion.Y, Jugador.L, Jugador.L);
        
        /* ASIGNA EN BUFFER LA LENGUA DE LA SERPIENTE DE ACUERDO A LA DIRECCION */
        if (Jugador.Velocidad.X < 0 && Jugador.Velocidad.Y == 0) { // Izquierda
            OLED_Linea(Jugador.Posicion.X, Jugador.Posicion.Y+2, Jugador.Posicion.X-4, Jugador.Posicion.Y);
            OLED_Linea(Jugador.Posicion.X, Jugador.Posicion.Y+2, Jugador.Posicion.X-4, Jugador.Posicion.Y+4);
        }
        else if (Jugador.Velocidad.X > 0 && Jugador.Velocidad.Y == 0) { // Derecha
            OLED_Linea(Jugador.Posicion.X+4, Jugador.Posicion.Y+2, Jugador.Posicion.X+8, Jugador.Posicion.Y+2);
            OLED_Linea(Jugador.Posicion.X+4, Jugador.Posicion.Y+2, Jugador.Posicion.X+8, Jugador.Posicion.Y+4);
        }
        else if (Jugador.Velocidad.Y < 0 && Jugador.Velocidad.X == 0) { // Arriba
            OLED_Linea(Jugador.Posicion.X+2, Jugador.Posicion.Y, Jugador.Posicion.X, Jugador.Posicion.Y-4);
            OLED_Linea(Jugador.Posicion.X+2, Jugador.Posicion.Y, Jugador.Posicion.X+4, Jugador.Posicion.Y-4);
        
        }
        else if (Jugador.Velocidad.Y > 0 && Jugador.Velocidad.X == 0) { // Abajo
            OLED_Linea(Jugador.Posicion.X+2, Jugador.Posicion.Y+4, Jugador.Posicion.X, Jugador.Posicion.Y+8);
            OLED_Linea(Jugador.Posicion.X+2, Jugador.Posicion.Y+4, Jugador.Posicion.X+4, Jugador.Posicion.Y+8);
        
        }
        
        /* ASIGNA EN BUFFER EL SPRITE DE LA MANZANA */
        OLED_Print_Sprite(Food.Posicion.X +2, Food.Posicion.Y + 4, Manzana);
        
        /* ASIGNA EN BUFFER EL CUERPO DE LA SERPIENTE */
        for (uint16_t i = 0; i<Width_Snake; i++) {
            if (Body[i].Activo == 1){
                OLED_Circulo(Body[i].Posicion.X, Body[i].Posicion.Y, 2);
            }
        }           
    }

    OLED_Print_Buffer(); // Envia el contenido del buffer al OLED 
    OLED_Clear(); // Borra el contenido del buffer
}

/***************************************************************
*   @fn SNAKE_Actualizar_Var
*   Actualiza las posiciones de la serpiente asi como su cuerpo
****************************************************************/
void SNAKE_Actualizar_Var(void){
    srand(10+Aleatorio++);

    ADC_Multi_Channel_Read(); // Captura el adc del canal 4 y 6
    uint8_t X_anterior, Y_anterior; // Variables auxiliares de la posicion actual
    Frame_Vel++; // Variable para actualizar el movimiento (observe la captura1 de la carpeta Docs)

    int16_t X_Reposo = 1024 - ADC_VALUE[0]; // Joystick para el eje X 
    int16_t Y_Reposo = 1024 - ADC_VALUE[1]; // Joystick para el eje Y

    /* INCREMENTA O DECREMENTA LA POSICION (X,Y) DE LA NAVE */
    if (X_Reposo > 552){ RIGHT; }
    else if(X_Reposo < 472) { LEFT; }

    if (Y_Reposo > 552){ UP; }
    else if(Y_Reposo < 472) { DOWN; }

    /* CREA LA COMIDA EN LA POSICION ALEATORIA (X,Y) */
    if (Food.Activo != 1){
        Food.Posicion.X = 3 + rand()%121;
        Food.Posicion.Y = 3 + rand()%57;
        Food.Activo = 1;
    }
 
    /* ACTUALIZACION DE LA POSICION CADA SEGUNDO (observe la captura1 de la carpeta Docs) */  
    if (Frame_Vel >= 7 ) { 
        Frame_Vel = 0;

        /* SE CAPTURA LA POSICION ACTUAL (X,Y) */
        X_anterior = Jugador.Posicion.X;
        Y_anterior = Jugador.Posicion.Y;
        
        /* ACTUALIZA LA POSICION (X,Y) DEL JUGADOR DE ACUERDO AL VECTOR VELOCIDAD */
        Jugador.Posicion.X += Jugador.Velocidad.X;
        Jugador.Posicion.Y += Jugador.Velocidad.Y;

        /* ACTUALIZA LA POSICION (X,Y) DEL CUERPO */
        for (uint16_t i = 0; i<Width_Snake; i++) {
            if (i == Width_Snake-1) {
                Body[Width_Snake-1-i].Posicion.X = X_anterior + 2;
                Body[Width_Snake-1-i].Posicion.Y = Y_anterior + 2;
            }
            else {
                Body[Width_Snake-1-i].Posicion.X = Body[Width_Snake-2-i].Posicion.X;
                Body[Width_Snake-1-i].Posicion.Y = Body[Width_Snake-2-i].Posicion.Y;
            }
        }
    } 
}

/***************************************************************
*   @fn SNAKE_Colision_Borde
*   Determina si la serpiente esta fuera de los limites del contorno
*   para actualizar su proxima posicion
****************************************************************/
void SNAKE_Colision_Borde(void){
    /* COLISION EN BORDES DEL EJE Y */
    if((Jugador.Posicion.Y + Jugador.L) > 62 || Jugador.Posicion.Y < 2){
        Jugador.Posicion.Y = 32;
        Flag_Game_Over = 1;
    }
    
    /* COLISION EN BORDES DEL EJE X */
    if ( (Jugador.Posicion.X <= 0) || ((Jugador.Posicion.X + Jugador.L) > 125)) {
        Jugador.Posicion.X = 120;
        Flag_Game_Over = 1;    
    }
}

/***************************************************************
*   @fn SNAKE_Colision_Comida
*   Determina si la serpiente se encuentra en la ubicacion de la comida
*   para posteriormente "actualizar" la proxima posicion
****************************************************************/
void SNAKE_Colision_Comida(void){
    if (Food.Posicion.X >= Jugador.Posicion.X && Food.Posicion.X <= (Jugador.Posicion.X+4)) {
        if (Food.Posicion.Y >= Jugador.Posicion.Y && Food.Posicion.Y <= (Jugador.Posicion.Y + Jugador.L) ) {
            Food.Activo = 0;
            Body[Body_Pos].Activo = 1;
            Body_Pos++;
            Jugador.Score++;
        }
    }
}
