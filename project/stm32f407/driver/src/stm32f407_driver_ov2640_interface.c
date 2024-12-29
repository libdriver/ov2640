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
 * @file      stm32f407_driver_ov2640_interface.c
 * @brief     stm32f407 driver ov2640 interface source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2023-11-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2023/11/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_ov2640_interface.h"
#include "delay.h"
#include "uart.h"
#include "iic.h"
#include "wire.h"
#include <stdarg.h>

/**
 * @brief  interface sccb bus init
 * @return status code
 *         - 0 success
 *         - 1 sccb init failed
 * @note   none
 */
uint8_t ov2640_interface_sccb_init(void)
{
    return iic_init();
}

/**
 * @brief  interface sccb bus deinit
 * @return status code
 *         - 0 success
 *         - 1 sccb deinit failed
 * @note   none
 */
uint8_t ov2640_interface_sccb_deinit(void)
{
    return iic_deinit();
}

/**
 * @brief      interface sccb bus read
 * @param[in]  addr sccb device write address
 * @param[in]  reg sccb register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t ov2640_interface_sccb_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    return iic_read(addr, reg, buf, len);
}

/**
 * @brief     interface sccb bus write
 * @param[in] addr sccb device write address
 * @param[in] reg sccb register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t ov2640_interface_sccb_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    return iic_write(addr, reg, buf, len);
}

/**
 * @brief  interface power down init
 * @return status code
 *         - 0 success
 *         - 1 power down init failed
 * @note   none
 */
uint8_t ov2640_interface_power_down_init(void)
{
    return wire_init();
}

/**
 * @brief  interface power down deinit
 * @return status code
 *         - 0 success
 *         - 1 power down deinit failed
 * @note   none
 */
uint8_t ov2640_interface_power_down_deinit(void)
{
    return wire_deinit();
}

/**
 * @brief     interface power down write
 * @param[in] level set level
 * @return    status code
 *            - 0 success
 *            - 1 power down write failed
 * @note      none
 */
uint8_t ov2640_interface_power_down_write(uint8_t level)
{
    return wire_write(level);
}

/**
 * @brief  interface reset init
 * @return status code
 *         - 0 success
 *         - 1 reset init failed
 * @note   none
 */
uint8_t ov2640_interface_reset_init(void)
{
    return wire_clock_init();
}

/**
 * @brief  interface reset deinit
 * @return status code
 *         - 0 success
 *         - 1 reset deinit failed
 * @note   none
 */
uint8_t ov2640_interface_reset_deinit(void)
{
    return wire_clock_deinit();
}

/**
 * @brief     interface reset write
 * @param[in] level set level
 * @return    status code
 *            - 0 success
 *            - 1 reset write failed
 * @note      none
 */
uint8_t ov2640_interface_reset_write(uint8_t level)
{
    return wire_clock_write(level);
}

/**
 * @brief     interface delay ms
 * @param[in] ms time
 * @note      none
 */
void ov2640_interface_delay_ms(uint32_t ms)
{
    delay_ms(ms);
}

/**
 * @brief     interface print format data
 * @param[in] fmt format data
 * @note      none
 */
void ov2640_interface_debug_print(const char *const fmt, ...)
{
    char str[256];
    uint16_t len;
    va_list args;
    
    memset((char *)str, 0, sizeof(char) * 256); 
    va_start(args, fmt);
    vsnprintf((char *)str, 255, (char const *)fmt, args);
    va_end(args);
    
    len = strlen((char *)str);
    (void)uart_write((uint8_t *)str, len);
}
