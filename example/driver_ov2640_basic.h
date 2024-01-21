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
 * @file      driver_ov2640_basic.h
 * @brief     driver ov2640 basic header file
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

#ifndef DRIVER_OV2640_BASIC_H
#define DRIVER_OV2640_BASIC_H

#include "driver_ov2640_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ov2640_example_driver ov2640 example driver function
 * @brief    ov2640 example driver modules
 * @ingroup  ov2640_driver
 * @{
 */

/**
 * @brief ov2640 basic example default definition
 */
#define OV2640_BASIC_DEFAULT_CLOCK_RATE_DOUBLE             OV2640_BOOL_FALSE                       /**< disable double rate */
#define OV2640_BASIC_DEFAULT_CLOCK_DIVIDER                 0x00                                    /**< div 0 */
#define OV2640_BASIC_DEFAULT_MODE                          OV2640_MODE_NORMAL                      /**< normal mode */
#define OV2640_BASIC_DEFAULT_POWER_RESET_PIN_REMAP         OV2640_BOOL_FALSE                       /**< disable power reset remap */
#define OV2640_BASIC_DEFAULT_OUTPUT_DRIVE                  OV2640_OUTPUT_DRIVE_2_CAPABILITY        /**< 2 capability */
#define OV2640_BASIC_DEFAULT_HORIZONTAL_MIRROR             OV2640_BOOL_TRUE                        /**< enable horizontal mirror */
#define OV2640_BASIC_DEFAULT_VERTICAL_FLIP                 OV2640_BOOL_TRUE                        /**< enable vertical flip */
#define OV2640_BASIC_DEFAULT_BAND_FILTER                   OV2640_BOOL_TRUE                        /**< enable band filter */
#define OV2640_BASIC_DEFAULT_AGC_CONTROL                   OV2640_CONTROL_AUTO                     /**< auto */
#define OV2640_BASIC_DEFAULT_EXPOSURE_CONTROL              OV2640_CONTROL_AUTO                     /**< auto */
#define OV2640_BASIC_DEFAULT_AGC_GAIN_CEILING              OV2640_AGC_8X                           /**< agc 8x */
#define OV2640_BASIC_DEFAULT_ZOOM_WINDOW_H_START           OV2640_BOOL_FALSE                       /**< disable zoom window horizontal start */
#define OV2640_BASIC_DEFAULT_PIN_STATUS                    OV2640_PIN_STATUS_TRI_STATE             /**< tri state */
#define OV2640_BASIC_DEFAULT_ZOOM_WINDOW_V_START           0x0000                                  /**< 0x0000 */
#define OV2640_BASIC_DEFAULT_LUMINANCE_HIGH                0x40                                    /**< 0x40 */
#define OV2640_BASIC_DEFAULT_LUMINANCE_LOW                 0x38                                    /**< 0x38 */
#define OV2640_BASIC_DEFAULT_FAST_MODE_HIGH                0x8                                     /**< 0x8 */
#define OV2640_BASIC_DEFAULT_FAST_MODE_LOW                 0x2                                     /**< 0x2 */
#define OV2640_BASIC_DEFAULT_FRAME_LENGTH_ADJ              0x0000                                  /**< 0x0000 */
#define OV2640_BASIC_DEFAULT_BAND                          OV2640_BAND_50HZ                        /**< 50Hz */
#define OV2640_BASIC_DEFAULT_AUTO_BAND                     OV2640_BOOL_FALSE                       /**< disable auto band */
#define OV2640_BASIC_DEFAULT_SNAPSHOT                      OV2640_BOOL_FALSE                       /**< disable snapshot */
#define OV2640_BASIC_DEFAULT_HISTO_LOW                     0x70                                    /**< histo low */
#define OV2640_BASIC_DEFAULT_HISTO_HIGH                    0x80                                    /**< histo high */
#define OV2640_BASIC_DEFAULT_BD50_AEC                      0x0CA                                   /**< bd50 aec */
#define OV2640_BASIC_DEFAULT_BD60_AEC                      0x0A8                                   /**< bd60 aec */
#define OV2640_BASIC_DEFAULT_RESOLUTION                    OV2640_RESOLUTION_UXGA                  /**< uxga */
#define OV2640_BASIC_DEFAULT_ZOOM                          OV2640_BOOL_FALSE                       /**< disable zoom */
#define OV2640_BASIC_DEFAULT_COLOR_BAR_TEST                OV2640_BOOL_FALSE                       /**< disable color bar test */
#define OV2640_BASIC_DEFAULT_PCLK                          OV2640_PCLK_NO_EFFECT                   /**< pclk no effect */
#define OV2640_BASIC_DEFAULT_H_WINDOW_START                142                                     /**< 142 */
#define OV2640_BASIC_DEFAULT_H_WINDOW_END                  942                                     /**< 942 */
#define OV2640_BASIC_DEFAULT_V_WINDOW_START                7                                       /**< 7 */
#define OV2640_BASIC_DEFAULT_V_WINDOW_END                  607                                     /**< 607 */
#define OV2640_BASIC_DEFAULT_VSYNC_PULSE_WIDTH             0x0000                                  /**< 0x0000 */
#define OV2640_BASIC_DEFAULT_AGC_GAIN                      0x0000                                  /**< 0x0000 */
#define OV2640_BASIC_DEFAULT_DUMMY_FRAME                   OV2640_DUMMY_FRAME_NONE                 /**< dummy frame none */
#define OV2640_BASIC_DEFAULT_AEC                           0x0CC                                   /**< 0x0CC */
#define OV2640_BASIC_DEFAULT_FRAME_EXPOSURE_PRE_ROW        0x40                                    /**< 0x40 */
#define OV2640_BASIC_DEFAULT_CHSYNC_HREF_SWAP              OV2640_BOOL_FALSE                       /**< disable swap */
#define OV2640_BASIC_DEFAULT_HREF_CHSYNC_SWAP              OV2640_BOOL_FALSE                       /**< disable swap */
#define OV2640_BASIC_DEFAULT_PCLK_OUTPUT_BY_HREF           OV2640_BOOL_FALSE                       /**< disable */
#define OV2640_BASIC_DEFAULT_PCLK_EDGE                     OV2640_EDGE_FALLING                     /**< falling edge */
#define OV2640_BASIC_DEFAULT_HREF_POLARITY                 OV2640_POLARITY_POSITIVE                /**< positive */
#define OV2640_BASIC_DEFAULT_VSYNC_POLARITY                OV2640_POLARITY_POSITIVE                /**< positive */
#define OV2640_BASIC_DEFAULT_HSYNC_POLARITY                OV2640_POLARITY_POSITIVE                /**< positive */
#define OV2640_BASIC_DEFAULT_LINE_INTERVAL_ADJUST          0x000                                   /**< 0x000 */
#define OV2640_BASIC_DEFAULT_HSYNC_START_POINT             0x08                                    /**< 0x08 */
#define OV2640_BASIC_DEFAULT_HSYNC_END_POINT               0x30                                    /**< 0x30 */
#define OV2640_BASIC_DEFAULT_LUMINANCE_AVG                 0x00                                    /**< 0x00 */
#define OV2640_BASIC_DEFAULT_FLASH_LIGHT                   0x20                                    /**< 0x20 */
#define OV2640_BASIC_DEFAULT_16_ZONE_AVG_WEIGHT            0x00000000                              /**< 0x00000000 */
#define OV2640_BASIC_DEFAULT_DSP_BPC                       OV2640_BOOL_TRUE                        /**< enable bpc */
#define OV2640_BASIC_DEFAULT_DSP_WPC                       OV2640_BOOL_TRUE                        /**< enable wpc */
#define OV2640_BASIC_DEFAULT_DSP_DVP_PCLK                  0x02                                    /**< 0x02 */
#define OV2640_BASIC_DEFAULT_DSP_CIP                       OV2640_BOOL_TRUE                        /**< enable cip */
#define OV2640_BASIC_DEFAULT_DSP_DMY                       OV2640_BOOL_TRUE                        /**< enable dmy */
#define OV2640_BASIC_DEFAULT_DSP_RAW_GMA                   OV2640_BOOL_TRUE                        /**< enable raw gma */
#define OV2640_BASIC_DEFAULT_DSP_DG                        OV2640_BOOL_FALSE                       /**< disable dg */
#define OV2640_BASIC_DEFAULT_DSP_AWB                       OV2640_BOOL_TRUE                        /**< enable awb */
#define OV2640_BASIC_DEFAULT_DSP_AWB_GAIN                  OV2640_BOOL_TRUE                        /**< enable awb gain */
#define OV2640_BASIC_DEFAULT_DSP_PRE                       OV2640_BOOL_TRUE                        /**< enable pre */
#define OV2640_BASIC_DEFAULT_DSP_DVP_Y8                    OV2640_BOOL_FALSE                       /**< disable dvp y8 */
#define OV2640_BASIC_DEFAULT_DSP_JPEG_OUTPUT               OV2640_BOOL_FALSE                       /**< disable jpeg output */
#define OV2640_BASIC_DEFAULT_DSP_DVP_OUTPUT_FORMAT         OV2640_DVP_OUTPUT_FORMAT_RGB565         /**< rgb565 format */
#define OV2640_BASIC_DEFAULT_DSP_JPEG_OUTPUT_HREF_TIMING   OV2640_HREF_TIMING_SENSOR               /**< sensor timing */
#define OV2640_BASIC_DEFAULT_DSP_BYTE_SWAP                 OV2640_BYTE_SWAP_UVUV                   /**< uvuv */
#define OV2640_BASIC_DEFAULT_DSP_IMAGE_HORIZONTAL          1600                                    /**< 1600 */
#define OV2640_BASIC_DEFAULT_DSP_IMAGE_VERTICAL            1200                                    /**< 1200 */
#define OV2640_BASIC_DEFAULT_DSP_DCW                       OV2640_BOOL_TRUE                        /**< enable dcw */
#define OV2640_BASIC_DEFAULT_DSP_SDE                       OV2640_BOOL_TRUE                        /**< enable sde */
#define OV2640_BASIC_DEFAULT_DSP_UV_ADJ                    OV2640_BOOL_TRUE                        /**< enable uv adj */
#define OV2640_BASIC_DEFAULT_DSP_UV_AVG                    OV2640_BOOL_TRUE                        /**< enable uv avg */
#define OV2640_BASIC_DEFAULT_DSP_CMX                       OV2640_BOOL_TRUE                        /**< enable cmx */
#define OV2640_BASIC_DEFAULT_DSP_LP_DP                     OV2640_BOOL_FALSE                       /**< disable lp dp */
#define OV2640_BASIC_DEFAULT_DSP_ROUND                     OV2640_BOOL_FALSE                       /**< disable round */
#define OV2640_BASIC_DEFAULT_DSP_VERTICAL_DIV              0x00                                    /**< div 0 */
#define OV2640_BASIC_DEFAULT_DSP_HORIZONTAL_DIV            0x00                                    /**< div 0 */
#define OV2640_BASIC_DEFAULT_DSP_HORIZONTAL_SIZE           1600                                    /**< 1600 */
#define OV2640_BASIC_DEFAULT_DSP_VERTICAL_SIZE             1200                                    /**< 1200 */
#define OV2640_BASIC_DEFAULT_DSP_OFFSET_X                  0                                       /**< offset 0 */
#define OV2640_BASIC_DEFAULT_DSP_OFFSET_Y                  0                                       /**< offset 0 */
#define OV2640_BASIC_DEFAULT_DSP_OUTPUT_WIDTH              1600                                    /**< 1600 */
#define OV2640_BASIC_DEFAULT_DSP_OUTPUT_HEIGHT             1200                                    /**< 1200 */
#define OV2640_BASIC_DEFAULT_DSP_ZOOM_SPEED                0x00                                    /**< speed 0 */
#define OV2640_BASIC_DEFAULT_DSP_QSF                       0x0C                                    /**< 0x0C */
#define OV2640_BASIC_DEFAULT_DSP_SCCB_MASTER_SPEED         4                                       /**< 4 */
#define OV2640_BASIC_DEFAULT_DSP_ADDRESS_AUTO_INC          OV2640_BOOL_FALSE                       /**< disable address auto inc */
#define OV2640_BASIC_DEFAULT_DSP_SCCB                      OV2640_BOOL_FALSE                       /**< disable sccb */
#define OV2640_BASIC_DEFAULT_DSP_SCCB_CLOCK_DELAY          OV2640_BOOL_FALSE                       /**< disable sccb clock delay */
#define OV2640_BASIC_DEFAULT_DSP_SCCB_ACCESS               OV2640_BOOL_FALSE                       /**< disable sccb access */
#define OV2640_BASIC_DEFAULT_DSP_SENSOR_PASS_ACCESS        OV2640_BOOL_TRUE                        /**< enable sensor pass access */
#define OV2640_BASIC_DEFAULT_DSP_AEC_ENABLE                OV2640_BOOL_FALSE                       /**< disable aec enable */
#define OV2640_BASIC_DEFAULT_DSP_AEC_SEL                   OV2640_BOOL_FALSE                       /**< disable aec sel */
#define OV2640_BASIC_DEFAULT_DSP_STAT_SEL                  OV2640_BOOL_FALSE                       /**< disable stat sel */
#define OV2640_BASIC_DEFAULT_DSP_VFIRST                    OV2640_BOOL_FALSE                       /**< disable vfirst */
#define OV2640_BASIC_DEFAULT_DSP_YUV422                    OV2640_BOOL_TRUE                        /**< enable yuv422 */
#define OV2640_BASIC_DEFAULT_DSP_YUV                       OV2640_BOOL_TRUE                        /**< enable yuv */
#define OV2640_BASIC_DEFAULT_DSP_RGB                       OV2640_BOOL_FALSE                       /**< disable rgb */
#define OV2640_BASIC_DEFAULT_DSP_RAW                       OV2640_BOOL_FALSE                       /**< disable raw */
#define OV2640_BASIC_DEFAULT_DSP_DP_SELX                   0x00                                    /**< selx 0x00 */
#define OV2640_BASIC_DEFAULT_DSP_DP_SELY                   0x00                                    /**< sely 0x00 */

/**
 * @brief ov2640 image resolution enumeration definition
 */
typedef enum
{
    OV2640_IMAGE_RESOLUTION_QQVGA     = 0,         /**< 160 x 120 */
    OV2640_IMAGE_RESOLUTION_QCIF      = 1,         /**< 176 x 144 */
    OV2640_IMAGE_RESOLUTION_QVGA      = 2,         /**< 320 x 240 */
    OV2640_IMAGE_RESOLUTION_WQVGA     = 3,         /**< 400 x 240 */
    OV2640_IMAGE_RESOLUTION_CIF       = 4,         /**< 352 x 288 */
    OV2640_IMAGE_RESOLUTION_VGA       = 5,         /**< 640 x 480 */
    OV2640_IMAGE_RESOLUTION_SVGA      = 6,         /**< 800 x 600 */
    OV2640_IMAGE_RESOLUTION_XGA       = 7,         /**< 1024 x 768 */
    OV2640_IMAGE_RESOLUTION_WXGA      = 8,         /**< 1280 x 800 */
    OV2640_IMAGE_RESOLUTION_XVGA      = 9,         /**< 1280 x 960 */
    OV2640_IMAGE_RESOLUTION_WXGA_PLUS = 10,        /**< 1440 x 900 */
    OV2640_IMAGE_RESOLUTION_SXGA      = 11,        /**< 1280 x 1024 */
    OV2640_IMAGE_RESOLUTION_UXGA      = 12,        /**< 1600 x 1200 */
} ov2640_image_resolution_t;

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t ov2640_basic_init(void);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ov2640_basic_deinit(void);

/**
 * @brief  basic example set jpeg mode
 * @return status code
 *         - 0 success
 *         - 1 set jpeg mode failed
 * @note   none
 */
uint8_t ov2640_basic_set_jpeg_mode(void);

/**
 * @brief  basic example set rgb565 mode
 * @return status code
 *         - 0 success
 *         - 1 set rgb565 mode failed
 * @note   none
 */
uint8_t ov2640_basic_set_rgb565_mode(void);

/**
 * @brief     basic example set light mode
 * @param[in] mode is the light mode
 * @return    status code
 *            - 0 success
 *            - 1 set light mode failed
 * @note      none
 */
uint8_t ov2640_basic_set_light_mode(ov2640_light_mode_t mode);

/**
 * @brief     basic example set color saturation
 * @param[in] color is the color saturation
 * @return    status code
 *            - 0 success
 *            - 1 set color saturation failed
 * @note      none
 */
uint8_t ov2640_basic_set_color_saturation(ov2640_color_saturation_t color);

/**
 * @brief     basic example set brightness
 * @param[in] brightness is the brightness
 * @return    status code
 *            - 0 success
 *            - 1 set brightness failed
 * @note      none
 */
uint8_t ov2640_basic_set_brightness(ov2640_brightness_t brightness);

/**
 * @brief     basic example set contrast
 * @param[in] contrast is the set contrast
 * @return    status code
 *            - 0 success
 *            - 1 set contrast failed
 * @note      none
 */
uint8_t ov2640_basic_set_contrast(ov2640_contrast_t contrast);

/**
 * @brief     basic example set special effect
 * @param[in] effect is the set special effect
 * @return    status code
 *            - 0 success
 *            - 1 set special_effect failed
 * @note      none
 */
uint8_t ov2640_basic_set_special_effect(ov2640_special_effect_t effect);

/**
 * @brief     basic example set image resolution
 * @param[in] resolution is the set image resolution
 * @return    status code
 *            - 0 success
 *            - 1 set image resolution failed
 * @note      none
 */
uint8_t ov2640_basic_set_image_resolution(ov2640_image_resolution_t resolution);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
