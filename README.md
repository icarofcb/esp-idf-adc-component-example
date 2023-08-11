| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- |

# Example: esp-idf-adc-component-example

This test code shows how to configure ADC and how to get raw readings and calibrated voltage level as a component on a CPP project for esp-idf, it also has a SPI driver for WS2812 RGB led.

## GPIO functions:

| GPIO                         | Direction | Configuration                                          |
| ---------------------------- | --------- | ------------------------------------------------------ |
| ADC1_CHANNEL2                | input     | ADC unit 1, channel 2                                  |
| ADC2_CHANNEL2                | input     | ADC unit 2, channel 2                                  |
| LED_STRIP_BLINK_GPIO         | output    | SPI driver for WS2812                                  |


## Test:
The example enables `ADC unit 1, channel 2` and `ADC unit 2, channel 2` reads the analogic value and outputs raw and the calibrated voltage. Notice that some ESP32, such as ESP32-C3, don't have ADC2.

## How to use example

Before project configuration and build, be sure to set the correct chip target using `idf.py set-target <chip_name>`

### Build and Flash

Build the project and flash it to the board, then run the monitor tool to view the serial output:

Run `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

### Hardware Required

* A development board with any Espressif SoC (e.g., ESP32-DevKitC, ESP-WROVER-KIT, etc.)
* A USB cable for Power supply and programming
* Some jumper wires to connect GPIOs.

## Example folder contents

The project **esp-idf-adc-component-example** contains one source file in C++ language [main.cpp](main/main.cpp). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── components
│   ├── cppadc
│   │   ├── CMakeLists.txt
│   │   ├── idf_component.yml
│   │   ├── include
│   │   │   └── adc
│   │   │       └── analogio.h
│   │   └── src
│   │       └── adc
│   │           └── cppadc.cpp
│   └── espressif_led_strip_2.4.1
│       ├── CMakeLists.txt
│       ├── idf_component.yml
│       ├── README.md
│       ├── include
│       │   ├── led_strip.h
│       │   ├── led_strip_rmt.h
│       │   ├── led_strip_spi.h
│       │   └── led_strip_types.h
│       ├── include
│       │   └──  led_strip_interface.h
│       └── src
│           ├── led_strip_api.c
│           ├── led_strip_rmt_dev.c
│           ├── led_strip_rmt_encoder.c
│           ├── led_strip_rmt_encoder.h
│           └── led_strip_spi_dev.cpp
├── main
│   ├── CMakeLists.txt
│   ├── main.h
│   └── main.cpp
└── README.md                  This is the file you are currently reading
```
