#pragma once

#include <ctype.h>
#include <inttypes.h>
#include <string.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "led_strip.h"
// GPIO assignment
#define LED_STRIP_BLINK_GPIO 38
static const char* TAG = "example_adc";
}

#include "analogio.h"

// Main class used for testing only
class Main final {
 public:
  void run(void);
  void adc_read(void);

  led_strip_handle_t led_strip;
  led_strip_handle_t configure_led(void);

  CppAdc1_oneshot ADC1_CHANNEL2{ADC_CHANNEL_2};
  CppAdc2_oneshot ADC2_CHANNEL2{ADC_CHANNEL_2};
};  // Main Class