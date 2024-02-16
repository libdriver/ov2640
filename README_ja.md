[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver OV2640

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ov2640/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

OV2640 CAMERACHIP™ イメージ センサーは、シングルチップ UXGA (1632x1232) カメラとイメージ プロセッサの全機能を小さな設置面積のパッケージで提供する低電圧 CMOS デバイスです。 OV2640 は、シリアル カメラ コントロール バス (SCCB) インターフェイスを通じて制御される、フルフレーム、サブサンプリング、スケーリングまたはウィンドウ化された 8 ビット/10 ビット画像を幅広い形式で提供します。

この製品は、UXGA 解像度で最大 15 フレーム/秒 (fps) で動作できるイメージ アレイを備えており、画質、フォーマット、出力データ転送を完全にユーザーが制御できます。 露出制御、ガンマ、ホワイトバランス、彩度、色相制御、白ピクセルキャンセリング、ノイズキャンセリングなどを含む、必要なすべての画像処理機能も、SCCB インターフェイスを通じてプログラム可能です。 OV2640 には、処理能力を向上させるための圧縮エンジンも含まれています。 さらに、OmniVision CAMERACHIP センサーは、独自のセンサー技術を使用して、固定パターン ノイズやスミアリングなどの画像汚染の一般的な照明/電源を削減または排除することで画質を向上させ、きれいで完全に安定したカラー画像を生成します。

LibDriver OV2640 は、LibDriver によって起動される OV2640 のフル機能ドライバーです。画像表示、画像キャプチャ、特殊効果設定などの機能を提供します。 LibDriver は MISRA に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example display](#example-display)
    - [example photo](#example-photo)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver OV2640のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver OV2640用のプラットフォームに依存しないSCCB, DVPバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver OV2640ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver OV2640プログラミング例が含まれています。

/ docディレクトリには、LibDriver OV2640オフラインドキュメントが含まれています。

/ datasheetディレクトリには、OV2640データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないSCCB, DVPバステンプレートを参照して、指定したプラットフォームのSCCB, DVPバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/ov2640/index.html](https://www.libdriver.com/docs/ov2640/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。