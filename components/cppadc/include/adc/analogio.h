#pragma once

#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "soc/soc_caps.h"

class CppAdc1_oneshot {
 private:
  adc_unit_t                  _unit_id = ADC_UNIT_1;              ///< ADC1 unit
  adc_channel_t               _adc1Channel;                       ///< ADC1 channel
  adc_atten_t                 _adcAttenuation = ADC_ATTEN_DB_11;  ///< ADC1 attenuation
  adc_bitwidth_t              _bitWidth       = ADC_BITWIDTH_12;  ///< ADC1 raw output bitwidth
  adc_oneshot_unit_handle_t   _adc1_handle;                       ///< ADC1 handler
  adc_cali_handle_t           _adc1_cali_handle;                  ///< ADC1 calibration handler
  adc_oneshot_unit_init_cfg_t _init_config1;                      ///< ADC1 config struct

  bool _calEnabled = false;
  bool _checkCalFuse();

 public:
  CppAdc1_oneshot(void);
  CppAdc1_oneshot(adc_channel_t channel);
  void SetChannel(adc_channel_t channel);
  esp_err_t SetBitWidth(adc_bitwidth_t bitWidth);
  esp_err_t SetBitWidth(int bitWidth);
  esp_err_t SetAttenuation(adc_atten_t attenuation);

  bool CheckCalFuse();
  int GetRaw();
  int GetVoltage();
};  // CppAdc Class

class CppAdc2_oneshot {
 private:
  adc_unit_t                  _unit_id = ADC_UNIT_2;              ///< ADC2 unit
  adc_channel_t               _adc2Channel;                       ///< ADC2 channel
  adc_atten_t                 _adcAttenuation = ADC_ATTEN_DB_11;  ///< ADC2 attenuation
  adc_bitwidth_t              _bitWidth       = ADC_BITWIDTH_12;  ///< ADC2 raw output bitwidth
  adc_oneshot_unit_handle_t   _adc2_handle;                       ///< ADC2 handler
  adc_cali_handle_t           _adc2_cali_handle;                  ///< ADC2 calibration handler
  adc_oneshot_unit_init_cfg_t _init_config2;                      ///< ADC2 config struct

  bool _calEnabled = false;
  bool _checkCalFuse();

 public:
  CppAdc2_oneshot(void);
  CppAdc2_oneshot(adc_channel_t channel);
  void SetChannel(adc_channel_t channel);
  esp_err_t SetBitWidth(adc_bitwidth_t bitWidth);
  esp_err_t SetBitWidth(int bitWidth);
  esp_err_t SetAttenuation(adc_atten_t attenuation);

  bool CheckCalFuse();
  int GetRaw();
  int GetVoltage();
};  // CppAdc Class