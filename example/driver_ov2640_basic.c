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
 * @file      driver_ov2640_basic.c
 * @brief     driver ov2640 basic source file
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

#include "driver_ov2640_basic.h"

static ov2640_handle_t gs_handle;        /**< ov2640 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t ov2640_basic_init(void)
{
    uint8_t res;
    
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
    
    /* ov2640 init */
    res = ov2640_init(&gs_handle);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: init failed.\n");
        
        return 1;
    }
    
    /* table init */
    res = ov2640_table_init(&gs_handle);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: table init failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default clock rate double */
    res = ov2640_set_clock_rate_double(&gs_handle, OV2640_BASIC_DEFAULT_CLOCK_RATE_DOUBLE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set clock rate double failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default clock divider */
    res = ov2640_set_clock_divider(&gs_handle, OV2640_BASIC_DEFAULT_CLOCK_DIVIDER);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set clock divider failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default mode */
    res = ov2640_set_mode(&gs_handle, OV2640_BASIC_DEFAULT_MODE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set mode failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default power reset pin remap */
    res = ov2640_set_power_reset_pin_remap(&gs_handle, OV2640_BASIC_DEFAULT_POWER_RESET_PIN_REMAP);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set power reset pin remap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default output drive */
    res = ov2640_set_output_drive(&gs_handle, OV2640_BASIC_DEFAULT_OUTPUT_DRIVE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set output drive failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default horizontal mirror */
    res = ov2640_set_horizontal_mirror(&gs_handle, OV2640_BASIC_DEFAULT_HORIZONTAL_MIRROR);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set horizontal mirror failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default vertical flip */
    res = ov2640_set_vertical_flip(&gs_handle, OV2640_BASIC_DEFAULT_VERTICAL_FLIP);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vertical flip failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default band filter */
    res = ov2640_set_band_filter(&gs_handle, OV2640_BASIC_DEFAULT_BAND_FILTER);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set band filter failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default agc control */
    res = ov2640_set_agc_control(&gs_handle, OV2640_BASIC_DEFAULT_AGC_CONTROL);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set agc control failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default exposure control */
    res = ov2640_set_exposure_control(&gs_handle, OV2640_BASIC_DEFAULT_EXPOSURE_CONTROL);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set exposure control failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default agc gain ceiling */
    res = ov2640_set_agc_gain_ceiling(&gs_handle, OV2640_BASIC_DEFAULT_AGC_GAIN_CEILING);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set agc gain ceiling failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default zoom window horizontal start point */
    res = ov2640_set_zoom_window_horizontal_start_point(&gs_handle, OV2640_BASIC_DEFAULT_ZOOM_WINDOW_H_START);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set zoom window horizontal start point failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default clock output power down pin status */
    res = ov2640_set_clock_output_power_down_pin_status(&gs_handle, OV2640_BASIC_DEFAULT_PIN_STATUS);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set clock output power down pin status failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default zoom mode vertical window start point */
    res = ov2640_set_zoom_mode_vertical_window_start_point(&gs_handle, OV2640_BASIC_DEFAULT_ZOOM_WINDOW_V_START);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set zoom mode vertical window start point failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default luminance signal high range */
    res = ov2640_set_luminance_signal_high_range(&gs_handle, OV2640_BASIC_DEFAULT_LUMINANCE_HIGH);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set luminance signal high range failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default luminance signal low range */
    res = ov2640_set_luminance_signal_low_range(&gs_handle, OV2640_BASIC_DEFAULT_LUMINANCE_LOW);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set luminance signal low range failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default fast mode large step range */
    res = ov2640_set_fast_mode_large_step_range(&gs_handle, OV2640_BASIC_DEFAULT_FAST_MODE_HIGH, OV2640_BASIC_DEFAULT_FAST_MODE_LOW);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set fast mode large step range failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default frame length adjustment */
    res = ov2640_set_frame_length_adjustment(&gs_handle, OV2640_BASIC_DEFAULT_FRAME_LENGTH_ADJ);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set frame length adjustment failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default band */
    res = ov2640_set_band(&gs_handle, OV2640_BASIC_DEFAULT_BAND);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set band failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default auto band */
    res = ov2640_set_auto_band(&gs_handle, OV2640_BASIC_DEFAULT_AUTO_BAND);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set auto band failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default live video after snapshot */
    res = ov2640_set_live_video_after_snapshot(&gs_handle, OV2640_BASIC_DEFAULT_SNAPSHOT);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set live video after snapshot failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default histogram algorithm low level */
    res = ov2640_set_histogram_algorithm_low_level(&gs_handle, OV2640_BASIC_DEFAULT_HISTO_LOW);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set histogram algorithm low level failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default histogram algorithm high level */
    res = ov2640_set_histogram_algorithm_high_level(&gs_handle, OV2640_BASIC_DEFAULT_HISTO_HIGH);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set histogram algorithm high level failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default 50hz banding aec */
    res = ov2640_set_50hz_banding_aec(&gs_handle, OV2640_BASIC_DEFAULT_BD50_AEC);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set 50hz banding aec failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default 60hz banding aec */
    res = ov2640_set_60hz_banding_aec(&gs_handle, OV2640_BASIC_DEFAULT_BD60_AEC);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set 60hz banding aec failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default resolution */
    res = ov2640_set_resolution(&gs_handle, OV2640_BASIC_DEFAULT_RESOLUTION);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set resolution failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default zoom */
    res = ov2640_set_zoom(&gs_handle, OV2640_BASIC_DEFAULT_ZOOM);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set zoom failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default color bar test */
    res = ov2640_set_color_bar_test(&gs_handle, OV2640_BASIC_DEFAULT_COLOR_BAR_TEST);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set color bar test failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default pclk */
    res = ov2640_set_pclk(&gs_handle, OV2640_BASIC_DEFAULT_PCLK);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set pclk failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default horizontal window start */
    res = ov2640_set_horizontal_window_start(&gs_handle, OV2640_BASIC_DEFAULT_H_WINDOW_START);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set horizontal window start failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default horizontal window end */
    res = ov2640_set_horizontal_window_end(&gs_handle, OV2640_BASIC_DEFAULT_H_WINDOW_END);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set horizontal window end failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default vertical window line start */
    res = ov2640_set_vertical_window_line_start(&gs_handle, OV2640_BASIC_DEFAULT_V_WINDOW_START);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vertical window line start failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default vertical window line end */
    res = ov2640_set_vertical_window_line_end(&gs_handle, OV2640_BASIC_DEFAULT_V_WINDOW_END);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vertical window line end failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default vsync pulse width */
    res = ov2640_set_vsync_pulse_width(&gs_handle, OV2640_BASIC_DEFAULT_VSYNC_PULSE_WIDTH);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vsync pulse width failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default agc gain */
    res = ov2640_set_agc_gain(&gs_handle, OV2640_BASIC_DEFAULT_AGC_GAIN);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set agc gain failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dummy frame */
    res = ov2640_set_dummy_frame(&gs_handle, OV2640_BASIC_DEFAULT_DUMMY_FRAME);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dummy frame failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default aec */
    res = ov2640_set_aec(&gs_handle, OV2640_BASIC_DEFAULT_AEC);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set aec failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default frame exposure pre charge row number */
    res = ov2640_set_frame_exposure_pre_charge_row_number(&gs_handle, OV2640_BASIC_DEFAULT_FRAME_EXPOSURE_PRE_ROW);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set frame exposure pre charge row number failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default chsync href swap */
    res = ov2640_set_chsync_href_swap(&gs_handle, OV2640_BASIC_DEFAULT_CHSYNC_HREF_SWAP);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set chsync href swap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default href chsync swap */
    res = ov2640_set_href_chsync_swap(&gs_handle, OV2640_BASIC_DEFAULT_HREF_CHSYNC_SWAP);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set href chsync swap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default pclk output qualified by href */
    res = ov2640_set_pclk_output_qualified_by_href(&gs_handle, OV2640_BASIC_DEFAULT_PCLK_OUTPUT_BY_HREF);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set pclk output qualified by href failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default pclk edge */
    res = ov2640_set_pclk_edge(&gs_handle, OV2640_BASIC_DEFAULT_PCLK_EDGE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set pclk edge failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default href polarity */
    res = ov2640_set_href_polarity(&gs_handle, OV2640_BASIC_DEFAULT_HREF_POLARITY);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set href polarity failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default vsync polarity */
    res = ov2640_set_vsync_polarity(&gs_handle, OV2640_BASIC_DEFAULT_VSYNC_POLARITY);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vsync polarity failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default hsync polarity */
    res = ov2640_set_hsync_polarity(&gs_handle, OV2640_BASIC_DEFAULT_HSYNC_POLARITY);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set hsync polarity failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default line interval adjust */
    res = ov2640_set_line_interval_adjust(&gs_handle, OV2640_BASIC_DEFAULT_LINE_INTERVAL_ADJUST);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set line interval adjust failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default hsync position and width start point */
    res = ov2640_set_hsync_position_and_width_start_point(&gs_handle, OV2640_BASIC_DEFAULT_HSYNC_START_POINT);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set hsync position and width start point failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default hsync position and width end point */
    res = ov2640_set_hsync_position_and_width_end_point(&gs_handle, OV2640_BASIC_DEFAULT_HSYNC_END_POINT);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set hsync position and width end point failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default luminance average */
    res = ov2640_set_luminance_average(&gs_handle, OV2640_BASIC_DEFAULT_LUMINANCE_AVG);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set luminance average failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default flash light */
    res = ov2640_set_flash_light(&gs_handle, OV2640_BASIC_DEFAULT_FLASH_LIGHT);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set flash light failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default 16 zone average weight option */
    res = ov2640_set_16_zone_average_weight_option(&gs_handle, OV2640_BASIC_DEFAULT_16_ZONE_AVG_WEIGHT);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set 16 zone average weight option failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable dsp bypass */
    res = ov2640_set_dsp_bypass(&gs_handle, OV2640_BOOL_TRUE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dsp bypass failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default bpc */
    res = ov2640_set_bpc(&gs_handle, OV2640_BASIC_DEFAULT_DSP_BPC);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set bpc failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default wpc */
    res = ov2640_set_wpc(&gs_handle, OV2640_BASIC_DEFAULT_DSP_WPC);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set wpc failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dvp pclk */
    res = ov2640_set_dvp_pclk(&gs_handle, OV2640_BASIC_DEFAULT_DSP_DVP_PCLK);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dvp pclk failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default cip */
    res = ov2640_set_cip(&gs_handle, OV2640_BASIC_DEFAULT_DSP_CIP);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set cip failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dmy */
    res = ov2640_set_dmy(&gs_handle, OV2640_BASIC_DEFAULT_DSP_DMY);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dmy failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default raw gma */
    res = ov2640_set_raw_gma(&gs_handle, OV2640_BASIC_DEFAULT_DSP_RAW_GMA);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set raw gma failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dg */
    res = ov2640_set_dg(&gs_handle, OV2640_BASIC_DEFAULT_DSP_DG);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dg failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default awb */
    res = ov2640_set_awb(&gs_handle, OV2640_BASIC_DEFAULT_DSP_AWB);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set awb failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default awb gain */
    res = ov2640_set_awb_gain(&gs_handle, OV2640_BASIC_DEFAULT_DSP_AWB_GAIN);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set awb gain failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default pre */
    res = ov2640_set_pre(&gs_handle, OV2640_BASIC_DEFAULT_DSP_PRE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set pre failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dvp y8 */
    res = ov2640_set_dvp_y8(&gs_handle, OV2640_BASIC_DEFAULT_DSP_DVP_Y8);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dvp y8 failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default jpeg output */
    res = ov2640_set_jpeg_output(&gs_handle, OV2640_BASIC_DEFAULT_DSP_JPEG_OUTPUT);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set jpeg output failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dvp output format */
    res = ov2640_set_dvp_output_format(&gs_handle, OV2640_BASIC_DEFAULT_DSP_DVP_OUTPUT_FORMAT);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dvp output format failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dvp jpeg output href timing */
    res = ov2640_set_dvp_jpeg_output_href_timing(&gs_handle, OV2640_BASIC_DEFAULT_DSP_JPEG_OUTPUT_HREF_TIMING);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dvp jpeg output href timing failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default byte swap */
    res = ov2640_set_byte_swap(&gs_handle, OV2640_BASIC_DEFAULT_DSP_BYTE_SWAP);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set byte swap failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default image horizontal */
    res = ov2640_set_image_horizontal(&gs_handle, OV2640_BASIC_DEFAULT_DSP_IMAGE_HORIZONTAL);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set image horizontal failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default image vertical */
    res = ov2640_set_image_vertical(&gs_handle, OV2640_BASIC_DEFAULT_DSP_IMAGE_VERTICAL);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set image vertical failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dcw */
    res = ov2640_set_dcw(&gs_handle, OV2640_BASIC_DEFAULT_DSP_DCW);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dcw failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default sde */
    res = ov2640_set_sde(&gs_handle, OV2640_BASIC_DEFAULT_DSP_SDE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sde failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default uv adj */
    res = ov2640_set_uv_adj(&gs_handle, OV2640_BASIC_DEFAULT_DSP_UV_ADJ);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set uv adj failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default uv avg */
    res = ov2640_set_uv_avg(&gs_handle, OV2640_BASIC_DEFAULT_DSP_UV_AVG);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set uv avg failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default cmx */
    res = ov2640_set_cmx(&gs_handle, OV2640_BASIC_DEFAULT_DSP_CMX);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set cmx failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default lp dp */
    res = ov2640_set_lp_dp(&gs_handle, OV2640_BASIC_DEFAULT_DSP_LP_DP);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set lp dp failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default round */
    res = ov2640_set_round(&gs_handle, OV2640_BASIC_DEFAULT_DSP_ROUND);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set round failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default vertical divider */
    res = ov2640_set_vertical_divider(&gs_handle, OV2640_BASIC_DEFAULT_DSP_VERTICAL_DIV);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vertical divider failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default horizontal divider */
    res = ov2640_set_horizontal_divider(&gs_handle, OV2640_BASIC_DEFAULT_DSP_HORIZONTAL_DIV);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set horizontal divider failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default horizontal size */
    res = ov2640_set_horizontal_size(&gs_handle, OV2640_BASIC_DEFAULT_DSP_HORIZONTAL_SIZE / 4);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set horizontal size failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default vertical size */
    res = ov2640_set_vertical_size(&gs_handle, OV2640_BASIC_DEFAULT_DSP_VERTICAL_SIZE / 4);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vertical size failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default offset x */
    res = ov2640_set_offset_x(&gs_handle, OV2640_BASIC_DEFAULT_DSP_OFFSET_X);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set offset x failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default offset y */
    res = ov2640_set_offset_y(&gs_handle, OV2640_BASIC_DEFAULT_DSP_OFFSET_Y);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set offset y failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default output width */
    res = ov2640_set_output_width(&gs_handle, OV2640_BASIC_DEFAULT_DSP_OUTPUT_WIDTH / 4);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set output width failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default output height */
    res = ov2640_set_output_height(&gs_handle, OV2640_BASIC_DEFAULT_DSP_OUTPUT_HEIGHT / 4);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set output height failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default zoom speed */
    res = ov2640_set_zoom_speed(&gs_handle, OV2640_BASIC_DEFAULT_DSP_ZOOM_SPEED);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set zoom speed failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default quantization scale factor */
    res = ov2640_set_quantization_scale_factor(&gs_handle, OV2640_BASIC_DEFAULT_DSP_QSF);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set quantization scale factor failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default sccb master speed */
    res = ov2640_set_sccb_master_speed(&gs_handle, OV2640_BASIC_DEFAULT_DSP_SCCB_MASTER_SPEED);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sccb master speed failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default address auto increase */
    res = ov2640_set_address_auto_increase(&gs_handle, OV2640_BASIC_DEFAULT_DSP_ADDRESS_AUTO_INC);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set address auto increase failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default sccb */
    res = ov2640_set_sccb(&gs_handle, OV2640_BASIC_DEFAULT_DSP_SCCB);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sccb failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default sccb master clock delay */
    res = ov2640_set_sccb_master_clock_delay(&gs_handle, OV2640_BASIC_DEFAULT_DSP_SCCB_CLOCK_DELAY);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sccb master clock delay failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default sccb master access */
    res = ov2640_set_sccb_master_access(&gs_handle, OV2640_BASIC_DEFAULT_DSP_SCCB_ACCESS);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sccb master access failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default sensor pass through access */
    res = ov2640_set_sensor_pass_through_access(&gs_handle, OV2640_BASIC_DEFAULT_DSP_SENSOR_PASS_ACCESS);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set sensor pass through access failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default aec enable */
    res = ov2640_set_aec_enable(&gs_handle, OV2640_BASIC_DEFAULT_DSP_AEC_ENABLE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set aec enable failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default aec sel */
    res = ov2640_set_aec_sel(&gs_handle, OV2640_BASIC_DEFAULT_DSP_AEC_SEL);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set aec sel failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default stat sel */
    res = ov2640_set_stat_sel(&gs_handle, OV2640_BASIC_DEFAULT_DSP_STAT_SEL);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set stat sel failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default vfirst */
    res = ov2640_set_vfirst(&gs_handle, OV2640_BASIC_DEFAULT_DSP_VFIRST);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set vfirst failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default yuv422 */
    res = ov2640_set_yuv422(&gs_handle, OV2640_BASIC_DEFAULT_DSP_YUV422);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set yuv422 failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default yuv */
    res = ov2640_set_yuv(&gs_handle, OV2640_BASIC_DEFAULT_DSP_YUV);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set yuv failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default rgb */
    res = ov2640_set_rgb(&gs_handle, OV2640_BASIC_DEFAULT_DSP_RGB);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set rgb failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default raw */
    res = ov2640_set_raw(&gs_handle, OV2640_BASIC_DEFAULT_DSP_RAW);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set raw failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dp selx */
    res = ov2640_set_dp_selx(&gs_handle, OV2640_BASIC_DEFAULT_DSP_DP_SELX);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dp selx failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dp sely */
    res = ov2640_set_dp_sely(&gs_handle, OV2640_BASIC_DEFAULT_DSP_DP_SELY);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dp sely failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable dsp bypass */
    res = ov2640_set_dsp_bypass(&gs_handle, OV2640_BOOL_FALSE);
    if (res != 0)
    {
        ov2640_interface_debug_print("ov2640: set dsp bypass failed.\n");
        (void)ov2640_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ov2640_basic_deinit(void)
{
    /* close ov2640 */
    if (ov2640_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example set jpeg mode
 * @return status code
 *         - 0 success
 *         - 1 set jpeg mode failed
 * @note   none
 */
uint8_t ov2640_basic_set_jpeg_mode(void)
{
    /* enter to jpeg mode */
    if (ov2640_table_jpeg_init(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example set rgb565 mode
 * @return status code
 *         - 0 success
 *         - 1 set rgb565 mode failed
 * @note   none
 */
uint8_t ov2640_basic_set_rgb565_mode(void)
{
    /* enter to rgb565 mode */
    if (ov2640_table_rgb565_init(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example set light mode
 * @param[in] mode is the light mode
 * @return    status code
 *            - 0 success
 *            - 1 set light mode failed
 * @note      none
 */
uint8_t ov2640_basic_set_light_mode(ov2640_light_mode_t mode)
{
    /* set light mode */
    if (ov2640_set_light_mode(&gs_handle, mode) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example set color saturation
 * @param[in] color is the color saturation
 * @return    status code
 *            - 0 success
 *            - 1 set color saturation failed
 * @note      none
 */
uint8_t ov2640_basic_set_color_saturation(ov2640_color_saturation_t color)
{
    /* set color saturation */
    if (ov2640_set_color_saturation(&gs_handle, color) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example set brightness
 * @param[in] brightness is the brightness
 * @return    status code
 *            - 0 success
 *            - 1 set brightness failed
 * @note      none
 */
uint8_t ov2640_basic_set_brightness(ov2640_brightness_t brightness)
{
    /* set brightness */
    if (ov2640_set_brightness(&gs_handle, brightness) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example set contrast
 * @param[in] contrast is the set contrast
 * @return    status code
 *            - 0 success
 *            - 1 set contrast failed
 * @note      none
 */
uint8_t ov2640_basic_set_contrast(ov2640_contrast_t contrast)
{
    /* set contrast */
    if (ov2640_set_contrast(&gs_handle, contrast) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example set special effect
 * @param[in] effect is the set special effect
 * @return    status code
 *            - 0 success
 *            - 1 set special_effect failed
 * @note      none
 */
uint8_t ov2640_basic_set_special_effect(ov2640_special_effect_t effect)
{
    /* set special effect */
    if (ov2640_set_special_effect(&gs_handle, effect) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     basic example set image resolution
 * @param[in] resolution is the set image resolution
 * @return    status code
 *            - 0 success
 *            - 1 set image resolution failed
 * @note      none
 */
uint8_t ov2640_basic_set_image_resolution(ov2640_image_resolution_t resolution)
{
    uint8_t res;
    
    switch (resolution)
    {
        case OV2640_IMAGE_RESOLUTION_QQVGA:
        {
            /* 160 x 120 */
            res = ov2640_set_output_width(&gs_handle, 160);
            if (res != 0)
            {
                break;
            }
            res = ov2640_set_output_height(&gs_handle, 120);
            if (res != 0)
            {
                break;
            }
            
            break;
        }
        case OV2640_IMAGE_RESOLUTION_QCIF:
        {
            /* 176 x 144 */
            res = ov2640_set_output_width(&gs_handle, 176);
            if (res != 0)
            {
                break;
            }
            res = ov2640_set_output_height(&gs_handle, 144);
            if (res != 0)
            {
                break;
            }
            
            break;
        }
        case OV2640_IMAGE_RESOLUTION_QVGA:
        {
            /* 320 x 240 */
            res = ov2640_set_output_width(&gs_handle, 320);
            if (res != 0)
            {
                break;
            }
            res = ov2640_set_output_height(&gs_handle, 240);
            if (res != 0)
            {
                break;
            }
            
            break;
        }
        case OV2640_IMAGE_RESOLUTION_WQVGA:
        {
            /* 400 x 240 */
            res = ov2640_set_output_width(&gs_handle, 400);
            if (res != 0)
            {
                break;
            }
            res = ov2640_set_output_height(&gs_handle, 240);
            if (res != 0)
            {
                break;
            }
            
            break;
        }
        case OV2640_IMAGE_RESOLUTION_CIF:
        {
            /* 352 x 288 */
            res = ov2640_set_output_width(&gs_handle, 352);
            if (res != 0)
            {
                break;
            }
            res = ov2640_set_output_height(&gs_handle, 288);
            if (res != 0)
            {
                break;
            }
            
            break;
        }
        case OV2640_IMAGE_RESOLUTION_VGA:
        {
            /* 640 x 480 */
            res = ov2640_set_output_width(&gs_handle, 640);
            if (res != 0)
            {
                break;
            }
            res = ov2640_set_output_height(&gs_handle, 480);
            if (res != 0)
            {
                break;
            }
            
            break;
        }
        case OV2640_IMAGE_RESOLUTION_SVGA:
        {
            /* 800 x 600 */
            res = ov2640_set_output_width(&gs_handle, 800);
            if (res != 0)
            {
                break;
            }
            res = ov2640_set_output_height(&gs_handle, 600);
            if (res != 0)
            {
                break;
            }
            
            break;
        }
        case OV2640_IMAGE_RESOLUTION_XGA:
        {
            /* 1024 x 768 */
            res = ov2640_set_output_width(&gs_handle, 1024);
            if (res != 0)
            {
                break;
            }
            res = ov2640_set_output_height(&gs_handle, 768);
            if (res != 0)
            {
                break;
            }
            
            break;
        }
        case OV2640_IMAGE_RESOLUTION_WXGA:
        {
            /* 1280 x 800 */
            res = ov2640_set_output_width(&gs_handle, 1280);
            if (res != 0)
            {
                break;
            }
            res = ov2640_set_output_height(&gs_handle, 800);
            if (res != 0)
            {
                break;
            }
            
            break;
        }
        case OV2640_IMAGE_RESOLUTION_XVGA:
        {
            /* 1280 x 960 */
            res = ov2640_set_output_width(&gs_handle, 1280);
            if (res != 0)
            {
                break;
            }
            res = ov2640_set_output_height(&gs_handle, 960);
            if (res != 0)
            {
                break;
            }
            
            break;
        }
        case OV2640_IMAGE_RESOLUTION_WXGA_PLUS:
        {
            /* 1440 x 900 */
            res = ov2640_set_output_width(&gs_handle, 1440);
            if (res != 0)
            {
                break;
            }
            res = ov2640_set_output_height(&gs_handle, 900);
            if (res != 0)
            {
                break;
            }
            
            break;
        }
        case OV2640_IMAGE_RESOLUTION_SXGA:
        {
            /* 1280 x 1024 */
            res = ov2640_set_output_width(&gs_handle, 1280);
            if (res != 0)
            {
                break;
            }
            res = ov2640_set_output_height(&gs_handle, 1024);
            if (res != 0)
            {
                break;
            }
            
            break;
        }
        case OV2640_IMAGE_RESOLUTION_UXGA:
        {
            /* 1600 x 1200 */
            res = ov2640_set_output_width(&gs_handle, 1600);
            if (res != 0)
            {
                break;
            }
            res = ov2640_set_output_height(&gs_handle, 1200);
            if (res != 0)
            {
                break;
            }
            
            break;
        }
        default :
        {
            res = 1;
            
            break;
        }
    }
    
    return res;
}
