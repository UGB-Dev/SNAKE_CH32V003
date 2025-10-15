/*

    SNAKE.h

*/

#include "SNAKE.h"

Player Jugador;

uint8_t Cuerpo_Snake[Width_Snake][3];
uint8_t Frame_Vel=0, Flag_Game_Over = 0;

/***************************************************************
*   @Fn Snake_Init
*   Inicializa los valores del snake
****************************************************************/
void SNAKE_Init(void){
    /* INICIALIZACION DE JUGADOR */
    Jugador = (Player){{120,31}, {-4,0}, 4}; 
    for (uint8_t i = 0; i<Width_Snake; i++) {
        Cuerpo_Snake[i][0] = Jugador.Posicion.X + Jugador.L + 2*(1+(i*2));
        Cuerpo_Snake[i][1] = Jugador.Posicion.Y + 2;//*(1+i);
        Cuerpo_Snake[i][2] = 1 ;
    }
}

/***************************************************************
*   @Fn Snake_Dibujar
*   Envia los datos al buffer para posteriormente enviarse al OLED
****************************************************************/
void SNAKE_Dibujar(void){
    /* DIBUJA CONTORNO */
    OLED_Cuadrado(0, 0, Width-1, High-1 );

    if (Flag_Game_Over == 1) {
        Flag_Game_Over = 0;
        OLED_Clear();
        OLED_Print_Str(20,31,"FIN DEL JUEGO :C");
        OLED_Print_Buffer();
        //Delay_Ms(2000);
        Jugador.Posicion.Y = 32;
        Jugador.Posicion.Y = 32;
         //OLED_Cuadrado(Jugador.Posicion.X, Jugador.Posicion.Y, Jugador.L, Jugador.L);
    }
    else {
        /* DIBUJA CABEZA */
        OLED_Cuadrado(Jugador.Posicion.X, Jugador.Posicion.Y, Jugador.L, Jugador.L);
        OLED_Linea(Jugador.Posicion.X, Jugador.Posicion.Y+2, Jugador.Posicion.X-4, Jugador.Posicion.Y);
        OLED_Linea(Jugador.Posicion.X, Jugador.Posicion.Y+2, Jugador.Posicion.X-4, Jugador.Posicion.Y+4);

        for (uint8_t i = 0; i<Width_Snake; i++) {
            if (Cuerpo_Snake[i][2] == 1){
                OLED_Circulo(Cuerpo_Snake[i][0], Cuerpo_Snake[i][1], 2);
            }
        }           
    }

    /* IMPRIME Y BORRA EL BUFFER */
    OLED_Print_Buffer(); 
    OLED_Clear(); 
}

void SNAKE_Actualizar_Var(){
    uint8_t X_anterior, Y_anterior;
    Frame_Vel++;

    /* CAPTURA EL ADC DE CANAL 4 */
    Jugador.Posicion.Y = 1 + (ADC_Read_Simple()*58)/1024;
 
    /* ACTUALIZACION DE LA POSICION CADA 330 ms */ // ** Observe "captura1" en carpeta "Docs" ; 15 = 1 segundo  
    if (Frame_Vel >= 2 ) { 
        Frame_Vel = 0;
        X_anterior = Jugador.Posicion.X;
        Y_anterior = Jugador.Posicion.Y;
        
        Jugador.Posicion.X += Jugador.Velocidad.X;
        Jugador.Posicion.Y += Jugador.Velocidad.Y;

        for (uint8_t i = 0; i<Width_Snake; i++) {
            if (i == Width_Snake-1) {
                Cuerpo_Snake[Width_Snake-1-i][0] = X_anterior + 2;
                Cuerpo_Snake[Width_Snake-1-i][1] = Y_anterior + 2;
            }
            else {
                Cuerpo_Snake[Width_Snake-1-i][0] = Cuerpo_Snake[Width_Snake-2-i][0];
                Cuerpo_Snake[Width_Snake-1-i][1] = Cuerpo_Snake[Width_Snake-2-i][1];
            }
        }
    } 
}

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


/*void Imprimir_Marcador(uint8_t X, uint8_t Y, uint8_t Score){
    OLED_Print_Char(X, Y, (Score/10)+'0'); // Decenas jugador 
    OLED_Print_Char(X+7, Y, (Score%10)+'0'); // Unidades jugador 
}

void Imprimir_Barra(uint8_t X, uint8_t Y){
    OLED_Linea(X, Y, X+20, Y);
    OLED_Linea(X, Y-1, X+20, Y-1);
}

void SNAKE_Colision_Barra(void){
    /* COLISION EN BARRA A
    if ( (Jugador.Posicion.Y-Jugador.L) == 50  ) {
        if ( (Jugador.Posicion.X >= (Jugador.Barra_A.X-2)) && (Jugador.Posicion.X <= (Jugador.Barra_A.X+22))) {
            if (Jugador.Posicion.X  == (Jugador.Barra_A.X-2)){
                Jugador.Velocidad.Y = Jugador.Velocidad.X = -5;
            }
            else if ( Jugador.Posicion.X  == (Jugador.Barra_A.X+22)) {
                Jugador.Velocidad.Y = -5;
                Jugador.Velocidad.X = 5;
            }
            else if(Jugador.Posicion.X < 2 || Jugador.Posicion.X > 125) {
            Jugador.Velocidad.Y = -5;
            }
            else {
                Jugador.Velocidad.Y = -5;
            }
        }
    }
    /* COLISION EN BARRA B
    else if (Jugador.Posicion.X == 121) {
        if ( (Y >= (Jugador.Barra_B.y-2)) && (Y <= (Jugador.Barra_B.y+14))) {
            if (Y == (Jugador.Barra_B.y-2)){
                Jugador.Velocidad.y = Jugador.Velocidad.x = -Jugador.Vel_Incr;
            }
            else if (Y == (Jugador.Barra_B.y+14)) {
                Jugador.Velocidad.y = Jugador.Vel_Incr;
                Jugador.Velocidad.x = -Jugador.Vel_Incr;
            }
            else {
                Jugador.Velocidad.x = -Jugador.Vel_Incr;
            }
            Jugador.Cont++;
        } 
    }*/
    /* INCREMENTA DIFICULTAD DESPUES DE 10 GOLPES EN 
    if (Jugador.Cont == 10) {
        Jugador.Vel_Incr++;
        Jugador.Cont = 0;
    }
}

void SNAKE_Colision_Jugador_Bloque(void){
    uint8_t BloqX_Max, BloqX_Min, BloqY_Max, BloqY_Min;

    for (uint8_t i=0; i<14; i++) {
        if (ID_Block[i] == 1) {
            BloqX_Max = Block_Position[i][0] + 10;
            BloqX_Min = Block_Position[i][0];
            BloqY_Max = Block_Position[i][1] + 5;
            BloqY_Min = Block_Position[i][1];

            if (( (Jugador.Posicion.Y-Jugador.L) == BloqY_Max) ) {
                if ((Jugador.Posicion.X >= BloqX_Min) && (Jugador.Posicion.X <= BloqX_Max)) {
                    Jugador.Velocidad.Y = 5;
                    ID_Block[i] = 0;
                    ID_Block[14]++;
                }
            }
            else if (((Jugador.Posicion.Y-Jugador.L) == BloqY_Min)) {
                if ((Jugador.Posicion.X >= BloqX_Min) && (Jugador.Posicion.X <= BloqX_Max)) {
                    Jugador.Velocidad.Y = -5;
                    ID_Block[i] = 0;
                    ID_Block[14]++;
                }
            }
        }
    }

    if (ID_Block[14] == 14) {
        ID_Block[14] = 0;
        for (uint8_t i=0; i<14; i++) {
            ID_Block[i] = 1;
        }
    }
}

*/