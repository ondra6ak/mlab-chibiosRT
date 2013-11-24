/*
    Based on OLIMEX STM32-P107
    Ported by Ondra Sestak 2013
    
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_


/*
 * Board identifier.
 */
#define BOARD_MLAB_STM32F107RxT01A
#define BOARD_NAME              "MLAB STM32F107RxT01A"

/*
 * Board frequencies.
 */
#define STM32_HSECLK            25000000

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F10X_CL

/*
 * IO pins assignments.
 */
#define LED1                8   /* PB8 */
#define LED2                7   /* PB7 */
#define SD_PROTECT          4   /* PB4 */
#define SD_DETECT           5   /* PB5 */
#define SPI1NSS             4   /* PA4 */
#define SPI2NSS             12  /* PB12 */

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The digits have the following meaning:
 *   0 - Analog input.
 *   1 - Push Pull output 10MHz.
 *   2 - Push Pull output 2MHz.
 *   3 - Push Pull output 50MHz.
 *   4 - Digital input.
 *   5 - Open Drain output 10MHz.
 *   6 - Open Drain output 2MHz.
 *   7 - Open Drain output 50MHz.
 *   8 - Digital input with PullUp or PullDown resistor depending on ODR.
 *   9 - Alternate Push Pull output 10MHz.
 *   A - Alternate Push Pull output 2MHz.
 *   B - Alternate Push Pull output 50MHz.
 *   C - Reserved.
 *   D - Alternate Open Drain output 10MHz.
 *   E - Alternate Open Drain output 2MHz.
 *   F - Alternate Open Drain output 50MHz.
 * Please refer to the STM32 Reference Manual for details.
 */

/*
 * Port A setup.
 * Everything input with pull-up except:
 * PA0  - Input with PU     (unconnected).
 * PA1  - Input with PU     (unconnected).
 * PA2  - Alternate output  (USART2 TX).
 * PA3  - Input with PU     (USART2 RX).
 * PA4  - Open Drain output (SPI1 NSS).
 * PA5  - Alternate output  (SPI1 SCK).
 * PA6  - Input with PU     (SPI1 MISO).
 * PA7  - Alternate output  (SPI1 MOSI).
 * PA8  - Alternate output  (MCO).
 * PA9  - Normal input      (OTG_VBUS).
 * PA10 - Normal input      (OTG_ID).
 * PA11 - Normal input      (OTG_DM).
 * PA12 - Normal input      (OTG_DP).
 * PA13 - Normal input      (TMS).
 * PA14 - Normal input      (TCK).
 * PA15 - Normal input      (TDI).
 */
#define VAL_GPIOACRL            0xB8B78B88      /*  PA7...PA0 */
#define VAL_GPIOACRH            0x4444444B      /* PA15...PA8 */
#define VAL_GPIOAODR            0xFFFFFFFF

/*
 * Port B setup:
 * PB0  - Input with PU     (unconnected).
 * PB1  - Input with PU     (unconnected).
 * PB2  - Normal input      (BOOT1).
 * PB3  - Normal input      (TDO).
 * PB4  - Normal input      (TRST).
 * PB5  - Input with PU     (unconnected).
 * PB6  - Input with PU     (unconnected).
 * PB7  - Push Pull output  (LED2).
 * PB8  - Push Pull output  (LED1).
 * PB9  - Input with PU     (unconnected).
 * PB10 - Open Drain        (I2C2 SCL).
 * PB11 - Open Drain        (I2C2 SDA).
 * PB12 - Open Drain output (SPI2 NSS).
 * PB13 - Alternate output  (SPI2 SCK).
 * PB14 - Input with PU     (SPI2 MISO).
 * PB15 - Alternate output  (SPI2 MOSI).
 */
#define VAL_GPIOBCRL            0x38844488      /*  PB7...PB0 */
#define VAL_GPIOBCRH            0xB8B7FF83      /* PB15...PB8 */
#define VAL_GPIOBODR            0xFFFFFFFF

/*
 * Port C setup:
 * PC0  - Input with PU     (unconnected).
 * PC1  - Input with PU     (unconnected).
 * PC2  - Input with PU     (unconnected).
 * PC3  - Input with PU     (unconnected).
 * PC4  - Input with PU     (unconnected).
 * PC5  - Input with PU     (unconnected).
 * PC6  - Input with PU     (unconnected).
 * PC7  - Input with PU     (unconnected).
 * PC8  - Input with PU     (unconnected).
 * PC9  - Input with PU     (unconnected).
 * PC10 - Alternate output  (UART4 TX).
 * PC11 - Input with PU     (UART4 RX).
 * PC12 - Input with PU     (unconnected).
 * PC13 - Input with PU     (unconnected).
 * PC14 - Normal input      (OSC32 IN).
 * PC15 - Normal input      (OSC32 OUT).
 */
#define VAL_GPIOCCRL            0x88888888      /*  PC7...PC0 */
#define VAL_GPIOCCRH            0x44888B88      /* PC15...PC8 */
#define VAL_GPIOCODR            0xFFFFFF3F

/*
 * Port D setup:
 * PD0  - Input with PU     (unconnected).
 * PD1  - Input with PU     (unconnected).
 * PD2  - Input with PU     (unconnected).
 * PD3  - Input with PU     (unconnected).
 * PD4  - Input with PU     (unconnected).
 * PD5  - Input with PU     (unconnected).
 * PD6  - Input with PU     (unconnected).
 * PD7  - Push Pull output  (USB_VBUSON).
 * PD8  - Input with PU     (unconnected).
 * PD9  - Input with PU     (unconnected).
 * PD10 - Input with PU     (unconnected).
 * PD11 - Input with PU     (unconnected).
 * PD12 - Input with PU     (unconnected).
 * PD13 - Input with PU     (unconnected).
 * PD14 - Input with PU     (unconnected).
 * PD15 - Input with PU     (unconnected).
 */
#define VAL_GPIODCRL            0x38888888      /*  PD7...PD0 */
#define VAL_GPIODCRH            0x88888888      /* PD15...PD8 */
#define VAL_GPIODODR            0xFFFFFFFF

/*
 * Port E setup.
 * Everything input with pull-up except:
 * PE15 - Normal input      (USB_FAULT).
 */
#define VAL_GPIOECRL            0x88888888      /*  PE7...PE0 */
#define VAL_GPIOECRH            0x48888888      /* PE15...PE8 */
#define VAL_GPIOEODR            0xFFFFFFFF

 
 /*
 * USB bus activation macro, required by the USB driver.
 */
#define usb_lld_connect_bus(usbp) 
/*define usb_lld_connect_bus(usbp) palClearPad(GPIOC, GPIOC_USB_DISC) */

/*
 * USB bus de-activation macro, required by the USB driver.
 */
#define usb_lld_disconnect_bus(usbp) 
/*define usb_lld_disconnect_bus(usbp) palSetPad(GPIOC, GPIOC_USB_DISC) */


#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */