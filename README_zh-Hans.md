[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver OV2640

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ov2640/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

OV2640摄像机™ 图像传感器是一种低电压CMOS器件，在小封装中提供单芯片UXGA（1632x1232）相机和图像处理器的全部功能。OV2640通过串行摄像头控制总线（SCCB）接口控制，提供各种格式的全帧、亚采样、缩放或窗口化的8位/10位图像。

该产品的图像阵列能够以UXGA分辨率以每秒15帧（fps）的速度运行，用户可以完全控制图像质量、格式和输出数据传输。所有所需的图像处理功能，包括曝光控制、伽玛、白平衡、颜色饱和度、色调控制、白色像素消除、噪声消除等，也可以通过SCCB接口进行编程。OV2640还包括用于提高处理能力的压缩引擎。此外，OmniVision CAMERACHIP传感器使用专有的传感器技术，通过减少或消除常见的图像污染光源/电源，如固定图案噪声、涂抹等，来提高图像质量，从而产生干净、完全稳定的彩色图像。

LibDriver OV2640是LibDriver推出的OV2640全功能驱动，该驱动提供图像显示，图像拍照，特殊效果设置等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example display](#example-display)
    - [example photo](#example-photo)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver OV2640的源文件。

/interface目录包含了LibDriver OV2640与平台无关的SCCB, DVP总线模板。

/test目录包含了LibDriver OV2640驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver OV2640编程范例。

/doc目录包含了LibDriver OV2640离线文档。

/datasheet目录包含了OV2640数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的SCCB, DVP总线模板，完成指定平台的SCCB, DVP总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example display

```C
#include "driver_ov2640_basic.h"

uint8_t res;

/* basic init */
res = ov2640_basic_init();
if (res != 0)
{
    return 1;
}

/* set to rgb565 mode */
res = ov2640_basic_set_rgb565_mode();
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

...

/* finish your display progress */    

...

/* ov2640 deinit */
(void)ov2640_basic_deinit();

return 0;
```

#### example photo

```C
#include "driver_ov2640_basic.h"

uint8_t res;

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

...

/* finish your jpeg captrue progress */    

...

/* ov2640 deinit */
(void)ov2640_basic_deinit();

return 0;
```

### 文档

在线文档: [https://www.libdriver.com/docs/ov2640/index.html](https://www.libdriver.com/docs/ov2640/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。