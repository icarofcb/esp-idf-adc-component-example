#include "main.h"

Main App;

led_strip_handle_t Main::configure_led(void) {
  // LED strip general initialization, according to your led board design
  led_strip_config_t strip_config;
  strip_config.strip_gpio_num =
      LED_STRIP_BLINK_GPIO;   // The GPIO that connected to the
                              // LED strip's data line
  strip_config.max_leds = 1;  // The number of LEDs in the strip,
  strip_config.led_pixel_format =
      LED_PIXEL_FORMAT_GRB;                   // Pixel format of your LED strip
  strip_config.led_model = LED_MODEL_WS2812;  // LED strip model
  strip_config.flags.invert_out = false;  // whether to invert the output signal

  // LED strip backend configuration: SPI
  led_strip_spi_config_t spi_config;
  spi_config.clk_src = SPI_CLK_SRC_DEFAULT;  // different clock source can lead
                                             // to different power consumption
  spi_config.flags.with_dma = true;  // Using DMA can improve performance and
                                     // help drive more LEDs
  spi_config.spi_bus = SPI2_HOST;    // SPI bus ID

  // LED Strip object handle
  led_strip_handle_t led_strip;
  ESP_ERROR_CHECK(
      led_strip_new_spi_device(&strip_config, &spi_config, &led_strip));
  ESP_LOGI(TAG, "Created LED strip object with SPI backend");
  return led_strip;
}

void Main::adc_read(void) {
  ESP_LOGI(TAG, " ADC1_CHANNEL2 raw: %d // voltage %d mV",
           ADC1_CHANNEL2.GetRaw(), ADC1_CHANNEL2.GetVoltage());
  ESP_LOGI(TAG, " ADC2_CHANNEL2 raw: %d // voltage %d mV",
           ADC2_CHANNEL2.GetRaw(), ADC2_CHANNEL2.GetVoltage());
}

extern "C" void app_main(void) {
  ESP_LOGI(TAG, " starting firmware ");

  App.led_strip = App.configure_led();
  ESP_ERROR_CHECK(led_strip_set_pixel(App.led_strip, 0, 0, 0, 5));
  ESP_ERROR_CHECK(led_strip_refresh(App.led_strip));
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  while (true) {
    App.adc_read();
    vTaskDelay(1500 / portTICK_PERIOD_MS);
  }
}
