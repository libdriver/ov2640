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
 * @file      dcmi.h
 * @brief     dcmi header file
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

#ifndef DCMI_H
#define DCMI_H

#include "stm32f4xx_hal.h"

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @defgroup dcmi dcmi function
 * @brief    dcmi function modules
 * @{
 */

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
uint8_t dcmi_init(uint8_t jpeg_enable);

/**
 * @brief  dcmi deint
 * @return status code
 *         - 0 success
 *         - 1 deinit
 * @note   none
 */
uint8_t dcmi_deinit(void);

/**
 * @brief  dcmi stop
 * @return status code
 *         - 0 success
 *         - 1 stop
 * @note   none
 */
uint8_t dcmi_stop(void);

/**
 * @brief  dcmi suspend
 * @return status code
 *         - 0 success
 *         - 1 suspend
 * @note   none
 */
uint8_t dcmi_suspend(void);

/**
 * @brief  dcmi resume
 * @return status code
 *         - 0 success
 *         - 1 resume
 * @note   none
 */
uint8_t dcmi_resume(void);

/**
 * @brief     dcmi snapshot start 
 * @param[in] *buf points to a dcmi buffer
 * @param[in] size is the buffer size
 * @return    status code
 *            - 0 success
 *            - 1 start failed
 * @note      none
 */
uint8_t dcmi_snapshot_start(uint8_t *buf, uint32_t size);

/**
 * @brief     dcmi continuous start 
 * @param[in] *buf points to a dcmi buffer
 * @param[in] size is the buffer size
 * @return    status code
 *            - 0 success
 *            - 1 start failed
 * @note      none
 */
uint8_t dcmi_continuous_start(uint8_t *buf, uint32_t size);

/**
 * @brief  dcmi get the handle
 * @return points to a dcmi handle
 * @note   none
 */
DCMI_HandleTypeDef *dcmi_get_handle(void);

/**
 * @brief  dcmi dma get the handle
 * @return points to a dcmi dma handle
 * @note   none
 */
DMA_HandleTypeDef *dcmi_get_dma_handle(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
