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
 * @file      dcmi.c
 * @brief     dcmi source file
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

#include "dcmi.h"

/**
 * @brief dcmi var definition
 */
DCMI_HandleTypeDef  g_dcmi_handle;            /**< dcmi handle */
DMA_HandleTypeDef   g_dcmi_dma_handle;        /**< dcmi dma handle */

/**
 * @brief     dcmi init
 * @param[in] jpeg_enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      D0 is PC6
 *            D1 is PC7
 *            D2 is PE0
 *            D3 is PE1
 *            D4 is PE4
 *            D5 is PB6
 *            D6 is PE5
 *            D7 is PE6
 *            PCLK is PA6
 *            HREF is PA4
 *            VSYNC is PB7
 */
uint8_t dcmi_init(uint8_t jpeg_enable)
{
    g_dcmi_handle.Instance = DCMI;
    g_dcmi_handle.Init.SynchroMode = DCMI_SYNCHRO_HARDWARE;
    g_dcmi_handle.Init.PCKPolarity = DCMI_PCKPOLARITY_RISING;
    g_dcmi_handle.Init.VSPolarity = DCMI_VSPOLARITY_LOW;
    g_dcmi_handle.Init.HSPolarity = DCMI_HSPOLARITY_LOW;
    g_dcmi_handle.Init.CaptureRate = DCMI_CR_ALL_FRAME;
    g_dcmi_handle.Init.ExtendedDataMode = DCMI_EXTEND_DATA_8B;
    if (jpeg_enable != 0)
    {
        g_dcmi_handle.Init.JPEGMode = DCMI_JPEG_ENABLE;
    }
    else
    {
        g_dcmi_handle.Init.JPEGMode = DCMI_JPEG_DISABLE;
    }
    
    /* hal dcmi init */
    if (HAL_DCMI_Init(&g_dcmi_handle) != HAL_OK)
    {
        return 1;
    }
    
    /* disable all int */
    __HAL_DCMI_DISABLE_IT(&g_dcmi_handle, DCMI_IT_LINE | DCMI_IT_VSYNC | DCMI_IT_ERR | DCMI_IT_OVR);
    
    /* enable used int */
    __HAL_DCMI_ENABLE_IT(&g_dcmi_handle, DCMI_IT_FRAME | DCMI_IT_ERR | DCMI_IT_OVR);
    
    return 0;
}

/**
 * @brief  dcmi deint
 * @return status code
 *         - 0 success
 *         - 1 deinit
 * @note   none
 */
uint8_t dcmi_deinit(void)
{
    /* dcmi deinit */
    if (HAL_DCMI_DeInit(&g_dcmi_handle) != HAL_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     dcmi snapshot start 
 * @param[in] *buf points to a dcmi buffer
 * @param[in] size is the buffer size
 * @return    status code
 *            - 0 success
 *            - 1 start failed
 * @note      none
 */
uint8_t dcmi_snapshot_start(uint8_t *buf, uint32_t size)
{
    /* dcmi start */
    if (HAL_DCMI_Start_DMA(&g_dcmi_handle, DCMI_MODE_SNAPSHOT, 
       (uint32_t)(buf), size) != HAL_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     dcmi continuous start 
 * @param[in] *buf points to a dcmi buffer
 * @param[in] size is the buffer size
 * @return    status code
 *            - 0 success
 *            - 1 start failed
 * @note      none
 */
uint8_t dcmi_continuous_start(uint8_t *buf, uint32_t size)
{
    /* dcmi start */
    if (HAL_DCMI_Start_DMA(&g_dcmi_handle, DCMI_MODE_CONTINUOUS, 
       (uint32_t)(buf), size) != HAL_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  dcmi stop
 * @return status code
 *         - 0 success
 *         - 1 stop
 * @note   none
 */
uint8_t dcmi_stop(void)
{
    /* stop */
    if (HAL_DCMI_Stop(&g_dcmi_handle) != HAL_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  dcmi suspend
 * @return status code
 *         - 0 success
 *         - 1 suspend
 * @note   none
 */
uint8_t dcmi_suspend(void)
{
    /* suspend */
    if (HAL_DCMI_Suspend(&g_dcmi_handle) != HAL_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  dcmi resume
 * @return status code
 *         - 0 success
 *         - 1 resume
 * @note   none
 */
uint8_t dcmi_resume(void)
{
    /* resume */
    if (HAL_DCMI_Resume(&g_dcmi_handle) != HAL_OK)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  dcmi get the handle
 * @return points to a dcmi handle
 * @note   none
 */
DCMI_HandleTypeDef *dcmi_get_handle(void)
{
    return &g_dcmi_handle;
}

/**
 * @brief  dcmi dma get the handle
 * @return points to a dcmi dma handle
 * @note   none
 */
DMA_HandleTypeDef *dcmi_get_dma_handle(void)
{
    return &g_dcmi_dma_handle;
}
