[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver OV2640

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ov2640/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

OV2640 CAMERACHIP™ 이미지 센서는 작은 설치 공간 패키지에서 단일 칩 UXGA(1632x1232) 카메라 및 이미지 프로세서의 모든 기능을 제공하는 저전압 CMOS 장치입니다. OV2640은 직렬 카메라 제어 버스(SCCB) 인터페이스를 통해 제어되는 다양한 형식의 풀 프레임, 서브 샘플링, 스케일링 또는 윈도우 8비트/10비트 이미지를 제공합니다.

이 제품은 UXGA 해상도에서 초당 최대 15프레임(fps)으로 작동할 수 있는 이미지 배열을 갖추고 있으며, 이미지 품질, 포맷 및 출력 데이터 전송에 대한 완전한 사용자 제어가 가능합니다. 노출 제어, 감마, 화이트 밸런스, 채도, 색조 제어, 화이트 픽셀 제거, 노이즈 제거 등을 포함하여 필요한 모든 이미지 처리 기능도 SCCB 인터페이스를 통해 프로그래밍할 수 있습니다. OV2640에는 처리 능력 향상을 위한 압축 엔진도 포함되어 있습니다. 또한 OmniVision CAMERACHIP 센서는 독점 센서 기술을 사용하여 고정 패턴 노이즈, 번짐 등과 같은 이미지 오염의 일반적인 조명/전기적 원인을 줄이거나 제거하여 깨끗하고 완전히 안정적인 컬러 이미지를 생성함으로써 이미지 품질을 향상시킵니다.

LibDriver OV2640은 LibDriver에서 출시한 OV2640의 전체 기능 드라이버입니다. 이미지 표시, 이미지 캡처, 특수 효과 설정 및 기타 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example display](#example-display)
    - [example photo](#example-photo)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver OV2640의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver OV2640용 플랫폼 독립적인 SCCB, DVP버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver OV2640드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver OV2640프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver OV2640오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 OV2640데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인 SCCB, DVP버스 템플릿을 참조하여 지정된 플랫폼에 대한 SCCB, DVP버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/ov2640/index.html](https://www.libdriver.com/docs/ov2640/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.