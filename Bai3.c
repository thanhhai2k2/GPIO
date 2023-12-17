/*******************************************************************************
 *
 * Copyright (c) 2020
 * Lumi, JSC.
 * All Rights Reserved
 *
 * Description: Lab2.3
 *
 * Author: Developer embedded team
 *
 * Last Changed By:  $Author: HoangNH $
 * Revision:         $Revision: 1.0 $
 * Last Changed:     $Date: 10/7/2020 $
 *
 ******************************************************************************/

#include "stm32f401re_rcc.h"
#include "stm32f401re_gpio.h"

// Define Logic GPIO_PIN -----------------------------------------------------
#define GPIO_PIN_SET   1
#define GPIO_PIN_RESET 0
#define GPIO_PIN_LOW   0
#define GPIO_PIN_HIGH  1

// Define GPIO_PIN -----------------------------------------------------------
#define LEDRED_GPIO_PORT        GPIOB
#define LEDRED_GPIO_PIN         GPIO_Pin_13
#define LEDRED_PIN              13
#define LEDREDControl_SetClock  RCC_AHB1Periph_GPIOB

#define BUTTON_GPIO_PORT        GPIOB
#define BUTTON_GPIO_PIN         GPIO_Pin_3
#define BUTTON_B2_PIN           3
#define BUTTONControl_SetClock  RCC_AHB1Periph_GPIOB

// Function declaration -----------------------------------------------------
static void LedControl_SetStatus(GPIO_TypeDef *GPIOx, uint8_t GPIO_PIN, uint8_t Status);
static void Delay(uint32_t ms);
static uint8_t ButtonRead_Status(GPIO_TypeDef *GPIOx, uint32_t GPIO_PIN);
static void Button_Init(void);
static void Led_Init(void);
static void AppInitCommon(void);

//-----------------------------------------------------------------------------
int main(void)
{
    AppInitCommon();

    while(1)
    {
        // Turn on the Led Red when pressing the button -----------------------
        if (ButtonRead_Status(BUTTON_GPIO_PORT, BUTTON_B2_PIN) == GPIO_PIN_LOW)
        {
            Delay(5);
            LedControl_SetStatus(LEDRED_GPIO_PORT, LEDRED_PIN, GPIO_PIN_SET);
        }

        // Turn off the led Red when pressing the button ----------------------
        else
        {
            LedControl_SetStatus(LEDRED_GPIO_PORT, LEDRED_PIN, GPIO_PIN_RESET);
        }
    }
}

/**
 * @func   Initializes All Peripheral
 * @brief  AppInitCommon
 * @param  None
 * @retval None
 */
static void AppInitCommon(void)
{
    // System Init -----------------------------------------------------------
    SystemCoreClockUpdate();

    // Button Init -----------------------------------------------------------
    Button_Init();

    // Led Init --------------------------------------------------------------
    Led_Init();
}

/**
 * @func   Control Turn on or Turn off Led
 * @brief  LedControl_SetStatus
 * @param  None
 * @retval None
 */
static void LedControl_SetStatus(GPIO_TypeDef *GPIOx, uint8_t GPIO_PIN, uint8_t Status)
{
    // Set bit in BSRR Registers --------------------------------------------
    if (Status == GPIO_PIN_SET)
    {
        GPIOx->BSRRL |= 1 << GPIO_PIN;
    }
    // Reset bit in BSRR Registers ------------------------------------------
    else if (Status == GPIO_PIN_RESET)
    {
        GPIOx->BSRRH |= 1 << GPIO_PIN;
    }
}

/**
 * @func   Read Status Button
 * @brief  ButtonRead_Status
 * @param  None
 * @retval None
 */
static uint8_t ButtonRead_Status(GPIO_TypeDef *GPIOx, uint32_t GPIO_PIN)
{
    uint32_t Read_Pin;

    // Read bit in IDR Registers --------------------------------------------
    Read_Pin = (GPIOx->IDR) >> GPIO_PIN;
    Read_Pin = Read_Pin & 0x01;

    return Read_Pin;
}

/**
 * @func   Delay Time
 * @brief  Delay
 * @param  None
 * @retval None
 */
static void Delay(uint32_t ms)
{
    uint32_t i, j;
    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 5000; j++)
        {
            ;
        }
    }
}

/**
 * @func   Initializes GPIO Use Led
 * @brief  Led_Init
 * @param  None
 * @retval None
 */
static void Led_Init(void)
{
    // Declare type variable GPIO Struct -------------------------------------
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable Clock GPIOA ----------------------------------------------------
    RCC_AHB1PeriphClockCmd(LEDREDControl_SetClock, ENABLE);

    // Choose Pin Led --------------------------------------------------------
    GPIO_InitStructure.GPIO_Pin = LEDRED_GPIO_PIN;

    // Choose Pin Led as Out -------------------------------------------------
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;

    // Choose Speed Pin ------------------------------------------------------
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    // Select type -----------------------------------------------------------
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

    // Select status ---------------------------------------------------------
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

    // The function initializes all of the above values -----------------------
    GPIO_Init(LEDRED_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @func   Initializes GPIO Use Button
 * @brief  Button_Init
 * @param  None
 * @retval None
 */
static void Button_Init(void)
{
    // Declare type variable GPIO Struct -------------------------------------
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable Clock GPIOC ----------------------------------------------------
    RCC_AHB1PeriphClockCmd(BUTTONControl_SetClock, ENABLE);

    // Choose Pin BUTTON -----------------------------------------------------
    GPIO_InitStructure.GPIO_Pin = BUTTON_GPIO_PIN;

    // Choose Pin Led as Input ------------------------------------------------
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;

    // Choose Speed Pin -------------------------------------------------------
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    // Select status ----------------------------------------------------------
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

    // The function initializes all of the above values ------------------------
    GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStructure);
}

/* END_FILE */
