/*******************************************************************************
 *
 * Copyright (c) 2020
 * Lumi, JSC.
 * All Rights Reserved
 *
 * Description: Lab2.2
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
#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 0
#define GPIO_PIN_LOW 0
#define GPIO_PIN_HIGH 1

// Define GPIO_PIN -----------------------------------------------------------
#define BUZZER_GPIO_PORT GPIOC
#define BUZZER_GPIO_PIN GPIO_Pin_9
#define BUZZER_PIN9 9
#define BUZZER_CONTROL_RCC RCC_AHB1Periph_GPIOC

#define BUTTON_GPIO_PORT GPIOB
#define BUTTON_GPIO_PIN GPIO_Pin_4
#define BUTTON_B5_PIN 4
#define BUTTON_CONTROL_RCC RCC_AHB1Periph_GPIOB

// Function declarations -----------------------------------------------------
static void Button_Init(void);
static void Buzzer_Init(void);
static void AppInitCommon(void);
static void BuzzerControl_SetStatus(GPIO_TypeDef *GPIOx, uint8_t GPIO_PIN, uint8_t Status);
static void Delay(uint32_t ms);
static uint8_t ButtonRead_Status(GPIO_TypeDef *GPIOx, uint32_t GPIO_PIN);

//-----------------------------------------------------------------------------
int main(void)
{
    AppInitCommon();

    while (1)
    {
        // Turn on the Buzzer when pressing the button-------------------------
        if (ButtonRead_Status(BUTTON_GPIO_PORT, BUTTON_B5_PIN) == GPIO_PIN_LOW)
        {
            Delay(5);
            BuzzerControl_SetStatus(BUZZER_GPIO_PORT, BUZZER_PIN9, GPIO_PIN_SET);
        }
        // Turn off the Buzzer when pressing the button------------------------
        else
        {
            BuzzerControl_SetStatus(BUZZER_GPIO_PORT, BUZZER_PIN9, GPIO_PIN_RESET);
        }
    }
}

/**
 * @func   Initializes
 * @brief  Initializes All Peripheral
 * @param  None
 * @retval None
 */
static void AppInitCommon(void)
{
    // System 84MHz-----------------------------------------------------------
    SystemCoreClockUpdate();

    // Button Init------------------------------------------------------------
    Button_Init();

    // Buzzer Init------------------------------------------------------------
    Buzzer_Init();
}

/**
 * @func   BuzzerControl_SetStatus
 * @brief  Control Turn on or Turn off Buzzer
 * @param  None
 * @retval None
 */
static void BuzzerControl_SetStatus(GPIO_TypeDef *GPIOx, uint8_t GPIO_PIN, uint8_t Status)
{
    // Set bit in BSRR Registers----------------------------------------------
    if (Status == GPIO_PIN_SET)
    {
        GPIOx->BSRRL |= 1 << GPIO_PIN;
    }
    // Reset bit in BSRR Registers--------------------------------------------
    else if (Status == GPIO_PIN_RESET)
    {
        GPIOx->BSRRH |= 1 << GPIO_PIN;
    }
}

/**
 * @func   ButtonRead_Status
 * @brief  Read Status Button
 * @param  None
 * @retval None
 */
static uint8_t ButtonRead_Status(GPIO_TypeDef *GPIOx, uint32_t GPIO_PIN)
{
    uint32_t Read_Pin;

    // Read bit in IDR Registers----------------------------------------------
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
 * @func   Initializes GPIO Use Buzzer
 * @brief  Buzzer_Init
 * @param  None
 * @retval None
 */
static void Buzzer_Init(void)
{
    // Declare type variable GPIO Struct-------------------------------------
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable Clock GPIOC----------------------------------------------------
    RCC_AHB1PeriphClockCmd(BUZZER_CONTROL_RCC, ENABLE);

    // Choose Pin Buzzer-----------------------------------------------------
    GPIO_InitStructure.GPIO_Pin = BUZZER_GPIO_PIN;

    // Choose Pin Buzzer as Out------------------------------------------------
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;

    // Choose Speed Pin------------------------------------------------------
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    // Select type------------------------------------------------------------
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

    // Select status----------------------------------------------------------
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;

    // The function initializes all of the above values-----------------------
    GPIO_Init(BUZZER_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @func   Initializes GPIO Use Button
 * @brief  Button_Init
 * @param  None
 * @retval None
 */
static void Button_Init(void)
{
    // Declare type variable GPIO Struc---------------------------------------
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable Clock GPIOB-----------------------------------------------------
    RCC_AHB1PeriphClockCmd(BUTTON_CONTROL_RCC, ENABLE);

    // Choose Pin BUTTON------------------------------------------------------
    GPIO_InitStructure.GPIO_Pin = BUTTON_GPIO_PIN;

    // Choose Pin Button as Input----------------------------------------------
    GPIO_InitStructure.GPIO
// Choose Speed Pin--------------------------------------------------------
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

// Select status------------------------------------------------------------
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

// The function initializes all of the above values-------------------------
GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStructure);
