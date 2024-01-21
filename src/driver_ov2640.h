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
 * @file      driver_ov2640.h
 * @brief     driver ov2640 header file
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

#ifndef DRIVER_OV2640_H
#define DRIVER_OV2640_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ov2640_driver ov2640 driver function
 * @brief    ov2640 driver modules
 * @{
 */

/**
 * @addtogroup ov2640_sensor_driver
 * @{
 */

/**
 * @brief ov2640 bool enumeration definition
 */
typedef enum
{
    OV2640_BOOL_FALSE = 0x00,        /**< false */
    OV2640_BOOL_TRUE  = 0x01,        /**< true */
} ov2640_bool_t;

/**
 * @brief ov2640 dummy frame enumeration definition
 */
typedef enum
{
    OV2640_DUMMY_FRAME_NONE = 0x00,        /**< none dummy frame */
    OV2640_DUMMY_FRAME_1    = 0x01,        /**< 1 dummy frame */
    OV2640_DUMMY_FRAME_3    = 0x02,        /**< 3 dummy frame */
    OV2640_DUMMY_FRAME_7    = 0x03,        /**< 7 dummy frame */
} ov2640_dummy_frame_t;

/**
 * @brief ov2640 mode enumeration definition
 */
typedef enum
{
    OV2640_MODE_NORMAL  = 0x00,        /**< normal mode */
    OV2640_MODE_STANDBY = 0x01,        /**< standby mode */
} ov2640_mode_t;

/**
 * @brief ov2640 band enumeration definition
 */
typedef enum
{
    OV2640_BAND_60HZ = 0x00,        /**< 60hz */
    OV2640_BAND_50HZ = 0x01,        /**< 50hz */
} ov2640_band_t;

/**
 * @brief ov2640 pin status enumeration definition
 */
typedef enum
{
    OV2640_PIN_STATUS_TRI_STATE = 0x00,        /**< tri state */
    OV2640_PIN_STATUS_LAST_STATE = 0x01,       /**< last state */
} ov2640_pin_status_t;

/**
 * @brief ov2640 output drive enumeration definition
 */
typedef enum
{
    OV2640_OUTPUT_DRIVE_1_CAPABILITY = 0x00,        /**< 1 capability */
    OV2640_OUTPUT_DRIVE_3_CAPABILITY = 0x01,        /**< 3 capability */
    OV2640_OUTPUT_DRIVE_2_CAPABILITY = 0x02,        /**< 2 capability */
    OV2640_OUTPUT_DRIVE_4_CAPABILITY = 0x03,        /**< 4 capability */
} ov2640_output_drive_t;

/**
 * @brief ov2640 resolution enumeration definition
 */
typedef enum
{
    OV2640_RESOLUTION_UXGA = 0x00,        /**< uxga mode */
    OV2640_RESOLUTION_CIF  = 0x01,        /**< cif mode */
    OV2640_RESOLUTION_SVGA = 0x04,        /**< svga mode */
} ov2640_resolution_t;

/**
 * @brief ov2640 control enumeration definition
 */
typedef enum
{
    OV2640_CONTROL_MANUAL = 0x00,        /**< manual */
    OV2640_CONTROL_AUTO   = 0x01,        /**< auto */
} ov2640_control_t;

/**
 * @brief ov2640 agc gain enumeration definition
 */
typedef enum
{
    OV2640_AGC_2X   = 0x00,        /**< 2x */
    OV2640_AGC_4X   = 0x01,        /**< 4x */
    OV2640_AGC_8X   = 0x02,        /**< 8x */
    OV2640_AGC_16X  = 0x03,        /**< 16x */
    OV2640_AGC_32X  = 0x04,        /**< 32x */
    OV2640_AGC_64X  = 0x05,        /**< 64x */
    OV2640_AGC_128X = 0x06,        /**< 128x */
} ov2640_agc_gain_t;

/**
 * @brief ov2640 edge enumeration definition
 */
typedef enum
{
    OV2640_EDGE_FALLING = 0x00,        /**< falling */
    OV2640_EDGE_RISING  = 0x01,        /**< rising */
} ov2640_edge_t;

/**
 * @brief ov2640 polarity enumeration definition
 */
typedef enum
{
    OV2640_POLARITY_POSITIVE = 0x00,        /**< positive */
    OV2640_POLARITY_NEGATIVE = 0x01,        /**< negative */
} ov2640_polarity_t;

/**
 * @brief ov2640 pclk enumeration definition
 */
typedef enum
{
    OV2640_PCLK_NO_EFFECT = 0x00,        /**< no effect */
    OV2640_PCLK_DIVIDE_2  = 0x01,        /**< divide by 2 */
    OV2640_PCLK_DIVIDE_4  = 0x02,        /**< divide by 4 */
} ov2640_pclk_t;

/**
 * @}
 */

/**
 * @addtogroup ov2640_dsp_driver
 * @{
 */

/**
 * @brief ov2640 dvp output format enumeration definition
 */
typedef enum
{
    OV2640_DVP_OUTPUT_FORMAT_YUV422 = 0x00,        /**< yuv422 */
    OV2640_DVP_OUTPUT_FORMAT_RAW10  = 0x01,        /**< dvp raw10 */
    OV2640_DVP_OUTPUT_FORMAT_RGB565 = 0x02,        /**< rgb565 */
} ov2640_dvp_output_format_t;

/**
 * @brief ov2640 href timing enumeration definition
 */
typedef enum
{
    OV2640_HREF_TIMING_SENSOR = 0x00,        /**< href is same as sensor */
    OV2640_HREF_TIMING_VSYNC  = 0x01,        /**< href vsync */
} ov2640_href_timing_t;

/**
 * @brief ov2640 byte sawp enumeration definition
 */
typedef enum
{
    OV2640_BYTE_SWAP_YUYV = 0x00,        /**< high byte first */
    OV2640_BYTE_SWAP_UVUV = 0x01,        /**< low byte first */
} ov2640_byte_swap_t;

/**
 * @brief ov2640 reset enumeration definition
 */
typedef enum
{
    OV2640_RESET_MICROCONTROLLER = 6,        /**< microcontroller reset */
    OV2640_RESET_SCCB            = 5,        /**< sccb reset */
    OV2640_RESET_JPEG            = 4,        /**< jpeg reset */
    OV2640_RESET_DVP             = 2,        /**< dvp reset */
    OV2640_RESET_IPU             = 1,        /**< ipu reset */
    OV2640_RESET_CIF             = 0,        /**< cif reset */
} ov2640_reset_t;

/**
 * @brief ov2640 bist enumeration definition
 */
typedef enum
{
    OV2640_BIST_MICROCONTROLLER_RESET = 7,        /**< microcontroller reset */
    OV2640_BIST_BOOT_ROM              = 6,        /**< boot rom select */
    OV2640_BIST_RW_1_ERROR_12K_BYTE   = 5,        /**< r/w 1 error for 12k - byte memory */
    OV2640_BIST_RW_0_ERROR_12K_BYTE   = 4,        /**< r/w 0 error for 12k - byte memory */
    OV2640_BIST_RW_1_ERROR_512_BYTE   = 3,        /**< r/w 1 error for 512 - byte memory */
    OV2640_BIST_RW_0_ERROR_512_BYTE   = 2,        /**< r/w 0 error for 512 - byte memory */
    OV2640_BIST_BUSY_OR_SHOT_RESET    = 1,        /**< busy or one shot reset */
    OV2640_BIST_LAUNCH                = 0,        /**< launch bist */
} ov2640_bist_t;

/**
 * @}
 */

/**
 * @addtogroup ov2640_function_driver
 * @{
 */

/**
 * @brief ov2640 light mode enumeration definition
 */
typedef enum
{
    OV2640_LIGHT_MODE_AUTO   = 0x1,        /**< auto */
    OV2640_LIGHT_MODE_SUNNY  = 0x2,        /**< sunny */
    OV2640_LIGHT_MODE_CLOUDY = 0x3,        /**< cloudy */
    OV2640_LIGHT_MODE_OFFICE = 0x4,        /**< office */
    OV2640_LIGHT_MODE_HOME   = 0x5,        /**< home */
} ov2640_light_mode_t;

/**
 * @brief ov2640 color saturation enumeration definition
 */
typedef enum
{
    OV2640_COLOR_SATURATION_POSITIVE_2 = 0x1,     /**< saturation +2 */
    OV2640_COLOR_SATURATION_POSITIVE_1 = 0x2,     /**< saturation +1 */
    OV2640_COLOR_SATURATION_0          = 0x3,     /**< saturation 0 */
    OV2640_COLOR_SATURATION_NEGATIVE_1 = 0x4,     /**< saturation -1 */
    OV2640_COLOR_SATURATION_NEGATIVE_2 = 0x5,     /**< saturation -2 */
} ov2640_color_saturation_t;

/**
 * @brief ov2640 brightness enumeration definition
 */
typedef enum
{
    OV2640_BRIGHTNESS_POSITIVE_2 = 0x1,     /**< brightness +2 */
    OV2640_BRIGHTNESS_POSITIVE_1 = 0x2,     /**< brightness +1 */
    OV2640_BRIGHTNESS_0          = 0x3,     /**< brightness 0 */
    OV2640_BRIGHTNESS_NEGATIVE_1 = 0x4,     /**< brightness -1 */
    OV2640_BRIGHTNESS_NEGATIVE_2 = 0x5,     /**< brightness -2 */
} ov2640_brightness_t;

/**
 * @brief ov2640 contrast enumeration definition
 */
typedef enum
{
    OV2640_CONTRAST_POSITIVE_2 = 0x1,     /**< contrast +2 */
    OV2640_CONTRAST_POSITIVE_1 = 0x2,     /**< contrast +1 */
    OV2640_CONTRAST_0          = 0x3,     /**< contrast 0 */
    OV2640_CONTRAST_NEGATIVE_1 = 0x4,     /**< contrast -1 */
    OV2640_CONTRAST_NEGATIVE_2 = 0x5,     /**< contrast -2 */
} ov2640_contrast_t;

/**
 * @brief ov2640 special effect enumeration definition
 */
typedef enum
{
    OV2640_SPECIAL_EFFECT_ANTIQUE     = 0x1,     /**< antique */
    OV2640_SPECIAL_EFFECT_BLUISH      = 0x2,     /**< bluish */
    OV2640_SPECIAL_EFFECT_GREENISH    = 0x3,     /**< greenish */
    OV2640_SPECIAL_EFFECT_REDDISH     = 0x4,     /**< reddish */
    OV2640_SPECIAL_EFFECT_BW          = 0x5,     /**< b&w */
    OV2640_SPECIAL_EFFECT_NEGATIVE    = 0x6,     /**< negative */
    OV2640_SPECIAL_EFFECT_BW_NEGATIVE = 0x7,     /**< b&w negative */
    OV2640_SPECIAL_EFFECT_NORMAL      = 0x8,     /**< normal */
} ov2640_special_effect_t;

/**
 * @}
 */

/**
 * @addtogroup ov2640_sensor_driver
 * @{
 */

/**
 * @brief ov2640 handle structure definition
 */
typedef struct ov2640_handle_s
{
    uint8_t (*sccb_init)(void);                                                          /**< point to an sccb_init function address */
    uint8_t (*sccb_deinit)(void);                                                        /**< point to an sccb_deinit function address */
    uint8_t (*sccb_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an sccb_read function address */
    uint8_t (*sccb_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an sccb_write function address */
    uint8_t (*power_down_init)(void);                                                    /**< point to a power_down_init function address */
    uint8_t (*power_down_deinit)(void);                                                  /**< point to a power_down_deinit function address */
    uint8_t (*power_down_write)(uint8_t level);                                          /**< point to a power_down_write function address */
    uint8_t (*reset_init)(void);                                                         /**< point to a reset_init function address */
    uint8_t (*reset_deinit)(void);                                                       /**< point to a reset_deinit function address */
    uint8_t (*reset_write)(uint8_t level);                                               /**< point to a reset_write function address */
    void (*delay_ms)(uint32_t ms);                                                       /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                     /**< point to a debug_print function address */
    uint8_t inited;                                                                      /**< inited flag */
} ov2640_handle_t;

/**
 * @brief ov2640 information structure definition
 */
typedef struct ov2640_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[16];                /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} ov2640_info_t;

/**
 * @}
 */

/**
 * @defgroup ov2640_link_driver ov2640 link driver function
 * @brief    ov2640 link driver modules
 * @ingroup  ov2640_driver
 * @{
 */

/**
 * @brief     initialize ov2640_handle_t structure
 * @param[in] HANDLE points to an ov2640 handle structure
 * @param[in] STRUCTURE is ov2640_handle_t
 * @note      none
 */
#define DRIVER_OV2640_LINK_INIT(HANDLE, STRUCTURE)               memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link sccb_init function
 * @param[in] HANDLE points to an ov2640 handle structure
 * @param[in] FUC points to an sccb_init function address
 * @note      none
 */
#define DRIVER_OV2640_LINK_SCCB_INIT(HANDLE, FUC)                (HANDLE)->sccb_init = FUC

/**
 * @brief     link sccb_deinit function
 * @param[in] HANDLE points to an ov2640 handle structure
 * @param[in] FUC points to an sccb_deinit function address
 * @note      none
 */
#define DRIVER_OV2640_LINK_SCCB_DEINIT(HANDLE, FUC)              (HANDLE)->sccb_deinit = FUC

/**
 * @brief     link sccb_read function
 * @param[in] HANDLE points to an ov2640 handle structure
 * @param[in] FUC points to an sccb_read function address
 * @note      none
 */
#define DRIVER_OV2640_LINK_SCCB_READ(HANDLE, FUC)                (HANDLE)->sccb_read = FUC

/**
 * @brief     link sccb_write function
 * @param[in] HANDLE points to an ov2640 handle structure
 * @param[in] FUC points to an sccb_write function address
 * @note      none
 */
#define DRIVER_OV2640_LINK_SCCB_WRITE(HANDLE, FUC)               (HANDLE)->sccb_write = FUC

/**
 * @brief     link power_down_init function
 * @param[in] HANDLE points to an ov2640 handle structure
 * @param[in] FUC points to an power_down_init function address
 * @note      none
 */
#define DRIVER_OV2640_LINK_POWER_DOWN_INIT(HANDLE, FUC)          (HANDLE)->power_down_init = FUC

/**
 * @brief     link power_down_deinit function
 * @param[in] HANDLE points to an ov2640 handle structure
 * @param[in] FUC points to an power_down_deinit function address
 * @note      none
 */
#define DRIVER_OV2640_LINK_POWER_DOWN_DEINIT(HANDLE, FUC)        (HANDLE)->power_down_deinit = FUC

/**
 * @brief     link power_down_write function
 * @param[in] HANDLE points to an ov2640 handle structure
 * @param[in] FUC points to an power_down_write function address
 * @note      none
 */
#define DRIVER_OV2640_LINK_POWER_DOWN_WRITE(HANDLE, FUC)         (HANDLE)->power_down_write = FUC

/**
 * @brief     link reset_init function
 * @param[in] HANDLE points to an ov2640 handle structure
 * @param[in] FUC points to an reset_init function address
 * @note      none
 */
#define DRIVER_OV2640_LINK_RESET_INIT(HANDLE, FUC)               (HANDLE)->reset_init = FUC

/**
 * @brief     link reset_deinit function
 * @param[in] HANDLE points to an ov2640 handle structure
 * @param[in] FUC points to an reset_deinit function address
 * @note      none
 */
#define DRIVER_OV2640_LINK_RESET_DEINIT(HANDLE, FUC)             (HANDLE)->reset_deinit = FUC

/**
 * @brief     link reset_write function
 * @param[in] HANDLE points to an ov2640 handle structure
 * @param[in] FUC points to an reset_write function address
 * @note      none
 */
#define DRIVER_OV2640_LINK_RESET_WRITE(HANDLE, FUC)              (HANDLE)->reset_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an ov2640 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_OV2640_LINK_DELAY_MS(HANDLE, FUC)                 (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an ov2640 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_OV2640_LINK_DEBUG_PRINT(HANDLE, FUC)              (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup ov2640_sensor_driver ov2640 sensor driver function
 * @brief    ov2640 sensor driver modules
 * @ingroup  ov2640_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an ov2640 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ov2640_info(ov2640_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an ov2640 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 sccb initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 gpio init failed
 *            - 5 hardware reset failed
 *            - 6 soft reset failed
 *            - 7 manufacturer id is invalid
 *            - 8 product id is invalid
 * @note      none
 */
uint8_t ov2640_init(ov2640_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an ov2640 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 soft reset failed
 *            - 5 power down failed
 * @note      none
 */
uint8_t ov2640_deinit(ov2640_handle_t *handle);

/**
 * @brief     table init
 * @param[in] *handle points to an ov2640 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 table init failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_table_init(ov2640_handle_t *handle);

/**
 * @brief     table jpeg init
 * @param[in] *handle points to an ov2640 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 table jpeg init failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_table_jpeg_init(ov2640_handle_t *handle);

/**
 * @brief     table rgb565 init
 * @param[in] *handle points to an ov2640 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 table rgb565 init failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_table_rgb565_init(ov2640_handle_t *handle);

/**
 * @brief     set agc gain
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] gain is the set gain
 * @return    status code
 *            - 0 success
 *            - 1 set agc gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 gain > 0x3FF
 * @note      gain = (bit[7] + 1) * (bit[6] + 1) * 
 *            (bit[5] + 1) * (bit[4] + 1) * (1 + bit[3:0]) / 16
 */
uint8_t ov2640_set_agc_gain(ov2640_handle_t *handle, uint16_t gain);

/**
 * @brief      get agc gain
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *gain points to a gain buffer
 * @return     status code
 *             - 0 success
 *             - 1 get agc gain failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_get_agc_gain(ov2640_handle_t *handle, uint16_t *gain);

/**
 * @brief     set dummy frame
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] frame is the set frame
 * @return    status code
 *            - 0 success
 *            - 1 set dummy frame failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_dummy_frame(ov2640_handle_t *handle, ov2640_dummy_frame_t frame);

/**
 * @brief      get dummy frame
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *frame points to a frame buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dummy frame failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_dummy_frame(ov2640_handle_t *handle, ov2640_dummy_frame_t *frame);

/**
 * @brief     set vertical window line start
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] start is the set start
 * @return    status code
 *            - 0 success
 *            - 1 set vertical window line start failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 start > 0x3FF
 * @note      none
 */
uint8_t ov2640_set_vertical_window_line_start(ov2640_handle_t *handle, uint16_t start);

/**
 * @brief      get vertical window line start
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *start points to a start buffer
 * @return     status code
 *             - 0 success
 *             - 1 get vertical window line start failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_vertical_window_line_start(ov2640_handle_t *handle, uint16_t *start);

/**
 * @brief     set vertical window line end
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] end is the set end
 * @return    status code
 *            - 0 success
 *            - 1 set vertical window line end failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 end > 0x3FF
 * @note      none
 */
uint8_t ov2640_set_vertical_window_line_end(ov2640_handle_t *handle, uint16_t end);

/**
 * @brief      get vertical window line end
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *end points to an end buffer
 * @return     status code
 *             - 0 success
 *             - 1 get vertical window line end failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_vertical_window_line_end(ov2640_handle_t *handle, uint16_t *end);

/**
 * @brief     enable or disable horizontal mirror
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set horizontal mirror failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_horizontal_mirror(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get horizontal mirror status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get horizontal mirror failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_horizontal_mirror(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable vertical flip
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set vertical flip failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_vertical_flip(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get vertical flip status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get vertical flip failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_vertical_flip(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     set aec
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] aec is the set param
 * @return    status code
 *            - 0 success
 *            - 1 set aec failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_aec(ov2640_handle_t *handle, uint16_t aec);

/**
 * @brief      get aec
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *aec points to an aec buffer
 * @return     status code
 *             - 0 success
 *             - 1 get aec failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_aec(ov2640_handle_t *handle, uint16_t *aec);

/**
 * @brief     set frame exposure pre charge row number
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] num is the pre charge row number
 * @return    status code
 *            - 0 success
 *            - 1 set frame exposure pre charge row number failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_frame_exposure_pre_charge_row_number(ov2640_handle_t *handle, uint8_t num);

/**
 * @brief      get frame exposure pre charge row number
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *num points to a pre charge row number buffer
 * @return     status code
 *             - 0 success
 *             - 1 get frame exposure pre charge row number failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_frame_exposure_pre_charge_row_number(ov2640_handle_t *handle, uint8_t *num);

/**
 * @brief     set mode
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] mode is the set mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_mode(ov2640_handle_t *handle, ov2640_mode_t mode);

/**
 * @brief      get mode
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *mode points to a mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_mode(ov2640_handle_t *handle, ov2640_mode_t *mode);

/**
 * @brief     enable or disable power reset pin remap
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set power reset pin remap failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_power_reset_pin_remap(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get power reset pin remap status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get power reset pin remap failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_power_reset_pin_remap(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     set output drive
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] select is the output drive
 * @return    status code
 *            - 0 success
 *            - 1 set output drive failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_output_drive(ov2640_handle_t *handle, ov2640_output_drive_t select);

/**
 * @brief      get output drive
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *select points to an output drive buffer
 * @return     status code
 *             - 0 success
 *             - 1 get output drive failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_output_drive(ov2640_handle_t *handle, ov2640_output_drive_t *select);

/**
 * @brief     set band
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] band is the set band
 * @return    status code
 *            - 0 success
 *            - 1 set band failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_band(ov2640_handle_t *handle, ov2640_band_t band);

/**
 * @brief      get band
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *band points to a band buffer
 * @return     status code
 *             - 0 success
 *             - 1 get band failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_band(ov2640_handle_t *handle, ov2640_band_t *band);

/**
 * @brief     enable or disable auto band
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set auto band failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_auto_band(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get auto band status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get auto band failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_auto_band(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable live video after snapshot
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set live video after snapshot failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_live_video_after_snapshot(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get live video after snapshot status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get live video after snapshot failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_live_video_after_snapshot(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     set clock output power down pin status
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] status is the set pin status
 * @return    status code
 *            - 0 success
 *            - 1 set clock output power down pin status failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_clock_output_power_down_pin_status(ov2640_handle_t *handle, ov2640_pin_status_t status);

/**
 * @brief      get clock output power down pin status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *status points to a pin status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get clock output power down pin status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_clock_output_power_down_pin_status(ov2640_handle_t *handle, ov2640_pin_status_t *status);

/**
 * @brief     enable or disable double clock rate
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set clock rate double failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_clock_rate_double(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get clock rate double status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get clock rate double failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_clock_rate_double(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     set clock divider
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] divider is the set divider
 * @return    status code
 *            - 0 success
 *            - 1 set clock divider failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 divider > 0x3F
 * @note      none
 */
uint8_t ov2640_set_clock_divider(ov2640_handle_t *handle, uint8_t divider);

/**
 * @brief      get clock divider
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *divider points to a divider buffer
 * @return     status code
 *             - 0 success
 *             - 1 get clock divider failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_clock_divider(ov2640_handle_t *handle, uint8_t *divider);

/**
 * @brief     soft reset
 * @param[in] *handle points to an ov2640 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 soft reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_soft_reset(ov2640_handle_t *handle);

/**
 * @brief     set resolution
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] resolution is the set resolution
 * @return    status code
 *            - 0 success
 *            - 1 set resolution failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_resolution(ov2640_handle_t *handle, ov2640_resolution_t resolution);

/**
 * @brief      get resolution
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *resolution points to a resolution buffer
 * @return     status code
 *             - 0 success
 *             - 1 get resolution failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_resolution(ov2640_handle_t *handle, ov2640_resolution_t *resolution);

/**
 * @brief     enable or disable zoom
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set zoom failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_zoom(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get zoom status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get zoom failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_zoom(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable color bar test
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set color bar test failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_color_bar_test(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get color bar test status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get color bar test failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_color_bar_test(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable band filter
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set band filter failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_band_filter(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get band filter status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get band filter failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_band_filter(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     set agc control
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] control is the set control
 * @return    status code
 *            - 0 success
 *            - 1 set agc control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_agc_control(ov2640_handle_t *handle, ov2640_control_t control);

/**
 * @brief      get agc control
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *control points to a control buffer
 * @return     status code
 *             - 0 success
 *             - 1 get agc control failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_agc_control(ov2640_handle_t *handle, ov2640_control_t *control);

/**
 * @brief     set exposure control
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] control is the set control
 * @return    status code
 *            - 0 success
 *            - 1 set exposure control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_exposure_control(ov2640_handle_t *handle, ov2640_control_t control);

/**
 * @brief      get exposure control
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *control points to a control buffer
 * @return     status code
 *             - 0 success
 *             - 1 get exposure control failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_exposure_control(ov2640_handle_t *handle, ov2640_control_t *control);

/**
 * @brief     set agc
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] agc is the set agc
 * @return    status code
 *            - 0 success
 *            - 1 set agc failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_agc_gain_ceiling(ov2640_handle_t *handle, ov2640_agc_gain_t agc);

/**
 * @brief      get agc
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *agc points to an agc buffer
 * @return     status code
 *             - 0 success
 *             - 1 get agc failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_get_agc_gain_ceiling(ov2640_handle_t *handle, ov2640_agc_gain_t *agc);

/**
 * @brief     enable or disable chsync href swap
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set chsync href swap failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_chsync_href_swap(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get chsync href swap status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get chsync href swap failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_chsync_href_swap(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable href chsync swap
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set href chsync swap failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_href_chsync_swap(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get href chsync swap status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get href chsync swap failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_href_chsync_swap(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable pclk output qualified by href
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set pclk output qualified by href failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_pclk_output_qualified_by_href(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get pclk output qualified by href status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get pclk output qualified by href failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_pclk_output_qualified_by_href(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     set pclk edge
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] edge is the pclk edge
 * @return    status code
 *            - 0 success
 *            - 1 set pclk edge failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_pclk_edge(ov2640_handle_t *handle, ov2640_edge_t edge);

/**
 * @brief      get pclk edge
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *edge points to an edge buffer
 * @return     status code
 *             - 0 success
 *             - 1 get pclk edge failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_pclk_edge(ov2640_handle_t *handle, ov2640_edge_t *edge);

/**
 * @brief     set href polarity
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] polarity is the set polarity
 * @return    status code
 *            - 0 success
 *            - 1 set href polarity failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_href_polarity(ov2640_handle_t *handle, ov2640_polarity_t polarity);

/**
 * @brief      get href polarity
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *polarity points to a polarity buffer
 * @return     status code
 *             - 0 success
 *             - 1 get href polarity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_href_polarity(ov2640_handle_t *handle, ov2640_polarity_t *polarity);

/**
 * @brief     set vsync polarity
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] polarity is the set polarity
 * @return    status code
 *            - 0 success
 *            - 1 set vsync polarity failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_vsync_polarity(ov2640_handle_t *handle, ov2640_polarity_t polarity);

/**
 * @brief      get vsync polarity
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *polarity points to a polarity buffer
 * @return     status code
 *             - 0 success
 *             - 1 get vsync polarity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_vsync_polarity(ov2640_handle_t *handle, ov2640_polarity_t *polarity);

/**
 * @brief     set hsync polarity
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] polarity is the set polarity
 * @return    status code
 *            - 0 success
 *            - 1 set hsync polarity failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_hsync_polarity(ov2640_handle_t *handle, ov2640_polarity_t polarity);

/**
 * @brief      get hsync polarity
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *polarity points to a polarity buffer
 * @return     status code
 *             - 0 success
 *             - 1 get hsync polarity failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_hsync_polarity(ov2640_handle_t *handle, ov2640_polarity_t *polarity);

/**
 * @brief     set luminance signal high range
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] range is the set range
 * @return    status code
 *            - 0 success
 *            - 1 set luminance signal high range failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_luminance_signal_high_range(ov2640_handle_t *handle, uint8_t range);

/**
 * @brief      get luminance signal high range
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *range points to a range buffer
 * @return     status code
 *             - 0 success
 *             - 1 get luminance signal high range failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_luminance_signal_high_range(ov2640_handle_t *handle, uint8_t *range);

/**
 * @brief     set luminance signal low range
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] range is the set range
 * @return    status code
 *            - 0 success
 *            - 1 set luminance signal low range failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_luminance_signal_low_range(ov2640_handle_t *handle, uint8_t range);

/**
 * @brief      get luminance signal low range
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *range points to a range buffer
 * @return     status code
 *             - 0 success
 *             - 1 get luminance signal low range failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_luminance_signal_low_range(ov2640_handle_t *handle, uint8_t *range);

/**
 * @brief     set fast mode large step range
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] high_threshold is the set high threshold
 * @param[in] low_threshold is the set low threshold
 * @return    status code
 *            - 0 success
 *            - 1 set fast mode large step range failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 high_threshold > 0xF
 *            - 5 low_threshold > 0xF
 * @note      none
 */
uint8_t ov2640_set_fast_mode_large_step_range(ov2640_handle_t *handle, uint8_t high_threshold, uint8_t low_threshold);

/**
 * @brief      get fast mode large step range
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *high_threshold points to a high threshold buffer
 * @param[out] *low_threshold points to a low threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get fast mode large step range failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_fast_mode_large_step_range(ov2640_handle_t *handle, uint8_t *high_threshold, uint8_t *low_threshold);

/**
 * @brief     set line interval adjust
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] adjust is the set line interval adjust
 * @return    status code
 *            - 0 success
 *            - 1 set line interval adjust failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 adjust > 0xFFF
 * @note      none
 */
uint8_t ov2640_set_line_interval_adjust(ov2640_handle_t *handle, uint16_t adjust);

/**
 * @brief      get line interval adjust
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *adjust points to a line interval adjust buffer
 * @return     status code
 *             - 0 success
 *             - 1 get line interval adjust failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_line_interval_adjust(ov2640_handle_t *handle, uint16_t *adjust);

/**
 * @brief     set hsync position and width end point
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] position is the set position
 * @return    status code
 *            - 0 success
 *            - 1 set hsync position and width end point failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 position > 0x3FF
 * @note      none
 */
uint8_t ov2640_set_hsync_position_and_width_end_point(ov2640_handle_t *handle, uint16_t position);

/**
 * @brief      get hsync position and width end point
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *position points to a position buffer
 * @return     status code
 *             - 0 success
 *             - 1 get hsync position and width end point failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_hsync_position_and_width_end_point(ov2640_handle_t *handle, uint16_t *position);

/**
 * @brief     set hsync position and width start point
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] position is the set position
 * @return    status code
 *            - 0 success
 *            - 1 set hsync position and width start point failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 position > 0x3FF
 * @note      none
 */
uint8_t ov2640_set_hsync_position_and_width_start_point(ov2640_handle_t *handle, uint16_t position);

/**
 * @brief      get hsync position and width start point
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *position points to a position buffer
 * @return     status code
 *             - 0 success
 *             - 1 get hsync position and width start point failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_hsync_position_and_width_start_point(ov2640_handle_t *handle, uint16_t *position);

/**
 * @brief     set vsync pulse width
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] width is the set width
 * @return    status code
 *            - 0 success
 *            - 1 set vsync pulse width failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_vsync_pulse_width(ov2640_handle_t *handle, uint16_t width);

/**
 * @brief      get vsync pulse width
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *width points to a width buffer
 * @return     status code
 *             - 0 success
 *             - 1 get vsync pulse width failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_vsync_pulse_width(ov2640_handle_t *handle, uint16_t *width);

/**
 * @brief     set luminance average
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] average is the luminance average
 * @return    status code
 *            - 0 success
 *            - 1 set luminance average failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_luminance_average(ov2640_handle_t *handle, uint8_t average);

/**
 * @brief      get luminance average
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *average points to a luminance average buffer
 * @return     status code
 *             - 0 success
 *             - 1 get luminance average failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_luminance_average(ov2640_handle_t *handle, uint8_t *average);

/**
 * @brief     set horizontal window start
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] start is the horizontal window start
 * @return    status code
 *            - 0 success
 *            - 1 set horizontal window start failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 start > 0x7FF
 * @note      none
 */
uint8_t ov2640_set_horizontal_window_start(ov2640_handle_t *handle, uint16_t start);

/**
 * @brief      get horizontal window start
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *start points to a horizontal window start buffer
 * @return     status code
 *             - 0 success
 *             - 1 get horizontal window start failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_horizontal_window_start(ov2640_handle_t *handle, uint16_t *start);

/**
 * @brief     set horizontal window end
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] end is the horizontal window end
 * @return    status code
 *            - 0 success
 *            - 1 set horizontal window end failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 end > 0x7FF
 * @note      none
 */
uint8_t ov2640_set_horizontal_window_end(ov2640_handle_t *handle, uint16_t end);

/**
 * @brief      get horizontal window end
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *end points to a horizontal window end buffer
 * @return     status code
 *             - 0 success
 *             - 1 get horizontal window end failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_horizontal_window_end(ov2640_handle_t *handle, uint16_t *end);

/**
 * @brief     set pclk
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] pclk is the set pclk
 * @return    status code
 *            - 0 success
 *            - 1 set pclk failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_pclk(ov2640_handle_t *handle, ov2640_pclk_t pclk);

/**
 * @brief      get pclk
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *pclk points to a pclk buffer
 * @return     status code
 *             - 0 success
 *             - 1 get pclk failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_pclk(ov2640_handle_t *handle, ov2640_pclk_t *pclk);

/**
 * @brief     enable or disable zoom window horizontal start point
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set zoom window horizontal start point failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_zoom_window_horizontal_start_point(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get zoom window horizontal start point status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get zoom window horizontal start point failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_zoom_window_horizontal_start_point(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     set frame length adjustment
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] frame is the set frame
 * @return    status code
 *            - 0 success
 *            - 1 set frame length adjustment failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 frame > 0x3FF
 * @note      none
 */
uint8_t ov2640_set_frame_length_adjustment(ov2640_handle_t *handle, uint16_t frame);

/**
 * @brief      get frame length adjustment
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *frame points to a frame buffer
 * @return     status code
 *             - 0 success
 *             - 1 get frame length adjustment failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_frame_length_adjustment(ov2640_handle_t *handle, uint16_t *frame);

/**
 * @brief     set zoom mode vertical window start point
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] point is the set point
 * @return    status code
 *            - 0 success
 *            - 1 set zoom mode vertical window start point failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 point > 0x3FF
 * @note      none
 */
uint8_t ov2640_set_zoom_mode_vertical_window_start_point(ov2640_handle_t *handle, uint16_t point);

/**
 * @brief      get zoom mode vertical window start point
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *point points to a point buffer
 * @return     status code
 *             - 0 success
 *             - 1 get zoom mode vertical window start point failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_zoom_mode_vertical_window_start_point(ov2640_handle_t *handle, uint16_t *point);

/**
 * @brief     set flash light
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] control is the set control
 * @return    status code
 *            - 0 success
 *            - 1 set flash light failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_flash_light(ov2640_handle_t *handle, uint8_t control);

/**
 * @brief      get flash light
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *control points to a control buffer
 * @return     status code
 *             - 0 success
 *             - 1 get flash light failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_flash_light(ov2640_handle_t *handle, uint8_t *control);

/**
 * @brief     set 50hz banding aec
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] aec is the set aec
 * @return    status code
 *            - 0 success
 *            - 1 set 50hz banding aec failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 aec > 0x3FF
 * @note      none
 */
uint8_t ov2640_set_50hz_banding_aec(ov2640_handle_t *handle, uint16_t aec);

/**
 * @brief      get 50hz banding aec
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *aec points to an aec buffer
 * @return     status code
 *             - 0 success
 *             - 1 get 50hz banding aec failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_50hz_banding_aec(ov2640_handle_t *handle, uint16_t *aec);

/**
 * @brief     set 60hz banding aec
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] aec is the set aec
 * @return    status code
 *            - 0 success
 *            - 1 set 60hz banding aec failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 aec > 0x3FF
 * @note      none
 */
uint8_t ov2640_set_60hz_banding_aec(ov2640_handle_t *handle, uint16_t aec);

/**
 * @brief      get 60hz banding aec
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *aec points to an aec buffer
 * @return     status code
 *             - 0 success
 *             - 1 get 60hz banding aec failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_60hz_banding_aec(ov2640_handle_t *handle, uint16_t *aec);

/**
 * @brief     set 16 zone average weight option
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] avg is the set avg
 * @return    status code
 *            - 0 success
 *            - 1 set 16 zone average weight option failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_16_zone_average_weight_option(ov2640_handle_t *handle, uint32_t avg);

/**
 * @brief      get 16 zone average weight option
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *avg points to an avg buffer
 * @return     status code
 *             - 0 success
 *             - 1 get 16 zone average weight option failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_16_zone_average_weight_option(ov2640_handle_t *handle, uint32_t *avg);

/**
 * @brief     set histogram algorithm low level
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] level is the low level
 * @return    status code
 *            - 0 success
 *            - 1 set histogram algorithm low level failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_histogram_algorithm_low_level(ov2640_handle_t *handle, uint8_t level);

/**
 * @brief      get histogram algorithm low level
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *level points to a low level buffer
 * @return     status code
 *             - 0 success
 *             - 1 get histogram algorithm low level failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_histogram_algorithm_low_level(ov2640_handle_t *handle, uint8_t *level);

/**
 * @brief     set histogram algorithm high level
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] level is the high level
 * @return    status code
 *            - 0 success
 *            - 1 set histogram algorithm high level failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_histogram_algorithm_high_level(ov2640_handle_t *handle, uint8_t level);

/**
 * @brief      get histogram algorithm high level
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *level points to a high level buffer
 * @return     status code
 *             - 0 success
 *             - 1 get histogram algorithm high level failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_histogram_algorithm_high_level(ov2640_handle_t *handle, uint8_t *level);

/**
 * @}
 */

/**
 * @defgroup ov2640_dsp_driver ov2640 dsp driver function
 * @brief    ov2640 dsp driver modules
 * @ingroup  ov2640_driver
 * @{
 */

/**
 * @brief     enable or disable dsp bypass
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set dsp bypass failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_dsp_bypass(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get dsp bypass status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dsp bypass failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_dsp_bypass(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable auto_mode
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set auto mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_auto_mode(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get auto mode status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get auto mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_auto_mode(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     set dvp pclk
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] pclk is the set pclk
 * @return    status code
 *            - 0 success
 *            - 1 set dvp pclk failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 pclk > 0x7F
 * @note      none
 */
uint8_t ov2640_set_dvp_pclk(ov2640_handle_t *handle, uint8_t pclk);

/**
 * @brief      get dvp pclk
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *pclk points to a pclk buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dvp pclk failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_dvp_pclk(ov2640_handle_t *handle, uint8_t *pclk);

/**
 * @brief     enable or disable dvp y8
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set dvp y8 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_dvp_y8(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get dvp y8 status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dvp y8 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_dvp_y8(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable jpeg output
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set jpeg output failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_jpeg_output(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get jpeg output status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get jpeg output failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_jpeg_output(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     set dvp output format
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] format is the dvp output format
 * @return    status code
 *            - 0 success
 *            - 1 set dvp output format failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_dvp_output_format(ov2640_handle_t *handle, ov2640_dvp_output_format_t format);

/**
 * @brief      get dvp output format
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *format is the dvp output format
 * @return     status code
 *             - 0 success
 *             - 1 get dvp output format failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_dvp_output_format(ov2640_handle_t *handle, ov2640_dvp_output_format_t *format);

/**
 * @brief     set dvp jpeg output href timing
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] timing is the href timing
 * @return    status code
 *            - 0 success
 *            - 1 set dvp jpeg output href timing failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_dvp_jpeg_output_href_timing(ov2640_handle_t *handle, ov2640_href_timing_t timing);

/**
 * @brief      get dvp jpeg output href timing
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *timing points to a href timing buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dvp jpeg output href timing failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_dvp_jpeg_output_href_timing(ov2640_handle_t *handle, ov2640_href_timing_t *timing);

/**
 * @brief     set byte swap
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] byte_swap is the byte swap
 * @return    status code
 *            - 0 success
 *            - 1 set byte swap failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_byte_swap(ov2640_handle_t *handle, ov2640_byte_swap_t byte_swap);

/**
 * @brief      get byte swap
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *byte_swap points to a byte swap buffer
 * @return     status code
 *             - 0 success
 *             - 1 get byte swap failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_byte_swap(ov2640_handle_t *handle, ov2640_byte_swap_t *byte_swap);

/**
 * @brief     enable or disable reset
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] type is the reset type
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_reset(ov2640_handle_t *handle, ov2640_reset_t type, ov2640_bool_t enable);

/**
 * @brief      get reset status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[in]  type is the reset type
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get reset failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_reset(ov2640_handle_t *handle, ov2640_reset_t type, ov2640_bool_t *enable);

/**
 * @brief     set sccb master speed
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] speed is the sccb master speed
 * @return    status code
 *            - 0 success
 *            - 1 set sccb master speed failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_sccb_master_speed(ov2640_handle_t *handle, uint8_t speed);

/**
 * @brief      get sccb master speed
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *speed points to an sccb master speed buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sccb master speed failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_sccb_master_speed(ov2640_handle_t *handle, uint8_t *speed);

/**
 * @brief     set sccb slave id
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] id is the set slave id
 * @return    status code
 *            - 0 success
 *            - 1 set sccb slave id failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_sccb_slave_id(ov2640_handle_t *handle, uint8_t id);

/**
 * @brief      get sccb slave id
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *id points to a slave id buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sccb slave id failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_sccb_slave_id(ov2640_handle_t *handle, uint8_t *id);

/**
 * @brief     enable or disable address auto increase
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set address auto increase failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_address_auto_increase(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get address auto increase status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get address auto increase failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_address_auto_increase(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable sccb
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set sccb failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_sccb(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get sccb status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sccb failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_sccb(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable sccb master clock delay
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set sccb master clock delay failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_sccb_master_clock_delay(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get sccb master clock delay status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sccb master clock delay failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_sccb_master_clock_delay(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable sccb master access
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set sccb master access failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_sccb_master_access(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get sccb master access status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sccb master access failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_sccb_master_access(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable sensor pass through access
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set sensor pass through access failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_sensor_pass_through_access(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get sensor pass through access status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sensor pass through access failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_sensor_pass_through_access(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable bist
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] bist is the bist type
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set bist failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_bist(ov2640_handle_t *handle, ov2640_bist_t bist, ov2640_bool_t enable);

/**
 * @brief      get bist status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[in]  bist is the bist type
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get bist failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_bist(ov2640_handle_t *handle, ov2640_bist_t bist, ov2640_bool_t *enable);

/**
 * @brief     set program memory pointer address
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] addr is the program memory pointer address
 * @return    status code
 *            - 0 success
 *            - 1 set program memory pointer address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_program_memory_pointer_address(ov2640_handle_t *handle, uint16_t addr);

/**
 * @brief      get program memory pointer address
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *addr points to a program memory pointer address buffer
 * @return     status code
 *             - 0 success
 *             - 1 get program memory pointer address failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_program_memory_pointer_address(ov2640_handle_t *handle, uint16_t *addr);

/**
 * @brief     set program memory pointer access address
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] addr is the program memory pointer access address
 * @return    status code
 *            - 0 success
 *            - 1 set program memory pointer access address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_program_memory_pointer_access_address(ov2640_handle_t *handle, uint8_t addr);

/**
 * @brief      get program memory pointer access address
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *addr points to a program memory pointer access address buffer
 * @return     status code
 *             - 0 success
 *             - 1 get program memory pointer access address failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_program_memory_pointer_access_address(ov2640_handle_t *handle, uint8_t *addr);

/**
 * @brief     set sccb protocol command
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] cmd is the sccb protocol command
 * @return    status code
 *            - 0 success
 *            - 1 set sccb protocol command failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_sccb_protocol_command(ov2640_handle_t *handle, uint8_t cmd);

/**
 * @brief      get sccb protocol command
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *cmd points to an sccb protocol command buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sccb protocol command failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_sccb_protocol_command(ov2640_handle_t *handle, uint8_t *cmd);

/**
 * @brief     set sccb protocol status
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] status is the sccb protocol status
 * @return    status code
 *            - 0 success
 *            - 1 set sccb protocol status failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_sccb_protocol_status(ov2640_handle_t *handle, uint8_t status);

/**
 * @brief      get sccb protocol status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *status points to an sccb protocol status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sccb protocol status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_sccb_protocol_status(ov2640_handle_t *handle, uint8_t *status);

/**
 * @brief     enable or disable cip
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set cip failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_cip(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get cip status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get cip failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_cip(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable dmy
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set dmy failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_dmy(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get dmy status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dmy failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_dmy(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable raw gma
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set raw gma failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_raw_gma(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get raw gma status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get raw gma failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_raw_gma(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable dg
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set dg failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_dg(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get dg status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dg failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_dg(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable awb
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set awb failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_awb(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get awb status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get awb failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_awb(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable awb gain
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set awb gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_awb_gain(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get awb gain status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get awb gain failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_awb_gain(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable lenc
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set lenc failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_lenc(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get lenc status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get lenc failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_lenc(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable pre
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set pre failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_pre(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get pre status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get pre failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_pre(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable aec enable
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set aec enable failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_aec_enable(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get aec enable status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get aec enable failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_aec_enable(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable aec sel
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set aec sel failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_aec_sel(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get aec sel status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get aec sel failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_aec_sel(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable stat sel
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set stat sel failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_stat_sel(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get stat sel status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get stat sel failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_stat_sel(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable vfirst
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set vfirst failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_vfirst(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get vfirst status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get vfirst failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_vfirst(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable yuv422
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set yuv422 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_yuv422(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get yuv422 status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get yuv422 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_yuv422(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable yuv
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set yuv failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_yuv(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get yuv status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get yuv failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_yuv(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable rgb
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set rgb failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_rgb(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get rgb status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get rgb failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_rgb(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable raw
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set raw failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_raw(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get raw status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get raw failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_raw(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable dcw
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set dcw failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_dcw(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get dcw status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dcw failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_dcw(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable sde
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set sde failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_sde(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get sde status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sde failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_sde(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable uv adj
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set uv adj failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_uv_adj(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get uv adj status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get uv adj failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_uv_adj(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable uv avg
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set uv avg failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_uv_avg(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get uv avg status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get uv avg failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_uv_avg(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable cmx
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set cmx failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_cmx(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get cmx status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get cmx failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_cmx(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable bpc
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set bpc failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_bpc(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get bpc status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get bpc failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_bpc(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable wpc
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set wpc failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_wpc(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get wpc status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get wpc failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_wpc(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     set sde indirect register address
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] addr is the set register address
 * @return    status code
 *            - 0 success
 *            - 1 set sde indirect register address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_sde_indirect_register_address(ov2640_handle_t *handle, uint8_t addr);

/**
 * @brief      get sde indirect register address
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *addr points to a register address buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sde indirect register address failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_sde_indirect_register_address(ov2640_handle_t *handle, uint8_t *addr);

/**
 * @brief     set sde indirect register data
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] data is the set data
 * @return    status code
 *            - 0 success
 *            - 1 set sde indirect register data failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_sde_indirect_register_data(ov2640_handle_t *handle, uint8_t data);

/**
 * @brief      get sde indirect register data
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sde indirect register data failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_sde_indirect_register_data(ov2640_handle_t *handle, uint8_t *data);

/**
 * @brief     set image horizontal
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] size is the image horizontal size
 * @return    status code
 *            - 0 success
 *            - 1 set image horizontal failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 size > 0xFFF
 * @note      none
 */
uint8_t ov2640_set_image_horizontal(ov2640_handle_t *handle, uint16_t size);

/**
 * @brief      get image horizontal
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *size points to an image horizontal size buffer
 * @return     status code
 *             - 0 success
 *             - 1 get image horizontal failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_image_horizontal(ov2640_handle_t *handle, uint16_t *size);

/**
 * @brief     set image vertical
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] size is the image vertical size
 * @return    status code
 *            - 0 success
 *            - 1 set image vertical failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 size > 0x7FF
 * @note      none
 */
uint8_t ov2640_set_image_vertical(ov2640_handle_t *handle, uint16_t size);

/**
 * @brief      get image vertical
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *size points to an image vertical size buffer
 * @return     status code
 *             - 0 success
 *             - 1 get image vertical failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_image_vertical(ov2640_handle_t *handle, uint16_t *size);

/**
 * @brief     set quantization scale factor
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] factor is the set quantization scale factor
 * @return    status code
 *            - 0 success
 *            - 1 set quantization scale factor failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_quantization_scale_factor(ov2640_handle_t *handle, uint8_t factor);

/**
 * @brief      get quantization scale factor
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *factor points to a quantization scale factor buffer
 * @return     status code
 *             - 0 success
 *             - 1 get quantization scale factor failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_quantization_scale_factor(ov2640_handle_t *handle, uint8_t *factor);

/**
 * @brief     enable or disable lp dp
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set lp dp failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_lp_dp(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get lp dp status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get lp dp failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_lp_dp(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     enable or disable round
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set round failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_round(ov2640_handle_t *handle, ov2640_bool_t enable);

/**
 * @brief      get round status
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get round failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_round(ov2640_handle_t *handle, ov2640_bool_t *enable);

/**
 * @brief     set vertical divider
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] divider is the set divider
 * @return    status code
 *            - 0 success
 *            - 1 set vertical divider failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 divider > 7
 * @note      none
 */
uint8_t ov2640_set_vertical_divider(ov2640_handle_t *handle, uint8_t divider);

/**
 * @brief      get vertical divider
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *divider points to a divider buffer
 * @return     status code
 *             - 0 success
 *             - 1 get vertical divider failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_vertical_divider(ov2640_handle_t *handle, uint8_t *divider);

/**
 * @brief     set horizontal divider
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] divider is the set divider
 * @return    status code
 *            - 0 success
 *            - 1 set horizontal divider failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 divider > 7
 * @note      none
 */
uint8_t ov2640_set_horizontal_divider(ov2640_handle_t *handle, uint8_t divider);

/**
 * @brief      get horizontal divider
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *divider points to a divider buffer
 * @return     status code
 *             - 0 success
 *             - 1 get horizontal divider failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_horizontal_divider(ov2640_handle_t *handle, uint8_t *divider);

/**
 * @brief     set horizontal size
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] size is the horizontal size
 * @return    status code
 *            - 0 success
 *            - 1 set horizontal size failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 size > 0x3FF
 * @note      none
 */
uint8_t ov2640_set_horizontal_size(ov2640_handle_t *handle, uint16_t size);

/**
 * @brief      get horizontal size
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *size points to a horizontal size buffer
 * @return     status code
 *             - 0 success
 *             - 1 get horizontal size failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_horizontal_size(ov2640_handle_t *handle, uint16_t *size);

/**
 * @brief     set vertical size
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] size is the vertical size
 * @return    status code
 *            - 0 success
 *            - 1 set vertical size failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 size > 0x1FF
 * @note      none
 */
uint8_t ov2640_set_vertical_size(ov2640_handle_t *handle, uint16_t size);

/**
 * @brief      get vertical size
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *size points to a vertical size buffer
 * @return     status code
 *             - 0 success
 *             - 1 get vertical size failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_vertical_size(ov2640_handle_t *handle, uint16_t *size);

/**
 * @brief     set offset x
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] size is the set offset x size
 * @return    status code
 *            - 0 success
 *            - 1 set offset x failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 size > 0x7FF
 * @note      none
 */
uint8_t ov2640_set_offset_x(ov2640_handle_t *handle, uint16_t size);

/**
 * @brief      get offset x
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *size points to a set offset x size buffer
 * @return     status code
 *             - 0 success
 *             - 1 get offset x failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_offset_x(ov2640_handle_t *handle, uint16_t *size);

/**
 * @brief     set offset y
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] size is the set offset y size
 * @return    status code
 *            - 0 success
 *            - 1 set offset y failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 size > 0x7FF
 * @note      none
 */
uint8_t ov2640_set_offset_y(ov2640_handle_t *handle, uint16_t size);

/**
 * @brief      get offset y
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *size points to a set offset y size buffer
 * @return     status code
 *             - 0 success
 *             - 1 get offset y failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_offset_y(ov2640_handle_t *handle, uint16_t *size);

/**
 * @brief     set dp selx
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] size is the set dp selx size
 * @return    status code
 *            - 0 success
 *            - 1 set dp selx failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 size > 0xF
 * @note      none
 */
uint8_t ov2640_set_dp_selx(ov2640_handle_t *handle, uint8_t size);

/**
 * @brief      get dp selx
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *size points to a set dp selx size buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dp selx failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_dp_selx(ov2640_handle_t *handle, uint8_t *size);

/**
 * @brief     set dp sely
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] size is the set dp sely size
 * @return    status code
 *            - 0 success
 *            - 1 set dp sely failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 size > 0xF
 * @note      none
 */
uint8_t ov2640_set_dp_sely(ov2640_handle_t *handle, uint8_t size);

/**
 * @brief      get dp sely
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *size points to a set dp sely size buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dp sely failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_dp_sely(ov2640_handle_t *handle, uint8_t *size);

/**
 * @brief     set output width
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] size is the set output width
 * @return    status code
 *            - 0 success
 *            - 1 set output width failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 size > 0x3FF
 * @note      none
 */
uint8_t ov2640_set_output_width(ov2640_handle_t *handle, uint16_t size);

/**
 * @brief      get output width
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *size points to an output width buffer
 * @return     status code
 *             - 0 success
 *             - 1 get output width failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_output_width(ov2640_handle_t *handle, uint16_t *size);

/**
 * @brief     set output height
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] size is the set output height
 * @return    status code
 *            - 0 success
 *            - 1 set output height failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 size > 0x1FF
 * @note      none
 */
uint8_t ov2640_set_output_height(ov2640_handle_t *handle, uint16_t size);

/**
 * @brief      get output height
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *size points to an output height buffer
 * @return     status code
 *             - 0 success
 *             - 1 get output height failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_output_height(ov2640_handle_t *handle, uint16_t *size);

/**
 * @brief     set zoom speed
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] speed is the zoom speed
 * @return    status code
 *            - 0 success
 *            - 1 set zoom speed failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 speed > 0xF
 * @note      none
 */
uint8_t ov2640_set_zoom_speed(ov2640_handle_t *handle, uint8_t speed);

/**
 * @brief      get zoom speed
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[out] *speed points to a zoom speed buffer
 * @return     status code
 *             - 0 success
 *             - 1 get zoom speed failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_zoom_speed(ov2640_handle_t *handle, uint8_t *speed);

/**
 * @}
 */

/**
 * @defgroup ov2640_function_driver ov2640 function driver function
 * @brief    ov2640 function driver modules
 * @ingroup  ov2640_driver
 * @{
 */

/**
 * @brief     set light mode
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] mode is the light mode
 * @return    status code
 *            - 0 success
 *            - 1 set light mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_light_mode(ov2640_handle_t *handle, ov2640_light_mode_t mode);

/**
 * @brief     set color saturation
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] color saturation is the color saturation
 * @return    status code
 *            - 0 success
 *            - 1 set color saturation failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_color_saturation(ov2640_handle_t *handle, ov2640_color_saturation_t color);

/**
 * @brief     set brightness
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] brightness is the set brightness
 * @return    status code
 *            - 0 success
 *            - 1 set brightness failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_brightness(ov2640_handle_t *handle, ov2640_brightness_t brightness);

/**
 * @brief     set contrast
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] contrast is the set contrast
 * @return    status code
 *            - 0 success
 *            - 1 set contrast failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_contrast(ov2640_handle_t *handle, ov2640_contrast_t contrast);

/**
 * @brief     set special effect
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] effect is the special effect
 * @return    status code
 *            - 0 success
 *            - 1 set special effect failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_special_effect(ov2640_handle_t *handle, ov2640_special_effect_t effect);

/**
 * @}
 */

/**
 * @defgroup ov2640_extend_driver ov2640 extend driver function
 * @brief    ov2640 extend driver modules
 * @ingroup  ov2640_driver
 * @{
 */

/**
 * @brief     set dsp reg
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] reg is the register address
 * @param[in] data is the set data
 * @return    status code
 *            - 0 success
 *            - 1 set dsp failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_dsp_reg(ov2640_handle_t *handle, uint8_t reg, uint8_t data);

/**
 * @brief      get dsp reg
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[in]  reg is the register address
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dsp failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_dsp_reg(ov2640_handle_t *handle, uint8_t reg, uint8_t *data);

/**
 * @brief     set sensor reg
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] reg is the register address
 * @param[in] data is the set data
 * @return    status code
 *            - 0 success
 *            - 1 set sensor failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ov2640_set_sensor_reg(ov2640_handle_t *handle, uint8_t reg, uint8_t data);

/**
 * @brief      get sensor reg
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[in]  reg is the register address
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sensor failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ov2640_get_sensor_reg(ov2640_handle_t *handle, uint8_t reg, uint8_t *data);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
