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
 * @file      main.c
 * @brief     main source file
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
#include "driver_ov2640_basic.h"
#include "ff.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "dcmi.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];                        /**< uart buffer */
volatile uint16_t g_len;                   /**< uart buffer length */
volatile uint16_t g_flag;                  /**< dcmi flag */
uint32_t g_start;                         /**< buffer start */
uint32_t g_end;                           /**< buffer end */
void (*dcmi_callback)(void) = NULL;        /**< dcmi callback */
uint8_t g_jpeg_buf[1024 * 96];             /**< jpeg buffer */

/**
 * @brief fs var definition
 */
FATFS g_fs;        /**< fatfs handle */
FIL g_file;        /**< fs handle */

/**
 * @brief jpeg callback
 * @note  none
 */
void a_jpeg_callback(void)
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t len = 0;

    /* get jpeg size */
    len = __HAL_DMA_GET_COUNTER(dcmi_get_dma_handle());

    /* output */
    uart_print("ov2640: dma size is %dbytes.\n", len);

    /* set end */
    len = len - 1;

    g_start = 0;
    g_end = 0;

    for (i = 0; i < len; i++)
    {
        if ((g_jpeg_buf[i] == 0xFF) && (g_jpeg_buf[i + 1] == 0xD8))
        {
            uart_print("ov2640: found jpeg 0xFF 0xD8.\n");
            g_start = i;

            break;
        }
    }

    for (j = i; j < len; j++)
    {
        if ((g_jpeg_buf[j] == 0xFF) && (g_jpeg_buf[j + 1] == 0xD9))
        {
            uart_print("ov2640: found jpeg 0xFF 0xD9.\n");
            g_end = j;

            break;
        }
    }

    if (g_end != 0)
    {
        g_flag = 1;
    }
    else
    {
        g_flag = 2;
        uart_print("ov2640: jpeg is error.\n");
    }
}

/**
 * @brief     ov2640 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t ov2640(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"path", required_argument, NULL, 1},
        {"time", required_argument, NULL, 2},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t time = 10;
    char path[33] = "0:test.jpeg";

    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }

    /* init 0 */
    optind = 0;

    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);

        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");

                break;
            }

            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");

                break;
            }

            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");

                break;
            }

            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);

                break;
            }

            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);

                break;
            }

            /* path */
            case 1 :
            {
                /* set the path */
                memset(path, 0, sizeof(char) * 33);
                snprintf(path, 32, "%s", optarg);

                break;
            }

            /* running time */
            case 2 :
            {
                /* set the time */
                time = atol(optarg);

                break;
            }

            /* the end */
            case -1 :
            {
                break;
            }

            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run functions */
    if (strcmp("t_reg", type) == 0)
    {
        /* run reg test */
        if (ov2640_register_test() != 0)
        {
            return 1;
        }

        return 0;
    }
    else if (strcmp("e_display", type) == 0)
    {
        time++;
        ov2640_interface_debug_print("ov2640: STM32F407 doesn't support display.\n");

        return 0;
    }
    else if (strcmp("e_photo", type) == 0)
    {
        uint8_t res;
        uint32_t timeout;

        /* basic init */
        res = ov2640_basic_init();
        if (res != 0)
        {
            return 1;
        }

        /* set to jpeg mode */
        res = ov2640_basic_set_jpeg_mode();
        if (res != 0)
        {
            (void)ov2640_basic_deinit();

            return 1;
        }

        /* set image resolution */
        res = ov2640_basic_set_image_resolution(OV2640_IMAGE_RESOLUTION_QQVGA);
        if (res != 0)
        {
            (void)ov2640_basic_deinit();

            return 1;
        }

        /* delay 500ms */
        ov2640_interface_delay_ms(500);

        /* set dcmi callback */
        dcmi_callback = a_jpeg_callback;

        /* init 0 */
        g_flag = 0;

        /* dcmi init in jpeg mode */
        res = dcmi_init(1);
        if (res != 0)
        {
            (void)ov2640_basic_deinit();

            return 1;
        }

        /* snapshot start */
        res = dcmi_snapshot_start(g_jpeg_buf, 1024 * 96);
        if (res != 0)
        {
            (void)dcmi_stop();
            (void)dcmi_deinit();
            (void)ov2640_basic_deinit();

            return 1;
        }

        /* set timeout */
        timeout = 10 * 100;

        /* wait timeout */
        while (timeout != 0)
        {
            /* check flag */
            if (g_flag != 0)
            {
                break;
            }

            timeout--;

            /* delay 10ms */
            ov2640_interface_delay_ms(10);
        }

        /* save */
        if (g_flag == 1)
        {
            FRESULT ret;
            UINT bw;

            /* mount */
            ret = f_mount(&g_fs, "0:", 1);
            if (ret != FR_OK)
            {
                ov2640_interface_debug_print("ov2640: mount failed.\n");
                (void)dcmi_stop();
                (void)dcmi_deinit();
                (void)ov2640_basic_deinit();

                return 1;
            }

            /* open file */
            ret = f_open(&g_file, path, FA_WRITE | FA_CREATE_ALWAYS);
            if (ret != FR_OK)
            {
                ov2640_interface_debug_print("ov2640: open file failed.\n");
                (void)f_unmount("0:");
                (void)dcmi_stop();
                (void)dcmi_deinit();
                (void)ov2640_basic_deinit();

                return 1;
            }

            /* write file */
            ret = f_write(&g_file, g_jpeg_buf + g_start, g_end - g_start + 1, &bw);
            if (ret != FR_OK)
            {
                ov2640_interface_debug_print("ov2640: write file failed.\n");
                (void)f_close(&g_file);
                (void)f_unmount("0:");
                (void)dcmi_stop();
                (void)dcmi_deinit();
                (void)ov2640_basic_deinit();

                return 1;
            }

            /* close file */
            ret = f_close(&g_file);
            if (ret != FR_OK)
            {
                ov2640_interface_debug_print("ov2640: close file failed.\n");
                (void)f_unmount("0:");
                (void)dcmi_stop();
                (void)dcmi_deinit();
                (void)ov2640_basic_deinit();

                return 1;
            }

            /* unmount */
            ret = f_unmount("0:");
            if (ret != FR_OK)
            {
                ov2640_interface_debug_print("ov2640: unmount failed.\n");
                (void)dcmi_stop();
                (void)dcmi_deinit();
                (void)ov2640_basic_deinit();

                return 1;
            }

            /* output */
            ov2640_interface_debug_print("ov2640: save file(%d) %s.\n", g_end - g_start + 1, path);
        }

        /** dcmi stop */
        (void)dcmi_stop();

        /* dcmi deint */
        (void)dcmi_deinit();

        /* ov2640 deinit */
        (void)ov2640_basic_deinit();

        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        ov2640_interface_debug_print("Usage:\n");
        ov2640_interface_debug_print("  ov2604 (-i | --information)\n");
        ov2640_interface_debug_print("  ov2604 (-h | --help)\n");
        ov2640_interface_debug_print("  ov2604 (-p | --port)\n");
        ov2640_interface_debug_print("  ov2604 (-t reg | --test=reg)\n");
        ov2640_interface_debug_print("  ov2604 (-e display | --example=display) [--time=<time>]\n");
        ov2640_interface_debug_print("  ov2604 (-e photo | --example=photo) [--path=<path>]\n");
        ov2640_interface_debug_print("\n");
        ov2640_interface_debug_print("Options:\n");
        ov2640_interface_debug_print("  -e <display | photo>, --example=<display | photo>\n");
        ov2640_interface_debug_print("                        Run the driver example.\n");
        ov2640_interface_debug_print("  -h, --help            Show the help.\n");
        ov2640_interface_debug_print("  -i, --information     Show the chip information.\n");
        ov2640_interface_debug_print("  -p, --port            Display the pin connections of the current board.\n");
        ov2640_interface_debug_print("      --path=<path>     Set the photo path.([default: 0:test.jpeg])\n");
        ov2640_interface_debug_print("  -t <reg>, --test=<reg>\n");
        ov2640_interface_debug_print("                        Run the driver test.\n");
        ov2640_interface_debug_print("      --time=<time>     Set the running times in second.([default: 10])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        ov2640_info_t info;

        /* print ov2640 info */
        ov2640_info(&info);
        ov2640_interface_debug_print("ov2640: chip is %s.\n", info.chip_name);
        ov2640_interface_debug_print("ov2640: manufacturer is %s.\n", info.manufacturer_name);
        ov2640_interface_debug_print("ov2640: interface is %s.\n", info.interface);
        ov2640_interface_debug_print("ov2640: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ov2640_interface_debug_print("ov2640: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ov2640_interface_debug_print("ov2640: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ov2640_interface_debug_print("ov2640: max current is %0.2fmA.\n", info.max_current_ma);
        ov2640_interface_debug_print("ov2640: max temperature is %0.1fC.\n", info.temperature_max);
        ov2640_interface_debug_print("ov2640: min temperature is %0.1fC.\n", info.temperature_min);

        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        ov2640_interface_debug_print("ov2640: SCL connected to GPIOB PIN8.\n");
        ov2640_interface_debug_print("ov2640: SDA connected to GPIOB PIN9.\n");
        ov2640_interface_debug_print("ov2640: RST connected to GPIOA PIN0.\n");
        ov2640_interface_debug_print("ov2640: PWD connected to GPIOA PIN8.\n");
        ov2640_interface_debug_print("ov2640: D0 connected to GPIOC PIN6.\n");
        ov2640_interface_debug_print("ov2640: D1 connected to GPIOC PIN7.\n");
        ov2640_interface_debug_print("ov2640: D2 connected to GPIOE PIN0.\n");
        ov2640_interface_debug_print("ov2640: D3 connected to GPIOE PIN1.\n");
        ov2640_interface_debug_print("ov2640: D4 connected to GPIOE PIN4.\n");
        ov2640_interface_debug_print("ov2640: D5 connected to GPIOB PIN6.\n");
        ov2640_interface_debug_print("ov2640: D6 connected to GPIOE PIN5.\n");
        ov2640_interface_debug_print("ov2640: D7 connected to GPIOE PIN6.\n");
        ov2640_interface_debug_print("ov2640: PCLK connected to GPIOA PIN6.\n");
        ov2640_interface_debug_print("ov2640: HREF connected to GPIOA PIN4.\n");
        ov2640_interface_debug_print("ov2640: VSYNC connected to GPIOB PIN7.\n");

        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;

    /* stm32f407 clock init and hal init */
    clock_init();

    /* delay init */
    delay_init();

    /* uart init */
    uart_init(115200);

    /* shell init && register ov2640 function */
    shell_init();
    shell_register("ov2640", ov2640);
    uart_print("ov2640: welcome to libdriver ov2640.\n");

    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("ov2640: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("ov2640: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("ov2640: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("ov2640: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("ov2640: param is invalid.\n");
            }
            else
            {
                uart_print("ov2640: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
