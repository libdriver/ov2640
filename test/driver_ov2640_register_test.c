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
 * @file      driver_ov2640_register_test.c
 * @brief     driver ov2640 register test source file
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
 
#include "driver_ov2640_register_test.h"
#include <stdlib.h>

static ov2640_handle_t gs_handle;        /**< ov2640 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t ov2640_register_test(void)
{
    uint8_t res;
    uint8_t reg8;
    uint8_t reg8_check;
    uint8_t high_threshold;
    uint8_t low_threshold;
    uint8_t high_threshold_check;
    uint8_t low_threshold_check;
    uint16_t reg16;
    uint16_t reg16_check;
    uint32_t reg32;
    uint32_t reg32_check;
    ov2640_info_t info;
    ov2640_dummy_frame_t dummy_frame;
    ov2640_bool_t enable;
    ov2640_mode_t mode;
    ov2640_output_drive_t drive;
    ov2640_band_t band;
    ov2640_pin_status_t status;
    ov2640_resolution_t resolution;
    ov2640_control_t control;
    ov2640_edge_t edge;
    ov2640_polarity_t polarity;
    ov2640_agc_gain_t agc;
    ov2640_pclk_t pclk;
    ov2640_dvp_output_format_t format;
    ov2640_href_timing_t timing;
    ov2640_byte_swap_t byte_swap;

    /* link interface function */
    DRIVER_OV2640_LINK_INIT(&gs_handle, ov2640_handle_t);
    DRIVER_OV2640_LINK_SCCB_INIT(&gs_handle, ov2640_interface_sccb_init);
    DRIVER_OV2640_LINK_SCCB_DEINIT(&gs_handle, ov2640_interface_sccb_deinit);
    DRIVER_OV2640_LINK_SCCB_READ(&gs_handle, ov2640_interface_sccb_read);
    DRIVER_OV2640_LINK_SCCB_WRITE(&gs_handle, ov2640_interface_sccb_write);
    DRIVER_OV2640_LINK_POWER_DOWN_INIT(&gs_handle, ov2640_interface_power_down_init);
    DRIVER_OV2640_LINK_POWER_DOWN_DEINIT(&gs_handle, ov2640_interface_power_down_deinit);
    DRIVER_OV2640_LINK_POWER_DOWN_WRITE(&gs_handle, ov2640_interface_power_down_write);
    DRIVER_OV2640_LINK_RESET_INIT(&gs_handle, ov2640_interface_reset_init);
    DRIVER_OV2640_LINK_RESET_DEINIT(&gs_handle, ov2640_interface_reset_deinit);
    DRIVER_OV2640_LINK_RESET_WRITE(&gs_handle, ov2640_interface_reset_write);
    DRIVER_OV2640_LINK_DELAY_MS(&gs_handle, ov2640_interface_delay_ms);
    DRIVER_OV2640_LINK_DEBUG_PRINT(&gs_handle, ov2640_interface_debug_print);
    
    /* get information */
    res = ov2640_info(&info);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip info */
        ov2640_interface_debug_print("ov2640: chip is %s.\n", info.chip_name);
        ov2640_interface_debug_print("ov2640: manufacturer is %s.\n", info.manufacturer_name);
        ov2640_interface_debug_print("ov2640: interface is %s.\n", info.interface);
        ov2640_interface_debug_print("ov2640: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ov2640_interface_debug_print("ov2640: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ov2640_interface_debug_print("ov2640: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ov2640_interface_debug_print("ov2640: max current is %0.2fmA.\n", info.max_current_ma);
        ov2640_interface_debug_print("ov2640: max temperature is %0.1fC.\n", info.temperature_max);
        ov2640_interface_debug_print("ov2640: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start register test */
    ov2640_interface_debug_print("ov2640: start register test.\n");
    
    /* init */
    res = ov2640_init(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    /* ov2640_set_agc_gain/ov2640_get_agc_gain test */
    ov2640_interface_debug_print("ov2640: ov2640_set_agc_gain/ov2640_get_agc_gain test.\n");
    
    reg16 = rand() % 256 | 0x100;
    res = ov2640_set_agc_gain(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set agc gain failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set agc gain %d.\n", reg16);
    res = ov2640_get_agc_gain(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get agc gain failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check agc gain %s.\n", reg16 == reg16_check ? "ok" : "error");
    
    /* ov2640_set_dummy_frame/ov2640_get_dummy_frame test */
    ov2640_interface_debug_print("ov2640: ov2640_set_dummy_frame/ov2640_get_dummy_frame test.\n");
    
    /* set dummy frame 1 */
    res = ov2640_set_dummy_frame(&gs_handle, OV2640_DUMMY_FRAME_1);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dummy frame failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set dummy frame 1.\n");
    res = ov2640_get_dummy_frame(&gs_handle, &dummy_frame);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dummy frame failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dummy frame %s.\n", dummy_frame == OV2640_DUMMY_FRAME_1 ? "ok" : "error");
    
    /* set dummy frame 3 */
    res = ov2640_set_dummy_frame(&gs_handle, OV2640_DUMMY_FRAME_3);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dummy frame failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set dummy frame 3.\n");
    res = ov2640_get_dummy_frame(&gs_handle, &dummy_frame);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dummy frame failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dummy frame %s.\n", dummy_frame == OV2640_DUMMY_FRAME_3 ? "ok" : "error");
    
    /* set dummy frame 7 */
    res = ov2640_set_dummy_frame(&gs_handle, OV2640_DUMMY_FRAME_7);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dummy frame failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set dummy frame 7.\n");
    res = ov2640_get_dummy_frame(&gs_handle, &dummy_frame);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dummy frame failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dummy frame %s.\n", dummy_frame == OV2640_DUMMY_FRAME_7 ? "ok" : "error");
    
    /* ov2640_set_vertical_window_line_start/ov2640_get_vertical_window_line_start test */
    ov2640_interface_debug_print("ov2640: ov2640_set_vertical_window_line_start/ov2640_get_vertical_window_line_start test.\n");
    
    reg16 = (rand() % 256) | (uint16_t)((uint16_t)1 << 8);
    res = ov2640_set_vertical_window_line_start(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vertical window line start failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set vertical window line start %d.\n", reg16);
    res = ov2640_get_vertical_window_line_start(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get vertical window line start failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check vertical window line start %s.\n", reg16 == reg16_check ? "ok" : "error");
    
    /* ov2640_set_vertical_window_line_end/ov2640_get_vertical_window_line_end test */
    ov2640_interface_debug_print("ov2640: ov2640_set_vertical_window_line_end/ov2640_get_vertical_window_line_end test.\n");
    
    reg16 = (rand() % 256) | (uint16_t)((uint16_t)2 << 8);
    res = ov2640_set_vertical_window_line_end(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vertical window line end failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set vertical window line end %d.\n", reg16);
    res = ov2640_get_vertical_window_line_end(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get vertical window line end failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check vertical window line end %s.\n", reg16 == reg16_check ? "ok" : "error");
    
    /* ov2640_set_horizontal_mirror/ov2640_get_horizontal_mirror test */
    ov2640_interface_debug_print("ov2640: ov2640_set_horizontal_mirror/ov2640_get_horizontal_mirror test.\n");
    
    /* enable horizontal mirror */
    res = ov2640_set_horizontal_mirror(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set horizontal mirror failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable horizontal mirror.\n");
    res = ov2640_get_horizontal_mirror(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get horizontal mirror failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check horizontal mirror %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable horizontal mirror */
    res = ov2640_set_horizontal_mirror(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set horizontal mirror failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable horizontal mirror.\n");
    res = ov2640_get_horizontal_mirror(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get horizontal mirror failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check horizontal mirror %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_vertical_flip/ov2640_get_vertical_flip test */
    ov2640_interface_debug_print("ov2640: ov2640_set_vertical_flip/ov2640_get_vertical_flip test.\n");
    
    /* enable vertical flip */
    res = ov2640_set_vertical_flip(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vertical flip failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable vertical flip.\n");
    res = ov2640_get_vertical_flip(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get vertical flip failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check vertical flip %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable vertical flip */
    res = ov2640_set_vertical_flip(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vertical flip failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable vertical flip.\n");
    res = ov2640_get_vertical_flip(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get vertical flip failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check vertical flip %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_aec/ov2640_get_aec test */
    ov2640_interface_debug_print("ov2640: ov2640_set_aec/ov2640_get_aec test.\n");
    
    reg16 = rand() % 0xFFFFU;
    res = ov2640_set_aec(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set aec failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set aec %d.\n", reg16);
    res = ov2640_get_aec(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get aec failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check aec %s.\n", reg16 == reg16_check ? "ok" : "error");
    
    /* ov2640_set_frame_exposure_pre_charge_row_number/ov2640_get_frame_exposure_pre_charge_row_number test */
    ov2640_interface_debug_print("ov2640: ov2640_set_frame_exposure_pre_charge_row_number/ov2640_get_frame_exposure_pre_charge_row_number test.\n");
    
    reg8 = rand() % 256;
    res = ov2640_set_frame_exposure_pre_charge_row_number(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set frame exposure pre charge row number failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set frame exposure pre charge row number %d.\n", reg8);
    res = ov2640_get_frame_exposure_pre_charge_row_number(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get frame exposure pre charge row number failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check frame exposure pre charge row number %s.\n", reg8 == reg8_check ? "ok" : "error");
    
    /* ov2640_set_mode/ov2640_get_mode test */
    ov2640_interface_debug_print("ov2640: ov2640_set_mode/ov2640_get_mode test.\n");
    
    /* set standby mode */
    res = ov2640_set_mode(&gs_handle, OV2640_MODE_STANDBY);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set mode failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set standby mode.\n");
    res = ov2640_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get mode failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check mode %s.\n", mode == OV2640_MODE_STANDBY ? "ok" : "error");
    
    /* set normal mode */
    res = ov2640_set_mode(&gs_handle, OV2640_MODE_NORMAL);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set mode failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set normal mode.\n");
    res = ov2640_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get mode failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check mode %s.\n", mode == OV2640_MODE_NORMAL ? "ok" : "error");
    
    /* ov2640_set_power_reset_pin_remap/ov2640_get_power_reset_pin_remap test */
    ov2640_interface_debug_print("ov2640: ov2640_set_power_reset_pin_remap/ov2640_get_power_reset_pin_remap test.\n");
    
    /* enable power reset pin remap */
    res = ov2640_set_power_reset_pin_remap(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set power reset pin remap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable power reset pin remap.\n");
    res = ov2640_get_power_reset_pin_remap(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get power reset pin remap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check power reset pin remap %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable power reset pin remap */
    res = ov2640_set_power_reset_pin_remap(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set power reset pin remap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable power reset pin remap.\n");
    res = ov2640_get_power_reset_pin_remap(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get power reset pin remap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check power reset pin remap %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_output_drive/ov2640_get_output_drive test */
    ov2640_interface_debug_print("ov2640: ov2640_set_output_drive/ov2640_get_output_drive test.\n");
    
    /* 1 capability */
    res = ov2640_set_output_drive(&gs_handle, OV2640_OUTPUT_DRIVE_1_CAPABILITY);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set output drive failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set output drive 1 capability.\n");
    res = ov2640_get_output_drive(&gs_handle, &drive);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get output drive failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check output drive %s.\n", drive == OV2640_OUTPUT_DRIVE_1_CAPABILITY ? "ok" : "error");
    
    /* 2 capability */
    res = ov2640_set_output_drive(&gs_handle, OV2640_OUTPUT_DRIVE_2_CAPABILITY);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set output drive failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set output drive 2 capability.\n");
    res = ov2640_get_output_drive(&gs_handle, &drive);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get output drive failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check output drive %s.\n", drive == OV2640_OUTPUT_DRIVE_2_CAPABILITY ? "ok" : "error");
    
    /* 3 capability */
    res = ov2640_set_output_drive(&gs_handle, OV2640_OUTPUT_DRIVE_3_CAPABILITY);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set output drive failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set output drive 3 capability.\n");
    res = ov2640_get_output_drive(&gs_handle, &drive);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get output drive failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check output drive %s.\n", drive == OV2640_OUTPUT_DRIVE_3_CAPABILITY ? "ok" : "error");
    
    /* 4 capability */
    res = ov2640_set_output_drive(&gs_handle, OV2640_OUTPUT_DRIVE_4_CAPABILITY);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set output drive failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set output drive 4 capability.\n");
    res = ov2640_get_output_drive(&gs_handle, &drive);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get output drive failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check output drive %s.\n", drive == OV2640_OUTPUT_DRIVE_4_CAPABILITY ? "ok" : "error");
    
    /* ov2640_set_band/ov2640_get_band test */
    ov2640_interface_debug_print("ov2640: ov2640_set_band/ov2640_get_band test.\n");
    
    /* set band 60Hz */
    res = ov2640_set_band(&gs_handle, OV2640_BAND_60HZ);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set band failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set band 60Hz.\n");
    res = ov2640_get_band(&gs_handle, &band);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get band failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check band %s.\n", band == OV2640_BAND_60HZ ? "ok" : "error");
    
    /* set band 50Hz */
    res = ov2640_set_band(&gs_handle, OV2640_BAND_50HZ);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set band failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set band 50Hz.\n");
    res = ov2640_get_band(&gs_handle, &band);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get band failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check band %s.\n", band == OV2640_BAND_50HZ ? "ok" : "error");
    
    /* ov2640_set_auto_band/ov2640_get_auto_band test */
    ov2640_interface_debug_print("ov2640: ov2640_set_auto_band/ov2640_get_auto_band test.\n");
    
    /* disable auto band */
    res = ov2640_set_auto_band(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set auto band failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable auto band.\n");
    res = ov2640_get_auto_band(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get auto band failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check auto band %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* enable auto band */
    res = ov2640_set_auto_band(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set auto band failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable auto band.\n");
    res = ov2640_get_auto_band(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get auto band failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check auto band %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* ov2640_set_live_video_after_snapshot/ov2640_get_live_video_after_snapshot test */
    ov2640_interface_debug_print("ov2640: ov2640_set_live_video_after_snapshot/ov2640_get_live_video_after_snapshot test.\n");
    
    /* enable live video after snapshot */
    res = ov2640_set_live_video_after_snapshot(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set live video after snapshot failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable live video after snapshot.\n");
    res = ov2640_get_live_video_after_snapshot(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get live video after snapshot failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check live video after snapshot %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable live video after snapshot */
    res = ov2640_set_live_video_after_snapshot(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set live video after snapshot failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable live video after snapshot.\n");
    res = ov2640_get_live_video_after_snapshot(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get live video after snapshot failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check live video after snapshot %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_clock_output_power_down_pin_status/ov2640_get_clock_output_power_down_pin_status test */
    ov2640_interface_debug_print("ov2640: ov2640_set_clock_output_power_down_pin_status/ov2640_get_clock_output_power_down_pin_status test.\n");
    
    /* set clock output power down pin last state */
    res = ov2640_set_clock_output_power_down_pin_status(&gs_handle, OV2640_PIN_STATUS_LAST_STATE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set clock output power down pin status failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set clock output power down pin last state.\n");
    res = ov2640_get_clock_output_power_down_pin_status(&gs_handle, &status);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get clock output power down pin status failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check clock output power down pin status %s.\n", status == OV2640_PIN_STATUS_LAST_STATE ? "ok" : "error");
    
    /* set clock output power down pin tri state */
    res = ov2640_set_clock_output_power_down_pin_status(&gs_handle, OV2640_PIN_STATUS_TRI_STATE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set clock output power down pin status failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set clock output power down pin tri state.\n");
    res = ov2640_get_clock_output_power_down_pin_status(&gs_handle, &status);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get clock output power down pin status failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check clock output power down pin status %s.\n", status == OV2640_PIN_STATUS_TRI_STATE ? "ok" : "error");
    
    /* ov2640_set_clock_rate_double/ov2640_get_clock_rate_double test */
    ov2640_interface_debug_print("ov2640: ov2640_set_clock_rate_double/ov2640_get_clock_rate_double test.\n");
    
    /* enable clock rate double */
    res = ov2640_set_clock_rate_double(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set clock rate double failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable clock rate double.\n");
    res = ov2640_get_clock_rate_double(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get clock rate double failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check clock rate double %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable clock rate double */
    res = ov2640_set_clock_rate_double(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set clock rate double failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable clock rate double.\n");
    res = ov2640_get_clock_rate_double(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get clock rate double failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check clock rate double %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_clock_divider/ov2640_get_clock_divider test */
    ov2640_interface_debug_print("ov2640: ov2640_set_clock_divider/ov2640_get_clock_divider test.\n");
    
    reg8 = rand() % 0x3F;
    res = ov2640_set_clock_divider(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set clock divider failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set clock divider %d.\n", reg8);
    res = ov2640_get_clock_divider(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get clock divider failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check clock divider %s.\n", reg8 == reg8_check ? "ok" : "error");
    
    /* ov2640_soft_reset test */
    ov2640_interface_debug_print("ov2640: ov2640_soft_reset test.\n");
    
    /* soft reset */
    res = ov2640_soft_reset(&gs_handle);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: soft reset failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check soft reset %s.\n", res == 0 ? "ok" : "error");
    
    /* ov2640_set_resolution/ov2640_get_resolution test */
    ov2640_interface_debug_print("ov2640: ov2640_set_resolution/ov2640_get_resolution test.\n");
    
    /* set resolution uxga */
    res = ov2640_set_resolution(&gs_handle, OV2640_RESOLUTION_UXGA);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set resolution failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set resolution uxga.\n");
    res = ov2640_get_resolution(&gs_handle, &resolution);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get resolution failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check resolution %s.\n", resolution == OV2640_RESOLUTION_UXGA ? "ok" : "error");
    
    /* set resolution cif */
    res = ov2640_set_resolution(&gs_handle, OV2640_RESOLUTION_CIF);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set resolution failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set resolution cif.\n");
    res = ov2640_get_resolution(&gs_handle, &resolution);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get resolution failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check resolution %s.\n", resolution == OV2640_RESOLUTION_CIF ? "ok" : "error");
    
    /* set resolution svga */
    res = ov2640_set_resolution(&gs_handle, OV2640_RESOLUTION_SVGA);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set resolution failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set resolution svga.\n");
    res = ov2640_get_resolution(&gs_handle, &resolution);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get resolution failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check resolution %s.\n", resolution == OV2640_RESOLUTION_SVGA ? "ok" : "error");
    
    /* ov2640_set_zoom/ov2640_get_zoom test */
    ov2640_interface_debug_print("ov2640: ov2640_set_zoom/ov2640_get_zoom test.\n");
    
    /* enable zoom */
    res = ov2640_set_zoom(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set zoom failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable zoom.\n");
    res = ov2640_get_zoom(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get zoom failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check zoom %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable zoom */
    res = ov2640_set_zoom(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set zoom failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable zoom.\n");
    res = ov2640_get_zoom(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get zoom failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check zoom %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_color_bar_test/ov2640_get_color_bar_test test */
    ov2640_interface_debug_print("ov2640: ov2640_set_color_bar_test/ov2640_get_color_bar_test test.\n");
    
    /* enable color bar test */
    res = ov2640_set_color_bar_test(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set color bar test failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable color bar test.\n");
    res = ov2640_get_color_bar_test(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get color bar test failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check color bar test %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable color bar test */
    res = ov2640_set_color_bar_test(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set color bar test failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable color bar test.\n");
    res = ov2640_get_color_bar_test(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get color bar test failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check color bar test %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_band_filter/ov2640_get_band_filter test */
    ov2640_interface_debug_print("ov2640: ov2640_set_band_filter/ov2640_get_band_filter test.\n");
    
    /* enable band filter */
    res = ov2640_set_band_filter(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set band filter failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable band filter.\n");
    res = ov2640_get_band_filter(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get band filter failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check band filter %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable band filter */
    res = ov2640_set_band_filter(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set band filter failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable band filter.\n");
    res = ov2640_get_band_filter(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get band filter failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check band filter %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_agc_control/ov2640_get_agc_control test */
    ov2640_interface_debug_print("ov2640: ov2640_set_agc_control/ov2640_get_agc_control test.\n");
    
    /* set agc control manual */
    res = ov2640_set_agc_control(&gs_handle, OV2640_CONTROL_MANUAL);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set agc control failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set agc control manual.\n");
    res = ov2640_get_agc_control(&gs_handle, &control);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get agc control failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check agc control %s.\n", control == OV2640_CONTROL_MANUAL ? "ok" : "error");
    
    /* set agc control auto */
    res = ov2640_set_agc_control(&gs_handle, OV2640_CONTROL_AUTO);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set agc control failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set agc control auto.\n");
    res = ov2640_get_agc_control(&gs_handle, &control);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get agc control failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check agc control %s.\n", control == OV2640_CONTROL_AUTO ? "ok" : "error");
    
    /* ov2640_set_exposure_control/ov2640_get_exposure_control test */
    ov2640_interface_debug_print("ov2640: ov2640_set_exposure_control/ov2640_get_exposure_control test.\n");
    
    /* set exposure control manual */
    res = ov2640_set_exposure_control(&gs_handle, OV2640_CONTROL_MANUAL);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set exposure control failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set exposure control manual.\n");
    res = ov2640_get_exposure_control(&gs_handle, &control);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get exposure control failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check exposure control %s.\n", control == OV2640_CONTROL_MANUAL ? "ok" : "error");
    
    /* set exposure control auto */
    res = ov2640_set_exposure_control(&gs_handle, OV2640_CONTROL_AUTO);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set exposure control failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set exposure control auto.\n");
    res = ov2640_get_exposure_control(&gs_handle, &control);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get exposure control failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check exposure control %s.\n", control == OV2640_CONTROL_AUTO ? "ok" : "error");
    
    /* ov2640_set_agc/ov2640_get_agc test */
    ov2640_interface_debug_print("ov2640: ov2640_set_agc/ov2640_get_agc test.\n");
    
    /* 2x */
    res = ov2640_set_agc_gain_ceiling(&gs_handle, OV2640_AGC_2X);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set agc gain ceiling failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set agc gain ceiling 2x.\n");
    res = ov2640_get_agc_gain_ceiling(&gs_handle, &agc);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get agc gain ceiling failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check agc gain ceiling %s.\n", OV2640_AGC_2X == agc ? "ok" : "error");
    
    /* 4x */
    res = ov2640_set_agc_gain_ceiling(&gs_handle, OV2640_AGC_4X);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set agc gain ceiling failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set agc gain ceiling 4x.\n");
    res = ov2640_get_agc_gain_ceiling(&gs_handle, &agc);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get agc gain ceiling failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check agc gain ceiling %s.\n", OV2640_AGC_4X == agc ? "ok" : "error");
    
    /* 8x */
    res = ov2640_set_agc_gain_ceiling(&gs_handle, OV2640_AGC_8X);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set agc gain ceiling failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set agc gain ceiling 8x.\n");
    res = ov2640_get_agc_gain_ceiling(&gs_handle, &agc);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get agc gain ceiling failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check agc gain ceiling %s.\n", OV2640_AGC_8X == agc ? "ok" : "error");
    
    /* 16x */
    res = ov2640_set_agc_gain_ceiling(&gs_handle, OV2640_AGC_16X);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set agc gain ceiling failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set agc gain ceiling 16x.\n");
    res = ov2640_get_agc_gain_ceiling(&gs_handle, &agc);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get agc gain ceiling failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check agc gain ceiling %s.\n", OV2640_AGC_16X == agc ? "ok" : "error");
    
    /* 32x */
    res = ov2640_set_agc_gain_ceiling(&gs_handle, OV2640_AGC_32X);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set agc gain ceiling failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set agc gain ceiling 32x.\n");
    res = ov2640_get_agc_gain_ceiling(&gs_handle, &agc);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get agc gain ceiling failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check agc gain ceiling %s.\n", OV2640_AGC_32X == agc ? "ok" : "error");
    
    /* 64x */
    res = ov2640_set_agc_gain_ceiling(&gs_handle, OV2640_AGC_64X);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set agc gain ceiling failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set agc gain ceiling 64x.\n");
    res = ov2640_get_agc_gain_ceiling(&gs_handle, &agc);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get agc gain ceiling failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check agc gain ceiling %s.\n", OV2640_AGC_64X == agc ? "ok" : "error");
    
    /* 128x */
    res = ov2640_set_agc_gain_ceiling(&gs_handle, OV2640_AGC_128X);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set agc gain ceiling failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set agc gain ceiling 128x.\n");
    res = ov2640_get_agc_gain_ceiling(&gs_handle, &agc);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get agc gain ceiling failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check agc gain ceiling %s.\n", OV2640_AGC_128X == agc ? "ok" : "error");
    
    /* ov2640_set_chsync_href_swap/ov2640_get_chsync_href_swap test */
    ov2640_interface_debug_print("ov2640: ov2640_set_chsync_href_swap/ov2640_get_chsync_href_swap test.\n");
    
    /* enable chsync href swap */
    res = ov2640_set_chsync_href_swap(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set chsync href swap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable chsync href swap.\n");
    res = ov2640_get_chsync_href_swap(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get chsync href swap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check chsync href swap %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable chsync href swap */
    res = ov2640_set_chsync_href_swap(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set chsync href swap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable chsync href swap.\n");
    res = ov2640_get_chsync_href_swap(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get chsync href swap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check chsync href swap %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_href_chsync_swap/ov2640_get_href_chsync_swap test */
    ov2640_interface_debug_print("ov2640: ov2640_set_href_chsync_swap/ov2640_get_href_chsync_swap test.\n");
    
    /* enable href chsync swap */
    res = ov2640_set_href_chsync_swap(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set href chsync swap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable href chsync swap.\n");
    res = ov2640_get_href_chsync_swap(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get href chsync swap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check href chsync swap %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable href chsync swap */
    res = ov2640_set_href_chsync_swap(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set href chsync swap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable href chsync swap.\n");
    res = ov2640_get_href_chsync_swap(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get href chsync swap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check href chsync swap %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_pclk_output_qualified_by_href/ov2640_get_pclk_output_qualified_by_href test */
    ov2640_interface_debug_print("ov2640: ov2640_set_pclk_output_qualified_by_href/ov2640_get_pclk_output_qualified_by_href test.\n");
    
    /* enable pclk output qualified by href */
    res = ov2640_set_pclk_output_qualified_by_href(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set pclk output qualified by href failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable pclk output qualified by href.\n");
    res = ov2640_get_pclk_output_qualified_by_href(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get pclk output qualified by href failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check pclk output qualified by href %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable pclk output qualified by href */
    res = ov2640_set_pclk_output_qualified_by_href(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set pclk output qualified by href failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable pclk output qualified by href.\n");
    res = ov2640_get_pclk_output_qualified_by_href(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get pclk output qualified by href failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check pclk output qualified by href %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_pclk_output_qualified_by_href/ov2640_get_pclk_output_qualified_by_href test */
    ov2640_interface_debug_print("ov2640: ov2640_set_pclk_output_qualified_by_href/ov2640_get_pclk_output_qualified_by_href test.\n");
    
    /* set pclk edge falling */
    res = ov2640_set_pclk_edge(&gs_handle, OV2640_EDGE_FALLING);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set pclk edge failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set pclk edge falling.\n");
    res = ov2640_get_pclk_edge(&gs_handle, &edge);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get pclk edge failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check pclk edge %s.\n", edge == OV2640_EDGE_FALLING ? "ok" : "error");
    
    /* set pclk edge rising */
    res = ov2640_set_pclk_edge(&gs_handle, OV2640_EDGE_RISING);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set pclk edge failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set pclk edge rising.\n");
    res = ov2640_get_pclk_edge(&gs_handle, &edge);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get pclk edge failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check pclk edge %s.\n", edge == OV2640_EDGE_RISING ? "ok" : "error");
    
    /* ov2640_set_href_polarity/ov2640_get_href_polarity test */
    ov2640_interface_debug_print("ov2640: ov2640_set_href_polarity/ov2640_get_href_polarity test.\n");
    
    /* set href polarity positive */
    res = ov2640_set_href_polarity(&gs_handle, OV2640_POLARITY_POSITIVE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set href polarity failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set href polarity positive.\n");
    res = ov2640_get_href_polarity(&gs_handle, &polarity);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get href polarity failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check href polarity %s.\n", polarity == OV2640_POLARITY_POSITIVE ? "ok" : "error");
    
    /* set href polarity negative */
    res = ov2640_set_href_polarity(&gs_handle, OV2640_POLARITY_NEGATIVE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set href polarity failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set href polarity negative.\n");
    res = ov2640_get_href_polarity(&gs_handle, &polarity);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get href polarity failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check href polarity %s.\n", polarity == OV2640_POLARITY_NEGATIVE ? "ok" : "error");
    
    /* ov2640_set_vsync_polarity/ov2640_get_vsync_polarity test */
    ov2640_interface_debug_print("ov2640: ov2640_set_vsync_polarity/ov2640_get_vsync_polarity test.\n");
    
    /* set vsync polarity positive */
    res = ov2640_set_vsync_polarity(&gs_handle, OV2640_POLARITY_POSITIVE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vsync polarity failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set vsync polarity positive.\n");
    res = ov2640_get_vsync_polarity(&gs_handle, &polarity);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get vsync polarity failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check vsync polarity %s.\n", polarity == OV2640_POLARITY_POSITIVE ? "ok" : "error");
    
    /* set vsync polarity negative */
    res = ov2640_set_vsync_polarity(&gs_handle, OV2640_POLARITY_NEGATIVE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vsync polarity failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set vsync polarity negative.\n");
    res = ov2640_get_vsync_polarity(&gs_handle, &polarity);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get vsync polarity failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check vsync polarity %s.\n", polarity == OV2640_POLARITY_NEGATIVE ? "ok" : "error");
    
    /* ov2640_set_hsync_polarity/ov2640_get_hsync_polarity test */
    ov2640_interface_debug_print("ov2640: ov2640_set_hsync_polarity/ov2640_get_hsync_polarity test.\n");
    
    /* set hsync polarity positive */
    res = ov2640_set_hsync_polarity(&gs_handle, OV2640_POLARITY_POSITIVE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set hsync polarity failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set hsync polarity positive.\n");
    res = ov2640_get_hsync_polarity(&gs_handle, &polarity);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get hsync polarity failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check hsync polarity %s.\n", polarity == OV2640_POLARITY_POSITIVE ? "ok" : "error");
    
    /* set hsync polarity negative */
    res = ov2640_set_hsync_polarity(&gs_handle, OV2640_POLARITY_NEGATIVE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set hsync polarity failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set hsync polarity negative.\n");
    res = ov2640_get_hsync_polarity(&gs_handle, &polarity);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get hsync polarity failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check hsync polarity %s.\n", polarity == OV2640_POLARITY_NEGATIVE ? "ok" : "error");
    
    /* ov2640_set_luminance_signal_high_range/ov2640_get_luminance_signal_high_range test */
    ov2640_interface_debug_print("ov2640: ov2640_set_luminance_signal_high_range/ov2640_get_luminance_signal_high_range test.\n");
    
    reg8 = rand() % 256;
    res = ov2640_set_luminance_signal_high_range(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set luminance signal high range failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set luminance signal high range %d.\n", reg8);
    res = ov2640_get_luminance_signal_high_range(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get luminance signal high range failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check luminance signal high range %s.\n", reg8_check == reg8 ? "ok" : "error");
    
    /* ov2640_set_luminance_signal_low_range/ov2640_get_luminance_signal_low_range test */
    ov2640_interface_debug_print("ov2640: ov2640_set_luminance_signal_low_range/ov2640_get_luminance_signal_low_range test.\n");
    
    reg8 = rand() % 256;
    res = ov2640_set_luminance_signal_low_range(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set luminance signal low range failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set luminance signal low range %d.\n", reg8);
    res = ov2640_get_luminance_signal_low_range(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get luminance signal low range failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check luminance signal low range %s.\n", reg8_check == reg8 ? "ok" : "error");
    
    /* ov2640_set_luminance_signal_low_range/ov2640_get_luminance_signal_low_range test */
    ov2640_interface_debug_print("ov2640: ov2640_set_luminance_signal_low_range/ov2640_get_luminance_signal_low_range test.\n");
    
    high_threshold = rand() % 0xF;
    low_threshold = rand() % 0xF;
    res = ov2640_set_fast_mode_large_step_range(&gs_handle, high_threshold, low_threshold);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set fast mode large step range failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set fast mode large step range high threshold %d.\n", high_threshold);
    ov2640_interface_debug_print("ov2640: set fast mode large step range low threshold %d.\n", low_threshold);
    res = ov2640_get_fast_mode_large_step_range(&gs_handle, &high_threshold_check, &low_threshold_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get fast mode large step range failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check fast mode large step range high threshold %s.\n", high_threshold == high_threshold_check ? "ok" : "error");
    ov2640_interface_debug_print("ov2640: check fast mode large step range low threshold %s.\n", low_threshold == low_threshold_check ? "ok" : "error");
    
    /* ov2640_set_line_interval_adjust/ov2640_get_line_interval_adjust test */
    ov2640_interface_debug_print("ov2640: ov2640_set_line_interval_adjust/ov2640_get_line_interval_adjust test.\n");
    
    reg16 = rand() % 0xFFF;
    res = ov2640_set_line_interval_adjust(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set line interval adjust failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set line interval adjust %d.\n", reg16);
    res = ov2640_get_line_interval_adjust(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get line interval adjust failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check line interval adjust %s.\n", reg16_check == reg16 ? "ok" : "error");
    
    /* ov2640_set_hsync_position_and_width_end_point/ov2640_get_hsync_position_and_width_end_point test */
    ov2640_interface_debug_print("ov2640: ov2640_set_hsync_position_and_width_end_point/ov2640_get_hsync_position_and_width_end_point test.\n");
    
    reg16 = rand() % 0x3FF;
    res = ov2640_set_hsync_position_and_width_end_point(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set hsync position and width end point failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set hsync position and width end point %d.\n", reg16);
    res = ov2640_get_hsync_position_and_width_end_point(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get hsync position and width end point failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check hsync position and width end point %s.\n", reg16_check == reg16 ? "ok" : "error");
    
    /* ov2640_set_hsync_position_and_width_start_point/ov2640_get_hsync_position_and_width_start_point test */
    ov2640_interface_debug_print("ov2640: ov2640_set_hsync_position_and_width_start_point/ov2640_get_hsync_position_and_width_start_point test.\n");
    
    reg16 = rand() % 0x3FF;
    res = ov2640_set_hsync_position_and_width_start_point(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set hsync position and width start point failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set hsync position and width start point %d.\n", reg16);
    res = ov2640_get_hsync_position_and_width_start_point(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get hsync position and width start point failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check hsync position and width start point %s.\n", reg16_check == reg16 ? "ok" : "error");
    
    /* ov2640_set_vsync_pulse_width/ov2640_get_vsync_pulse_width test */
    ov2640_interface_debug_print("ov2640: ov2640_set_vsync_pulse_width/ov2640_get_vsync_pulse_width test.\n");
    
    reg16 = rand() % 0xFFF;
    res = ov2640_set_vsync_pulse_width(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vsync pulse width failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set vsync pulse width %d.\n", reg16);
    res = ov2640_get_vsync_pulse_width(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get vsync pulse width failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check vsync pulse width %s.\n", reg16_check == reg16 ? "ok" : "error");
    
    /* ov2640_set_luminance_average/ov2640_get_luminance_average test */
    ov2640_interface_debug_print("ov2640: ov2640_set_luminance_average/ov2640_get_luminance_average test.\n");
    
    reg8 = rand() % 256;
    res = ov2640_set_luminance_average(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set luminance average failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set luminance average %d.\n", reg8);
    res = ov2640_get_luminance_average(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get luminance average failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check luminance average %s.\n", reg8_check == reg8 ? "ok" : "error");
    
    /* ov2640_set_horizontal_window_start/ov2640_get_horizontal_window_start test */
    ov2640_interface_debug_print("ov2640: ov2640_set_horizontal_window_start/ov2640_get_horizontal_window_start test.\n");
    
    reg16 = rand() % 0x7FF;
    res = ov2640_set_horizontal_window_start(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set horizontal window start failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set horizontal window start %d.\n", reg16);
    res = ov2640_get_horizontal_window_start(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get horizontal window start failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check horizontal window start %s.\n", reg16_check == reg16 ? "ok" : "error");
    
    /* ov2640_set_horizontal_window_end/ov2640_get_horizontal_window_end test */
    ov2640_interface_debug_print("ov2640: ov2640_set_horizontal_window_end/ov2640_get_horizontal_window_end test.\n");
    
    reg16 = rand() % 0x7FF;
    res = ov2640_set_horizontal_window_end(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set horizontal window end failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set horizontal window end %d.\n", reg16);
    res = ov2640_get_horizontal_window_end(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get horizontal window end failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check horizontal window end %s.\n", reg16_check == reg16 ? "ok" : "error");
    
    /* ov2640_set_pclk/ov2640_get_pclk test */
    ov2640_interface_debug_print("ov2640: ov2640_set_pclk/ov2640_get_pclk test.\n");
    
    /* set pclk no effect */
    res = ov2640_set_pclk(&gs_handle, OV2640_PCLK_NO_EFFECT);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set pclk failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set pclk no effect.\n");
    res = ov2640_get_pclk(&gs_handle, &pclk);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get pclk failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check pclk %s.\n", pclk == OV2640_PCLK_NO_EFFECT ? "ok" : "error");
    
    /* set pclk divide by 2 */
    res = ov2640_set_pclk(&gs_handle, OV2640_PCLK_DIVIDE_2);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set pclk failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set pclk divide by 2.\n");
    res = ov2640_get_pclk(&gs_handle, &pclk);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get pclk failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check pclk %s.\n", pclk == OV2640_PCLK_DIVIDE_2 ? "ok" : "error");
    
    /* set pclk divide by 4 */
    res = ov2640_set_pclk(&gs_handle, OV2640_PCLK_DIVIDE_4);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set pclk failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set pclk divide by 4.\n");
    res = ov2640_get_pclk(&gs_handle, &pclk);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get pclk failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check pclk %s.\n", pclk == OV2640_PCLK_DIVIDE_4 ? "ok" : "error");
    
    /* ov2640_set_zoom_window_horizontal_start_point/ov2640_get_zoom_window_horizontal_start_point test */
    ov2640_interface_debug_print("ov2640: ov2640_set_zoom_window_horizontal_start_point/ov2640_get_zoom_window_horizontal_start_point test.\n");
    
    /* enable zoom window horizontal start point */
    res = ov2640_set_zoom_window_horizontal_start_point(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set zoom window horizontal start point failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable zoom window horizontal start point.\n");
    res = ov2640_get_zoom_window_horizontal_start_point(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get zoom window horizontal start point failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check zoom window horizontal start point %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable zoom window horizontal start point */
    res = ov2640_set_zoom_window_horizontal_start_point(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set zoom window horizontal start point failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable zoom window horizontal start point.\n");
    res = ov2640_get_zoom_window_horizontal_start_point(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get zoom window horizontal start point failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check zoom window horizontal start point %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_frame_length_adjustment/ov2640_get_frame_length_adjustment test */
    ov2640_interface_debug_print("ov2640: ov2640_set_frame_length_adjustment/ov2640_get_frame_length_adjustment test.\n");
    
    reg16 = rand() % 0x3FF;
    res = ov2640_set_frame_length_adjustment(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set frame length adjustment failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set frame length adjustment %d.\n", reg16);
    res = ov2640_get_frame_length_adjustment(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get frame length adjustment failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check frame length adjustment %s.\n", reg16_check == reg16 ? "ok" : "error");
    
    /* ov2640_set_zoom_mode_vertical_window_start_point/ov2640_get_zoom_mode_vertical_window_start_point test */
    ov2640_interface_debug_print("ov2640: ov2640_set_zoom_mode_vertical_window_start_point/ov2640_get_zoom_mode_vertical_window_start_point test.\n");
    
    reg16 = rand() % 0x3FF;
    res = ov2640_set_zoom_mode_vertical_window_start_point(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set zoom mode vertical window start point failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set zoom mode vertical window start point %d.\n", reg16);
    res = ov2640_get_zoom_mode_vertical_window_start_point(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get zoom mode vertical window start point failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check zoom mode vertical window start point %s.\n", reg16_check == reg16 ? "ok" : "error");
    
    /* ov2640_set_flash_light/ov2640_get_flash_light test */
    ov2640_interface_debug_print("ov2640: ov2640_set_flash_light/ov2640_get_flash_light test.\n");
    
    reg8 = rand() % 256;
    res = ov2640_set_flash_light(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set flash light failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set flash light %d.\n", reg8);
    res = ov2640_get_flash_light(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get flash light failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check flash light %s.\n", reg8_check == reg8 ? "ok" : "error");
    
    /* ov2640_set_50hz_banding_aec/ov2640_get_50hz_banding_aec test */
    ov2640_interface_debug_print("ov2640: ov2640_set_50hz_banding_aec/ov2640_get_50hz_banding_aec test.\n");
    
    reg16 = rand() % 0x3FF;
    res = ov2640_set_50hz_banding_aec(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set 50hz banding aec failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set 50hz banding aec %d.\n", reg16);
    res = ov2640_get_50hz_banding_aec(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get 50hz banding aec failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check 50hz banding aec %s.\n", reg16_check == reg16 ? "ok" : "error");
    
    /* ov2640_set_60hz_banding_aec/ov2640_get_60hz_banding_aec test */
    ov2640_interface_debug_print("ov2640: ov2640_set_60hz_banding_aec/ov2640_get_60hz_banding_aec test.\n");
    
    reg16 = rand() % 0x3FF;
    res = ov2640_set_60hz_banding_aec(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set 60hz banding aec failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set 60hz banding aec %d.\n", reg16);
    res = ov2640_get_60hz_banding_aec(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get 60hz banding aec failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check 60hz banding aec %s.\n", reg16_check == reg16 ? "ok" : "error");
    
    /* ov2640_set_16_zone_average_weight_option/ov2640_get_16_zone_average_weight_option test */
    ov2640_interface_debug_print("ov2640: ov2640_set_16_zone_average_weight_option/ov2640_get_16_zone_average_weight_option test.\n");
    
    reg32 = rand() % 0xFFFFFFF;
    res = ov2640_set_16_zone_average_weight_option(&gs_handle, reg32);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set 16 zone average weight option failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set 16 zone average weight option %d.\n", reg32);
    res = ov2640_get_16_zone_average_weight_option(&gs_handle, &reg32_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get 16 zone average weight option failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check 16 zone average weight option %s.\n", reg32_check == reg32 ? "ok" : "error");
    
    /* ov2640_set_histogram_algorithm_low_level/ov2640_get_histogram_algorithm_low_level test */
    ov2640_interface_debug_print("ov2640: ov2640_set_histogram_algorithm_low_level/ov2640_get_histogram_algorithm_low_level test.\n");
    
    reg8 = rand() % 256;
    res = ov2640_set_histogram_algorithm_low_level(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set histogram algorithm low level failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set histogram algorithm low level %d.\n", reg8);
    res = ov2640_get_histogram_algorithm_low_level(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get histogram algorithm low level failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check histogram algorithm low level %s.\n", reg8_check == reg8 ? "ok" : "error");
    
    /* ov2640_set_histogram_algorithm_high_level/ov2640_get_histogram_algorithm_high_level test */
    ov2640_interface_debug_print("ov2640: ov2640_set_histogram_algorithm_high_level/ov2640_get_histogram_algorithm_high_level test.\n");
    
    reg8 = rand() % 256;
    res = ov2640_set_histogram_algorithm_high_level(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set histogram algorithm high level failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set histogram algorithm high level %d.\n", reg8);
    res = ov2640_get_histogram_algorithm_high_level(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get histogram algorithm high level failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check histogram algorithm high level %s.\n", reg8_check == reg8 ? "ok" : "error");
    
    /* ov2640_set_dsp_bypass/ov2640_get_dsp_bypass test */
    ov2640_interface_debug_print("ov2640: ov2640_set_dsp_bypass/ov2640_get_dsp_bypass test.\n");
    
    /* disable dsp bypass */
    res = ov2640_set_dsp_bypass(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dsp bypass failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable dsp bypass.\n");
    res = ov2640_get_dsp_bypass(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dsp bypass failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dsp bypass %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* enable dsp bypass */
    res = ov2640_set_dsp_bypass(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dsp bypass failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable dsp bypass.\n");
    res = ov2640_get_dsp_bypass(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dsp bypass failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dsp bypass %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* ov2640_set_auto_mode/ov2640_get_auto_mode test */
    ov2640_interface_debug_print("ov2640: ov2640_set_auto_mode/ov2640_get_auto_mode test.\n");
    
    /* enable auto mode */
    res = ov2640_set_auto_mode(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set auto mode failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable auto mode.\n");
    res = ov2640_get_auto_mode(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get auto mode failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check auto mode %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable auto mode */
    res = ov2640_set_auto_mode(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set auto mode failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable auto mode.\n");
    res = ov2640_get_auto_mode(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get auto mode failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check auto mode %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_dvp_pclk/ov2640_get_dvp_pclk test */
    ov2640_interface_debug_print("ov2640: ov2640_set_dvp_pclk/ov2640_get_dvp_pclk test.\n");
    
    reg8 = rand() % 0x7F;
    res = ov2640_set_dvp_pclk(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dvp pclk failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set dvp pclk %d.\n", reg8);
    res = ov2640_get_dvp_pclk(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dvp pclk failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dvp pclk %s.\n", reg8 == reg8_check ? "ok" : "error");
    
    /* ov2640_set_dvp_y8/ov2640_get_dvp_y8 test */
    ov2640_interface_debug_print("ov2640: ov2640_set_dvp_y8/ov2640_get_dvp_y8 test.\n");
    
    /* disable dvp y8 */
    res = ov2640_set_dvp_y8(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dvp y8 failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable dvp y8.\n");
    res = ov2640_get_dvp_y8(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dvp y8 failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dvp y8 %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* enable dvp y8 */
    res = ov2640_set_dvp_y8(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dvp y8 failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable dvp y8.\n");
    res = ov2640_get_dvp_y8(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dvp y8 failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dvp y8 %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* ov2640_set_jpeg_output/ov2640_get_jpeg_output test */
    ov2640_interface_debug_print("ov2640: ov2640_set_jpeg_output/ov2640_get_jpeg_output test.\n");
    
    /* disable jpeg output */
    res = ov2640_set_jpeg_output(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set jpeg output failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable jpeg output.\n");
    res = ov2640_get_jpeg_output(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get jpeg output failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check jpeg output %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* enable jpeg output */
    res = ov2640_set_jpeg_output(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set jpeg output failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable jpeg output.\n");
    res = ov2640_get_jpeg_output(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get jpeg output failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check jpeg output %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* ov2640_set_dvp_output_format/ov2640_get_dvp_output_format test */
    ov2640_interface_debug_print("ov2640: ov2640_set_dvp_output_format/ov2640_get_dvp_output_format test.\n");
    
    /* set dvp output format yuv422 */
    res = ov2640_set_dvp_output_format(&gs_handle, OV2640_DVP_OUTPUT_FORMAT_YUV422);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dvp output format failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set dvp output format yuv422.\n");
    res = ov2640_get_dvp_output_format(&gs_handle, &format);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dvp output format failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dvp output format %s.\n", format == OV2640_DVP_OUTPUT_FORMAT_YUV422 ? "ok" : "error");
    
    /* set dvp output format dvp raw10 */
    res = ov2640_set_dvp_output_format(&gs_handle, OV2640_DVP_OUTPUT_FORMAT_RAW10);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dvp output format failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set dvp output format dvp raw10.\n");
    res = ov2640_get_dvp_output_format(&gs_handle, &format);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dvp output format failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dvp output format %s.\n", format == OV2640_DVP_OUTPUT_FORMAT_RAW10 ? "ok" : "error");
    
    /* set dvp output format rgb565 */
    res = ov2640_set_dvp_output_format(&gs_handle, OV2640_DVP_OUTPUT_FORMAT_RGB565);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dvp output format failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set dvp output format rgb565.\n");
    res = ov2640_get_dvp_output_format(&gs_handle, &format);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dvp output format failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dvp output format %s.\n", format == OV2640_DVP_OUTPUT_FORMAT_RGB565 ? "ok" : "error");
    
    /* ov2640_set_dvp_jpeg_output_href_timing/ov2640_get_dvp_jpeg_output_href_timing test */
    ov2640_interface_debug_print("ov2640: ov2640_set_dvp_jpeg_output_href_timing/ov2640_get_dvp_jpeg_output_href_timing test.\n");
    
    /* set href is same as sensor */
    res = ov2640_set_dvp_jpeg_output_href_timing(&gs_handle, OV2640_HREF_TIMING_SENSOR);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dvp jpeg output href timing failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set href is same as sensor.\n");
    res = ov2640_get_dvp_jpeg_output_href_timing(&gs_handle, &timing);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dvp jpeg output href timing failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dvp jpeg output href timing %s.\n", timing == OV2640_HREF_TIMING_SENSOR ? "ok" : "error");
    
    /* set href vsync */
    res = ov2640_set_dvp_jpeg_output_href_timing(&gs_handle, OV2640_HREF_TIMING_VSYNC);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dvp jpeg output href timing failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set href vsync.\n");
    res = ov2640_get_dvp_jpeg_output_href_timing(&gs_handle, &timing);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dvp jpeg output href timing failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dvp jpeg output href timing %s.\n", timing == OV2640_HREF_TIMING_VSYNC ? "ok" : "error");
    
    /* ov2640_set_byte_swap/ov2640_get_byte_swap test */
    ov2640_interface_debug_print("ov2640: ov2640_set_byte_swap/ov2640_get_byte_swap test.\n");
    
    /* set high byte first */
    res = ov2640_set_byte_swap(&gs_handle, OV2640_BYTE_SWAP_YUYV);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set byte swap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set high byte first.\n");
    res = ov2640_get_byte_swap(&gs_handle, &byte_swap);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get byte swap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check byte swap %s.\n", byte_swap == OV2640_BYTE_SWAP_YUYV ? "ok" : "error");
    
    /* set low byte first */
    res = ov2640_set_byte_swap(&gs_handle, OV2640_BYTE_SWAP_UVUV);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set byte swap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set low byte first.\n");
    res = ov2640_get_byte_swap(&gs_handle, &byte_swap);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get byte swap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check byte swap %s.\n", byte_swap == OV2640_BYTE_SWAP_UVUV ? "ok" : "error");
    
    /* ov2640_set_reset/ov2640_get_reset test */
    ov2640_interface_debug_print("ov2640: ov2640_set_reset/ov2640_get_reset test.\n");
    
    /* microcontroller reset */
    res = ov2640_set_reset(&gs_handle, OV2640_RESET_MICROCONTROLLER, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set reset failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: microcontroller reset.\n");
    res = ov2640_get_reset(&gs_handle, OV2640_RESET_MICROCONTROLLER, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get reset failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check microcontroller reset %s.\n", res == 0 ? "ok" : "error");
    
    /* sccb reset */
    res = ov2640_set_reset(&gs_handle, OV2640_RESET_SCCB, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set reset failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: sccb reset.\n");
    res = ov2640_get_reset(&gs_handle, OV2640_RESET_SCCB, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get reset failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check sccb reset %s.\n", res == 0 ? "ok" : "error");
    
    /* jpeg reset */
    res = ov2640_set_reset(&gs_handle, OV2640_RESET_JPEG, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set reset failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: jpeg reset.\n");
    res = ov2640_get_reset(&gs_handle, OV2640_RESET_JPEG, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get reset failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check jpeg reset %s.\n", res == 0 ? "ok" : "error");
    
    /* dvp reset */
    res = ov2640_set_reset(&gs_handle, OV2640_RESET_DVP, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set reset failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: dvp reset.\n");
    res = ov2640_get_reset(&gs_handle, OV2640_RESET_DVP, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get reset failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dvp reset %s.\n", res == 0 ? "ok" : "error");
    
    /* ipu reset */
    res = ov2640_set_reset(&gs_handle, OV2640_RESET_IPU, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set reset failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: ipu reset.\n");
    res = ov2640_get_reset(&gs_handle, OV2640_RESET_IPU, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get reset failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check ipu reset %s.\n", res == 0 ? "ok" : "error");
    
    /* ov2640_set_sccb_master_speed/ov2640_get_sccb_master_speed test */
    ov2640_interface_debug_print("ov2640: ov2640_set_sccb_master_speed/ov2640_get_sccb_master_speed test.\n");
    
    reg8 = rand() % 256;
    res = ov2640_set_sccb_master_speed(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sccb master speed failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set sccb master speed %d.\n", reg8);
    res = ov2640_get_sccb_master_speed(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get sccb master speed failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check sccb master speed %s.\n", reg8 == reg8_check ? "ok" : "error");
    
    /* ov2640_set_sccb_slave_id/ov2640_get_sccb_slave_id test */
    ov2640_interface_debug_print("ov2640: ov2640_set_sccb_slave_id/ov2640_get_sccb_slave_id test.\n");
    
    reg8 = 0x60;
    res = ov2640_set_sccb_slave_id(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sccb slave id failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set sccb slave id %d.\n", reg8);
    res = ov2640_get_sccb_slave_id(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get sccb slave id failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check sccb slave id %s.\n", reg8 == reg8_check ? "ok" : "error");
    
    /* ov2640_set_address_auto_increase/ov2640_get_address_auto_increase test */
    ov2640_interface_debug_print("ov2640: ov2640_set_address_auto_increase/ov2640_get_address_auto_increase test.\n");
    
    /* disable address auto increase */
    res = ov2640_set_address_auto_increase(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set address auto increase failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable address auto increase.\n");
    res = ov2640_get_address_auto_increase(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get address auto increase failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check address auto increase %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* enable address auto increase */
    res = ov2640_set_address_auto_increase(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set address auto increase failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable address auto increase.\n");
    res = ov2640_get_address_auto_increase(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get address auto increase failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check address auto increase %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* ov2640_set_sccb/ov2640_get_sccb test */
    ov2640_interface_debug_print("ov2640: ov2640_set_sccb/ov2640_get_sccb test.\n");
    
    /* enable sccb */
    res = ov2640_set_sccb(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sccb failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable sccb.\n");
    res = ov2640_get_sccb(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get sccb failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check sccb %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* ov2640_set_sccb_master_clock_delay/ov2640_get_sccb_master_clock_delay test */
    ov2640_interface_debug_print("ov2640: ov2640_set_sccb_master_clock_delay/ov2640_get_sccb_master_clock_delay test.\n");
    
    /* enable sccb master clock delay */
    res = ov2640_set_sccb_master_clock_delay(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sccb master clock delay failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable sccb master clock delay.\n");
    res = ov2640_get_sccb_master_clock_delay(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get sccb master clock delay failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check sccb master clock delay %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable sccb master clock delay */
    res = ov2640_set_sccb_master_clock_delay(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sccb master clock delay failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable sccb master clock delay.\n");
    res = ov2640_get_sccb_master_clock_delay(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get sccb master clock delay failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check sccb master clock delay %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_sccb_master_access/ov2640_get_sccb_master_access test */
    ov2640_interface_debug_print("ov2640: ov2640_set_sccb_master_access/ov2640_get_sccb_master_access test.\n");
    
    /* enable sccb master access */
    res = ov2640_set_sccb_master_access(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sccb master access failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable sccb master access.\n");
    res = ov2640_get_sccb_master_access(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get sccb master access failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check sccb master access %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable sccb master access */
    res = ov2640_set_sccb_master_access(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sccb master access failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable sccb master access.\n");
    res = ov2640_get_sccb_master_access(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get sccb master access failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check sccb master access %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_sensor_pass_through_access/ov2640_get_sensor_pass_through_access test */
    ov2640_interface_debug_print("ov2640: ov2640_set_sensor_pass_through_access/ov2640_get_sensor_pass_through_access test.\n");
    
    /* enable sensor pass through access */
    res = ov2640_set_sensor_pass_through_access(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sensor pass through access failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable sensor pass through access.\n");
    res = ov2640_get_sensor_pass_through_access(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get sensor pass through access failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check sensor pass through access %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable sensor pass through access */
    res = ov2640_set_sensor_pass_through_access(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sensor pass through access failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable sensor pass through access.\n");
    res = ov2640_get_sensor_pass_through_access(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get sensor pass through access failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check sensor pass through access %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_bist/ov2640_get_bist test */
    ov2640_interface_debug_print("ov2640: ov2640_set_bist/ov2640_get_bist test.\n");
    
    /* enable microcontroller reset */
    res = ov2640_set_bist(&gs_handle, OV2640_BIST_MICROCONTROLLER_RESET, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable microcontroller reset.\n");
    res = ov2640_get_bist(&gs_handle, OV2640_BIST_MICROCONTROLLER_RESET, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bist %s.\n", res == 0 ? "ok" : "error");
    
    /* disable microcontroller reset */
    res = ov2640_set_bist(&gs_handle, OV2640_BIST_MICROCONTROLLER_RESET, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable microcontroller reset.\n");
    res = ov2640_get_bist(&gs_handle, OV2640_BIST_MICROCONTROLLER_RESET, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bist %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* enable boot rom select */
    res = ov2640_set_bist(&gs_handle, OV2640_BIST_BOOT_ROM, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable boot rom select.\n");
    res = ov2640_get_bist(&gs_handle, OV2640_BIST_BOOT_ROM, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bist %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable boot rom select */
    res = ov2640_set_bist(&gs_handle, OV2640_BIST_BOOT_ROM, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable boot rom select.\n");
    res = ov2640_get_bist(&gs_handle, OV2640_BIST_BOOT_ROM, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bist %s.\n", res == 0 ? "ok" : "error");
    
    /* enable r/w 1 error for 12k - byte memory */
    res = ov2640_set_bist(&gs_handle, OV2640_BIST_RW_1_ERROR_12K_BYTE, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable r/w 1 error for 12k - byte memory.\n");
    res = ov2640_get_bist(&gs_handle, OV2640_BIST_RW_1_ERROR_12K_BYTE, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bist %s.\n", res == 0 ? "ok" : "error");
    
    /* disable r/w 1 error for 12k - byte memory */
    res = ov2640_set_bist(&gs_handle, OV2640_BIST_RW_1_ERROR_12K_BYTE, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable r/w 1 error for 12k - byte memory.\n");
    res = ov2640_get_bist(&gs_handle, OV2640_BIST_RW_1_ERROR_12K_BYTE, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bist %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* enable r/w 0 error for 12k - byte memory */
    res = ov2640_set_bist(&gs_handle, OV2640_BIST_RW_0_ERROR_12K_BYTE, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable r/w 0 error for 12k - byte memory.\n");
    res = ov2640_get_bist(&gs_handle, OV2640_BIST_RW_0_ERROR_12K_BYTE, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bist %s.\n", res == 0 ? "ok" : "error");
    
    /* disable r/w 0 error for 12k - byte memory */
    res = ov2640_set_bist(&gs_handle, OV2640_BIST_RW_0_ERROR_12K_BYTE, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable r/w 0 error for 12k - byte memory.\n");
    res = ov2640_get_bist(&gs_handle, OV2640_BIST_RW_0_ERROR_12K_BYTE, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bist %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* enable r/w 1 error for 512 - byte memory */
    res = ov2640_set_bist(&gs_handle, OV2640_BIST_RW_1_ERROR_512_BYTE, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable r/w 1 error for 512 - byte memory.\n");
    res = ov2640_get_bist(&gs_handle, OV2640_BIST_RW_1_ERROR_512_BYTE, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bist %s.\n", res == 0 ? "ok" : "error");
    
    /* disable r/w 1 error for 512 - byte memory */
    res = ov2640_set_bist(&gs_handle, OV2640_BIST_RW_1_ERROR_512_BYTE, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable r/w 1 error for 512 - byte memory.\n");
    res = ov2640_get_bist(&gs_handle, OV2640_BIST_RW_1_ERROR_512_BYTE, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bist %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* enable r/w 0 error for 512 - byte memory */
    res = ov2640_set_bist(&gs_handle, OV2640_BIST_RW_0_ERROR_512_BYTE, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable r/w 0 error for 512 - byte memory.\n");
    res = ov2640_get_bist(&gs_handle, OV2640_BIST_RW_0_ERROR_512_BYTE, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bist %s.\n", res == 0 ? "ok" : "error");
    
    /* disable r/w 0 error for 512 - byte memory */
    res = ov2640_set_bist(&gs_handle, OV2640_BIST_RW_0_ERROR_512_BYTE, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable r/w 0 error for 512 - byte memory.\n");
    res = ov2640_get_bist(&gs_handle, OV2640_BIST_RW_0_ERROR_512_BYTE, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bist %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* enable busy or one shot reset */
    res = ov2640_set_bist(&gs_handle, OV2640_BIST_BUSY_OR_SHOT_RESET, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable busy or one shot reset.\n");
    res = ov2640_get_bist(&gs_handle, OV2640_BIST_BUSY_OR_SHOT_RESET, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bist %s.\n", res == 0 ? "ok" : "error");
    
    /* disable busy or one shot reset */
    res = ov2640_set_bist(&gs_handle, OV2640_BIST_BUSY_OR_SHOT_RESET, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable busy or one shot reset.\n");
    res = ov2640_get_bist(&gs_handle, OV2640_BIST_BUSY_OR_SHOT_RESET, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bist %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* enable launch bist */
    res = ov2640_set_bist(&gs_handle, OV2640_BIST_LAUNCH, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable launch bist.\n");
    res = ov2640_get_bist(&gs_handle, OV2640_BIST_LAUNCH, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bist %s.\n", res == 0 ? "ok" : "error");
    
    /* disable launch bist */
    res = ov2640_set_bist(&gs_handle, OV2640_BIST_LAUNCH, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable launch bist.\n");
    res = ov2640_get_bist(&gs_handle, OV2640_BIST_LAUNCH, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bist failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bist %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_program_memory_pointer_address/ov2640_get_program_memory_pointer_address test */
    ov2640_interface_debug_print("ov2640: ov2640_set_program_memory_pointer_address/ov2640_get_program_memory_pointer_address test.\n");
    
    /* set program memory pointer address */
    reg16 = 0;
    res = ov2640_set_program_memory_pointer_address(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set program memory pointer address failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set program memory pointer address %d.\n", reg16);
    res = ov2640_get_program_memory_pointer_address(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get program memory pointer address failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check program memory pointer address %s.\n", reg16 == reg16_check ? "ok" : "error");
    
    /* ov2640_set_program_memory_pointer_access_address/ov2640_get_program_memory_pointer_access_address test */
    ov2640_interface_debug_print("ov2640: ov2640_set_program_memory_pointer_access_address/ov2640_get_program_memory_pointer_access_address test.\n");
    
    reg8 = 0;
    res = ov2640_set_program_memory_pointer_access_address(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set program memory pointer access address failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set program memory pointer access address %d.\n", reg8);
    res = ov2640_get_program_memory_pointer_access_address(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get program memory pointer access address failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check program memory pointer access address %s.\n", reg8 == reg8_check ? "ok" : "error");
    
    /* ov2640_set_sccb_protocol_command/ov2640_get_sccb_protocol_command test */
    ov2640_interface_debug_print("ov2640: ov2640_set_sccb_protocol_command/ov2640_get_sccb_protocol_command test.\n");
    
    reg8 = 0;
    res = ov2640_set_sccb_protocol_command(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sccb protocol command failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set sccb protocol command %d.\n", reg8);
    res = ov2640_get_sccb_protocol_command(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get sccb protocol command failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check sccb protocol command %s.\n", reg8 == reg8_check ? "ok" : "error");
    
    /* ov2640_set_sccb_protocol_status/ov2640_get_sccb_protocol_status test */
    ov2640_interface_debug_print("ov2640: ov2640_set_sccb_protocol_status/ov2640_get_sccb_protocol_status test.\n");
    
    /* set sccb protocol status */
    reg8 = 0xD9;
    res = ov2640_set_sccb_protocol_status(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sccb protocol status failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set sccb protocol status %d.\n", reg8);
    res = ov2640_get_sccb_protocol_status(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get sccb protocol status failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check sccb protocol status %s.\n", res == 0 ? "ok" : "error");
    
    /* ov2640_set_cip/ov2640_get_cip test */
    ov2640_interface_debug_print("ov2640: ov2640_set_cip/ov2640_get_cip test.\n");
    
    /* disable cip */
    res = ov2640_set_cip(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set cip failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable cip.\n");
    res = ov2640_get_cip(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get cip failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check cip %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* enable cip */
    res = ov2640_set_cip(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set cip failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable cip.\n");
    res = ov2640_get_cip(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get cip failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check cip %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* ov2640_set_dmy/ov2640_get_dmy test */
    ov2640_interface_debug_print("ov2640: ov2640_set_dmy/ov2640_get_dmy test.\n");
    
    /* enable dmy */
    res = ov2640_set_dmy(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dmy failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable dmy.\n");
    res = ov2640_get_dmy(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dmy failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dmy %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable dmy */
    res = ov2640_set_dmy(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dmy failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable dmy.\n");
    res = ov2640_get_dmy(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dmy failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dmy %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_raw_gma/ov2640_get_raw_gma test */
    ov2640_interface_debug_print("ov2640: ov2640_set_raw_gma/ov2640_get_raw_gma test.\n");
    
    /* enable raw gma */
    res = ov2640_set_raw_gma(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set raw gma failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable raw gma.\n");
    res = ov2640_get_raw_gma(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get raw gma failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check raw gma %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable raw gma */
    res = ov2640_set_raw_gma(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set raw gma failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable raw gma.\n");
    res = ov2640_get_raw_gma(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get raw gma failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check raw gma %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_dg/ov2640_get_dg test */
    ov2640_interface_debug_print("ov2640: ov2640_set_dg/ov2640_get_dg test.\n");
    
    /* enable dg */
    res = ov2640_set_dg(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dg failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable dg.\n");
    res = ov2640_get_dg(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dg failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dg %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable dg */
    res = ov2640_set_dg(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dg failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable dg.\n");
    res = ov2640_get_dg(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dg failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dg %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_awb/ov2640_get_awb test */
    ov2640_interface_debug_print("ov2640: ov2640_set_awb/ov2640_get_awb test.\n");
    
    /* enable awb */
    res = ov2640_set_awb(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set awb failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable awb.\n");
    res = ov2640_get_awb(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get awb failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check awb %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable awb */
    res = ov2640_set_awb(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set awb failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable awb.\n");
    res = ov2640_get_awb(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get awb failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check awb %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_awb_gain/ov2640_get_awb_gain test */
    ov2640_interface_debug_print("ov2640: ov2640_set_awb_gain/ov2640_get_awb_gain test.\n");
    
    /* enable awb gain */
    res = ov2640_set_awb_gain(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set awb gain failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable awb gain.\n");
    res = ov2640_get_awb_gain(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get awb gain failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check awb gain %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable awb gain */
    res = ov2640_set_awb_gain(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set awb gain failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable awb gain.\n");
    res = ov2640_get_awb_gain(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get awb gain failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check awb gain %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_lenc/ov2640_get_lenc test */
    ov2640_interface_debug_print("ov2640: ov2640_set_lenc/ov2640_get_lenc test.\n");
    
    /* enable lenc */
    res = ov2640_set_lenc(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set lenc failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable lenc.\n");
    res = ov2640_get_lenc(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get lenc failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check lenc %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable lenc */
    res = ov2640_set_lenc(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set lenc failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable lenc.\n");
    res = ov2640_get_lenc(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get lenc failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check lenc %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_pre/ov2640_get_pre test */
    ov2640_interface_debug_print("ov2640: ov2640_set_pre/ov2640_get_pre test.\n");
    
    /* enable pre */
    res = ov2640_set_pre(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set pre failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable pre.\n");
    res = ov2640_get_pre(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get pre failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check pre %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable pre */
    res = ov2640_set_pre(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set pre failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable pre.\n");
    res = ov2640_get_pre(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get pre failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check pre %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_aec_enable/ov2640_get_aec_enable test */
    ov2640_interface_debug_print("ov2640: ov2640_set_aec_enable/ov2640_get_aec_enable test.\n");
    
    /* enable aec enable */
    res = ov2640_set_aec_enable(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set aec enable failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable aec enable.\n");
    res = ov2640_get_aec_enable(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get aec enable failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check aec enable %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable aec enable */
    res = ov2640_set_aec_enable(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set aec enable failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable aec enable.\n");
    res = ov2640_get_aec_enable(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get aec enable failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check aec enable %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_aec_sel/ov2640_get_aec_sel test */
    ov2640_interface_debug_print("ov2640: ov2640_set_aec_sel/ov2640_get_aec_sel test.\n");
    
    /* enable aec sel */
    res = ov2640_set_aec_sel(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set aec sel failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable aec sel.\n");
    res = ov2640_get_aec_sel(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get aec sel failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check aec sel %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable aec sel */
    res = ov2640_set_aec_sel(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set aec sel failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable aec sel.\n");
    res = ov2640_get_aec_sel(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get aec sel failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check aec sel %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_stat_sel/ov2640_get_stat_sel test */
    ov2640_interface_debug_print("ov2640: ov2640_set_stat_sel/ov2640_get_stat_sel test.\n");
    
    /* enable stat sel */
    res = ov2640_set_stat_sel(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set stat sel failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable stat sel.\n");
    res = ov2640_get_stat_sel(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get stat sel failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check stat sel %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable stat sel */
    res = ov2640_set_stat_sel(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set stat sel failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable stat sel.\n");
    res = ov2640_get_stat_sel(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get stat sel failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check stat sel %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_vfirst/ov2640_get_vfirst test */
    ov2640_interface_debug_print("ov2640: ov2640_set_vfirst/ov2640_get_vfirst test.\n");
    
    /* enable vfirst */
    res = ov2640_set_vfirst(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vfirst failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable vfirst.\n");
    res = ov2640_get_vfirst(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get vfirst failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check vfirst %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable vfirst */
    res = ov2640_set_vfirst(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vfirst failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable vfirst.\n");
    res = ov2640_get_vfirst(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get vfirst failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check vfirst %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_yuv422/ov2640_get_yuv422 test */
    ov2640_interface_debug_print("ov2640: ov2640_set_yuv422/ov2640_get_yuv422 test.\n");
    
    /* enable yuv422 */
    res = ov2640_set_yuv422(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set yuv422 failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable yuv422.\n");
    res = ov2640_get_yuv422(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get yuv422 failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check yuv422 %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable yuv422 */
    res = ov2640_set_yuv422(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set yuv422 failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable yuv422.\n");
    res = ov2640_get_yuv422(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get yuv422 failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check yuv422 %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_yuv/ov2640_get_yuv test */
    ov2640_interface_debug_print("ov2640: ov2640_set_yuv/ov2640_get_yuv test.\n");
    
    /* enable yuv */
    res = ov2640_set_yuv(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set yuv failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable yuv.\n");
    res = ov2640_get_yuv(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get yuv failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check yuv %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable yuv */
    res = ov2640_set_yuv(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set yuv failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable yuv.\n");
    res = ov2640_get_yuv(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get yuv failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check yuv %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_rgb/ov2640_get_rgb test */
    ov2640_interface_debug_print("ov2640: ov2640_set_rgb/ov2640_get_rgb test.\n");
    
    /* enable rgb */
    res = ov2640_set_rgb(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set rgb failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable rgb.\n");
    res = ov2640_get_rgb(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get rgb failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check rgb %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable rgb */
    res = ov2640_set_rgb(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set rgb failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable rgb.\n");
    res = ov2640_get_rgb(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get rgb failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check rgb %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_raw/ov2640_get_raw test */
    ov2640_interface_debug_print("ov2640: ov2640_set_raw/ov2640_get_raw test.\n");
    
    /* enable raw */
    res = ov2640_set_raw(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set raw failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable raw.\n");
    res = ov2640_get_raw(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get raw failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check raw %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable raw */
    res = ov2640_set_raw(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set raw failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable raw.\n");
    res = ov2640_get_raw(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get raw failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check raw %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_dcw/ov2640_get_dcw test */
    ov2640_interface_debug_print("ov2640: ov2640_set_dcw/ov2640_get_dcw test.\n");
    
    /* enable dcw */
    res = ov2640_set_dcw(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dcw failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable dcw.\n");
    res = ov2640_get_dcw(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dcw failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dcw %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable dcw */
    res = ov2640_set_dcw(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dcw failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable dcw.\n");
    res = ov2640_get_dcw(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dcw failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dcw %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_sde/ov2640_get_sde test */
    ov2640_interface_debug_print("ov2640: ov2640_set_sde/ov2640_get_sde test.\n");
    
    /* enable sde */
    res = ov2640_set_sde(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sde failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable sde.\n");
    res = ov2640_get_sde(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get sde failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check sde %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable sde */
    res = ov2640_set_sde(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sde failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable sde.\n");
    res = ov2640_get_sde(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get sde failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check sde %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_uv_adj/ov2640_get_uv_adj test */
    ov2640_interface_debug_print("ov2640: ov2640_set_uv_adj/ov2640_get_uv_adj test.\n");
    
    /* enable uv adj */
    res = ov2640_set_uv_adj(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set uv adj failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable uv adj.\n");
    res = ov2640_get_uv_adj(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get uv adj failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check uv adj %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable uv adj */
    res = ov2640_set_uv_adj(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set uv adj failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable uv adj.\n");
    res = ov2640_get_uv_adj(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get uv adj failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check uv adj %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_uv_avg/ov2640_get_uv_avg test */
    ov2640_interface_debug_print("ov2640: ov2640_set_uv_avg/ov2640_get_uv_avg test.\n");
    
    /* enable uv avg */
    res = ov2640_set_uv_avg(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set uv avg failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable uv avg.\n");
    res = ov2640_get_uv_avg(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get uv avg failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check uv avg %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable uv avg */
    res = ov2640_set_uv_avg(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set uv avg failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable uv avg.\n");
    res = ov2640_get_uv_avg(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get uv avg failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check uv avg %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_cmx/ov2640_get_cmx test */
    ov2640_interface_debug_print("ov2640: ov2640_set_cmx/ov2640_get_cmx test.\n");
    
    /* enable cmx */
    res = ov2640_set_cmx(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set cmx failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable cmx.\n");
    res = ov2640_get_cmx(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get cmx failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check cmx %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable cmx */
    res = ov2640_set_cmx(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set cmx failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable cmx.\n");
    res = ov2640_get_cmx(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get cmx failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check cmx %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_bpc/ov2640_get_bpc test */
    ov2640_interface_debug_print("ov2640: ov2640_set_bpc/ov2640_get_bpc test.\n");
    
    /* enable bpc */
    res = ov2640_set_bpc(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bpc failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable bpc.\n");
    res = ov2640_get_bpc(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bpc failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bpc %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable bpc */
    res = ov2640_set_bpc(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bpc failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable bpc.\n");
    res = ov2640_get_bpc(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get bpc failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check bpc %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_wpc/ov2640_get_wpc test */
    ov2640_interface_debug_print("ov2640: ov2640_set_wpc/ov2640_get_wpc test.\n");
    
    /* enable wpc */
    res = ov2640_set_wpc(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set wpc failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable wpc.\n");
    res = ov2640_get_wpc(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get wpc failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check wpc %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable wpc */
    res = ov2640_set_wpc(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set wpc failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable wpc.\n");
    res = ov2640_get_wpc(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get wpc failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check wpc %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_sde_indirect_register_address/ov2640_get_sde_indirect_register_address test */
    ov2640_interface_debug_print("ov2640: ov2640_set_sde_indirect_register_address/ov2640_get_sde_indirect_register_address test.\n");
    
    /* set sde indirect register address */
    reg8 = 0x00;
    res = ov2640_set_sde_indirect_register_address(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sde indirect register address failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set sde indirect register address %d.\n", reg8);
    res = ov2640_get_sde_indirect_register_address(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get sde indirect register address failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check sde indirect register address %s.\n", reg8 == reg8_check ? "ok" : "error");
    
    /* ov2640_set_sde_indirect_register_data/ov2640_get_sde_indirect_register_data test */
    ov2640_interface_debug_print("ov2640: ov2640_set_sde_indirect_register_data/ov2640_get_sde_indirect_register_data test.\n");
    
    /* set sde indirect register data */
    reg8 = rand() % 256;
    res = ov2640_set_sde_indirect_register_data(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sde indirect register data failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set sde indirect register data %d.\n", reg8);
    res = ov2640_get_sde_indirect_register_data(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get sde indirect register data failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check sde indirect register data %s.\n", reg8 == reg8_check ? "ok" : "error");
    
    /* ov2640_set_image_horizontal/ov2640_get_image_horizontal test */
    ov2640_interface_debug_print("ov2640: ov2640_set_image_horizontal/ov2640_get_image_horizontal test.\n");
    
    reg16 = rand() % 0xFFF;
    res = ov2640_set_image_horizontal(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set image horizontal failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set image horizontal %d.\n", reg16);
    res = ov2640_get_image_horizontal(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get image horizontal failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check image horizontal %s.\n", reg16 == reg16_check ? "ok" : "error");
    
    /* ov2640_set_image_vertical/ov2640_get_image_vertical test */
    ov2640_interface_debug_print("ov2640: ov2640_set_image_vertical/ov2640_get_image_vertical test.\n");
    
    reg16 = rand() % 0x7FF;
    res = ov2640_set_image_vertical(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set image vertical failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set image vertical %d.\n", reg16);
    res = ov2640_get_image_vertical(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get image vertical failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check image vertical %s.\n", reg16 == reg16_check ? "ok" : "error");
    
    /* ov2640_set_quantization_scale_factor/ov2640_get_quantization_scale_factor test */
    ov2640_interface_debug_print("ov2640: ov2640_set_quantization_scale_factor/ov2640_get_quantization_scale_factor test.\n");
    
    reg8 = rand() % 16;
    res = ov2640_set_quantization_scale_factor(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set quantization scale factor failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set quantization scale factor %d.\n", reg8);
    res = ov2640_get_quantization_scale_factor(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get quantization scale factor failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check quantization scale factor %s.\n", reg8 == reg8_check ? "ok" : "error");
    
    /* ov2640_set_lp_dp/ov2640_get_lp_dp test */
    ov2640_interface_debug_print("ov2640: ov2640_set_lp_dp/ov2640_get_lp_dp test.\n");
    
    /* enable lp dp */
    res = ov2640_set_lp_dp(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set lp dp failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable lp dp.\n");
    res = ov2640_get_lp_dp(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get lp dp failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check lp dp %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable lp dp */
    res = ov2640_set_lp_dp(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set lp dp failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable lp dp.\n");
    res = ov2640_get_lp_dp(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get lp dp failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check lp dp %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_round/ov2640_get_round test */
    ov2640_interface_debug_print("ov2640: ov2640_set_round/ov2640_get_round test.\n");
    
    /* enable round */
    res = ov2640_set_round(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set round failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: enable round.\n");
    res = ov2640_get_round(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get round failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check round %s.\n", enable == OV2640_BOOL_TRUE ? "ok" : "error");
    
    /* disable round */
    res = ov2640_set_round(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set round failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: disable round.\n");
    res = ov2640_get_round(&gs_handle, &enable);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get round failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check round %s.\n", enable == OV2640_BOOL_FALSE ? "ok" : "error");
    
    /* ov2640_set_vertical_divider/ov2640_get_vertical_divider test */
    ov2640_interface_debug_print("ov2640: ov2640_set_vertical_divider/ov2640_get_vertical_divider test.\n");
    
    reg8 = rand() % 8;
    res = ov2640_set_vertical_divider(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vertical divider failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set vertical divider %d.\n", reg8);
    res = ov2640_get_vertical_divider(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get vertical divider failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check vertical divider %s.\n", reg8 == reg8_check ? "ok" : "error");
    
    /* ov2640_set_horizontal_divider/ov2640_get_horizontal_divider test */
    ov2640_interface_debug_print("ov2640: ov2640_set_horizontal_divider/ov2640_get_horizontal_divider test.\n");
    
    reg8 = rand() % 8;
    res = ov2640_set_horizontal_divider(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set horizontal divider failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set horizontal divider %d.\n", reg8);
    res = ov2640_get_horizontal_divider(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get horizontal divider failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check horizontal divider %s.\n", reg8 == reg8_check ? "ok" : "error");
    
    /* ov2640_set_horizontal_size/ov2640_get_horizontal_size test */
    ov2640_interface_debug_print("ov2640: ov2640_set_horizontal_size/ov2640_get_horizontal_size test.\n");
    
    reg16 = (rand() % 0x3FF) / 4;
    res = ov2640_set_horizontal_size(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set horizontal size failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set horizontal size %d.\n", reg16);
    res = ov2640_get_horizontal_size(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get horizontal size failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check horizontal size %s.\n", reg16 == reg16_check ? "ok" : "error");
    
    /* ov2640_set_vertical_size/ov2640_get_vertical_size test */
    ov2640_interface_debug_print("ov2640: ov2640_set_vertical_size/ov2640_get_vertical_size test.\n");
    
    reg16 = (rand() % 0x1FF) / 4;
    res = ov2640_set_vertical_size(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vertical size failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set vertical size %d.\n", reg16);
    res = ov2640_get_vertical_size(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get vertical size failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check vertical size %s.\n", reg16 == reg16_check ? "ok" : "error");
    
    /* ov2640_set_offset_x/oov2640_get_offset_x test */
    ov2640_interface_debug_print("ov2640: ov2640_set_offset_x/oov2640_get_offset_x test.\n");
    
    /* set offset x */
    reg16 = rand() % 0x7FF;
    res = ov2640_set_offset_x(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set offset x failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set offset x %d.\n", reg16);
    res = ov2640_get_offset_x(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get offset x failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check offset x %s.\n", reg16 == reg16_check ? "ok" : "error");
    
    /* ov2640_set_offset_y/oov2640_get_offset_y test */
    ov2640_interface_debug_print("ov2640: ov2640_set_offset_y/oov2640_get_offset_y test.\n");
    
    /* set offset y */
    reg16 = rand() % 0x7FF;
    res = ov2640_set_offset_y(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set offset y failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set offset y %d.\n", reg16);
    res = ov2640_get_offset_y(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get offset y failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check offset y %s.\n", reg16 == reg16_check ? "ok" : "error");
    
    /* ov2640_set_dp_selx/ov2640_get_dp_selx test */
    ov2640_interface_debug_print("ov2640: ov2640_set_dp_selx/ov2640_get_dp_selx test.\n");
    
    /* set dp selx */
    reg8 = rand() % 0xF;
    res = ov2640_set_dp_selx(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dp selx failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set dp selx %d.\n", reg8);
    res = ov2640_get_dp_selx(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dp selx failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dp selx %s.\n", reg8 == reg8_check ? "ok" : "error");
    
    /* ov2640_set_dp_sely/ov2640_get_dp_sely test */
    ov2640_interface_debug_print("ov2640: ov2640_set_dp_sely/ov2640_get_dp_sely test.\n");
    
    /* set dp sely */
    reg8 = rand() % 0xF;
    res = ov2640_set_dp_sely(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dp sely failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set dp sely %d.\n", reg8);
    res = ov2640_get_dp_sely(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get dp sely failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check dp sely %s.\n", reg8 == reg8_check ? "ok" : "error");
    
    /* ov2640_set_output_width/ov2640_get_output_wide test */
    ov2640_interface_debug_print("ov2640: ov2640_set_output_width/ov2640_get_output_wide test.\n");
    
    /* set output wide */
    reg16 = rand() % 0x3FF;
    res = ov2640_set_output_width(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set output width failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set output width %d.\n", reg16);
    res = ov2640_get_output_width(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get output width failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check output width %s.\n", reg16 == reg16_check ? "ok" : "error");
    
    /* ov2640_set_output_height/ov2640_get_output_height test */
    ov2640_interface_debug_print("ov2640: ov2640_set_output_height/ov2640_get_output_height test.\n");
    
    /* set output height */
    reg16 = rand() % 0x1FF;
    res = ov2640_set_output_height(&gs_handle, reg16);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set output height failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set output height %d.\n", reg16);
    res = ov2640_get_output_height(&gs_handle, &reg16_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get output height failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check output height %s.\n", reg16 == reg16_check ? "ok" : "error");
    
    /* ov2640_set_zoom_speed/ov2640_get_zoom_speed test */
    ov2640_interface_debug_print("ov2640: ov2640_set_zoom_speed/ov2640_get_zoom_speed test.\n");
    
    /* set zoom speed */
    reg8 = 0;
    res = ov2640_set_zoom_speed(&gs_handle, reg8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set zoom speed failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: set zoom speed %d.\n", reg8);
    res = ov2640_get_zoom_speed(&gs_handle, &reg8_check);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: get zoom speed failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check zoom speed %s.\n", reg8 == reg8_check ? "ok" : "error");
    
    /* ov2640_set_light_mode test */
    ov2640_interface_debug_print("ov2640: ov2640_set_light_mode test.\n");
    
    /* set light mode auto */
    res = ov2640_set_light_mode(&gs_handle, OV2640_LIGHT_MODE_AUTO);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set light mode failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check light mode auto %s.\n", res == 0 ? "ok" : "error");
    
    /* set light mode sunny */
    res = ov2640_set_light_mode(&gs_handle, OV2640_LIGHT_MODE_SUNNY);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set light mode failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check light mode sunny %s.\n", res == 0 ? "ok" : "error");
    
    /* set light mode cloudy */
    res = ov2640_set_light_mode(&gs_handle, OV2640_LIGHT_MODE_CLOUDY);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set light mode failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check light mode cloudy %s.\n", res == 0 ? "ok" : "error");
    
    /* set light mode office */
    res = ov2640_set_light_mode(&gs_handle, OV2640_LIGHT_MODE_OFFICE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set light mode failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check light mode office %s.\n", res == 0 ? "ok" : "error");
    
    /* set light mode home */
    res = ov2640_set_light_mode(&gs_handle, OV2640_LIGHT_MODE_HOME);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set light mode failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check light mode home %s.\n", res == 0 ? "ok" : "error");
    
    /* ov2640_set_color_saturation test */
    ov2640_interface_debug_print("ov2640: ov2640_set_color_saturation test.\n");
    
    /* set color saturation +2 */
    res = ov2640_set_color_saturation(&gs_handle, OV2640_COLOR_SATURATION_POSITIVE_2);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set color saturation failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check color saturation +2 %s.\n", res == 0 ? "ok" : "error");
    
    /* set color saturation +1 */
    res = ov2640_set_color_saturation(&gs_handle, OV2640_COLOR_SATURATION_POSITIVE_1);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set color saturation failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check color saturation +1 %s.\n", res == 0 ? "ok" : "error");
    
    /* set color saturation 0 */
    res = ov2640_set_color_saturation(&gs_handle, OV2640_COLOR_SATURATION_0);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set color saturation failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check color saturation 0 %s.\n", res == 0 ? "ok" : "error");
    
    /* set color saturation -1 */
    res = ov2640_set_color_saturation(&gs_handle, OV2640_COLOR_SATURATION_NEGATIVE_1);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set color saturation failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check color saturation -1 %s.\n", res == 0 ? "ok" : "error");
    
    /* set color saturation -2 */
    res = ov2640_set_color_saturation(&gs_handle, OV2640_COLOR_SATURATION_NEGATIVE_2);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set color saturation failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check color saturation -2 %s.\n", res == 0 ? "ok" : "error");
    
    /* ov2640_set_brightness test */
    ov2640_interface_debug_print("ov2640: ov2640_set_brightness test.\n");
    
    /* set brightness +2 */
    res = ov2640_set_brightness(&gs_handle, OV2640_BRIGHTNESS_POSITIVE_2);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set brightness failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check brightness +2 %s.\n", res == 0 ? "ok" : "error");
    
    /* set brightness +1 */
    res = ov2640_set_brightness(&gs_handle, OV2640_BRIGHTNESS_POSITIVE_1);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set brightness failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check brightness +1 %s.\n", res == 0 ? "ok" : "error");
    
    /* set brightness 0 */
    res = ov2640_set_brightness(&gs_handle, OV2640_BRIGHTNESS_0);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set brightness failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check brightness 0 %s.\n", res == 0 ? "ok" : "error");
    
    /* set brightness -1 */
    res = ov2640_set_brightness(&gs_handle, OV2640_BRIGHTNESS_NEGATIVE_1);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set brightness failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check brightness -1 %s.\n", res == 0 ? "ok" : "error");
    
    /* set brightness -2 */
    res = ov2640_set_brightness(&gs_handle, OV2640_BRIGHTNESS_NEGATIVE_2);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set brightness failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check brightness -2 %s.\n", res == 0 ? "ok" : "error");
    
    /* ov2640_set_contrast test */
    ov2640_interface_debug_print("ov2640: ov2640_set_contrast test.\n");
    
    /* set contrast +2 */
    res = ov2640_set_contrast(&gs_handle, OV2640_CONTRAST_POSITIVE_2);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set contrast failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check contrast +2 %s.\n", res == 0 ? "ok" : "error");
    
    /* set contrast +1 */
    res = ov2640_set_contrast(&gs_handle, OV2640_CONTRAST_POSITIVE_1);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set contrast failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check contrast +1 %s.\n", res == 0 ? "ok" : "error");
    
    /* set contrast 0 */
    res = ov2640_set_contrast(&gs_handle, OV2640_CONTRAST_0);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set contrast failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check contrast 0 %s.\n", res == 0 ? "ok" : "error");
    
    /* set contrast -1 */
    res = ov2640_set_contrast(&gs_handle, OV2640_CONTRAST_NEGATIVE_1);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set contrast failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check contrast -1 %s.\n", res == 0 ? "ok" : "error");
    
    /* set contrast -2 */
    res = ov2640_set_contrast(&gs_handle, OV2640_CONTRAST_NEGATIVE_2);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set contrast failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check contrast -2 %s.\n", res == 0 ? "ok" : "error");
    
    /* ov2640_set_special_effect test */
    ov2640_interface_debug_print("ov2640: ov2640_set_special_effect test.\n");
    
    /* set special effect antique */
    res = ov2640_set_special_effect(&gs_handle, OV2640_SPECIAL_EFFECT_ANTIQUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set special effect failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check special effect antique %s.\n", res == 0 ? "ok" : "error");
    
    /* set special effect bluish */
    res = ov2640_set_special_effect(&gs_handle, OV2640_SPECIAL_EFFECT_BLUISH);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set special effect failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check special effect bluish %s.\n", res == 0 ? "ok" : "error");
    
    /* set special effect greenish */
    res = ov2640_set_special_effect(&gs_handle, OV2640_SPECIAL_EFFECT_GREENISH);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set special effect failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check special effect greenish %s.\n", res == 0 ? "ok" : "error");
    
    /* set special effect reddish */
    res = ov2640_set_special_effect(&gs_handle, OV2640_SPECIAL_EFFECT_REDDISH);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set special effect failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check special effect reddish %s.\n", res == 0 ? "ok" : "error");
    
    /* set special effect b&w */
    res = ov2640_set_special_effect(&gs_handle, OV2640_SPECIAL_EFFECT_BW);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set special effect failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check special effect b&w %s.\n", res == 0 ? "ok" : "error");
    
    /* set special effect negative */
    res = ov2640_set_special_effect(&gs_handle, OV2640_SPECIAL_EFFECT_NEGATIVE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set special effect failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check special effect negative %s.\n", res == 0 ? "ok" : "error");
    
    /* set special effect b&w negative */
    res = ov2640_set_special_effect(&gs_handle, OV2640_SPECIAL_EFFECT_BW_NEGATIVE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set special effect failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check special effect b&w negative %s.\n", res == 0 ? "ok" : "error");
    
    /* set special effect normal */
    res = ov2640_set_special_effect(&gs_handle, OV2640_SPECIAL_EFFECT_NORMAL);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set special effect failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    ov2640_interface_debug_print("ov2640: check special effect normal %s.\n", res == 0 ? "ok" : "error");
    
    /* finish register */
    ov2640_interface_debug_print("ov2640: finish register test.\n");
    (void)ov2640_deinit(&gs_handle);
    
    return 0;
}
