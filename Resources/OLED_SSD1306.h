/*

    OLED_SSD1306.h

*/

#ifndef __OLED_SSD1306_H__
#define __OLED_SSD1306_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "ch32v00x.h"
#include "I2C_SOFTWARE.h"
#include <stdlib.h>

extern const uint8_t Config_OLED[];
extern const uint8_t OLED_FONT[];
extern uint8_t Buffer[];

void Dato_(void);
void Comando_(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Print_Pixel(uint8_t Pos_x, uint8_t Pos_y);
void OLED_Print_Buffer(void);
void OLED_Linea(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1 );
void OLED_Circulo(uint8_t Xc, uint8_t Yc, uint8_t r);
void OLED_Cuadrado(uint8_t X0, uint8_t Y0, uint8_t LadoX, uint8_t LadoY);
void OLED_Print_Str(uint8_t xpos, uint8_t ypos,const char* DATA);
void OLED_Print_Char(uint8_t xpos, uint8_t ypos, char DATA);
void OLED_Print_Sprite(uint8_t X_pos, uint8_t Y_pos, const uint16_t* Sprite);

#ifdef __cplusplus
 }
#endif //__OLED_SSD1306_H__
#endif

/* genera oscilacion en x y
    x0 =   (x0-Cx)*Sin + Cx;
    y0 =  (y0-Cy)*Cos + Cy;

    x1 =  (x1-Cx)*Sin + Cx;
    y1 =  (y1-Cy)*Cos + Cy;

    x2 =  (x2-Cx)*Sin + Cx;
    y2 =  (y2-Cy)*Cos + Cy;

    x3 =  (x3-Cx)*Sin + Cx;
    y3 =  (y3-Cy)*Cos + Cy;
*/

/* rotacion infinito
    x0 = (x0 - Cx)*Cos - (y0-Cy)*Sin + Cx;
    y0 = (x0 - Cx)*Sin + (y0-Cy)*Cos + Cy;

    x1 = (x1 - Cx)*Cos - (y1-Cy)*Sin + Cx;
    y1 = (x1 - Cx)*Sin + (y1-Cy)*Cos + Cy;

    x2 = (x2 - Cx)*Cos - (y2-Cy)*Sin + Cx;
    y2 = (x2 - Cx)*Sin + (y2-Cy)*Cos + Cy;

    x3 = (x3 - Cx)*Cos - (y3-Cy)*Sin + Cx;
    y3 = (x3 - Cx)*Sin + (y3-Cy)*Cos + Cy;
*/

/* FIGURA ABRE Y CIERRA EMPEZANDO DESDE CENTRO
    x0 =  ((x0-Cx)*Sin + Cx);
    y0 =  (y0-Cy)*Sin + Cy;

    x1 =  (x1-Cx)*Sin + Cx;
    y1 =  (y1-Cy)*Sin + Cy;

    x2 =  (x2-Cx)*Sin + Cx;
    y2 =  (y2-Cy)*Sin + Cy;

    x3 =  (x3-Cx)*Sin + Cx;
    y3 =  (y3-Cy)*Sin + Cy;
*/

/* FIGURA ABRE Y CIERRA EMPEZANDO DESDE FUERA
    x0 =  ((x0-Cx)*Cos + Cx);
    y0 =  (y0-Cy)*Cos + Cy;

    x1 =  (x1-Cx)*Cos + Cx;
    y1 =  (y1-Cy)*Cos + Cy;

    x2 =  (x2-Cx)*Cos + Cx;
    y2 =  (y2-Cy)*Cos + Cy;

    x3 =  (x3-Cx)*Cos + Cx;
    y3 =  (y3-Cy)*Cos + Cy;
*/

/* rotacion antihorario
    x0 =  (y0-Cy)*Sin + Cx;
    y0 =  (y0-Cy)*Cos + Cy;

    x1 =  (y1-Cy)*Sin + Cx;
    y1 =  (y1-Cy)*Cos + Cy;

    x2 =  (y2-Cy)*Sin + Cx;
    y2 =  (y2-Cy)*Cos + Cy;

    x3 =  (y3-Cy)*Sin + Cx;
    y3 = (y3-Cy)*Cos + Cy;
*/

/* rotacion horario
    x0 =  (y0-Cy)*Cos + Cx;
    y0 =  (y0-Cy)*Sin + Cy;

    x1 =  (y1-Cy)*Cos + Cx;
    y1 =  (y1-Cy)*Sin + Cy;

    x2 =  (y2-Cy)*Cos + Cx;
    y2 =  (y2-Cy)*Sin + Cy;

    x3 =  (y3-Cy)*Cos + Cx;
    y3 =  (y3-Cy)*Sin + Cy;
*/

/* bsarra flotante
    x0 =   (x0-Cx)*Sin + Cx;
    y0 =  (x0-Cx)*Cos + Cy;

    x1 =  (x0-Cx)*Sin + Cx;
    y1 =  (x0-Cx)*Cos + Cy;

    x2 =  (x0-Cx)*Sin + Cx;
    y2 =  (x0-Cx)*Cos + Cy;

    x3 =  (x0-Cx)*Sin + Cx;
    y3 =  (x0-Cx)*Cos + Cy;
*/

/* manecilla
    *x = (*y-Cx)*Cos + Cx;
    *y = (*y-Cx)*Sin + Cy;
*/

/* L central
    *x = (*y-Cx)*Cos + Cx;
    *y = (*y-Cy)*Sin + Cy;
*/
/* L casi
    *x =  (*x-Cx)*Cos + Cx;
    *y =  (*x-Cx)*Sin + Cy;
*/

/* reloj arena
    x0 =  (x0 - Cx)*Sin + Cx;
    y0 = (x0 - Cx)*Cos + Cy;
*/

/* dibuja un pundo que gira en un cuadrado
    float m = fmaxf(fabsf(Cos), fabsf(Sin));
    *x =  Cx + (Cos/m) * 63;
    *y =  Cy + (Sin/m) * 31;

*/
