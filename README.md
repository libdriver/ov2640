[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver OV2640

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ov2640/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The OV2640 CAMERACHIP™ image sensor is a low voltage CMOS device that provides the full functionality of a single-chip UXGA (1632x1232) camera and image processor in a small footprint package. The OV2640 provides full-frame, sub-sampled, scaled or windowed 8-bit/10-bit images in a wide range of formats, controlled through the Serial Camera Control Bus (SCCB) interface. 

This product has an image array capable of operating at up to 15 frames per second (fps) in UXGA resolution with complete user control over image quality, formatting and output data transfer. All required image processing functions, including exposure control, gamma, white balance, color saturation, hue control, white pixel canceling, noise canceling, and more, are also programmable through the SCCB interface. The OV2640 also includes a compression engine for increased processing power. In addition, OmniVision CAMERACHIP sensors use proprietary sensor technology to improve image quality by reducing or eliminating common lighting/electrical sources of image contamination, such as fixed pattern noise, smearing, etc., to produce a clean, fully stable color image.

LibDriver OV2640 is a full function driver of OV2640 launched by LibDriver.It provides image display, image capture, special effects settings and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example display](#example-display)
    - [example photo](#example-photo)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver OV2640 source files.

/interface includes LibDriver OV2640 SCCB, DVP platform independent template.

/test includes LibDriver OV2640 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver OV2640 sample code.

/doc includes LibDriver OV2640 offline document.

/datasheet includes OV2640 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface SCCB, DVP platform independent template and finish your platform SCCB, DVP driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

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

### Document

Online documents: [https://www.libdriver.com/docs/ov2640/index.html](https://www.libdriver.com/docs/ov2640/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.