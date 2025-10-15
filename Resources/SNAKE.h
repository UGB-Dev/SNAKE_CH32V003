/*

    SNAKE.h

*/

#ifndef __SNAKE_H__
#define __SNAKE_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "ADC.h"
#include "OLED_SSD1306.h"

#define Width 128
#define High 64
#define Width_Snake 30

#define UP Jugador.Velocidad.X = 0; \
           Jugador.Velocidad.Y = -1;
#define DOWN Jugador.Velocidad.X = 0; \
             Jugador.Velocidad.Y = 1;
#define LEFT Jugador.Velocidad.X = -1; \
             Jugador.Velocidad.Y = 0;
#define RIGHT Jugador.Velocidad.X = 1; \
              Jugador.Velocidad.Y = 0;
           

typedef struct {
    int X;
    int Y;
}Position;

typedef struct{
    Position Posicion;
    Position Velocidad;
    uint8_t L;
}Player;

extern uint8_t ID_Block[];
extern uint8_t Frame_Vel, Flag_Game_Over;

void Imprimir_Marcador(uint8_t X, uint8_t Y, uint8_t Score);
void Imprimir_Barra(uint8_t X, uint8_t Y);
void SNAKE_Init(void);
void SNAKE_Colision_Borde(void);
void SNAKE_Colision_Barra(void);
void SNAKE_Dibujar(void);
void SNAKE_Actualizar_Var(void);
void SNAKE_Colision_Pelota_Bloque(void);

#ifdef __cplusplus
 }
#endif //__SNAKE_H__
#endif