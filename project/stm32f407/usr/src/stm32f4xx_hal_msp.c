/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      stm32f4xx_hal_msp.c
 * @brief     stm32f4xx hal msp source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2022-11-11
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2022/11/11  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "stm32f4xx_hal.h"
#include "dcmi.h"
#include "sdio.h"

/** 
 * @defgroup msp HAL_MSP_Private_Functions
 * @{
 */

/**
 * @brief  initializes the global msp.
 * @note   none
 */
void HAL_MspInit(void)
{
    
}

/**
 * @brief  deinitializes the global msp.
 * @note   none
 */
void HAL_MspDeInit(void)
{
    
}

/**
 * @brief     uart hal init
 * @param[in] *huart points to a uart handle
 * @note      none
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    if (huart->Instance == USART1)
    {
        /* enable uart gpio clock */
        __HAL_RCC_GPIOA_CLK_ENABLE();
        
        /* enable usart1 clock */
        __HAL_RCC_USART1_CLK_ENABLE();
        
        /**
         * PA9  ------> USART1_TX
         * PA10 ------> USART1_RX 
         */
        GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
        /* enable nvic */
        HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
    if (huart->Instance == USART2)
    {
        /* enable uart gpio clock */
        __HAL_RCC_GPIOA_CLK_ENABLE();
        
        /* enable usart2 clock */
        __HAL_RCC_USART2_CLK_ENABLE();
    
        /**
         * PA2 ------> USART2_TX
         * PA3 ------> USART2_RX 
         */
        GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
        /* enable nvic */
        HAL_NVIC_SetPriority(USART2_IRQn, 2, 0);
        HAL_NVIC_EnableIRQ(USART2_IRQn);
    }
}

/**
 * @brief     uart hal deinit
 * @param[in] *huart points to a uart handle
 * @note      none
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
    if (huart->Instance == USART1)
    {
        /* disable usart1 clock */
        __HAL_RCC_USART1_CLK_DISABLE();
        
        /* uart gpio deinit */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);
        
        /* disable nvic */
        HAL_NVIC_DisableIRQ(USART1_IRQn);
    }
    if (huart->Instance == USART2)
    {
        /* disable usart2 clock */
        __HAL_RCC_USART2_CLK_DISABLE();
        
        /* uart gpio deinit */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);
        
        /* disable nvic */
        HAL_NVIC_DisableIRQ(USART2_IRQn);
    }
}

/**
 * @brief     sd hal init
 * @param[in] *hsd points to a sd handle
 * @note      none
 */
void HAL_SD_MspInit(SD_HandleTypeDef *hsd)
{
    GPIO_InitTypeDef GPIO_Initure;
    DMA_HandleTypeDef *sd_tx_dma_handle;
    DMA_HandleTypeDef *sd_rx_dma_handle;
    
    /* enable sdio clock */
    __HAL_RCC_SDIO_CLK_ENABLE();
    
    /* enable dma2 clock */
    __HAL_RCC_DMA2_CLK_ENABLE();
    
    /* enable sdio gpio clock */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    
    /**
     * PC8  ------> SDIO D0
     * PC9  ------> SDIO D1
     * PC10 ------> SDIO D2
     * PC11 ------> SDIO D3
     * PC12 ------> SDIO SCK
     */
    GPIO_Initure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
    GPIO_Initure.Mode = GPIO_MODE_AF_PP;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;
    GPIO_Initure.Alternate = GPIO_AF12_SDIO;
    HAL_GPIO_Init(GPIOC, &GPIO_Initure);
    
    /**
     * PD2 ------> SDIO CMD
     */
    GPIO_Initure.Pin = GPIO_PIN_2;
    HAL_GPIO_Init(GPIOD, &GPIO_Initure);
    
    /* enable sd interrupt */
    HAL_NVIC_SetPriority(SDMMC1_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(SDMMC1_IRQn);
    
    /* get tx dma handle */
    sd_tx_dma_handle = sdio_get_tx_dma_handle();
    
    /* get rx dma handle */
    sd_rx_dma_handle = sdio_get_rx_dma_handle();
    
    /* set rx dma */
    sd_rx_dma_handle->Instance = DMA2_Stream3;
    sd_rx_dma_handle->Init.Channel = DMA_CHANNEL_4;
    sd_rx_dma_handle->Init.Direction = DMA_PERIPH_TO_MEMORY;
    sd_rx_dma_handle->Init.PeriphInc = DMA_PINC_DISABLE;
    sd_rx_dma_handle->Init.MemInc = DMA_MINC_ENABLE;
    sd_rx_dma_handle->Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    sd_rx_dma_handle->Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    sd_rx_dma_handle->Init.Mode = DMA_PFCTRL;
    sd_rx_dma_handle->Init.Priority = DMA_PRIORITY_VERY_HIGH;
    sd_rx_dma_handle->Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    sd_rx_dma_handle->Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    sd_rx_dma_handle->Init.MemBurst = DMA_MBURST_INC4;
    sd_rx_dma_handle->Init.PeriphBurst = DMA_PBURST_INC4;

    /* link rx dma */
    __HAL_LINKDMA(hsd, hdmarx, *sd_rx_dma_handle);
    (void)HAL_DMA_DeInit(sd_rx_dma_handle);
    (void)HAL_DMA_Init(sd_rx_dma_handle);
    
    /* set tx dma */
    sd_tx_dma_handle->Instance = DMA2_Stream6;
    sd_tx_dma_handle->Init.Channel = DMA_CHANNEL_4;
    sd_tx_dma_handle->Init.Direction = DMA_MEMORY_TO_PERIPH;
    sd_tx_dma_handle->Init.PeriphInc = DMA_PINC_DISABLE;
    sd_tx_dma_handle->Init.MemInc = DMA_MINC_ENABLE;
    sd_tx_dma_handle->Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    sd_tx_dma_handle->Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    sd_tx_dma_handle->Init.Mode = DMA_PFCTRL;
    sd_tx_dma_handle->Init.Priority = DMA_PRIORITY_VERY_HIGH;
    sd_tx_dma_handle->Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    sd_tx_dma_handle->Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    sd_tx_dma_handle->Init.MemBurst = DMA_MBURST_INC4;
    sd_tx_dma_handle->Init.PeriphBurst = DMA_PBURST_INC4;
    
    /* link tx dma */
    __HAL_LINKDMA(hsd, hdmatx, *sd_tx_dma_handle);
    (void)HAL_DMA_DeInit(sd_tx_dma_handle);
    (void)HAL_DMA_Init(sd_tx_dma_handle);
  
    /* enable dma interrupt */
    HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 4, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
    HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);
}

/**
 * @brief     sd hal deinit
 * @param[in] *hsd points to a sd handle
 * @note      none
 */
void HAL_SD_MspDeInit(SD_HandleTypeDef *hsd)
{
    DMA_HandleTypeDef *sd_tx_dma_handle;
    DMA_HandleTypeDef *sd_rx_dma_handle;
    
    /* disable sdio clock */
    __HAL_RCC_SDIO_CLK_DISABLE();
    
    /* deinit sd gpio */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12);
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);
    
    /* get tx dma handle */
    sd_tx_dma_handle = sdio_get_tx_dma_handle();
    
    /* get rx dma handle */
    sd_rx_dma_handle = sdio_get_rx_dma_handle();
    
    /* disable dma */
    (void)HAL_DMA_DeInit(sd_tx_dma_handle);
    (void)HAL_DMA_DeInit(sd_rx_dma_handle);
    
    /* disable sd interrupt */
    HAL_NVIC_DisableIRQ(SDMMC1_IRQn);
    
    /* disable dma interrupt */
    HAL_NVIC_DisableIRQ(DMA2_Stream3_IRQn);
    HAL_NVIC_DisableIRQ(DMA2_Stream6_IRQn);
}

/**
 * @brief     dcmi hal init
 * @param[in] *hdcmi points to a dcmi handle
 * @note      none
 */
void HAL_DCMI_MspInit(DCMI_HandleTypeDef* hdcmi)
{
    GPIO_InitTypeDef GPIO_Initure;
    DMA_HandleTypeDef *dma_handle;
    
    /* enable dcmi clock */
    __HAL_RCC_DCMI_CLK_ENABLE();
    
    /* enable dma2 clock */
    __HAL_RCC_DMA2_CLK_ENABLE();
    
    /* enable gpio */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    
    /**
     * PA4  ------> HREF
     * PA6  ------> PCLK
     */
    GPIO_Initure.Pin = GPIO_PIN_4 | GPIO_PIN_6;
    GPIO_Initure.Mode = GPIO_MODE_AF_PP;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;
    GPIO_Initure.Alternate = GPIO_AF13_DCMI;
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);
    
    /**
     * PB6  ------> D5
     * PB7  ------> VSYNC
     */
    GPIO_Initure.Pin = GPIO_PIN_6 | GPIO_PIN_7;  
    HAL_GPIO_Init(GPIOB, &GPIO_Initure);
    
    /**
     * PC6  ------> D0
     * PC7  ------> D1
     */
    GPIO_Initure.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    HAL_GPIO_Init(GPIOC, &GPIO_Initure);
    
    /**
     * PE0  ------> D2
     * PE1  ------> D3
     * PE4  ------> D4
     * PE5  ------> D6
     * PE6  ------> D7
     */
    GPIO_Initure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6; 
    HAL_GPIO_Init(GPIOE, &GPIO_Initure);
    
    /* set dcmi nvic */
    HAL_NVIC_SetPriority(DCMI_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(DCMI_IRQn);
    
    /* get dma handle */
    dma_handle = dcmi_get_dma_handle();
    
    /* set dma */
    dma_handle->Instance                 = DMA2_Stream1;
    dma_handle->Init.Channel             = DMA_CHANNEL_1;
    dma_handle->Init.Direction           = DMA_PERIPH_TO_MEMORY;
    dma_handle->Init.PeriphInc           = DMA_PINC_DISABLE;
    dma_handle->Init.MemInc              = DMA_MINC_ENABLE;
    dma_handle->Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    dma_handle->Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
    dma_handle->Init.Mode                = DMA_CIRCULAR;
    dma_handle->Init.Priority            = DMA_PRIORITY_HIGH;
    dma_handle->Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
    dma_handle->Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    dma_handle->Init.MemBurst            = DMA_MBURST_SINGLE;
    dma_handle->Init.PeriphBurst         = DMA_PBURST_SINGLE; 
    
    /* link dma */
    __HAL_LINKDMA(hdcmi, DMA_Handle, *dma_handle);
    
    /* dma init */
    (void)HAL_DMA_DeInit(dma_handle);
    (void)HAL_DMA_Init(dma_handle);
    
    /* set dma2 nvic */
    HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 7, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn); 
}

/**
 * @brief     dcmi hal deinit
 * @param[in] *hdcmi points to a dcmi handle
 * @note      none
 */
void HAL_DCMI_MspDeInit(DCMI_HandleTypeDef* hdcmi)
{
    DMA_HandleTypeDef *dma_handle;
    
    /* disable dcmi clock */
    __HAL_RCC_DCMI_CLK_DISABLE();
    
    /* deinit dcmi gpio */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4 | GPIO_PIN_6);
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6 | GPIO_PIN_7);
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6 | GPIO_PIN_7);
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);
    
    /* get dma handle */
    dma_handle = dcmi_get_dma_handle();
    
    /* disable dma */
    (void)HAL_DMA_DeInit(dma_handle);
    
    /* disable dcmi interrupt */
    HAL_NVIC_DisableIRQ(DCMI_IRQn);
    
    /* disable dma interrupt */
    HAL_NVIC_DisableIRQ(DMA2_Stream1_IRQn); 
}

/**
 * @}
 */
