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
 * @file      driver_ov2640.c
 * @brief     driver ov2640 source file
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

#include "driver_ov2640.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "OmniVision OV2640"        /**< chip name */
#define MANUFACTURER_NAME         "OmniVision"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.5f                       /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.0f                       /**< chip max supply voltage */
#define MAX_CURRENT               40.0f                      /**< chip max current */
#define TEMPERATURE_MIN           -30.0f                     /**< chip min operating temperature */
#define TEMPERATURE_MAX           70.0f                      /**< chip max operating temperature */
#define DRIVER_VERSION            1000                       /**< driver version */

/**
 * @brief iic address definition
 */
#define OV2640_ADDRESS        0x60         /**< iic address */

/**
 * @brief chip dsp bank register definition
 */
#define OV2640_REG_DSP_BANK_R_BYPASS        0x05        /**< bypass dsp register */
#define OV2640_REG_DSP_BANK_QS              0x44        /**< quantization scale factor register */
#define OV2640_REG_DSP_BANK_CTRLI           0x50        /**< control register */
#define OV2640_REG_DSP_BANK_HSIZE           0x51        /**< hsize register */
#define OV2640_REG_DSP_BANK_VSIZE           0x52        /**< vsize register */
#define OV2640_REG_DSP_BANK_XOFFL           0x53        /**< offset x register */
#define OV2640_REG_DSP_BANK_YOFFL           0x54        /**< offset y register */
#define OV2640_REG_DSP_BANK_VHYX            0x55        /**< vhyx register */
#define OV2640_REG_DSP_BANK_DPRP            0x56        /**< dprp register */
#define OV2640_REG_DSP_BANK_TEST            0x57        /**< test register */
#define OV2640_REG_DSP_BANK_ZMOW            0x5A        /**< zmow register */
#define OV2640_REG_DSP_BANK_ZMOH            0x5B        /**< zmoh register */
#define OV2640_REG_DSP_BANK_ZMHH            0x5C        /**< zmhh register */
#define OV2640_REG_DSP_BANK_BPADDR          0x7C        /**< sde indirect address register */
#define OV2640_REG_DSP_BANK_BPDATA          0x7D        /**< sde indirect data register */
#define OV2640_REG_DSP_BANK_CTRL2           0x86        /**< module2 enable register */
#define OV2640_REG_DSP_BANK_CTRL3           0x87        /**< module3 enable register */
#define OV2640_REG_DSP_BANK_SIZEL           0x8C        /**< sizel register */
#define OV2640_REG_DSP_BANK_HSIZE8          0xC0        /**< image horizontal size register */
#define OV2640_REG_DSP_BANK_VSIZE8          0xC1        /**< image vertical size register */
#define OV2640_REG_DSP_BANK_CTRL0           0xC2        /**< module0 enable register */
#define OV2640_REG_DSP_BANK_CTRL1           0xC3        /**< module1 enable register */
#define OV2640_REG_DSP_BANK_R_DVP_SP        0xD3        /**< dvp sp register */
#define OV2640_REG_DSP_BANK_IMAGE_MODE      0xDA        /**< image mode register */
#define OV2640_REG_DSP_BANK_RESET           0xE0        /**< reset register */
#define OV2640_REG_DSP_BANK_MS_SP           0xF0        /**< sccb master speed register */
#define OV2640_REG_DSP_BANK_SS_ID           0xF7        /**< sccb slave id register */
#define OV2640_REG_DSP_BANK_SS_CTRL         0xF8        /**< sccb slave control register */
#define OV2640_REG_DSP_BANK_MC_BIST         0xF9        /**< microcontroller reset register */
#define OV2640_REG_DSP_BANK_MC_AL           0xFA        /**< program memory pointer address low register */
#define OV2640_REG_DSP_BANK_MC_AH           0xFB        /**< program memory pointer address high register */
#define OV2640_REG_DSP_BANK_MC_D            0xFC        /**< program memory pointer address register */
#define OV2640_REG_DSP_BANK_P_CMD           0xFD        /**< sccb protocol command register */
#define OV2640_REG_DSP_BANK_P_STATUS        0xFE        /**< sccb protocol status register */
#define OV2640_REG_DSP_BANK_RA_DLMT         0xFF        /**< bank select register */

/**
 * @brief chip sensor bank register definition
 */
#define OV2640_REG_SENSOR_BANK_GAIN         0x00        /**< gain register */
#define OV2640_REG_SENSOR_BANK_COM1         0x03        /**< com1 register */
#define OV2640_REG_SENSOR_BANK_REG04        0x04        /**< reg04 register */
#define OV2640_REG_SENSOR_BANK_REG08        0x08        /**< reg08 register */
#define OV2640_REG_SENSOR_BANK_COM2         0x09        /**< com2 register */
#define OV2640_REG_SENSOR_BANK_PIDH         0x0A        /**< product id number msb register */
#define OV2640_REG_SENSOR_BANK_PIDL         0x0B        /**< product id number lsb register */
#define OV2640_REG_SENSOR_BANK_COM3         0x0C        /**< com3 register */
#define OV2640_REG_SENSOR_BANK_COM4         0x0D        /**< com4 register */
#define OV2640_REG_SENSOR_BANK_AEC          0x10        /**< aec register */
#define OV2640_REG_SENSOR_BANK_CLKRC        0x11        /**< clkrc register */
#define OV2640_REG_SENSOR_BANK_COM7         0x12        /**< com7 register */
#define OV2640_REG_SENSOR_BANK_COM8         0x13        /**< com8 register */
#define OV2640_REG_SENSOR_BANK_COM9         0x14        /**< com9 register */
#define OV2640_REG_SENSOR_BANK_COM10        0x15        /**< com10 register */
#define OV2640_REG_SENSOR_BANK_HREFST       0x17        /**< hrefst register */
#define OV2640_REG_SENSOR_BANK_HREFEND      0x18        /**< hrefend register */
#define OV2640_REG_SENSOR_BANK_VSTRT        0x19        /**< vstrt register */
#define OV2640_REG_SENSOR_BANK_VEND         0x1A        /**< vend register */
#define OV2640_REG_SENSOR_BANK_MIDH         0x1C        /**< id byte high register */
#define OV2640_REG_SENSOR_BANK_MIDL         0x1D        /**< id byte low register */
#define OV2640_REG_SENSOR_BANK_AEW          0x24        /**< aew register */
#define OV2640_REG_SENSOR_BANK_AEB          0x25        /**< aeb register */
#define OV2640_REG_SENSOR_BANK_VV           0x26        /**< vv register */
#define OV2640_REG_SENSOR_BANK_REG2A        0x2A        /**< reg2a register */
#define OV2640_REG_SENSOR_BANK_FRARL        0x2B        /**< frarl register */
#define OV2640_REG_SENSOR_BANK_ADDVSL       0x2D        /**< addvsl register */
#define OV2640_REG_SENSOR_BANK_ADDVSH       0x2E        /**< addvsh register */
#define OV2640_REG_SENSOR_BANK_YAVG         0x2F        /**< yavg register */
#define OV2640_REG_SENSOR_BANK_HSDY         0x30        /**< hsdy register */
#define OV2640_REG_SENSOR_BANK_HEDY         0x31        /**< hedy register */
#define OV2640_REG_SENSOR_BANK_REG32        0x32        /**< reg32 register */
#define OV2640_REG_SENSOR_BANK_ARCOM2       0x34        /**< arcom2 register */
#define OV2640_REG_SENSOR_BANK_REG45        0x45        /**< reg45 register */
#define OV2640_REG_SENSOR_BANK_FLL          0x46        /**< fll register */
#define OV2640_REG_SENSOR_BANK_FLH          0x47        /**< flh register */
#define OV2640_REG_SENSOR_BANK_COM19        0x48        /**< com19 register */
#define OV2640_REG_SENSOR_BANK_ZOOMS        0x49        /**< zooms register */
#define OV2640_REG_SENSOR_BANK_COM22        0x4B        /**< com22 register */
#define OV2640_REG_SENSOR_BANK_COM25        0x4E        /**< com25 register */
#define OV2640_REG_SENSOR_BANK_BD50         0x4F        /**< bd50 register */
#define OV2640_REG_SENSOR_BANK_BD60         0x50        /**< bd60 register */
#define OV2640_REG_SENSOR_BANK_REG5D        0x5D        /**< reg5d register */
#define OV2640_REG_SENSOR_BANK_REG5E        0x5E        /**< reg5e register */
#define OV2640_REG_SENSOR_BANK_REG5F        0x5F        /**< reg5f register */
#define OV2640_REG_SENSOR_BANK_REG60        0x60        /**< reg60 register */
#define OV2640_REG_SENSOR_BANK_HISTO_LOW    0x61        /**< histo low register */
#define OV2640_REG_SENSOR_BANK_HISTO_HIGH   0x62        /**< histo high register */

/**
 * @brief innter table globle definition
 */
const uint8_t gsc_ov2640_init_table[][2];            /**< init register */
const uint8_t gsc_ov2640_jpeg_init_table[][2];        /**< jpeg init register */
const uint8_t gsc_ov2640_rgb565_init_table[][2];      /**< rgb565 init register */

/**
 * @brief init table definition
 */
const uint8_t gsc_ov2640_init_table[][2] = 
{
    {0xFF, 0x00},
    {0x2C, 0xFF},
    {0x2E, 0xDF},
    {0xFF, 0x01},
    {0x3C, 0x32},
    {0x11, 0x00},
    {0x09, 0x02},
    {0x04, 0xD8},
    {0x13, 0xE5},
    {0x14, 0x48},
    {0x2C, 0x0C},
    {0x33, 0x78},
    {0x3A, 0x33},
    {0x3B, 0xFB},
    {0x3E, 0x00},
    {0x43, 0x11},
    {0x16, 0x10},
    {0x39, 0x92},
    {0x35, 0xDA},
    {0x22, 0x1A},
    {0x37, 0xC3},
    {0x23, 0x00},
    {0x34, 0xC0},
    {0x36, 0x1A},
    {0x06, 0x88},
    {0x07, 0xC0},
    {0x0D, 0x87},
    {0x0E, 0x41},
    {0x4C, 0x00},
    {0x48, 0x00},
    {0x5B, 0x00},
    {0x42, 0x03},
    {0x4A, 0x81},
    {0x21, 0x99},
    {0x24, 0x40},
    {0x25, 0x38},
    {0x26, 0x82},
    {0x5C, 0x00},
    {0x63, 0x00},
    {0x46, 0x00},
    {0x0C, 0x3C},
    {0x61, 0x70},
    {0x62, 0x80},
    {0x7C, 0x05},
    {0x20, 0x80},
    {0x28, 0x30},
    {0x6C, 0x00},
    {0x6D, 0x80},
    {0x6E, 0x00},
    {0x70, 0x02},
    {0x71, 0x94},
    {0x73, 0xC1},
    {0x3D, 0x34},
    {0x5A, 0x57},
    {0x12, 0x00},
    {0x17, 0x11},
    {0x18, 0x75},
    {0x19, 0x01},
    {0x1A, 0x97},
    {0x32, 0x36},
    {0x03, 0x0F},
    {0x37, 0x40},
    {0x4F, 0xCA},
    {0x50, 0xA8},
    {0x5A, 0x23},
    {0x6D, 0x00},
    {0x6D, 0x38},
    {0xFF, 0x00},
    {0xE5, 0x7F},
    {0xF9, 0xC0},
    {0x41, 0x24},
    {0xE0, 0x14},
    {0x76, 0xFF},
    {0x33, 0xA0},
    {0x42, 0x20},
    {0x43, 0x18},
    {0x4C, 0x00},
    {0x87, 0xD5},
    {0x88, 0x3F},
    {0xD7, 0x03},
    {0xD9, 0x10},
    {0xD3, 0x82},
    {0xC8, 0x08},
    {0xC9, 0x80},
    {0x7C, 0x00},
    {0x7D, 0x00},
    {0x7C, 0x03},
    {0x7D, 0x48},
    {0x7D, 0x48},
    {0x7C, 0x08},
    {0x7D, 0x20},
    {0x7D, 0x10},
    {0x7D, 0x0E},
    {0x90, 0x00},
    {0x91, 0x0E},
    {0x91, 0x1A},
    {0x91, 0x31},
    {0x91, 0x5A},
    {0x91, 0x69},
    {0x91, 0x75},
    {0x91, 0x7E},
    {0x91, 0x88},
    {0x91, 0x8F},
    {0x91, 0x96},
    {0x91, 0xA3},
    {0x91, 0xAF},
    {0x91, 0xC4},
    {0x91, 0xD7},
    {0x91, 0xE8},
    {0x91, 0x20},
    {0x92, 0x00},
    {0x93, 0x06},
    {0x93, 0xE3},
    {0x93, 0x05},
    {0x93, 0x05},
    {0x93, 0x00},
    {0x93, 0x04},
    {0x93, 0x00},
    {0x93, 0x00},
    {0x93, 0x00},
    {0x93, 0x00},
    {0x93, 0x00},
    {0x93, 0x00},
    {0x93, 0x00},
    {0x96, 0x00},
    {0x97, 0x08},
    {0x97, 0x19},
    {0x97, 0x02},
    {0x97, 0x0C},
    {0x97, 0x24},
    {0x97, 0x30},
    {0x97, 0x28},
    {0x97, 0x26},
    {0x97, 0x02},
    {0x97, 0x98},
    {0x97, 0x80},
    {0x97, 0x00},
    {0x97, 0x00},
    {0xC3, 0xEF},
    {0xA4, 0x00},
    {0xA8, 0x00},
    {0xC5, 0x11},
    {0xC6, 0x51},
    {0xBF, 0x80},
    {0xC7, 0x10},
    {0xB6, 0x66},
    {0xB8, 0xA5},
    {0xB7, 0x64},
    {0xB9, 0x7C},
    {0xB3, 0xAF},
    {0xB4, 0x97},
    {0xB5, 0xFF},
    {0xB0, 0xC5},
    {0xB1, 0x94},
    {0xB2, 0x0F},
    {0xC4, 0x5C},
    {0xC0, 0xC8},
    {0xC1, 0x96},
    {0x8C, 0x00},
    {0x86, 0x3D},
    {0x50, 0x00},
    {0x51, 0x90},
    {0x52, 0x2C},
    {0x53, 0x00},
    {0x54, 0x00},
    {0x55, 0x88},
    {0x5A, 0x90},
    {0x5B, 0x2C},
    {0x5C, 0x05},
    {0xD3, 0x02},
    {0xC3, 0xED},
    {0x7F, 0x00},
    {0xDA, 0x09},
    {0xE5, 0x1F},
    {0xE1, 0x67},
    {0xE0, 0x00},
    {0xDD, 0x7F},
    {0x05, 0x00},
};

/**
 * @brief jpeg init table definition
 */
const uint8_t gsc_ov2640_jpeg_init_table[][2] = 
{
    {0xFF, 0x00},
    {0xDA, 0x10},
    {0xD7, 0x03},
    {0xDF, 0x00},
    {0x33, 0x80},
    {0x3C, 0x40},
    {0xE1, 0x77},
    {0x00, 0x00},
    {0xFF, 0x01},
    {0xE0, 0x14},
    {0xE1, 0x77},
    {0xE5, 0x1F},
    {0xD7, 0x03},
    {0xDA, 0x10},
    {0xE0, 0x00},
};

/**
 * @brief rgb565 init table definition
 */
const uint8_t gsc_ov2640_rgb565_init_table[][2] = 
{
    {0xFF, 0x00},
    {0xDA, 0x09},
    {0xD7, 0x03},
    {0xDF, 0x02},
    {0x33, 0xA0},
    {0x3C, 0x00},
    {0xE1, 0x67},
    {0xFF, 0x01},
    {0xE0, 0x00},
    {0xE1, 0x00},
    {0xE5, 0x00},
    {0xD7, 0x00},
    {0xDA, 0x00},
    {0xE0, 0x00},
};

/**
 * @brief      dsp read
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[in]  reg is the register address
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 dsp read failed
 * @note       none
 */
static uint8_t a_ov2640_dsp_read(ov2640_handle_t *handle, uint8_t reg, uint8_t *data)
{
    uint8_t config;
    
    if (handle->sccb_read(OV2640_ADDRESS, OV2640_REG_DSP_BANK_RA_DLMT, &config, 1) != 0)             /* read ra_dlmt */
    {
        return 1;                                                                                    /* return error */
    }
    if ((config & 0x01) != 0)                                                                        /* check config */
    {
        config &= ~(1 << 0);                                                                         /* clear bit0 */
        if (handle->sccb_write(OV2640_ADDRESS, OV2640_REG_DSP_BANK_RA_DLMT, &config, 1) != 0)        /* use the dsp bank */
        {
            return 1;                                                                                /* return error */
        }
    }
    
    if (handle->sccb_read(OV2640_ADDRESS, reg, data, 1) != 0)                                        /* read dsp reg */
    {
        return 1;                                                                                    /* return error */
    }
    
    return 0;                                                                                        /* success return 0 */
}

/**
 * @brief     dsp write
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] reg is the register address
 * @param[in] data is the set data
 * @return    status code
 *            - 0 success
 *            - 1 dsp write failed
 * @note      none
 */
static uint8_t a_ov2640_dsp_write(ov2640_handle_t *handle, uint8_t reg, uint8_t data)
{
    uint8_t config;
    
    if (handle->sccb_read(OV2640_ADDRESS, OV2640_REG_DSP_BANK_RA_DLMT, &config, 1) != 0)             /* read ra_dlmt */
    {
        return 1;                                                                                    /* return error */
    }
    if ((config & 0x01) != 0)                                                                        /* check config */
    {
        config &= ~(1 << 0);                                                                         /* clear bit0 */
        if (handle->sccb_write(OV2640_ADDRESS, OV2640_REG_DSP_BANK_RA_DLMT, &config, 1) != 0)        /* use the dsp bank */
        {
            return 1;                                                                                /* return error */
        }
    }
    
    if (handle->sccb_write(OV2640_ADDRESS, reg, &data, 1) != 0)                                      /* write dsp reg */
    {
        return 1;                                                                                    /* return error */
    }
    
    return 0;                                                                                        /* success return 0 */
}

/**
 * @brief      sensor read
 * @param[in]  *handle points to an ov2640 handle structure
 * @param[in]  reg is the register address
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 sensor read failed
 * @note       none
 */
static uint8_t a_ov2640_sensor_read(ov2640_handle_t *handle, uint8_t reg, uint8_t *data)
{
    uint8_t config;
    
    if (handle->sccb_read(OV2640_ADDRESS, OV2640_REG_DSP_BANK_RA_DLMT, &config, 1) != 0)             /* read ra_dlmt */
    {
        return 1;                                                                                    /* return error */
    }
    if ((config & 0x01) == 0)                                                                        /* check config */
    {
        config |= (1 << 0);                                                                          /* set bit0 */
        if (handle->sccb_write(OV2640_ADDRESS, OV2640_REG_DSP_BANK_RA_DLMT, &config, 1) != 0)        /* use the dsp bank */
        {
            return 1;                                                                                /* return error */
        }
    }
    
    if (handle->sccb_read(OV2640_ADDRESS, reg, data, 1) != 0)                                        /* read dsp reg */
    {
        return 1;                                                                                    /* return error */
    }
    
    return 0;                                                                                        /* success return 0 */
}

/**
 * @brief     sensor write
 * @param[in] *handle points to an ov2640 handle structure
 * @param[in] reg is the register address
 * @param[in] data is the set data
 * @return    status code
 *            - 0 success
 *            - 1 sensor write failed
 * @note      none
 */
static uint8_t a_ov2640_sensor_write(ov2640_handle_t *handle, uint8_t reg, uint8_t data)
{
    uint8_t config;
    
    if (handle->sccb_read(OV2640_ADDRESS, OV2640_REG_DSP_BANK_RA_DLMT, &config, 1) != 0)             /* read ra_dlmt */
    {
        return 1;                                                                                    /* return error */
    }
    if ((config & 0x01) == 0)                                                                        /* check config */
    {
        config |= (1 << 0);                                                                          /* set bit0 */
        if (handle->sccb_write(OV2640_ADDRESS, OV2640_REG_DSP_BANK_RA_DLMT, &config, 1) != 0)        /* use the dsp bank */
        {
            return 1;                                                                                /* return error */
        }
    }
    
    if (handle->sccb_write(OV2640_ADDRESS, reg, &data, 1) != 0)                                      /* write dsp reg */
    {
        return 1;                                                                                    /* return error */
    }
    
    return 0;                                                                                        /* success return 0 */
}

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
uint8_t ov2640_init(ov2640_handle_t *handle)
{
    uint8_t res;
    uint8_t reg;
    uint16_t id;
    
    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->debug_print == NULL)                                               /* check debug_print */
    {
        return 3;                                                                  /* return error */
    }
    if (handle->sccb_init == NULL)                                                 /* check sccb_init */
    {
        handle->debug_print("ov2640: sccb_init is null.\n");                       /* sccb_init is null */
       
        return 3;                                                                  /* return error */
    }
    if (handle->sccb_deinit == NULL)                                               /* check sccb_deinit */
    {
        handle->debug_print("ov2640: sccb_deinit is null.\n");                     /* sccb_deinit is null */
       
        return 3;                                                                  /* return error */
    }
    if (handle->sccb_read == NULL)                                                 /* check sccb_read */
    {
        handle->debug_print("ov2640: sccb_read is null.\n");                       /* sccb_read is null */
       
        return 3;                                                                  /* return error */
    }
    if (handle->sccb_write == NULL)                                                /* check sccb_write */
    {
        handle->debug_print("ov2640: sccb_write is null.\n");                      /* sccb_write is null */
       
        return 3;                                                                  /* return error */
    }
    if (handle->power_down_init == NULL)                                           /* check power_down_init */
    {
        handle->debug_print("ov2640: power_down_init is null.\n");                 /* power_down_init is null */
       
        return 3;                                                                  /* return error */
    }
    if (handle->power_down_deinit == NULL)                                         /* check power_down_deinit */
    {
        handle->debug_print("ov2640: power_down_deinit is null.\n");               /* power_down_deinit is null */
       
        return 3;                                                                  /* return error */
    }
    if (handle->power_down_write == NULL)                                          /* check power_down_write */
    {
        handle->debug_print("ov2640: power_down_write is null.\n");                /* power_down_write is null */
       
        return 3;                                                                  /* return error */
    }
    if (handle->reset_init == NULL)                                                /* check reset_init */
    {
        handle->debug_print("ov2640: reset_init is null.\n");                      /* reset_init is null */
       
        return 3;                                                                  /* return error */
    }
    if (handle->reset_deinit == NULL)                                              /* check reset_deinit */
    {
        handle->debug_print("ov2640: reset_deinit is null.\n");                    /* reset_deinit is null */
       
        return 3;                                                                  /* return error */
    }
    if (handle->reset_write == NULL)                                               /* check reset_write */
    {
        handle->debug_print("ov2640: reset_write is null.\n");                     /* reset_write is null */
       
        return 3;                                                                  /* return error */
    }
    if (handle->delay_ms == NULL)                                                  /* check delay_ms */
    {
        handle->debug_print("ov2640: delay_ms is null.\n");                        /* delay_ms is null */
       
        return 3;                                                                  /* return error */
    }
    
    if (handle->power_down_init() != 0)                                            /* power down init */
    {
        handle->debug_print("ov2640: power down init failed.\n");                  /* power down init failed */
       
        return 4;                                                                  /* return error */
    }
    if (handle->reset_init() != 0)                                                 /* reset init */
    {
        handle->debug_print("ov2640: reset init failed.\n");                       /* reset init failed */
        (void)handle->power_down_deinit();                                         /* power down deinit */
        
        return 4;                                                                  /* return error */
    }
    if (handle->sccb_init() != 0)                                                  /* sccb init */
    {
        handle->debug_print("ov2640: sccb init failed.\n");                        /* sccb init failed */
        (void)handle->reset_deinit();                                              /* reset deinit */
        (void)handle->power_down_deinit();                                         /* power down deinit */
        
        return 1;                                                                  /* return error */
    }
    
    if (handle->power_down_write(0) != 0)                                          /* power on */
    {
        handle->debug_print("ov2640: power down write failed.\n");                 /* power down write failed */
        (void)handle->sccb_deinit();                                               /* sccb deinit */
        (void)handle->reset_deinit();                                              /* reset deinit */
        (void)handle->power_down_deinit();                                         /* power down deinit */
        
        return 5;                                                                  /* return error */
    }
    handle->delay_ms(10);                                                          /* delay 10ms */
    
    if (handle->reset_write(0) != 0)                                               /* reset write low */
    {
        handle->debug_print("ov2640: reset write failed.\n");                      /* reset write failed */
        (void)handle->sccb_deinit();                                               /* sccb deinit */
        (void)handle->reset_deinit();                                              /* reset deinit */
        (void)handle->power_down_deinit();                                         /* power down deinit */
        
        return 5;                                                                  /* return error */
    }
    handle->delay_ms(10);                                                          /* delay 10ms */
    if (handle->reset_write(1) != 0)                                               /* reset write high */
    {
        handle->debug_print("ov2640: reset write failed.\n");                      /* reset write failed */
        (void)handle->sccb_deinit();                                               /* sccb deinit */
        (void)handle->reset_deinit();                                              /* reset deinit */
        (void)handle->power_down_deinit();                                         /* power down deinit */
        
        return 5;                                                                  /* return error */
    }
    handle->delay_ms(10);                                                          /* delay 10ms */
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM7, &reg);         /* read com7 */
    if (res != 0)                                                                  /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                      /* sensor read failed */
        (void)handle->sccb_deinit();                                               /* sccb deinit */
        (void)handle->reset_deinit();                                              /* reset deinit */
        (void)handle->power_down_deinit();                                         /* power down deinit */
        
        return 6;                                                                  /* return error */
    }
    reg |= (1 << 7);                                                               /* set software reset */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM7, reg);         /* write com7 */
    if (res != 0)                                                                  /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                     /* sensor write failed */
        (void)handle->sccb_deinit();                                               /* sccb deinit */
        (void)handle->reset_deinit();                                              /* reset deinit */
        (void)handle->power_down_deinit();                                         /* power down deinit */
        
        return 6;                                                                  /* return error */
    }
    handle->delay_ms(50);                                                          /* delay 50ms */
    
    res = a_ov2640_sensor_read(handle,  OV2640_REG_SENSOR_BANK_MIDH, &reg);        /* read id number */
    if (res != 0)                                                                  /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                      /* sensor read failed */
        (void)handle->sccb_deinit();                                               /* sccb deinit */
        (void)handle->reset_deinit();                                              /* reset deinit */
        (void)handle->power_down_deinit();                                         /* power down deinit */
        
        return 7;                                                                  /* return error */
    }
    id = (uint16_t)reg << 8;                                                       /* set msb */
    res = a_ov2640_sensor_read(handle,  OV2640_REG_SENSOR_BANK_MIDL, &reg);        /* read id number */
    if (res != 0)                                                                  /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                      /* sensor read failed */
        (void)handle->sccb_deinit();                                               /* sccb deinit */
        (void)handle->reset_deinit();                                              /* reset deinit */
        (void)handle->power_down_deinit();                                         /* power down deinit */
        
        return 7;                                                                  /* return error */
    }
    id |= reg;                                                                     /* set lsb */
    if (id != 0X7FA2)                                                              /* check id */
    {
        handle->debug_print("ov2640: manufacturer id is invalid.\n");              /* manufacturer id is invalid */
        (void)handle->sccb_deinit();                                               /* sccb deinit */
        (void)handle->reset_deinit();                                              /* reset deinit */
        (void)handle->power_down_deinit();                                         /* power down deinit */
        
        return 7;                                                                  /* return error */
    }
    res = a_ov2640_sensor_read(handle,  OV2640_REG_SENSOR_BANK_PIDH, &reg);        /* read product id number msb */
    if (res != 0)                                                                  /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                      /* sensor read failed */
        (void)handle->sccb_deinit();                                               /* sccb deinit */
        (void)handle->reset_deinit();                                              /* reset deinit */
        (void)handle->power_down_deinit();                                         /* power down deinit */
        
        return 8;                                                                  /* return error */
    }
    id = (uint16_t)reg << 8;                                                       /* set msb */
    res = a_ov2640_sensor_read(handle,  OV2640_REG_SENSOR_BANK_PIDL, &reg);        /* read product id number lsb */
    if (res != 0)                                                                  /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                      /* sensor read failed */
        (void)handle->sccb_deinit();                                               /* sccb deinit */
        (void)handle->reset_deinit();                                              /* reset deinit */
        (void)handle->power_down_deinit();                                         /* power down deinit */
        
        return 8;                                                                  /* return error */
    }
    id |= reg;                                                                     /* set lsb */
    if (id != 0X2642)                                                              /* check id */
    {
        handle->debug_print("ov2640: product id is invalid.\n");                   /* product id is invalid */
        (void)handle->sccb_deinit();                                               /* sccb deinit */
        (void)handle->reset_deinit();                                              /* reset deinit */
        (void)handle->power_down_deinit();                                         /* power down deinit */
        
        return 8;                                                                  /* return error */
    }
    handle->inited = 1;                                                            /* flag finish initialization */
    
    return 0;                                                                      /* success return 0 */
}

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
uint8_t ov2640_deinit(ov2640_handle_t *handle)
{
    uint8_t res;
    uint8_t reg;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM7, &reg);        /* read com7 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 4;                                                                 /* return error */
    }
    reg |= (1 << 7);                                                              /* set software reset */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM7, reg);        /* write com7 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 4;                                                                 /* return error */
    }
    handle->delay_ms(50);                                                         /* delay 50ms */
    
    if (handle->power_down_write(1) != 0)                                         /* power down */
    {
        handle->debug_print("ov2640: power down write failed.\n");                /* power down write failed */
        
        return 5;                                                                 /* return error */
    }
    handle->delay_ms(10);                                                         /* delay 10ms */
    
    if (handle->reset_deinit() != 0)                                              /* reset deinit */
    {
        handle->debug_print("ov2640: reset deinit failed.\n");                    /* reset deinit failed */
       
        return 1;                                                                 /* return error */
    }
    if (handle->power_down_deinit() != 0)                                         /* power down deinit */
    {
        handle->debug_print("ov2640: power down deinit failed.\n");               /* power down deinit failed */
       
        return 1;                                                                 /* return error */
    }
    if (handle->sccb_deinit() != 0)                                               /* sccb deinit */
    {
        handle->debug_print("ov2640: sccb deinit failed.\n");                     /* sccb deinit failed */
       
        return 1;                                                                 /* return error */
    }
    handle->inited = 0;                                                           /* flag close */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_table_init(ov2640_handle_t *handle)
{
    uint8_t res;
    uint8_t reg;
    uint16_t i;
    
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    for (i = 0; i < (sizeof(gsc_ov2640_init_table) / 2); i++)                       /* write all */
    {
        reg = gsc_ov2640_init_table[i][1];                                          /* set reg */
        res = handle->sccb_write(OV2640_ADDRESS, 
                                 gsc_ov2640_init_table[i][0], 
                                (uint8_t *)&reg, 1);                                /* sccb write */
        if (res != 0)                                                               /* check the result */
        {
            handle->debug_print("ov2640: sccb write failed.\n");                    /* sccb write failed */
           
            return 1;                                                               /* return error */
        }
    }
    
    return 0;                                                                       /* success return 0 */
}

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
uint8_t ov2640_table_jpeg_init(ov2640_handle_t *handle)
{
    uint8_t res;
    uint8_t reg;
    uint16_t i;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    for (i = 0; i < (sizeof(gsc_ov2640_jpeg_init_table) / 2); i++)                       /* write all */
    {
        reg = gsc_ov2640_jpeg_init_table[i][1];                                          /* set reg */
        res = handle->sccb_write(OV2640_ADDRESS, 
                                 gsc_ov2640_jpeg_init_table[i][0], 
                                (uint8_t *)&reg, 1);                                     /* sccb write */
        if (res != 0)                                                                    /* check the result */
        {
            handle->debug_print("ov2640: sccb write failed.\n");                         /* sccb write failed */
           
            return 1;                                                                    /* return error */
        }
    }
    
    return 0;                                                                            /* success return 0 */
}

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
uint8_t ov2640_table_rgb565_init(ov2640_handle_t *handle)
{
    uint8_t res;
    uint8_t reg;
    uint16_t i;
    
    if (handle == NULL)                                                                    /* check handle */
    {
        return 2;                                                                          /* return error */
    }
    if (handle->inited != 1)                                                               /* check handle initialization */
    {
        return 3;                                                                          /* return error */
    }
    
    for (i = 0; i < (sizeof(gsc_ov2640_rgb565_init_table) / 2); i++)                       /* write all */
    {
        reg = gsc_ov2640_rgb565_init_table[i][1];                                          /* set reg */
        res = handle->sccb_write(OV2640_ADDRESS, 
                                 gsc_ov2640_rgb565_init_table[i][0], 
                                (uint8_t *)&reg, 1);                                       /* sccb write */
        if (res != 0)                                                                      /* check the result */
        {
            handle->debug_print("ov2640: sccb write failed.\n");                           /* sccb write failed */
           
            return 1;                                                                      /* return error */
        }
    }
    
    return 0;                                                                              /* success return 0 */
}

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
uint8_t ov2640_set_agc_gain(ov2640_handle_t *handle, uint16_t gain)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    if (gain > 0x3FF)                                                                     /* check gain */
    {
        handle->debug_print("ov2640: gain > 0x3FF.\n");                                   /* gain > 0x3FF */
        
        return 4;                                                                         /* return error */
    }
    
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_GAIN, gain & 0xFF);        /* write gain */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                            /* sensor write failed */
        
        return 1;                                                                         /* return error */
    }
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG45, &prev);              /* read gain */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                             /* sensor read failed */
        
        return 1;                                                                         /* return error */
    }
    prev &= ~(3 << 6);                                                                    /* clear settings */
    prev |= ((gain >> 8) & 0x03) << 6;                                                    /* set gain */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_REG45, prev);              /* write gain */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                            /* sensor write failed */
        
        return 1;                                                                         /* return error */
    }
    
    return 0;                                                                             /* success return 0 */
}

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
uint8_t ov2640_get_agc_gain(ov2640_handle_t *handle, uint16_t *gain)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_GAIN, &prev);       /* read gain */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *gain = prev;                                                                 /* get gain */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG45, &prev);      /* read gain */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *gain |= (uint16_t)((prev >> 6) & 0x03) << 8;                                 /* get gain */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_set_dummy_frame(ov2640_handle_t *handle, ov2640_dummy_frame_t frame)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM1, &prev);       /* read com1 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    prev &= ~(3 << 6);                                                            /* clear settings */
    prev |= (frame << 6);                                                         /* set frame */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM1, prev);       /* write com1 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_get_dummy_frame(ov2640_handle_t *handle, ov2640_dummy_frame_t *frame)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM1, &prev);       /* read com1 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *frame = (ov2640_dummy_frame_t)((prev >> 6) & 0x03);                          /* get frame */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_set_vertical_window_line_start(ov2640_handle_t *handle, uint16_t start)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (start > 0x3FF)                                                            /* check start */
    {
        handle->debug_print("ov2640: start > 0x3FF.\n");                          /* start > 0x3FF */
        
        return 4;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM1, &prev);       /* read com1 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    prev &= ~(3 << 0);                                                            /* clear settings */
    prev |= ((start & 0x03) << 0);                                                /* set vstart */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM1, prev);       /* write com1 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    prev = (start >> 2) & 0xFF;                                                   /* set msb part */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_VSTRT, prev);      /* write vstart */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_get_vertical_window_line_start(ov2640_handle_t *handle, uint16_t *start)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM1, &prev);       /* read com1 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *start = prev & 0x03;                                                         /* set start lsb */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_VSTRT, &prev);      /* read vstart */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *start |= (prev << 2);                                                        /* set msb */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_set_vertical_window_line_end(ov2640_handle_t *handle, uint16_t end)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (end > 0x3FF)                                                              /* check end */
    {
        handle->debug_print("ov2640: end > 0x3FF.\n");                            /* end > 0x3FF */
        
        return 4;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM1, &prev);       /* read com1 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    prev &= ~(3 << 2);                                                            /* clear settings */
    prev |= ((end & 0x03) << 2);                                                  /* set vend */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM1, prev);       /* write com1 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    prev = (end >> 2) & 0xFF;                                                     /* set msb part */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_VEND, prev);       /* write vend */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_get_vertical_window_line_end(ov2640_handle_t *handle, uint16_t *end)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM1, &prev);       /* read com1 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *end = (prev >> 2) & 0x03;                                                    /* set end lsb */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_VEND, &prev);       /* read vend */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *end |= (prev << 2);                                                          /* set msb */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_set_horizontal_mirror(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG04, &prev);      /* read reg04 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    prev &= ~(1 << 7);                                                            /* clear settings */
    prev |= enable << 7;                                                          /* set bool */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_REG04, prev);      /* write reg04 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_get_horizontal_mirror(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG04, &prev);      /* read reg04 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 7) & 0x01);                                /* get bool */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_set_vertical_flip(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG04, &prev);      /* read reg04 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    prev &= ~(1 << 6);                                                            /* clear settings */
    prev |= enable << 6;                                                          /* set bool */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_REG04, prev);      /* write reg04 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_get_vertical_flip(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG04, &prev);      /* read reg04 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 6) & 0x01);                                /* get bool */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_set_aec(ov2640_handle_t *handle, uint16_t aec)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG04, &prev);      /* read reg04 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    prev &= ~(3 << 0);                                                            /* clear settings */
    prev |= (aec & 0x03) << 0;                                                    /* set aec */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_REG04, prev);      /* write reg04 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    prev = (aec >> 2) & 0xFF;                                                     /* set aec */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_AEC, prev);        /* write aec */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG45, &prev);      /* read reg45 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    prev &= ~(0x3F << 0);                                                         /* clear settings */
    prev |= ((aec >> 10) & 0x3F) << 0;                                            /* set aec */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_REG45, prev);      /* write reg45 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_get_aec(ov2640_handle_t *handle, uint16_t *aec)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    *aec = 0;                                                                     /* init 0 */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG04, &prev);      /* read reg04 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *aec |= prev & 0x03;                                                          /* set bit[1:0] */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_AEC, &prev);        /* read aec */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *aec |= (prev << 2);                                                          /* set bit[9:2] */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG45, &prev);      /* read reg45 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *aec |= ((prev & 0x3F) << 10);                                                /* set bit[15:10] */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_set_frame_exposure_pre_charge_row_number(ov2640_handle_t *handle, uint8_t num)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    prev = num;                                                                   /* set number */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_REG08, prev);      /* write reg08 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_get_frame_exposure_pre_charge_row_number(ov2640_handle_t *handle, uint8_t *num)
{
    uint8_t res;
    
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG08, num);      /* read reg08 */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                   /* sensor read failed */
        
        return 1;                                                               /* return error */
    }
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t ov2640_set_mode(ov2640_handle_t *handle, ov2640_mode_t mode)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM2, &prev);      /* read com2 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 4);                                                           /* clear settings */
    prev |= mode << 4;                                                           /* set mode */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM2, prev);      /* write com2 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_mode(ov2640_handle_t *handle, ov2640_mode_t *mode)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM2, &prev);      /* read com2 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *mode = (ov2640_mode_t)((prev >> 4) & 0x01);                                 /* get mode */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_power_reset_pin_remap(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM2, &prev);      /* read com2 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 2);                                                           /* clear settings */
    prev |= enable << 2;                                                         /* set bool */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM2, prev);      /* write com2 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_power_reset_pin_remap(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM2, &prev);      /* read com2 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 2) & 0x01);                               /* get bool */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_output_drive(ov2640_handle_t *handle, ov2640_output_drive_t select)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM2, &prev);      /* read com2 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(3 << 0);                                                           /* clear settings */
    prev |= select << 0;                                                         /* set select */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM2, prev);      /* write com2 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_output_drive(ov2640_handle_t *handle, ov2640_output_drive_t *select)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM2, &prev);      /* read com2 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *select = (ov2640_output_drive_t)(prev & 0x03);                              /* get drive */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_band(ov2640_handle_t *handle, ov2640_band_t band)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM3, &prev);      /* read com3 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 2);                                                           /* clear settings */
    prev |= band << 2;                                                           /* set band */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM3, prev);      /* write com3 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_band(ov2640_handle_t *handle, ov2640_band_t *band)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM3, &prev);      /* read com3 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *band = (ov2640_band_t)((prev >> 2) & 0x01);                                 /* get band */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_auto_band(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM3, &prev);      /* read com3 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 1);                                                           /* clear settings */
    prev |= enable << 1;                                                         /* set bool */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM3, prev);      /* write com3 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_auto_band(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM3, &prev);      /* read com3 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 1) & 0x01);                               /* get bool */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_live_video_after_snapshot(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM3, &prev);      /* read com3 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 0);                                                           /* clear settings */
    prev |= enable << 0;                                                         /* set bool */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM3, prev);      /* write com3 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_live_video_after_snapshot(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM3, &prev);      /* read com3 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 0) & 0x01);                               /* get bool */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_clock_output_power_down_pin_status(ov2640_handle_t *handle, ov2640_pin_status_t status)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM4, &prev);      /* read com4 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 2);                                                           /* clear settings */
    prev |= status << 2;                                                         /* set status */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM4, prev);      /* write com4 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_clock_output_power_down_pin_status(ov2640_handle_t *handle, ov2640_pin_status_t *status)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM4, &prev);      /* read com4 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *status = (ov2640_pin_status_t)((prev >> 2) & 0x01);                         /* get pin status */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_clock_rate_double(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_CLKRC, &prev);     /* read clkrc */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 7);                                                           /* clear settings */
    prev |= enable << 7;                                                         /* set bool */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_CLKRC, prev);     /* write clkrc */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_clock_rate_double(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_CLKRC, &prev);     /* read clkrc */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 7) & 0x01);                               /* get bool */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_clock_divider(ov2640_handle_t *handle, uint8_t divider)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    if (divider > 0x3F)                                                          /* check divider */
    {
        handle->debug_print("ov2640: divider > 0x3F.\n");                        /* divider > 0x3F */
        
        return 4;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_CLKRC, &prev);     /* read clkrc */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(0x3F << 0);                                                        /* clear settings */
    prev |= divider << 0;                                                        /* set divider */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_CLKRC, prev);     /* write clkrc */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_clock_divider(ov2640_handle_t *handle, uint8_t *divider)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_CLKRC, &prev);     /* read clkrc */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *divider = (prev & 0x3F);                                                    /* get divider */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_soft_reset(ov2640_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM7, &prev);      /* read com7 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 7);                                                           /* clear settings */
    prev |= 1 << 7;                                                              /* set enable */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM7, prev);      /* write com7 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    handle->delay_ms(10);                                                        /* delay 10ms */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_resolution(ov2640_handle_t *handle, ov2640_resolution_t resolution)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM7, &prev);      /* read com7 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(7 << 4);                                                           /* clear settings */
    prev |= resolution << 4;                                                     /* set resolution */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM7, prev);      /* write com7 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_resolution(ov2640_handle_t *handle, ov2640_resolution_t *resolution)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM7, &prev);      /* read com7 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *resolution = (ov2640_resolution_t)((prev >> 4) & 0x07);                     /* get resolution */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_zoom(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM7, &prev);      /* read com7 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 2);                                                           /* clear settings */
    prev |= enable << 2;                                                         /* set bool */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM7, prev);      /* write com7 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_zoom(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM7, &prev);      /* read com7 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 2) & 0x01);                               /* get bool */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_color_bar_test(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM7, &prev);      /* read com7 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 1);                                                           /* clear settings */
    prev |= enable << 1;                                                         /* set bool */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM7, prev);      /* write com7 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_color_bar_test(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM7, &prev);      /* read com7 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 1) & 0x01);                               /* get bool */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_band_filter(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM8, &prev);      /* read com8 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 5);                                                           /* clear settings */
    prev |= enable << 5;                                                         /* set bool */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM8, prev);      /* write com8 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_band_filter(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM8, &prev);      /* read com8 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 5) & 0x01);                               /* get the bool */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_agc_control(ov2640_handle_t *handle, ov2640_control_t control)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM8, &prev);      /* read com8 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 2);                                                           /* clear settings */
    prev |= control << 2;                                                        /* set control */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM8, prev);      /* write com8 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_agc_control(ov2640_handle_t *handle, ov2640_control_t *control)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM8, &prev);      /* read com8 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *control = (ov2640_control_t)((prev >> 2) & 0x01);                           /* get control */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_exposure_control(ov2640_handle_t *handle, ov2640_control_t control)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM8, &prev);      /* read com8 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 0);                                                           /* clear settings */
    prev |= control << 0;                                                        /* set control */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM8, prev);      /* write com8 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_exposure_control(ov2640_handle_t *handle, ov2640_control_t *control)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM8, &prev);      /* read com8 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *control = (ov2640_control_t)((prev >> 0) & 0x01);                           /* get control */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_agc_gain_ceiling(ov2640_handle_t *handle, ov2640_agc_gain_t agc)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM9, &prev);      /* read com9 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(7 << 5);                                                           /* clear settings */
    prev |= agc << 5;                                                            /* set agc */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM9, prev);      /* write com9 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_agc_gain_ceiling(ov2640_handle_t *handle, ov2640_agc_gain_t *agc)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM9, &prev);      /* read com9 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *agc = (ov2640_agc_gain_t)((prev >> 5) & 0x07);                              /* get agc */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_chsync_href_swap(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM10, &prev);     /* read com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 7);                                                           /* clear settings */
    prev |= enable << 7;                                                         /* set bool */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM10, prev);     /* write com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_chsync_href_swap(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM10, &prev);     /* read com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 7) & 0x01);                               /* get bool */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_href_chsync_swap(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM10, &prev);     /* read com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 6);                                                           /* clear settings */
    prev |= enable << 6;                                                         /* set bool */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM10, prev);     /* write com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_href_chsync_swap(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM10, &prev);     /* read com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 6) & 0x01);                               /* get bool */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_pclk_output_qualified_by_href(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM10, &prev);     /* read com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 5);                                                           /* clear settings */
    prev |= enable << 5;                                                         /* set bool */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM10, prev);     /* write com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_pclk_output_qualified_by_href(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM10, &prev);     /* read com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 5) & 0x01);                               /* get bool */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_pclk_edge(ov2640_handle_t *handle, ov2640_edge_t edge)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM10, &prev);     /* read com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 4);                                                           /* clear settings */
    prev |= edge << 4;                                                           /* set edge */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM10, prev);     /* write com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_pclk_edge(ov2640_handle_t *handle, ov2640_edge_t *edge)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM10, &prev);     /* read com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *edge = (ov2640_edge_t)((prev >> 4) & 0x01);                                 /* get edge */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_href_polarity(ov2640_handle_t *handle, ov2640_polarity_t polarity)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM10, &prev);     /* read com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 3);                                                           /* clear settings */
    prev |= polarity << 3;                                                       /* set polarity */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM10, prev);     /* write com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_href_polarity(ov2640_handle_t *handle, ov2640_polarity_t *polarity)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM10, &prev);     /* read com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *polarity = (ov2640_polarity_t)((prev >> 3) & 0x01);                         /* get polarity */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_vsync_polarity(ov2640_handle_t *handle, ov2640_polarity_t polarity)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM10, &prev);     /* read com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 1);                                                           /* clear settings */
    prev |= polarity << 1;                                                       /* set polarity */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM10, prev);     /* write com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_vsync_polarity(ov2640_handle_t *handle, ov2640_polarity_t *polarity)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM10, &prev);     /* read com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *polarity = (ov2640_polarity_t)((prev >> 1) & 0x01);                         /* get polarity */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_hsync_polarity(ov2640_handle_t *handle, ov2640_polarity_t polarity)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM10, &prev);     /* read com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 0);                                                           /* clear settings */
    prev |= polarity << 0;                                                       /* set polarity */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM10, prev);     /* write com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_hsync_polarity(ov2640_handle_t *handle, ov2640_polarity_t *polarity)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM10, &prev);     /* read com10 */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *polarity = (ov2640_polarity_t)((prev >> 0) & 0x01);                         /* get polarity */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_luminance_signal_high_range(ov2640_handle_t *handle, uint8_t range)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    prev = range;                                                              /* set range */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_AEW, prev);     /* write aew */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                 /* sensor write failed */
        
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t ov2640_get_luminance_signal_high_range(ov2640_handle_t *handle, uint8_t *range)
{
    uint8_t res;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_AEW, range);     /* read aew */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                  /* sensor read failed */
        
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t ov2640_set_luminance_signal_low_range(ov2640_handle_t *handle, uint8_t range)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    prev = range;                                                              /* set range */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_AEB, prev);     /* write aeb */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                 /* sensor write failed */
        
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t ov2640_get_luminance_signal_low_range(ov2640_handle_t *handle, uint8_t *range)
{
    uint8_t res;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_AEB, range);     /* read aeb */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                  /* sensor read failed */
        
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t ov2640_set_fast_mode_large_step_range(ov2640_handle_t *handle, uint8_t high_threshold, uint8_t low_threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (high_threshold > 0xF)                                                 /* check high_threshold */
    {
        handle->debug_print("ov2640: high_threshold > 0xF.\n");               /* high_threshold > 0xF */
        
        return 4;                                                             /* return error */
    }
    if (low_threshold > 0xF)                                                  /* check low_threshold */
    {
        handle->debug_print("ov2640: low_threshold > 0xF.\n");                /* low_threshold > 0xF */
        
        return 5;                                                             /* return error */
    }
    
    prev = (high_threshold & 0xF) << 4 | (low_threshold & 0xF);               /* set range */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_VV, prev);     /* write vv */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                /* sensor write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_fast_mode_large_step_range(ov2640_handle_t *handle, uint8_t *high_threshold, uint8_t *low_threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_VV, &prev);     /* read vv */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                 /* sensor read failed */
        
        return 1;                                                             /* return error */
    }
    *high_threshold = (prev >> 4) & 0x0F;                                     /* get high threshold */
    *low_threshold = (prev >> 0) & 0x0F;                                      /* get low threshold */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_line_interval_adjust(ov2640_handle_t *handle, uint16_t adjust)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    if (adjust > 0xFFF)                                                          /* check adjust */
    {
        handle->debug_print("ov2640: adjust > 0xFFF.\n");                        /* adjust > 0xFFF */
        
        return 4;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG2A, &prev);     /* read reg2a */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(0xF << 4);                                                         /* clear settings */
    prev |= ((adjust >> 8) & 0xF) << 4;                                          /* set adjust */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_REG2A, prev);     /* write reg 2a */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    prev = adjust & 0xFF;                                                        /* set adjust */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_FRARL, prev);     /* write frarl */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_line_interval_adjust(ov2640_handle_t *handle, uint16_t *adjust)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG2A, &prev);     /* read reg2a */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *adjust = (uint16_t)((prev >> 4) & 0xFF) << 8;                               /* set adjust */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_FRARL, &prev);     /* read frarl */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *adjust |= prev;                                                             /* set adjust */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_hsync_position_and_width_end_point(ov2640_handle_t *handle, uint16_t position)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    if (position > 0x3FF)                                                        /* check position */
    {
        handle->debug_print("ov2640: position > 0x3FF.\n");                      /* position > 0x3FF */
        
        return 4;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG2A, &prev);     /* read reg2a */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(0x3 << 2);                                                         /* clear settings */
    prev |= ((position >> 8) & 0x3) << 2;                                        /* set position */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_REG2A, prev);     /* write reg 2a */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    prev = position & 0xFF;                                                      /* set position */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_HEDY, prev);      /* write hedy */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_hsync_position_and_width_end_point(ov2640_handle_t *handle, uint16_t *position)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG2A, &prev);     /* read reg2a */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *position = (uint16_t)((prev >> 2) & 0x03) << 8;                             /* set position */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_HEDY, &prev);      /* read hedy */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *position |= prev;                                                           /* set position */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_hsync_position_and_width_start_point(ov2640_handle_t *handle, uint16_t position)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    if (position > 0x3FF)                                                        /* check position */
    {
        handle->debug_print("ov2640: position > 0x3FF.\n");                      /* position > 0x3FF */
        
        return 4;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG2A, &prev);     /* read reg2a */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(0x3 << 0);                                                         /* clear settings */
    prev |= ((position >> 8) & 0x3) << 0;                                        /* set position */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_REG2A, prev);     /* write reg 2a */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    prev = position & 0xFF;                                                      /* set position */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_HSDY, prev);      /* write hsdy */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_hsync_position_and_width_start_point(ov2640_handle_t *handle, uint16_t *position)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG2A, &prev);     /* read reg2a */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *position = (uint16_t)((prev >> 0) & 0x03) << 8;                             /* set position */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_HSDY, &prev);      /* read hsdy */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *position |= prev;                                                           /* set position */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_vsync_pulse_width(ov2640_handle_t *handle, uint16_t width)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    prev = width & 0xFF;                                                         /* set width */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_ADDVSL, prev);    /* write addvsl */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    prev = (width >> 8) & 0xFF;                                                  /* set width */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_ADDVSH, prev);    /* write addvsh */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_vsync_pulse_width(ov2640_handle_t *handle, uint16_t *width)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_ADDVSL, &prev);    /* read addvsl */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *width = (uint16_t)prev;                                                     /* set width */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_ADDVSH, &prev);    /* read addvsh */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *width |= (uint16_t)prev << 8;                                               /* set width */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_luminance_average(ov2640_handle_t *handle, uint8_t average)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    prev = average;                                                              /* set average */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_YAVG, prev);      /* write yavg */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                   /* sensor write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_luminance_average(ov2640_handle_t *handle, uint8_t *average)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_YAVG, &prev);      /* read yavg */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                    /* sensor read failed */
        
        return 1;                                                                /* return error */
    }
    *average = prev;                                                             /* set average */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_horizontal_window_start(ov2640_handle_t *handle, uint16_t start)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (start > 0x7FF)                                                            /* check start */
    {
        handle->debug_print("ov2640: start > 0x7FF.\n");                          /* start > 0x7FF */
        
        return 4;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG32, &prev);      /* read reg32 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    prev &= ~(7 << 0);                                                            /* clear settings */
    prev |= ((start & 0x07) << 0);                                                /* set start */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_REG32, prev);      /* write reg32 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    prev = (start >> 3) & 0xFF;                                                   /* set msb part */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_HREFST, prev);     /* write hrefst */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_get_horizontal_window_start(ov2640_handle_t *handle, uint16_t *start)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG32, &prev);      /* read reg32 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *start = prev & 0x07;                                                         /* set start lsb */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_HREFST, &prev);     /* read hrefst */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *start |= (prev << 3);                                                        /* set msb */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_set_horizontal_window_end(ov2640_handle_t *handle, uint16_t end)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (end > 0x7FF)                                                              /* check end */
    {
        handle->debug_print("ov2640: end > 0x7FF.\n");                            /* end > 0x7FF */
        
        return 4;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG32, &prev);      /* read reg32 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    prev &= ~(7 << 3);                                                            /* clear settings */
    prev |= ((end & 0x07) << 3);                                                  /* set end */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_REG32, prev);      /* write reg32 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    prev = (end >> 3) & 0xFF;                                                     /* set msb part */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_HREFEND, prev);    /* write hrefend */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_get_horizontal_window_end(ov2640_handle_t *handle, uint16_t *end)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG32, &prev);      /* read reg32 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *end = (prev >> 3) & 0x07;                                                    /* set start lsb */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_HREFEND, &prev);    /* read hrefend */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *end |= (prev << 3);                                                          /* set msb */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_set_pclk(ov2640_handle_t *handle, ov2640_pclk_t pclk)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG32, &prev);      /* read reg32 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    prev &= ~(3 << 6);                                                            /* clear settings */
    prev |= (pclk << 6);                                                          /* pclk start */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_REG32, prev);      /* write reg32 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_get_pclk(ov2640_handle_t *handle, ov2640_pclk_t *pclk)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG32, &prev);      /* read reg32 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *pclk = (ov2640_pclk_t)((prev >> 6) & 0x03);                                  /* get pclk */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_set_zoom_window_horizontal_start_point(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_ARCOM2, &prev);     /* read arcom2 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    prev &= ~(1 << 2);                                                            /* clear settings */
    prev |= (enable << 2);                                                        /* set bool */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_ARCOM2, prev);     /* write arcom2 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_get_zoom_window_horizontal_start_point(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_ARCOM2, &prev);     /* read arcom2 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 2) & 0x01);                                /* get bool */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_set_frame_length_adjustment(ov2640_handle_t *handle, uint16_t frame)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (frame > 0x3FF)                                                            /* check frame */
    {
        handle->debug_print("ov2640: frame > 0x3FF.\n");                          /* frame > 0x3FF */
        
        return 4;                                                                 /* return error */
    }
    
    prev = frame & 0xFF;                                                          /* set frame lsb */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_FLL, prev);        /* write fll */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    prev = (frame >> 8) & 0xFF;                                                   /* set frame msb */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_FLH, prev);        /* write flh */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_get_frame_length_adjustment(ov2640_handle_t *handle, uint16_t *frame)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_FLL, &prev);        /* read fll */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *frame = (uint16_t)prev;                                                      /* set frame */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_FLH, &prev);        /* read flh */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *frame |= (uint16_t)prev << 8;                                                /* set frame */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_set_zoom_mode_vertical_window_start_point(ov2640_handle_t *handle, uint16_t point)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (point > 0x3FF)                                                            /* check point */
    {
        handle->debug_print("ov2640: point > 0x3FF.\n");                          /* point > 0x3FF */
        
        return 4;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM19, &prev);      /* read com19 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    prev &= ~(3 << 0);                                                            /* clear settings */
    prev |= point & 0x03;                                                         /* set point */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM19, prev);      /* write com19 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    prev = (point >> 2) & 0xFF;                                                   /* set point */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_ZOOMS, prev);      /* write zooms */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_get_zoom_mode_vertical_window_start_point(ov2640_handle_t *handle, uint16_t *point)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM19, &prev);      /* read com19 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *point = prev & 0x03;                                                         /* get point */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_ZOOMS, &prev);      /* read zooms */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *point |= prev << 2;                                                          /* set point */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_set_flash_light(ov2640_handle_t *handle, uint8_t control)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    prev = control;                                                               /* set control */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM22, prev);      /* write com22 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_get_flash_light(ov2640_handle_t *handle, uint8_t *control)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM22, &prev);      /* read com22 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *control = prev;                                                              /* get control */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_set_50hz_banding_aec(ov2640_handle_t *handle, uint16_t aec)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (aec > 0x3FF)                                                              /* check aec */
    {
        handle->debug_print("ov2640: aec > 0x3FF.\n");                            /* aec > 0x3FF */
        
        return 4;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM25, &prev);      /* read com25 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    prev &= ~(3 << 6);                                                            /* clear settings */
    prev |= ((aec >> 8) & 0x03) << 6;                                             /* set aec */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM25, prev);      /* write com25 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    prev = aec & 0xFF;                                                            /* set aec */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_BD50, prev);       /* write bd50 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_get_50hz_banding_aec(ov2640_handle_t *handle, uint16_t *aec)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM25, &prev);      /* read com25 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *aec = (uint16_t)((prev >> 6) & 0x03) << 8;                                   /* set aec */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_BD50, &prev);       /* read bd50 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *aec |= prev;                                                                 /* set aec */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_set_60hz_banding_aec(ov2640_handle_t *handle, uint16_t aec)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (aec > 0x3FF)                                                              /* check aec */
    {
        handle->debug_print("ov2640: aec > 0x3FF.\n");                            /* aec > 0x3FF */
        
        return 4;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM25, &prev);      /* read com25 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    prev &= ~(3 << 4);                                                            /* clear settings */
    prev |= ((aec >> 8) & 0x03) << 4;                                             /* set aec */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_COM25, prev);      /* write com25 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    prev = aec & 0xFF;                                                            /* set aec */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_BD60, prev);       /* write bd60 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_get_60hz_banding_aec(ov2640_handle_t *handle, uint16_t *aec)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_COM25, &prev);      /* read com25 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *aec = (uint16_t)((prev >> 4) & 0x03) << 8;                                   /* set aec */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_BD60, &prev);       /* read bd60 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *aec |= prev;                                                                 /* set aec */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_set_16_zone_average_weight_option(ov2640_handle_t *handle, uint32_t avg)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    prev = (avg >> 0) & 0xFF;                                                     /* set avg */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_REG5D, prev);      /* write reg 5d */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    prev = (avg >> 8) & 0xFF;                                                     /* set avg */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_REG5E, prev);      /* write reg5e */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    prev = (avg >> 16) & 0xFF;                                                    /* set avg */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_REG5F, prev);      /* write reg 5f */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    prev = (avg >> 24) & 0xFF;                                                    /* set avg */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_REG60, prev);      /* write reg60 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                    /* sensor write failed */
        
        return 1;                                                                 /* return error */
    }
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_get_16_zone_average_weight_option(ov2640_handle_t *handle, uint32_t *avg)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG5D, &prev);      /* read reg5d */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *avg = (uint32_t)prev;                                                        /* set avg */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG5E, &prev);      /* read reg5e */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *avg |= (uint32_t)prev << 8;                                                  /* set avg */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG5F, &prev);      /* read reg5f */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *avg |= (uint32_t)prev << 16;                                                 /* set avg */
    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_REG60, &prev);      /* read reg60 */
    if (res != 0)                                                                 /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                     /* sensor read failed */
        
        return 1;                                                                 /* return error */
    }
    *avg |= (uint32_t)prev << 24;                                                 /* set avg */
    
    return 0;                                                                     /* success return 0 */
}

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
uint8_t ov2640_set_histogram_algorithm_low_level(ov2640_handle_t *handle, uint8_t level)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }

    prev = level;                                                                       /* set level */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_HISTO_LOW, prev);        /* write histo low */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                          /* sensor write failed */
        
        return 1;                                                                       /* return error */
    }
    
    return 0;                                                                           /* success return 0 */
}

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
uint8_t ov2640_get_histogram_algorithm_low_level(ov2640_handle_t *handle, uint8_t *level)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                 /* check handle */
    {
        return 2;                                                                       /* return error */
    }
    if (handle->inited != 1)                                                            /* check handle initialization */
    {
        return 3;                                                                       /* return error */
    }

    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_HISTO_LOW, &prev);        /* read histo low */
    if (res != 0)                                                                       /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                           /* sensor read failed */
        
        return 1;                                                                       /* return error */
    }
    *level = prev;                                                                      /* get level */
    
    return 0;                                                                           /* success return 0 */
}

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
uint8_t ov2640_set_histogram_algorithm_high_level(ov2640_handle_t *handle, uint8_t level)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }

    prev = level;                                                                        /* set level */
    res = a_ov2640_sensor_write(handle, OV2640_REG_SENSOR_BANK_HISTO_HIGH, prev);        /* write histo high */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("ov2640: sensor write failed.\n");                           /* sensor write failed */
        
        return 1;                                                                        /* return error */
    }
    
    return 0;                                                                            /* success return 0 */
}

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
uint8_t ov2640_get_histogram_algorithm_high_level(ov2640_handle_t *handle, uint8_t *level)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }

    res = a_ov2640_sensor_read(handle, OV2640_REG_SENSOR_BANK_HISTO_HIGH, &prev);        /* read histo high */
    if (res != 0)                                                                        /* check result */
    {
        handle->debug_print("ov2640: sensor read failed.\n");                            /* sensor read failed */
        
        return 1;                                                                        /* return error */
    }
    *level = prev;                                                                       /* set level */
    
    return 0;                                                                            /* success return 0 */
}

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
uint8_t ov2640_set_dsp_bypass(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }

    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_R_BYPASS, &prev);        /* read r bypass */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                       /* dsp read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 0);                                                           /* clear settings */
    prev |= enable << 0;                                                         /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_R_BYPASS, prev);        /* write r bypass */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                      /* dsp write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_dsp_bypass(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }

    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_R_BYPASS, &prev);        /* read r bypass */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                       /* dsp read failed */
        
        return 1;                                                                /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 0) & 0x01);                               /* get bool */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_auto_mode(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }

    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_R_DVP_SP, &prev);        /* read r dvp sp */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                       /* dsp read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 7);                                                           /* clear settings */
    prev |= enable << 7;                                                         /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_R_DVP_SP, prev);        /* write r dvp sp */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                      /* dsp write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_auto_mode(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }

    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_R_DVP_SP, &prev);        /* read r dvp sp */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                       /* dsp read failed */
        
        return 1;                                                                /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 7) & 0x01);                               /* get bool */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_dvp_pclk(ov2640_handle_t *handle, uint8_t pclk)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    if (pclk > 0x7F)                                                             /* check pclk */
    {
        handle->debug_print("ov2640: pclk > 0x7F.\n");                           /* pclk > 0x7F */
        
        return 4;                                                                /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_R_DVP_SP, &prev);        /* read r dvp sp */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                       /* dsp read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(0x7F << 0);                                                        /* clear settings */
    prev |= pclk << 0;                                                           /* set pclk */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_R_DVP_SP, prev);        /* write r dvp sp */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                      /* dsp write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_dvp_pclk(ov2640_handle_t *handle, uint8_t *pclk)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_R_DVP_SP, &prev);        /* read r dvp sp */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                       /* dsp read failed */
        
        return 1;                                                                /* return error */
    }
    *pclk = prev & 0x7F;                                                         /* get pclk */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_dvp_y8(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_IMAGE_MODE, &prev);      /* read image mode */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                       /* dsp read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 6);                                                           /* clear settings */
    prev |= enable << 6;                                                         /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_IMAGE_MODE, prev);      /* write image mode */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                      /* dsp write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_dvp_y8(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_IMAGE_MODE, &prev);      /* read image mode */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                       /* dsp read failed */
        
        return 1;                                                                /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 6) & 0x01);                               /* get bool */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_jpeg_output(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_IMAGE_MODE, &prev);      /* read image mode */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                       /* dsp read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 4);                                                           /* clear settings */
    prev |= enable << 4;                                                         /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_IMAGE_MODE, prev);      /* write image mode */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                      /* dsp write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_jpeg_output(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_IMAGE_MODE, &prev);      /* read image mode */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                       /* dsp read failed */
        
        return 1;                                                                /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 4) & 0x01);                               /* get bool */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_dvp_output_format(ov2640_handle_t *handle, ov2640_dvp_output_format_t format)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_IMAGE_MODE, &prev);      /* read image mode */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                       /* dsp read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(3 << 2);                                                           /* clear settings */
    prev |= format << 2;                                                         /* set format */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_IMAGE_MODE, prev);      /* write image mode */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                      /* dsp write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_dvp_output_format(ov2640_handle_t *handle, ov2640_dvp_output_format_t *format)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_IMAGE_MODE, &prev);      /* read image mode */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                       /* dsp read failed */
        
        return 1;                                                                /* return error */
    }
    *format = (ov2640_dvp_output_format_t)((prev >> 2) & 0x3);                   /* set format */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_dvp_jpeg_output_href_timing(ov2640_handle_t *handle, ov2640_href_timing_t timing)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_IMAGE_MODE, &prev);      /* read image mode */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                       /* dsp read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 1);                                                           /* clear settings */
    prev |= timing << 1;                                                         /* set timing */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_IMAGE_MODE, prev);      /* write image mode */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                      /* dsp write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_dvp_jpeg_output_href_timing(ov2640_handle_t *handle, ov2640_href_timing_t *timing)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_IMAGE_MODE, &prev);      /* read image mode */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                       /* dsp read failed */
        
        return 1;                                                                /* return error */
    }
    *timing = (ov2640_href_timing_t)((prev >> 1) & 0x01);                        /* get timing */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_byte_swap(ov2640_handle_t *handle, ov2640_byte_swap_t byte_swap)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_IMAGE_MODE, &prev);      /* read image mode */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                       /* dsp read failed */
        
        return 1;                                                                /* return error */
    }
    prev &= ~(1 << 0);                                                           /* clear settings */
    prev |= byte_swap << 0;                                                      /* set byte swap */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_IMAGE_MODE, prev);      /* write image mode */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                      /* dsp write failed */
        
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_get_byte_swap(ov2640_handle_t *handle, ov2640_byte_swap_t *byte_swap)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_IMAGE_MODE, &prev);      /* read image mode */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                       /* dsp read failed */
        
        return 1;                                                                /* return error */
    }
    *byte_swap = (ov2640_byte_swap_t)((prev >> 0) & 0x01);                       /* get byte swap */
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ov2640_set_reset(ov2640_handle_t *handle, ov2640_reset_t type, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_RESET, &prev);        /* read reset */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << type);                                                     /* clear settings */
    prev |= enable << type;                                                   /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_RESET, prev);        /* write reset */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    handle->delay_ms(10);                                                     /* delay 10ms */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_reset(ov2640_handle_t *handle, ov2640_reset_t type, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_RESET, &prev);        /* read reset */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> type) & 0x01);                         /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_sccb_master_speed(ov2640_handle_t *handle, uint8_t speed)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    prev = speed;                                                             /* set speed */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_MS_SP, prev);        /* write sccb master speed */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_sccb_master_speed(ov2640_handle_t *handle, uint8_t *speed)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_MS_SP, &prev);        /* read sccb master speed */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *speed = prev;                                                            /* get speed */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_sccb_slave_id(ov2640_handle_t *handle, uint8_t id)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    prev = id;                                                                /* set id */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_SS_ID, prev);        /* write sccb slave id */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_sccb_slave_id(ov2640_handle_t *handle, uint8_t *id)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_SS_ID, &prev);        /* read sccb slave id */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *id = prev;                                                               /* set id */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_address_auto_increase(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_SS_CTRL, &prev);      /* read ss ctrl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 5);                                                        /* clear settings */
    prev |= enable << 5;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_SS_CTRL, prev);      /* write ss ctrl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_address_auto_increase(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_SS_CTRL, &prev);      /* read ss ctrl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 5) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_sccb(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_SS_CTRL, &prev);      /* read ss ctrl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 3);                                                        /* clear settings */
    prev |= enable << 3;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_SS_CTRL, prev);      /* write ss ctrl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_sccb(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_SS_CTRL, &prev);      /* read ss ctrl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 3) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_sccb_master_clock_delay(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_SS_CTRL, &prev);      /* read ss ctrl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 2);                                                        /* clear settings */
    prev |= enable << 2;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_SS_CTRL, prev);      /* write ss ctrl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_sccb_master_clock_delay(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_SS_CTRL, &prev);      /* read ss ctrl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 2) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_sccb_master_access(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_SS_CTRL, &prev);      /* read ss ctrl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 1);                                                        /* clear settings */
    prev |= enable << 1;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_SS_CTRL, prev);      /* write ss ctrl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_sccb_master_access(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_SS_CTRL, &prev);      /* read ss ctrl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 1) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_sensor_pass_through_access(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_SS_CTRL, &prev);      /* read ss ctrl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 0);                                                        /* clear settings */
    prev |= enable << 0;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_SS_CTRL, prev);      /* write ss ctrl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_sensor_pass_through_access(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_SS_CTRL, &prev);      /* read ss ctrl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 0) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_bist(ov2640_handle_t *handle, ov2640_bist_t bist, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_MC_BIST, &prev);      /* read mc bist */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << bist);                                                     /* clear settings */
    prev |= enable << bist;                                                   /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_MC_BIST, prev);      /* write mc bist */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_bist(ov2640_handle_t *handle, ov2640_bist_t bist, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_MC_BIST, &prev);      /* read mc bist */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> bist) & 0x01);                         /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_program_memory_pointer_address(ov2640_handle_t *handle, uint16_t addr)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    prev = addr & 0xFF;                                                     /* set address low */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_MC_AL, prev);      /* write mc al */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                 /* dsp write failed */
        
        return 1;                                                           /* return error */
    }
    prev = (addr >> 8) & 0xFF;                                              /* set address high */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_MC_AH, prev);      /* write mc ah */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                 /* dsp write failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t ov2640_get_program_memory_pointer_address(ov2640_handle_t *handle, uint16_t *addr)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_MC_AL, &prev);      /* read mc al */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                  /* dsp read failed */
        
        return 1;                                                           /* return error */
    }
    *addr = (uint16_t)prev;                                                 /* set lsb */
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_MC_AH, &prev);      /* read mc ah */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                  /* dsp read failed */
        
        return 1;                                                           /* return error */
    }
    *addr |= (uint16_t)((uint16_t)prev << 8);                               /* set msb */
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t ov2640_set_program_memory_pointer_access_address(ov2640_handle_t *handle, uint8_t addr)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    prev = addr;                                                            /* set address */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_MC_D, prev);       /* write mc d */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                 /* dsp write failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t ov2640_get_program_memory_pointer_access_address(ov2640_handle_t *handle, uint8_t *addr)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_MC_D, &prev);       /* read mc d */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                  /* dsp read failed */
        
        return 1;                                                           /* return error */
    }
    *addr = prev;                                                           /* set address */
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t ov2640_set_sccb_protocol_command(ov2640_handle_t *handle, uint8_t cmd)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    prev = cmd;                                                             /* set command */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_P_CMD, prev);      /* write p cmd */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                 /* dsp write failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t ov2640_get_sccb_protocol_command(ov2640_handle_t *handle, uint8_t *cmd)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_P_CMD, &prev);      /* read p cmd */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                  /* dsp read failed */
        
        return 1;                                                           /* return error */
    }
    *cmd = prev;                                                            /* set command */
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t ov2640_set_sccb_protocol_status(ov2640_handle_t *handle, uint8_t status)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    prev = status;                                                          /* set status */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_P_STATUS, prev);   /* write p status */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                 /* dsp write failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t ov2640_get_sccb_protocol_status(ov2640_handle_t *handle, uint8_t *status)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_P_STATUS, &prev);   /* read p status */
    if (res != 0)                                                           /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                  /* dsp read failed */
        
        return 1;                                                           /* return error */
    }
    *status = prev;                                                         /* set status */
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t ov2640_set_cip(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL1, &prev);        /* read ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 7);                                                        /* clear settings */
    prev |= enable << 7;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL1, prev);        /* write ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_cip(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL1, &prev);        /* read ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 7) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_dmy(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL1, &prev);        /* read ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 6);                                                        /* clear settings */
    prev |= enable << 6;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL1, prev);        /* write ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_dmy(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL1, &prev);        /* read ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 6) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_raw_gma(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL1, &prev);        /* read ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 5);                                                        /* clear settings */
    prev |= enable << 5;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL1, prev);        /* write ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_raw_gma(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL1, &prev);        /* read ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 5) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_dg(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL1, &prev);        /* read ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 4);                                                        /* clear settings */
    prev |= enable << 4;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL1, prev);        /* write ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_dg(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL1, &prev);        /* read ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 4) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_awb(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL1, &prev);        /* read ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 3);                                                        /* clear settings */
    prev |= enable << 3;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL1, prev);        /* write ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_awb(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL1, &prev);        /* read ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 3) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_awb_gain(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL1, &prev);        /* read ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 2);                                                        /* clear settings */
    prev |= enable << 2;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL1, prev);        /* write ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_awb_gain(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL1, &prev);        /* read ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 2) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_lenc(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL1, &prev);        /* read ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 1);                                                        /* clear settings */
    prev |= enable << 1;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL1, prev);        /* write ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_lenc(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL1, &prev);        /* read ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 1) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_pre(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL1, &prev);        /* read ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 0);                                                        /* clear settings */
    prev |= enable << 0;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL1, prev);        /* write ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_pre(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL1, &prev);        /* read ctrl1 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 0) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_aec_enable(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL0, &prev);        /* read ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 7);                                                        /* clear settings */
    prev |= enable << 7;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL0, prev);        /* write ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_aec_enable(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL0, &prev);        /* read ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 7) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_aec_sel(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL0, &prev);        /* read ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 6);                                                        /* clear settings */
    prev |= enable << 6;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL0, prev);        /* write ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_aec_sel(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL0, &prev);        /* read ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 6) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_stat_sel(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL0, &prev);        /* read ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 5);                                                        /* clear settings */
    prev |= enable << 5;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL0, prev);        /* write ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_stat_sel(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL0, &prev);        /* read ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 5) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_vfirst(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL0, &prev);        /* read ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 4);                                                        /* clear settings */
    prev |= enable << 4;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL0, prev);        /* write ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_vfirst(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL0, &prev);        /* read ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 4) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_yuv422(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL0, &prev);        /* read ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 3);                                                        /* clear settings */
    prev |= enable << 3;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL0, prev);        /* write ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_yuv422(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL0, &prev);        /* read ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 3) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_yuv(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL0, &prev);        /* read ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 2);                                                        /* clear settings */
    prev |= enable << 2;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL0, prev);        /* write ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_yuv(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL0, &prev);        /* read ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 2) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_rgb(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL0, &prev);        /* read ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 1);                                                        /* clear settings */
    prev |= enable << 1;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL0, prev);        /* write ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_rgb(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL0, &prev);        /* read ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 1) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_raw(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL0, &prev);        /* read ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 0);                                                        /* clear settings */
    prev |= enable << 0;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL0, prev);        /* write ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_raw(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL0, &prev);        /* read ctrl0 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 0) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_dcw(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL2, &prev);        /* read ctrl2 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 5);                                                        /* clear settings */
    prev |= enable << 5;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL2, prev);        /* write ctrl2 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_dcw(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL2, &prev);        /* read ctrl2 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 5) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_sde(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL2, &prev);        /* read ctrl2 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 4);                                                        /* clear settings */
    prev |= enable << 4;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL2, prev);        /* write ctrl2 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_sde(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL2, &prev);        /* read ctrl2 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 4) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_uv_adj(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL2, &prev);        /* read ctrl2 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 3);                                                        /* clear settings */
    prev |= enable << 3;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL2, prev);        /* write ctrl2 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_uv_adj(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL2, &prev);        /* read ctrl2 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 3) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_uv_avg(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL2, &prev);        /* read ctrl2 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 2);                                                        /* clear settings */
    prev |= enable << 2;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL2, prev);        /* write ctrl2 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_uv_avg(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL2, &prev);        /* read ctrl2 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 2) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_cmx(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL2, &prev);        /* read ctrl2 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 0);                                                        /* clear settings */
    prev |= enable << 0;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL2, prev);        /* write ctrl2 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_cmx(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL2, &prev);        /* read ctrl2 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 0) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_bpc(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL3, &prev);        /* read ctrl3 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 7);                                                        /* clear settings */
    prev |= enable << 7;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL3, prev);        /* write ctrl3 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_bpc(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL3, &prev);        /* read ctrl3 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 7) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_wpc(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL3, &prev);        /* read ctrl3 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 6);                                                        /* clear settings */
    prev |= enable << 6;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRL3, prev);        /* write ctrl3 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_wpc(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRL3, &prev);        /* read ctrl3 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 6) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_sde_indirect_register_address(ov2640_handle_t *handle, uint8_t addr)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    prev = addr;                                                              /* set address */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_BPADDR, prev);       /* write bpaddr */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_sde_indirect_register_address(ov2640_handle_t *handle, uint8_t *addr)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_BPADDR, &prev);       /* read bpaddr */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *addr = prev;                                                             /* get address */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_sde_indirect_register_data(ov2640_handle_t *handle, uint8_t data)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    prev = data;                                                              /* set data */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_BPDATA, prev);       /* write bpdata */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_sde_indirect_register_data(ov2640_handle_t *handle, uint8_t *data)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_BPDATA, &prev);       /* read bpdata */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *data = prev;                                                             /* get data */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_image_horizontal(ov2640_handle_t *handle, uint16_t size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (size > 0xFFF)                                                         /* check size */
    {
        handle->debug_print("ov2640: size > 0xFFF.\n");                       /* size > 0xFFF */
        
        return 4;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_SIZEL, &prev);        /* read sizel */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 6);                                                        /* clear hsize bit11 */
    prev &= ~(7 << 3);                                                        /* clear hsize bit2-0 */
    prev |= ((size >> 11) & 0x01) << 6;                                       /* set bit11 */
    prev |= ((size >> 0) & 0x07) << 3;                                        /* set bit2-0 */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_SIZEL, prev);        /* write sizel */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    prev = (size >> 3) & 0xFF;                                                /* set data */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_HSIZE8, prev);       /* write hsize8 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_image_horizontal(ov2640_handle_t *handle, uint16_t *size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_SIZEL, &prev);        /* read sizel */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size = (uint16_t)((prev >> 6) & 0x01) << 11;                             /* set bit11 */
    *size |= ((prev >> 3) & 0x07) << 0;                                       /* set bit0-2 */
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_HSIZE8, &prev);       /* read hsize8 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size |= prev << 3;                                                       /* set bit3-10 */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_image_vertical(ov2640_handle_t *handle, uint16_t size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (size > 0x7FF)                                                         /* check size */
    {
        handle->debug_print("ov2640: size > 0x7FF.\n");                       /* size > 0x7FF */
        
        return 4;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_SIZEL, &prev);        /* read sizel */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(7 << 0);                                                        /* clear hsize bit2-0 */
    prev |= ((size >> 0) & 0x07) << 0;                                        /* set bit2-0 */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_SIZEL, prev);        /* write sizel */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    prev = (size >> 3) & 0xFF;                                                /* set data */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_VSIZE8, prev);       /* write vsize8 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_image_vertical(ov2640_handle_t *handle, uint16_t *size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_SIZEL, &prev);        /* read sizel */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size = ((prev >> 0) & 0x07) << 0;                                        /* set bit0-2 */
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_VSIZE8, &prev);       /* read vsize8 */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size |= prev << 3;                                                       /* set bit3-10 */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_quantization_scale_factor(ov2640_handle_t *handle, uint8_t factor)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    prev = factor;                                                        /* set factor */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_QS, prev);       /* write qs */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");               /* dsp write failed */
        
        return 1;                                                         /* return error */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t ov2640_get_quantization_scale_factor(ov2640_handle_t *handle, uint8_t *factor)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_QS, &prev);       /* read qs */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                /* dsp read failed */
        
        return 1;                                                         /* return error */
    }
    *factor = prev;                                                       /* set factor */
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t ov2640_set_lp_dp(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRLI, &prev);        /* read ctrli */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 7);                                                        /* clear settings */
    prev |= enable << 7;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRLI, prev);        /* write ctrli */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_lp_dp(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRLI, &prev);        /* read ctrli */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 7) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_round(ov2640_handle_t *handle, ov2640_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRLI, &prev);        /* read ctrli */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 6);                                                        /* clear settings */
    prev |= enable << 6;                                                      /* set bool */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRLI, prev);        /* write ctrli */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_round(ov2640_handle_t *handle, ov2640_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRLI, &prev);        /* read ctrli */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (ov2640_bool_t)((prev >> 6) & 0x01);                            /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_vertical_divider(ov2640_handle_t *handle, uint8_t divider)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (divider > 7)                                                          /* check divider */
    {
        handle->debug_print("ov2640: divider > 7.\n");                        /* divider > 7 */
        
        return 4;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRLI, &prev);        /* read ctrli */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(7 << 3);                                                        /* clear settings */
    prev |= divider << 3;                                                     /* set divider */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRLI, prev);        /* write ctrli */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_vertical_divider(ov2640_handle_t *handle, uint8_t *divider)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRLI, &prev);        /* read ctrli */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *divider = (prev >> 3) & 0x7;                                             /* set divider */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_horizontal_divider(ov2640_handle_t *handle, uint8_t divider)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (divider > 7)                                                          /* check divider */
    {
        handle->debug_print("ov2640: divider > 7.\n");                        /* divider > 7 */
        
        return 4;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRLI, &prev);        /* read ctrli */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(7 << 0);                                                        /* clear settings */
    prev |= divider << 0;                                                     /* set divider */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_CTRLI, prev);        /* write ctrli */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_horizontal_divider(ov2640_handle_t *handle, uint8_t *divider)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_CTRLI, &prev);        /* read ctrli */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *divider = (prev >> 0) & 0x7;                                             /* set divider */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_horizontal_size(ov2640_handle_t *handle, uint16_t size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (size > 0x3FF)                                                         /* check size */
    {
        handle->debug_print("ov2640: size > 0x3FF.\n");                       /* size > 0x3FF */
        
        return 4;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_TEST, &prev);         /* read test */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 7);                                                        /* clear hsize bit11 */
    prev |= ((size >> 9) & 0x01) << 7;                                        /* set bit9 */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_TEST, prev);         /* write test */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_VHYX, &prev);         /* read vhyx */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 3);                                                        /* clear hsize bit11 */
    prev |= ((size >> 8) & 0x01) << 3;                                        /* set bit8 */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_VHYX, prev);         /* write vhyx */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    prev = (size >> 0) & 0xFF;                                                /* set data */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_HSIZE, prev);        /* write hsize */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_horizontal_size(ov2640_handle_t *handle, uint16_t *size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_TEST, &prev);         /* read test */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size = (uint16_t)((prev >> 7) & 0x01) << 9;                              /* set size */
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_VHYX, &prev);         /* read vhyx */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size |= (uint16_t)((prev >> 3) & 0x01) << 8;                             /* set size */
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_HSIZE, &prev);        /* read hsize */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size |= prev;                                                            /* set size */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_vertical_size(ov2640_handle_t *handle, uint16_t size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (size > 0x1FF)                                                         /* check size */
    {
        handle->debug_print("ov2640: size > 0x1FF.\n");                       /* size > 0x1FF */
        
        return 4;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_VHYX, &prev);         /* read vhyx */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 7);                                                        /* clear hsize bit11 */
    prev |= ((size >> 8) & 0x01) << 7;                                        /* set bit8 */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_VHYX, prev);         /* write vhyx */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    prev = (size >> 0) & 0xFF;                                                /* set data */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_VSIZE, prev);        /* write vsize */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_vertical_size(ov2640_handle_t *handle, uint16_t *size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_VHYX, &prev);         /* read vhyx */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size = (uint16_t)((prev >> 7) & 0x01) << 8;                              /* set size */
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_VSIZE, &prev);        /* read vsize */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size |= prev;                                                            /* set size */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_offset_x(ov2640_handle_t *handle, uint16_t size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (size > 0x7FF)                                                         /* check size */
    {
        handle->debug_print("ov2640: size > 0x7FF.\n");                       /* size > 0x7FF */
        
        return 4;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_VHYX, &prev);         /* read vhyx */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(7 << 0);                                                        /* clear settings */
    prev |= ((size >> 8) & 0x07) << 0;                                        /* set bit8 */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_VHYX, prev);         /* write vhyx */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    prev = (size >> 0) & 0xFF;                                                /* set data */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_XOFFL, prev);        /* write xoffl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_offset_x(ov2640_handle_t *handle, uint16_t *size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_VHYX, &prev);         /* read vhyx */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size = (uint16_t)((prev >> 0) & 0x07) << 8;                              /* set size */
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_XOFFL, &prev);        /* read xoffl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size |= prev;                                                            /* set size */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_offset_y(ov2640_handle_t *handle, uint16_t size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (size > 0x7FF)                                                         /* check size */
    {
        handle->debug_print("ov2640: size > 0x7FF.\n");                       /* size > 0x7FF */
        
        return 4;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_VHYX, &prev);         /* read vhyx */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(7 << 4);                                                        /* clear settings */
    prev |= ((size >> 8) & 0x07) << 4;                                        /* set bit8 */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_VHYX, prev);         /* write vhyx */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    prev = (size >> 0) & 0xFF;                                                /* set data */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_YOFFL, prev);        /* write yoffl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_offset_y(ov2640_handle_t *handle, uint16_t *size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_VHYX, &prev);         /* read vhyx */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size = (uint16_t)((prev >> 4) & 0x07) << 8;                              /* set size */
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_YOFFL, &prev);        /* read yoffl */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size |= prev;                                                            /* set size */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_dp_selx(ov2640_handle_t *handle, uint8_t size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (size > 0xF)                                                           /* check size */
    {
        handle->debug_print("ov2640: size > 0xF.\n");                         /* size > 0xF */
        
        return 4;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_DPRP, &prev);         /* read dprp */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(0xF << 0);                                                      /* clear settings */
    prev |= size << 0;                                                        /* set size */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_DPRP, prev);         /* write dprp */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_dp_selx(ov2640_handle_t *handle, uint8_t *size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_DPRP, &prev);         /* read dprp */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size = prev & 0xF;                                                       /* get size */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_dp_sely(ov2640_handle_t *handle, uint8_t size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (size > 0xF)                                                           /* check size */
    {
        handle->debug_print("ov2640: size > 0xF.\n");                         /* size > 0xF */
        
        return 4;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_DPRP, &prev);         /* read dprp */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(0xF << 4);                                                      /* clear settings */
    prev |= size << 4;                                                        /* set size */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_DPRP, prev);         /* write dprp */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_dp_sely(ov2640_handle_t *handle, uint8_t *size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_DPRP, &prev);         /* read dprp */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size = (prev >> 4) & 0xF;                                                /* get size */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_output_width(ov2640_handle_t *handle, uint16_t size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (size > 0x3FF)                                                         /* check size */
    {
        handle->debug_print("ov2640: size > 0x3FF.\n");                       /* size > 0x3FF */
        
        return 4;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_ZMHH, &prev);         /* read zmhh */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(0x3 << 0);                                                      /* clear settings */
    prev |= ((size >> 8) & 0x3) << 0;                                         /* set size */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_ZMHH, prev);         /* write zmhh */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    prev = size & 0xFF;                                                       /* set size */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_ZMOW, prev);         /* write zmow */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_output_width(ov2640_handle_t *handle, uint16_t *size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }

    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_ZMHH, &prev);         /* read zmhh */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size = (uint16_t)(prev & 0x03) << 8;                                     /* set size */
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_ZMOW, &prev);         /* read zmow */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size |= prev;                                                            /* set size */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_output_height(ov2640_handle_t *handle, uint16_t size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (size > 0x1FF)                                                         /* check size */
    {
        handle->debug_print("ov2640: size > 0x1FF.\n");                       /* size > 0x1FF */
        
        return 4;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_ZMHH, &prev);         /* read zmhh */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(0x1 << 2);                                                      /* clear settings */
    prev |= ((size >> 8) & 0x1) << 2;                                         /* set size */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_ZMHH, prev);         /* write zmhh */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    prev = size & 0xFF;                                                       /* set size */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_ZMOH, prev);         /* write zmoh */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_output_height(ov2640_handle_t *handle, uint16_t *size)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }

    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_ZMHH, &prev);         /* read zmhh */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size = (uint16_t)((prev >> 2) & 0x01) << 8;                              /* set size */
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_ZMOH, &prev);         /* read zmoh */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *size |= prev;                                                            /* set size */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_zoom_speed(ov2640_handle_t *handle, uint8_t speed)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    if (speed > 0xF)                                                          /* check result */
    {
        handle->debug_print("ov2640: speed > 0xF.\n");                        /* speed > 0xF */
        
        return 4;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_ZMHH, &prev);         /* read zmhh */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(0xF << 4);                                                      /* clear settings */
    prev |= speed << 4;                                                       /* set speed */
    res = a_ov2640_dsp_write(handle, OV2640_REG_DSP_BANK_ZMHH, prev);         /* write zmhh */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_get_zoom_speed(ov2640_handle_t *handle, uint8_t *speed)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_ov2640_dsp_read(handle, OV2640_REG_DSP_BANK_ZMHH, &prev);         /* read zmhh */
    if (res != 0)                                                             /* check result */
    {
        handle->debug_print("ov2640: dsp read failed.\n");                    /* dsp read failed */
        
        return 1;                                                             /* return error */
    }
    *speed = (prev >> 4) & 0xFF;                                              /* get speed */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t ov2640_set_light_mode(ov2640_handle_t *handle, ov2640_light_mode_t mode)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    
    switch (mode)                                                                     /* select mode */
    {
        case OV2640_LIGHT_MODE_AUTO :                                                 /* auto */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0xC7, prev);                             /* write 0xc7 */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_LIGHT_MODE_SUNNY :                                                /* sunny */
        {
            prev = 0x40;                                                              /* set 0x40 */
            res = a_ov2640_dsp_write(handle, 0xC7, prev);                             /* write 0xc7 */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x5E;                                                              /* set 0x5E */
            res = a_ov2640_dsp_write(handle, 0xCC, prev);                             /* write 0xcc */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x41;                                                              /* set 0x41 */
            res = a_ov2640_dsp_write(handle, 0xCD, prev);                             /* write 0xcd */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x54;                                                              /* set 0x54 */
            res = a_ov2640_dsp_write(handle, 0xCE, prev);                             /* write 0xce */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_LIGHT_MODE_CLOUDY :                                               /* cloudy */
        {
            prev = 0x40;                                                              /* set 0x40 */
            res = a_ov2640_dsp_write(handle, 0xC7, prev);                             /* write 0xc7 */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x65;                                                              /* set 0x65 */
            res = a_ov2640_dsp_write(handle, 0xCC, prev);                             /* write 0xcc */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x41;                                                              /* set 0x41 */
            res = a_ov2640_dsp_write(handle, 0xCD, prev);                             /* write 0xcd */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x4F;                                                              /* set 0x4F */
            res = a_ov2640_dsp_write(handle, 0xCE, prev);                             /* write 0xce */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_LIGHT_MODE_OFFICE :                                               /* office */
        {
            prev = 0x40;                                                              /* set 0x40 */
            res = a_ov2640_dsp_write(handle, 0xC7, prev);                             /* write 0xc7 */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x52;                                                              /* set 0x52 */
            res = a_ov2640_dsp_write(handle, 0xCC, prev);                             /* write 0xcc */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x41;                                                              /* set 0x41 */
            res = a_ov2640_dsp_write(handle, 0xCD, prev);                             /* write 0xcd */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x66;                                                              /* set 0x66 */
            res = a_ov2640_dsp_write(handle, 0xCE, prev);                             /* write 0xce */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_LIGHT_MODE_HOME :                                                 /* home */
        {
            prev = 0x40;                                                              /* set 0x40 */
            res = a_ov2640_dsp_write(handle, 0xC7, prev);                             /* write 0xc7 */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x42;                                                              /* set 0x42 */
            res = a_ov2640_dsp_write(handle, 0xCC, prev);                             /* write 0xcc */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x3F;                                                              /* set 0x3F */
            res = a_ov2640_dsp_write(handle, 0xCD, prev);                             /* write 0xcd */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x71;                                                              /* set 0x71 */
            res = a_ov2640_dsp_write(handle, 0xCE, prev);                             /* write 0xce */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        default :                                                                     /* default */
        {
            res = 1;                                                                  /* set error */
            
            break;                                                                    /* break */
        }
    }
    
    return res;                                                                       /* success return 0 */
}

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
uint8_t ov2640_set_color_saturation(ov2640_handle_t *handle, ov2640_color_saturation_t color)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    
    switch (color)                                                                    /* select color saturation */
    {
        case OV2640_COLOR_SATURATION_POSITIVE_2 :                                     /* saturation +2 */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x02;                                                              /* set 0x02 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x03;                                                              /* set 0x03 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x68;                                                              /* set 0x68 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x68;                                                              /* set 0x68 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_COLOR_SATURATION_POSITIVE_1 :                                     /* saturation +1 */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x02;                                                              /* set 0x02 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x03;                                                              /* set 0x03 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x58;                                                              /* set 0x58 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x58;                                                              /* set 0x58 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_COLOR_SATURATION_0 :                                              /* saturation 0 */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x02;                                                              /* set 0x02 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x03;                                                              /* set 0x03 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x48;                                                              /* set 0x48 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x48;                                                              /* set 0x48 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_COLOR_SATURATION_NEGATIVE_1 :                                     /* saturation -1 */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x02;                                                              /* set 0x02 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x03;                                                              /* set 0x03 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x38;                                                              /* set 0x38 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x38;                                                              /* set 0x38 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_COLOR_SATURATION_NEGATIVE_2 :                                     /* saturation -2 */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x02;                                                              /* set 0x02 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x03;                                                              /* set 0x03 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x28;                                                              /* set 0x28 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x28;                                                              /* set 0x28 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        default :                                                                     /* default */
        {
            res = 1;                                                                  /* set error */
            
            break;                                                                    /* break */
        }
    }
    
    return res;                                                                       /* success return 0 */
}

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
uint8_t ov2640_set_brightness(ov2640_handle_t *handle, ov2640_brightness_t brightness)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    
    switch (brightness)                                                               /* select brightness */
    {
        case OV2640_BRIGHTNESS_POSITIVE_2 :                                           /* brightness +2 */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x04;                                                              /* set 0x04 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x09;                                                              /* set 0x09 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x40;                                                              /* set 0x40 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_BRIGHTNESS_POSITIVE_1 :                                           /* brightness +1 */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x04;                                                              /* set 0x04 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x09;                                                              /* set 0x09 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x30;                                                              /* set 0x30 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_BRIGHTNESS_0 :                                                    /* brightness 0 */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x04;                                                              /* set 0x04 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x09;                                                              /* set 0x09 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x20;                                                              /* set 0x20 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_BRIGHTNESS_NEGATIVE_1 :                                           /* brightness -1 */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x04;                                                              /* set 0x04 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x09;                                                              /* set 0x09 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x10;                                                              /* set 0x10 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_BRIGHTNESS_NEGATIVE_2 :                                           /* brightness -2 */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x04;                                                              /* set 0x04 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x09;                                                              /* set 0x09 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        default :                                                                     /* default */
        {
            res = 1;                                                                  /* set error */
            
            break;                                                                    /* break */
        }
    }
    
    return res;                                                                       /* success return 0 */
}

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
uint8_t ov2640_set_contrast(ov2640_handle_t *handle, ov2640_contrast_t contrast)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    
    switch (contrast)                                                                 /* select contrast */
    {
        case OV2640_CONTRAST_POSITIVE_2 :                                             /* contrast +2 */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x04;                                                              /* set 0x04 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x07;                                                              /* set 0x07 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x20;                                                              /* set 0x20 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x28;                                                              /* set 0x28 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x0C;                                                              /* set 0x0C */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x06;                                                              /* set 0x06 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_CONTRAST_POSITIVE_1 :                                             /* contrast +1 */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x04;                                                              /* set 0x04 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x07;                                                              /* set 0x07 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x20;                                                              /* set 0x20 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x24;                                                              /* set 0x24 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x16;                                                              /* set 0x16 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x06;                                                              /* set 0x06 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_CONTRAST_0 :                                                      /* contrast 0 */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x04;                                                              /* set 0x04 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x07;                                                              /* set 0x07 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x20;                                                              /* set 0x20 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x20;                                                              /* set 0x20 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x20;                                                              /* set 0x20 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x06;                                                              /* set 0x06 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_CONTRAST_NEGATIVE_1 :                                             /* contrast -1 */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x04;                                                              /* set 0x04 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x07;                                                              /* set 0x07 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x20;                                                              /* set 0x20 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x1C;                                                              /* set 0x1C */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x2A;                                                              /* set 0x2A */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x06;                                                              /* set 0x06 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_CONTRAST_NEGATIVE_2 :                                             /* contrast -2 */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x04;                                                              /* set 0x04 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x07;                                                              /* set 0x07 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x20;                                                              /* set 0x20 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x18;                                                              /* set 0x18 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x34;                                                              /* set 0x34 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x06;                                                              /* set 0x06 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        default :                                                                     /* default */
        {
            res = 1;                                                                  /* set error */
            
            break;                                                                    /* break */
        }
    }
    
    return res;                                                                       /* success return 0 */
}

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
uint8_t ov2640_set_special_effect(ov2640_handle_t *handle, ov2640_special_effect_t effect)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    
    switch (effect)                                                                   /* select effect */
    {
        case OV2640_SPECIAL_EFFECT_ANTIQUE :                                          /* antique */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x18;                                                              /* set 0x18 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x05;                                                              /* set 0x05 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x40;                                                              /* set 0x40 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0xA6;                                                              /* set 0xA6 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_SPECIAL_EFFECT_BLUISH :                                           /* bluish */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x18;                                                              /* set 0x18 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x05;                                                              /* set 0x05 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0xA0;                                                              /* set 0xA0 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x40;                                                              /* set 0x40 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_SPECIAL_EFFECT_GREENISH :                                         /* greenish */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x18;                                                              /* set 0x18 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x05;                                                              /* set 0x05 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x40;                                                              /* set 0x40 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x40;                                                              /* set 0x40 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_SPECIAL_EFFECT_REDDISH :                                          /* reddish */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x18;                                                              /* set 0x18 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x05;                                                              /* set 0x05 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x40;                                                              /* set 0x40 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0xC0;                                                              /* set 0xC0 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_SPECIAL_EFFECT_BW :                                               /* b&w */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x18;                                                              /* set 0x18 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x05;                                                              /* set 0x05 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x80;                                                              /* set 0x80 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x80;                                                              /* set 0x80 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_SPECIAL_EFFECT_NEGATIVE :                                         /* negative */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x40;                                                              /* set 0x40 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x05;                                                              /* set 0x05 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x80;                                                              /* set 0x80 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x80;                                                              /* set 0x80 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_SPECIAL_EFFECT_BW_NEGATIVE :                                      /* b&w negative */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x58;                                                              /* set 0x58 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x05;                                                              /* set 0x05 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x80;                                                              /* set 0x80 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x80;                                                              /* set 0x80 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        case OV2640_SPECIAL_EFFECT_NORMAL :                                           /* normal */
        {
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x00;                                                              /* set 0x00 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x05;                                                              /* set 0x05 */
            res = a_ov2640_dsp_write(handle, 0x7C, prev);                             /* write 0x7c */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x80;                                                              /* set 0x80 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            prev = 0x80;                                                              /* set 0x80 */
            res = a_ov2640_dsp_write(handle, 0x7D, prev);                             /* write 0x7d */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("ov2640: dsp write failed.\n");                   /* dsp write failed */
                
                break;                                                                /* break */
            }
            
            break;                                                                    /* break */
        }
        default :                                                                     /* default */
        {
            res = 1;                                                                  /* set error */
            
            break;                                                                    /* break */
        }
    }
    
    return res;                                                                       /* success return 0 */
}

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
uint8_t ov2640_get_dsp_reg(ov2640_handle_t *handle, uint8_t reg, uint8_t *data)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    return a_ov2640_dsp_read(handle, reg, data);        /* dsp read */
}

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
uint8_t ov2640_set_dsp_reg(ov2640_handle_t *handle, uint8_t reg, uint8_t data)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    return a_ov2640_dsp_write(handle, reg, data);       /* dsp write */
}

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
uint8_t ov2640_get_sensor_reg(ov2640_handle_t *handle, uint8_t reg, uint8_t *data)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    return a_ov2640_sensor_read(handle, reg, data);     /* sensor read */
}

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
uint8_t ov2640_set_sensor_reg(ov2640_handle_t *handle, uint8_t reg, uint8_t data)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    return a_ov2640_sensor_write(handle, reg, data);    /* sensor write */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an ov2640 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ov2640_info(ov2640_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(ov2640_info_t));                         /* initialize ov2640 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "SCCB DVP", 16);                       /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
