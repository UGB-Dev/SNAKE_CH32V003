/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : UGB_Dev
 * Version            : V1.0.0
 * Date               : 2025/10/14
 * Description        : SNAKE.
 *********************************************************************************/

#include "debug.h"
#include "I2C_SOFTWARE.h"
#include "OLED_SSD1306.h"
#include "ADC_MULTI_CHANNEL.h"
#include "SNAKE.h"

int main(void){
    Delay_Init();
    I2C_SOFT_Init(100000); // I2C a 100 Kb/s
    ADC_Multi_Channel_Init();
    OLED_Init();
    OLED_Clear();
    OLED_Print_Buffer();

    SNAKE_Init();

    while(1){
        SNAKE_Actualizar_Var();
        SNAKE_Colision_Borde();
        SNAKE_Colision_Comida();
        SNAKE_Dibujar();
    }
}
