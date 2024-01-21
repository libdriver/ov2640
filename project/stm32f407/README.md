### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

GPIO Pin: RST/PWD PA0/PA8.

SDIO Pin: D0/D1/D2/D3/SCK/CMD PC8/PC9/PC10/PC11/PC12/PD2.

DCMI Pin: D0/D1/D2/D3/D4/D5/D6/D7/PCLK/HREF/VSYNC 

​                   PC6/PC7/PE0/PE1/PE4/PB6/PE5/PE6/PA6/PA4/PB7.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. OV2640

#### 3.1 Command Instruction

1. Show ov2640 chip and driver information.

   ```shell
   ov2640 (-i | --information)
   ```

2. Show ov2640 help.

   ```shell
   ov2640 (-h | --help)
   ```

3. Show ov2640 pin connections of the current board.

   ```shell
   ov2640 (-p | --port)
   ```

4. Run ov2640 reg test.

   ```shell
   ov2640 (-t reg | --test=reg)
   ```

5. Run ov2640 display function, time is the set time in second.

   ```shell
   ov2640 (-e display | --example=display) --time=<time>
   ```

7. Run ov2640 photo function, path is the set pah.

   ```shell
   ov2640 (-e photo | --example=photo) [--path=<path>]
   ```

#### 3.2 Command Example

```shell
ov2640 -i

ov2640: chip is OmniVision OV2640.
ov2640: manufacturer is OmniVision.
ov2640: interface is SCCB DVP.
ov2640: driver version is 1.0.
ov2640: min supply voltage is 2.5V.
ov2640: max supply voltage is 3.0V.
ov2640: max current is 40.00mA.
ov2640: max temperature is 70.0C.
ov2640: min temperature is -30.0C.
```

```shell
ov2640 -p

ov2640: SCL connected to GPIOB PIN8.
ov2640: SDA connected to GPIOB PIN9.
ov2640: RST connected to GPIOA PIN0.
ov2640: PWD connected to GPIOA PIN8.
ov2640: D0 connected to GPIOC PIN6.
ov2640: D1 connected to GPIOC PIN7.
ov2640: D2 connected to GPIOE PIN0.
ov2640: D3 connected to GPIOE PIN1.
ov2640: D4 connected to GPIOE PIN4.
ov2640: D5 connected to GPIOB PIN6.
ov2640: D6 connected to GPIOE PIN5.
ov2640: D7 connected to GPIOE PIN6.
ov2640: PCLK connected to GPIOA PIN6.
ov2640: HREF connected to GPIOA PIN4.
ov2640: VSYNC connected to GPIOB PIN7.
```

```shell
ov2640 -t reg

ov2640: chip is OmniVision OV2640.
ov2640: manufacturer is OmniVision.
ov2640: interface is SCCB DVP.
ov2640: driver version is 1.0.
ov2640: min supply voltage is 2.5V.
ov2640: max supply voltage is 3.0V.
ov2640: max current is 40.00mA.
ov2640: max temperature is 70.0C.
ov2640: min temperature is -30.0C.
ov2640: start register test.
ov2640: ov2640_set_agc_gain/ov2640_get_agc_gain test.
ov2640: set agc gain 432.
ov2640: check agc gain ok.
ov2640: ov2640_set_dummy_frame/ov2640_get_dummy_frame test.
ov2640: set dummy frame 1.
ov2640: check dummy frame ok.
ov2640: set dummy frame 3.
ov2640: check dummy frame ok.
ov2640: set dummy frame 7.
ov2640: check dummy frame ok.
ov2640: ov2640_set_vertical_window_line_start/ov2640_get_vertical_window_line_start test.
ov2640: set vertical window line start 459.
ov2640: check vertical window line start ok.
ov2640: ov2640_set_vertical_window_line_end/ov2640_get_vertical_window_line_end test.
ov2640: set vertical window line end 585.
ov2640: check vertical window line end ok.
ov2640: ov2640_set_horizontal_mirror/ov2640_get_horizontal_mirror test.
ov2640: enable horizontal mirror.
ov2640: check horizontal mirror ok.
ov2640: disable horizontal mirror.
ov2640: check horizontal mirror ok.
ov2640: ov2640_set_vertical_flip/ov2640_get_vertical_flip test.
ov2640: enable vertical flip.
ov2640: check vertical flip ok.
ov2640: disable vertical flip.
ov2640: check vertical flip ok.
ov2640: ov2640_set_aec/ov2640_get_aec test.
ov2640: set aec 22025.
ov2640: check aec ok.
ov2640: ov2640_set_frame_exposure_pre_charge_row_number/ov2640_get_frame_exposure_pre_charge_row_number test.
ov2640: set frame exposure pre charge row number 7.
ov2640: check frame exposure pre charge row number ok.
ov2640: ov2640_set_mode/ov2640_get_mode test.
ov2640: set standby mode.
ov2640: check mode ok.
ov2640: set normal mode.
ov2640: check mode ok.
ov2640: ov2640_set_power_reset_pin_remap/ov2640_get_power_reset_pin_remap test.
ov2640: enable power reset pin remap.
ov2640: check power reset pin remap ok.
ov2640: disable power reset pin remap.
ov2640: check power reset pin remap ok.
ov2640: ov2640_set_output_drive/ov2640_get_output_drive test.
ov2640: set output drive 1 capability.
ov2640: check output drive ok.
ov2640: set output drive 2 capability.
ov2640: check output drive ok.
ov2640: set output drive 3 capability.
ov2640: check output drive ok.
ov2640: set output drive 4 capability.
ov2640: check output drive ok.
ov2640: ov2640_set_band/ov2640_get_band test.
ov2640: set band 60Hz.
ov2640: check band ok.
ov2640: set band 50Hz.
ov2640: check band ok.
ov2640: ov2640_set_auto_band/ov2640_get_auto_band test.
ov2640: disable auto band.
ov2640: check auto band ok.
ov2640: enable auto band.
ov2640: check auto band ok.
ov2640: ov2640_set_live_video_after_snapshot/ov2640_get_live_video_after_snapshot test.
ov2640: enable live video after snapshot.
ov2640: check live video after snapshot ok.
ov2640: disable live video after snapshot.
ov2640: check live video after snapshot ok.
ov2640: ov2640_set_clock_output_power_down_pin_status/ov2640_get_clock_output_power_down_pin_status test.
ov2640: set clock output power down pin last state.
ov2640: check clock output power down pin status ok.
ov2640: set clock output power down pin tri state.
ov2640: check clock output power down pin status ok.
ov2640: ov2640_set_clock_rate_double/ov2640_get_clock_rate_double test.
ov2640: enable clock rate double.
ov2640: check clock rate double ok.
ov2640: disable clock rate double.
ov2640: check clock rate double ok.
ov2640: ov2640_set_clock_divider/ov2640_get_clock_divider test.
ov2640: set clock divider 59.
ov2640: check clock divider ok.
ov2640: ov2640_soft_reset test.
ov2640: check soft reset ok.
ov2640: ov2640_set_resolution/ov2640_get_resolution test.
ov2640: set resolution uxga.
ov2640: check resolution ok.
ov2640: set resolution cif.
ov2640: check resolution ok.
ov2640: set resolution svga.
ov2640: check resolution ok.
ov2640: ov2640_set_zoom/ov2640_get_zoom test.
ov2640: enable zoom.
ov2640: check zoom ok.
ov2640: disable zoom.
ov2640: check zoom ok.
ov2640: ov2640_set_color_bar_test/ov2640_get_color_bar_test test.
ov2640: enable color bar test.
ov2640: check color bar test ok.
ov2640: disable color bar test.
ov2640: check color bar test ok.
ov2640: ov2640_set_band_filter/ov2640_get_band_filter test.
ov2640: enable band filter.
ov2640: check band filter ok.
ov2640: disable band filter.
ov2640: check band filter ok.
ov2640: ov2640_set_agc_control/ov2640_get_agc_control test.
ov2640: set agc control manual.
ov2640: check agc control ok.
ov2640: set agc control auto.
ov2640: check agc control ok.
ov2640: ov2640_set_exposure_control/ov2640_get_exposure_control test.
ov2640: set exposure control manual.
ov2640: check exposure control ok.
ov2640: set exposure control auto.
ov2640: check exposure control ok.
ov2640: ov2640_set_agc/ov2640_get_agc test.
ov2640: set agc gain ceiling 2x.
ov2640: check agc gain ceiling ok.
ov2640: set agc gain ceiling 4x.
ov2640: check agc gain ceiling ok.
ov2640: set agc gain ceiling 8x.
ov2640: check agc gain ceiling ok.
ov2640: set agc gain ceiling 16x.
ov2640: check agc gain ceiling ok.
ov2640: set agc gain ceiling 32x.
ov2640: check agc gain ceiling ok.
ov2640: set agc gain ceiling 64x.
ov2640: check agc gain ceiling ok.
ov2640: set agc gain ceiling 128x.
ov2640: check agc gain ceiling ok.
ov2640: ov2640_set_chsync_href_swap/ov2640_get_chsync_href_swap test.
ov2640: enable chsync href swap.
ov2640: check chsync href swap ok.
ov2640: disable chsync href swap.
ov2640: check chsync href swap ok.
ov2640: ov2640_set_href_chsync_swap/ov2640_get_href_chsync_swap test.
ov2640: enable href chsync swap.
ov2640: check href chsync swap ok.
ov2640: disable href chsync swap.
ov2640: check href chsync swap ok.
ov2640: ov2640_set_pclk_output_qualified_by_href/ov2640_get_pclk_output_qualified_by_href test.
ov2640: enable pclk output qualified by href.
ov2640: check pclk output qualified by href ok.
ov2640: disable pclk output qualified by href.
ov2640: check pclk output qualified by href ok.
ov2640: ov2640_set_pclk_output_qualified_by_href/ov2640_get_pclk_output_qualified_by_href test.
ov2640: set pclk edge falling.
ov2640: check pclk edge ok.
ov2640: set pclk edge rising.
ov2640: check pclk edge ok.
ov2640: ov2640_set_href_polarity/ov2640_get_href_polarity test.
ov2640: set href polarity positive.
ov2640: check href polarity ok.
ov2640: set href polarity negative.
ov2640: check href polarity ok.
ov2640: ov2640_set_vsync_polarity/ov2640_get_vsync_polarity test.
ov2640: set vsync polarity positive.
ov2640: check vsync polarity ok.
ov2640: set vsync polarity negative.
ov2640: check vsync polarity ok.
ov2640: ov2640_set_hsync_polarity/ov2640_get_hsync_polarity test.
ov2640: set hsync polarity positive.
ov2640: check hsync polarity ok.
ov2640: set hsync polarity negative.
ov2640: check hsync polarity ok.
ov2640: ov2640_set_luminance_signal_high_range/ov2640_get_luminance_signal_high_range test.
ov2640: set luminance signal high range 200.
ov2640: check luminance signal high range ok.
ov2640: ov2640_set_luminance_signal_low_range/ov2640_get_luminance_signal_low_range test.
ov2640: set luminance signal low range 127.
ov2640: check luminance signal low range ok.
ov2640: ov2640_set_luminance_signal_low_range/ov2640_get_luminance_signal_low_range test.
ov2640: set fast mode large step range high threshold 12.
ov2640: set fast mode large step range low threshold 4.
ov2640: check fast mode large step range high threshold ok.
ov2640: check fast mode large step range low threshold ok.
ov2640: ov2640_set_line_interval_adjust/ov2640_get_line_interval_adjust test.
ov2640: set line interval adjust 1263.
ov2640: check line interval adjust ok.
ov2640: ov2640_set_hsync_position_and_width_end_point/ov2640_get_hsync_position_and_width_end_point test.
ov2640: set hsync position and width end point 769.
ov2640: check hsync position and width end point ok.
ov2640: ov2640_set_hsync_position_and_width_start_point/ov2640_get_hsync_position_and_width_start_point test.
ov2640: set hsync position and width start point 651.
ov2640: check hsync position and width start point ok.
ov2640: ov2640_set_vsync_pulse_width/ov2640_get_vsync_pulse_width test.
ov2640: set vsync pulse width 2913.
ov2640: check vsync pulse width ok.
ov2640: ov2640_set_luminance_average/ov2640_get_luminance_average test.
ov2640: set luminance average 101.
ov2640: check luminance average ok.
ov2640: ov2640_set_horizontal_window_start/ov2640_get_horizontal_window_start test.
ov2640: set horizontal window start 761.
ov2640: check horizontal window start ok.
ov2640: ov2640_set_horizontal_window_end/ov2640_get_horizontal_window_end test.
ov2640: set horizontal window end 872.
ov2640: check horizontal window end ok.
ov2640: ov2640_set_pclk/ov2640_get_pclk test.
ov2640: set pclk no effect.
ov2640: check pclk ok.
ov2640: set pclk divide by 2.
ov2640: check pclk ok.
ov2640: set pclk divide by 4.
ov2640: check pclk ok.
ov2640: ov2640_set_zoom_window_horizontal_start_point/ov2640_get_zoom_window_horizontal_start_point test.
ov2640: enable zoom window horizontal start point.
ov2640: check zoom window horizontal start point ok.
ov2640: disable zoom window horizontal start point.
ov2640: check zoom window horizontal start point ok.
ov2640: ov2640_set_frame_length_adjustment/ov2640_get_frame_length_adjustment test.
ov2640: set frame length adjustment 617.
ov2640: check frame length adjustment ok.
ov2640: ov2640_set_zoom_mode_vertical_window_start_point/ov2640_get_zoom_mode_vertical_window_start_point test.
ov2640: set zoom mode vertical window start point 33.
ov2640: check zoom mode vertical window start point ok.
ov2640: ov2640_set_flash_light/ov2640_get_flash_light test.
ov2640: set flash light 61.
ov2640: check flash light ok.
ov2640: ov2640_set_50hz_banding_aec/ov2640_get_50hz_banding_aec test.
ov2640: set 50hz banding aec 144.
ov2640: check 50hz banding aec ok.
ov2640: ov2640_set_60hz_banding_aec/ov2640_get_60hz_banding_aec test.
ov2640: set 60hz banding aec 502.
ov2640: check 60hz banding aec ok.
ov2640: ov2640_set_16_zone_average_weight_option/ov2640_get_16_zone_average_weight_option test.
ov2640: set 16 zone average weight option 52947640.
ov2640: check 16 zone average weight option ok.
ov2640: ov2640_set_histogram_algorithm_low_level/ov2640_get_histogram_algorithm_low_level test.
ov2640: set histogram algorithm low level 90.
ov2640: check histogram algorithm low level ok.
ov2640: ov2640_set_histogram_algorithm_high_level/ov2640_get_histogram_algorithm_high_level test.
ov2640: set histogram algorithm high level 57.
ov2640: check histogram algorithm high level ok.
ov2640: ov2640_set_dsp_bypass/ov2640_get_dsp_bypass test.
ov2640: disable dsp bypass.
ov2640: check dsp bypass ok.
ov2640: enable dsp bypass.
ov2640: check dsp bypass ok.
ov2640: ov2640_set_auto_mode/ov2640_get_auto_mode test.
ov2640: enable auto mode.
ov2640: check auto mode ok.
ov2640: disable auto mode.
ov2640: check auto mode ok.
ov2640: ov2640_set_dvp_pclk/ov2640_get_dvp_pclk test.
ov2640: set dvp pclk 29.
ov2640: check dvp pclk ok.
ov2640: ov2640_set_dvp_y8/ov2640_get_dvp_y8 test.
ov2640: disable dvp y8.
ov2640: check dvp y8 ok.
ov2640: enable dvp y8.
ov2640: check dvp y8 ok.
ov2640: ov2640_set_jpeg_output/ov2640_get_jpeg_output test.
ov2640: disable jpeg output.
ov2640: check jpeg output ok.
ov2640: enable jpeg output.
ov2640: check jpeg output ok.
ov2640: ov2640_set_dvp_output_format/ov2640_get_dvp_output_format test.
ov2640: set dvp output format yuv422.
ov2640: check dvp output format ok.
ov2640: set dvp output format dvp raw10.
ov2640: check dvp output format ok.
ov2640: set dvp output format rgb565.
ov2640: check dvp output format ok.
ov2640: ov2640_set_dvp_jpeg_output_href_timing/ov2640_get_dvp_jpeg_output_href_timing test.
ov2640: set href is same as sensor.
ov2640: check dvp jpeg output href timing ok.
ov2640: set href vsync.
ov2640: check dvp jpeg output href timing ok.
ov2640: ov2640_set_byte_swap/ov2640_get_byte_swap test.
ov2640: set high byte first.
ov2640: check byte swap ok.
ov2640: set low byte first.
ov2640: check byte swap ok.
ov2640: ov2640_set_reset/ov2640_get_reset test.
ov2640: microcontroller reset.
ov2640: check microcontroller reset ok.
ov2640: sccb reset.
ov2640: check sccb reset ok.
ov2640: jpeg reset.
ov2640: check jpeg reset ok.
ov2640: dvp reset.
ov2640: check dvp reset ok.
ov2640: ipu reset.
ov2640: check ipu reset ok.
ov2640: ov2640_set_sccb_master_speed/ov2640_get_sccb_master_speed test.
ov2640: set sccb master speed 232.
ov2640: check sccb master speed ok.
ov2640: ov2640_set_sccb_slave_id/ov2640_get_sccb_slave_id test.
ov2640: set sccb slave id 96.
ov2640: check sccb slave id ok.
ov2640: ov2640_set_address_auto_increase/ov2640_get_address_auto_increase test.
ov2640: disable address auto increase.
ov2640: check address auto increase ok.
ov2640: enable address auto increase.
ov2640: check address auto increase ok.
ov2640: ov2640_set_sccb/ov2640_get_sccb test.
ov2640: enable sccb.
ov2640: check sccb ok.
ov2640: ov2640_set_sccb_master_clock_delay/ov2640_get_sccb_master_clock_delay test.
ov2640: enable sccb master clock delay.
ov2640: check sccb master clock delay ok.
ov2640: disable sccb master clock delay.
ov2640: check sccb master clock delay ok.
ov2640: ov2640_set_sccb_master_access/ov2640_get_sccb_master_access test.
ov2640: enable sccb master access.
ov2640: check sccb master access ok.
ov2640: disable sccb master access.
ov2640: check sccb master access ok.
ov2640: ov2640_set_sensor_pass_through_access/ov2640_get_sensor_pass_through_access test.
ov2640: enable sensor pass through access.
ov2640: check sensor pass through access ok.
ov2640: disable sensor pass through access.
ov2640: check sensor pass through access ok.
ov2640: ov2640_set_bist/ov2640_get_bist test.
ov2640: enable microcontroller reset.
ov2640: check bist ok.
ov2640: disable microcontroller reset.
ov2640: check bist ok.
ov2640: enable boot rom select.
ov2640: check bist ok.
ov2640: disable boot rom select.
ov2640: check bist ok.
ov2640: enable r/w 1 error for 12k - byte memory.
ov2640: check bist ok.
ov2640: disable r/w 1 error for 12k - byte memory.
ov2640: check bist ok.
ov2640: enable r/w 0 error for 12k - byte memory.
ov2640: check bist ok.
ov2640: disable r/w 0 error for 12k - byte memory.
ov2640: check bist ok.
ov2640: enable r/w 1 error for 512 - byte memory.
ov2640: check bist ok.
ov2640: disable r/w 1 error for 512 - byte memory.
ov2640: check bist ok.
ov2640: enable r/w 0 error for 512 - byte memory.
ov2640: check bist ok.
ov2640: disable r/w 0 error for 512 - byte memory.
ov2640: check bist ok.
ov2640: enable busy or one shot reset.
ov2640: check bist ok.
ov2640: disable busy or one shot reset.
ov2640: check bist ok.
ov2640: enable launch bist.
ov2640: check bist ok.
ov2640: disable launch bist.
ov2640: check bist ok.
ov2640: ov2640_set_program_memory_pointer_address/ov2640_get_program_memory_pointer_address test.
ov2640: set program memory pointer address 0.
ov2640: check program memory pointer address ok.
ov2640: ov2640_set_program_memory_pointer_access_address/ov2640_get_program_memory_pointer_access_address test.
ov2640: set program memory pointer access address 0.
ov2640: check program memory pointer access address ok.
ov2640: ov2640_set_sccb_protocol_command/ov2640_get_sccb_protocol_command test.
ov2640: set sccb protocol command 0.
ov2640: check sccb protocol command ok.
ov2640: ov2640_set_sccb_protocol_status/ov2640_get_sccb_protocol_status test.
ov2640: set sccb protocol status 217.
ov2640: check sccb protocol status ok.
ov2640: ov2640_set_cip/ov2640_get_cip test.
ov2640: disable cip.
ov2640: check cip ok.
ov2640: enable cip.
ov2640: check cip ok.
ov2640: ov2640_set_dmy/ov2640_get_dmy test.
ov2640: enable dmy.
ov2640: check dmy ok.
ov2640: disable dmy.
ov2640: check dmy ok.
ov2640: ov2640_set_raw_gma/ov2640_get_raw_gma test.
ov2640: enable raw gma.
ov2640: check raw gma ok.
ov2640: disable raw gma.
ov2640: check raw gma ok.
ov2640: ov2640_set_dg/ov2640_get_dg test.
ov2640: enable dg.
ov2640: check dg ok.
ov2640: disable dg.
ov2640: check dg ok.
ov2640: ov2640_set_awb/ov2640_get_awb test.
ov2640: enable awb.
ov2640: check awb ok.
ov2640: disable awb.
ov2640: check awb ok.
ov2640: ov2640_set_awb_gain/ov2640_get_awb_gain test.
ov2640: enable awb gain.
ov2640: check awb gain ok.
ov2640: disable awb gain.
ov2640: check awb gain ok.
ov2640: ov2640_set_lenc/ov2640_get_lenc test.
ov2640: enable lenc.
ov2640: check lenc ok.
ov2640: disable lenc.
ov2640: check lenc ok.
ov2640: ov2640_set_pre/ov2640_get_pre test.
ov2640: enable pre.
ov2640: check pre ok.
ov2640: disable pre.
ov2640: check pre ok.
ov2640: ov2640_set_aec_enable/ov2640_get_aec_enable test.
ov2640: enable aec enable.
ov2640: check aec enable ok.
ov2640: disable aec enable.
ov2640: check aec enable ok.
ov2640: ov2640_set_aec_sel/ov2640_get_aec_sel test.
ov2640: enable aec sel.
ov2640: check aec sel ok.
ov2640: disable aec sel.
ov2640: check aec sel ok.
ov2640: ov2640_set_stat_sel/ov2640_get_stat_sel test.
ov2640: enable stat sel.
ov2640: check stat sel ok.
ov2640: disable stat sel.
ov2640: check stat sel ok.
ov2640: ov2640_set_vfirst/ov2640_get_vfirst test.
ov2640: enable vfirst.
ov2640: check vfirst ok.
ov2640: disable vfirst.
ov2640: check vfirst ok.
ov2640: ov2640_set_yuv422/ov2640_get_yuv422 test.
ov2640: enable yuv422.
ov2640: check yuv422 ok.
ov2640: disable yuv422.
ov2640: check yuv422 ok.
ov2640: ov2640_set_yuv/ov2640_get_yuv test.
ov2640: enable yuv.
ov2640: check yuv ok.
ov2640: disable yuv.
ov2640: check yuv ok.
ov2640: ov2640_set_rgb/ov2640_get_rgb test.
ov2640: enable rgb.
ov2640: check rgb ok.
ov2640: disable rgb.
ov2640: check rgb ok.
ov2640: ov2640_set_raw/ov2640_get_raw test.
ov2640: enable raw.
ov2640: check raw ok.
ov2640: disable raw.
ov2640: check raw ok.
ov2640: ov2640_set_dcw/ov2640_get_dcw test.
ov2640: enable dcw.
ov2640: check dcw ok.
ov2640: disable dcw.
ov2640: check dcw ok.
ov2640: ov2640_set_sde/ov2640_get_sde test.
ov2640: enable sde.
ov2640: check sde ok.
ov2640: disable sde.
ov2640: check sde ok.
ov2640: ov2640_set_uv_adj/ov2640_get_uv_adj test.
ov2640: enable uv adj.
ov2640: check uv adj ok.
ov2640: disable uv adj.
ov2640: check uv adj ok.
ov2640: ov2640_set_uv_avg/ov2640_get_uv_avg test.
ov2640: enable uv avg.
ov2640: check uv avg ok.
ov2640: disable uv avg.
ov2640: check uv avg ok.
ov2640: ov2640_set_cmx/ov2640_get_cmx test.
ov2640: enable cmx.
ov2640: check cmx ok.
ov2640: disable cmx.
ov2640: check cmx ok.
ov2640: ov2640_set_bpc/ov2640_get_bpc test.
ov2640: enable bpc.
ov2640: check bpc ok.
ov2640: disable bpc.
ov2640: check bpc ok.
ov2640: ov2640_set_wpc/ov2640_get_wpc test.
ov2640: enable wpc.
ov2640: check wpc ok.
ov2640: disable wpc.
ov2640: check wpc ok.
ov2640: ov2640_set_sde_indirect_register_address/ov2640_get_sde_indirect_register_address test.
ov2640: set sde indirect register address 0.
ov2640: check sde indirect register address ok.
ov2640: ov2640_set_sde_indirect_register_data/ov2640_get_sde_indirect_register_data test.
ov2640: set sde indirect register data 201.
ov2640: check sde indirect register data ok.
ov2640: ov2640_set_image_horizontal/ov2640_get_image_horizontal test.
ov2640: set image horizontal 1423.
ov2640: check image horizontal ok.
ov2640: ov2640_set_image_vertical/ov2640_get_image_vertical test.
ov2640: set image vertical 220.
ov2640: check image vertical ok.
ov2640: ov2640_set_quantization_scale_factor/ov2640_get_quantization_scale_factor test.
ov2640: set quantization scale factor 15.
ov2640: check quantization scale factor ok.
ov2640: ov2640_set_lp_dp/ov2640_get_lp_dp test.
ov2640: enable lp dp.
ov2640: check lp dp ok.
ov2640: disable lp dp.
ov2640: check lp dp ok.
ov2640: ov2640_set_round/ov2640_get_round test.
ov2640: enable round.
ov2640: check round ok.
ov2640: disable round.
ov2640: check round ok.
ov2640: ov2640_set_vertical_divider/ov2640_get_vertical_divider test.
ov2640: set vertical divider 0.
ov2640: check vertical divider ok.
ov2640: ov2640_set_horizontal_divider/ov2640_get_horizontal_divider test.
ov2640: set horizontal divider 1.
ov2640: check horizontal divider ok.
ov2640: ov2640_set_horizontal_size/ov2640_get_horizontal_size test.
ov2640: set horizontal size 139.
ov2640: check horizontal size ok.
ov2640: ov2640_set_vertical_size/ov2640_get_vertical_size test.
ov2640: set vertical size 125.
ov2640: check vertical size ok.
ov2640: ov2640_set_offset_x/oov2640_get_offset_x test.
ov2640: set offset x 1294.
ov2640: check offset x ok.
ov2640: ov2640_set_offset_y/oov2640_get_offset_y test.
ov2640: set offset y 1421.
ov2640: check offset y ok.
ov2640: ov2640_set_dp_selx/ov2640_get_dp_selx test.
ov2640: set dp selx 9.
ov2640: check dp selx ok.
ov2640: ov2640_set_dp_sely/ov2640_get_dp_sely test.
ov2640: set dp sely 13.
ov2640: check dp sely ok.
ov2640: ov2640_set_output_width/ov2640_get_output_wide test.
ov2640: set output width 198.
ov2640: check output width ok.
ov2640: ov2640_set_output_height/ov2640_get_output_height test.
ov2640: set output height 340.
ov2640: check output height ok.
ov2640: ov2640_set_zoom_speed/ov2640_get_zoom_speed test.
ov2640: set zoom speed 0.
ov2640: check zoom speed ok.
ov2640: ov2640_set_light_mode test.
ov2640: check light mode auto ok.
ov2640: check light mode sunny ok.
ov2640: check light mode cloudy ok.
ov2640: check light mode office ok.
ov2640: check light mode home ok.
ov2640: ov2640_set_color_saturation test.
ov2640: check color saturation +2 ok.
ov2640: check color saturation +1 ok.
ov2640: check color saturation 0 ok.
ov2640: check color saturation -1 ok.
ov2640: check color saturation -2 ok.
ov2640: ov2640_set_brightness test.
ov2640: check brightness +2 ok.
ov2640: check brightness +1 ok.
ov2640: check brightness 0 ok.
ov2640: check brightness -1 ok.
ov2640: check brightness -2 ok.
ov2640: ov2640_set_contrast test.
ov2640: check contrast +2 ok.
ov2640: check contrast +1 ok.
ov2640: check contrast 0 ok.
ov2640: check contrast -1 ok.
ov2640: check contrast -2 ok.
ov2640: ov2640_set_special_effect test.
ov2640: check special effect antique ok.
ov2640: check special effect bluish ok.
ov2640: check special effect greenish ok.
ov2640: check special effect reddish ok.
ov2640: check special effect b&w ok.
ov2640: check special effect negative ok.
ov2640: check special effect b&w negative ok.
ov2640: check special effect normal ok.
ov2640: finish register test.
```

```shell
ov2640 -e display --time=10

ov2640: STM32F407 doesn't support display.
```

```shell
ov2640 -e photo --path=0:test.jpeg

ov2640: dma size is 47360bytes.
ov2640: found jpeg 0xFF 0xD8.
ov2640: found jpeg 0xFF 0xD9.
ov2640: save file(7115) 0:test.jpeg.
```

```shell
ov2640 -h

Usage:
  ov2604 (-i | --information)
  ov2604 (-h | --help)
  ov2604 (-p | --port)
  ov2604 (-t reg | --test=reg)
  ov2604 (-e display | --example=display) [--time=<time>]
  ov2604 (-e photo | --example=photo) [--path=<path>]

Options:
  -e <display | photo>, --example=<display | photo>
                        Run the driver example.
  -h, --help            Show the help.
  -i, --information     Show the chip information.
  -p, --port            Display the pin connections of the current board.
      --path=<path>     Set the photo path.([default: 0:test.jpeg])
  -t <reg>, --test=<reg>
                        Run the driver test.
      --time=<time>     Set the running times in second.([default: 10])
```

