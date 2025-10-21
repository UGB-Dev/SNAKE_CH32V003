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
#include <stdlib.h>
#include "ADC_MULTI_CHANNEL.h"
#include "OLED_SSD1306.h"

#define Width 128
#define Height 64
#define Width_Snake 100

#define UP    Jugador.Velocidad.X = 0; \
              Jugador.Velocidad.Y = -4;
#define DOWN  Jugador.Velocidad.X = 0; \
              Jugador.Velocidad.Y = 4;
#define LEFT  Jugador.Velocidad.X = -4; \
              Jugador.Velocidad.Y = 0;
#define RIGHT Jugador.Velocidad.X = 4; \
              Jugador.Velocidad.Y = 0;        

typedef struct {
    int X;
    int Y;
}Position;

typedef struct{
    Position Posicion;
    Position Velocidad;
    uint8_t L;
    uint16_t Score;
}Player;

typedef struct{
    Position Posicion;
    uint8_t Activo;
}Snake_Body;

extern uint8_t Frame_Vel, Flag_Game_Over, Aleatorio;
extern uint16_t Body_Pos;
extern const uint16_t Manzana[];

void SNAKE_Init(void);
void SNAKE_Dibujar(void);
void SNAKE_Actualizar_Var(void);
void SNAKE_Colision_Borde(void);
void SNAKE_Colision_Comida(void);

#ifdef __cplusplus
 }
#endif //__SNAKE_H__
#endif