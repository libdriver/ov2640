[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver OV2640

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ov2640/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

OV2640攝像機 ™  圖像感測器是一種低電壓CMOS器件，在小封裝中提供單晶片UXGA（1632x1232）相機和影像處理器的全部功能。 OV2640通過串列監視器控制匯流排（SCCB）介面控制，提供各種格式的全幀、亞採樣、縮放或視窗化的8比特/10比特影像。

該產品的影像陣列能够以UXGA分辯率以每秒15幀（fps）的速度運行，用戶可以完全控制圖像品質、格式和輸出資料傳輸。 所有所需的圖像處理功能，包括曝光控制、伽瑪、白平衡、顏色飽和度、色調控制、白色點數消除、雜訊消除等，也可以通過SCCB介面進行程式設計。 OV2640還包括用於提高處理能力的壓縮引擎。 此外，OmniVision CAMERACHIP感測器使用專有的感測器科技，通過减少或消除常見的影像污染光源/電源，如固定圖案雜訊、塗抹等，來提高圖像品質，從而產生乾淨、完全穩定的彩色影像。

LibDriver OV2640是LibDriver推出的OV2640全功能驅動，該驅動提供影像顯示，影像拍照，特殊效果設定等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example display](#example-display)
    - [example photo](#example-photo)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver OV2640的源文件。

/interface目錄包含了LibDriver OV2640與平台無關的SCCB, DVP總線模板。

/test目錄包含了LibDriver OV2640驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver OV2640編程範例。

/doc目錄包含了LibDriver OV2640離線文檔。

/datasheet目錄包含了OV2640數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的SCCB, DVP總線模板，完成指定平台的SCCB, DVP總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/ov2640/index.html](https://www.libdriver.com/docs/ov2640/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。
