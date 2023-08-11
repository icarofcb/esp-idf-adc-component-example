#include "analogio.h"

bool CppAdc1_oneshot::_checkCalFuse() {

  esp_err_t ret{ESP_FAIL};
  bool calibrated = false;

#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
  if (!calibrated) {

    adc_cali_curve_fitting_config_t cali_config;
    cali_config.unit_id   = _unit_id;
    cali_config.atten     = _adcAttenuation;
    cali_config.bitwidth  = _bitWidth;

    ret = adc_cali_create_scheme_curve_fitting(&cali_config, &_adc1_cali_handle);
    if (ret == ESP_OK) {
      calibrated = true;
    }
  }
#endif

#if ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
  if (!calibrated) {

    adc_cali_curve_fitting_config_t cali_config;
    cali_config.unit_id   = _unit_id;
    cali_config.atten     = _adcAttenuation;
    cali_config.bitwidth  = _bitWidth;

    ret = adc_cali_create_scheme_line_fitting(&cali_config, &_adc1_cali_handle);
    if (ret == ESP_OK) {
      calibrated = true;
    }
  }
#endif

  return calibrated;
}

CppAdc1_oneshot::CppAdc1_oneshot(void) {}

CppAdc1_oneshot::CppAdc1_oneshot(adc_channel_t channel) {
  SetChannel(channel);
}

void CppAdc1_oneshot::SetChannel(adc_channel_t channel) {
  _adc1Channel = channel;

  //-------------ADC1 unit Init---------------//
  _init_config1.unit_id  = _unit_id;
  _init_config1.ulp_mode = ADC_ULP_MODE_DISABLE;

  ESP_ERROR_CHECK(adc_oneshot_new_unit(&_init_config1, &_adc1_handle));

  //-------------ADC1 channel config---------------//
  adc_oneshot_chan_cfg_t config;
  config.bitwidth = _bitWidth;
  config.atten    = _adcAttenuation;

  ESP_ERROR_CHECK(adc_oneshot_config_channel(_adc1_handle, _adc1Channel, &config));

  _calEnabled = _checkCalFuse();
}

bool CppAdc1_oneshot::CheckCalFuse() {
  return _checkCalFuse();
}

int CppAdc1_oneshot::GetRaw() {
  int adc_raw;
  ESP_ERROR_CHECK(adc_oneshot_read(_adc1_handle, _adc1Channel, &adc_raw));
  return adc_raw;
}

int CppAdc1_oneshot::GetVoltage() {
  int adc_voltage;
  if (_calEnabled) {
    ESP_ERROR_CHECK(
        adc_cali_raw_to_voltage(_adc1_cali_handle, GetRaw(), &adc_voltage));
    return adc_voltage;
  } else {
    return -1;
  }
}

esp_err_t CppAdc1_oneshot::SetBitWidth(adc_bitwidth_t bitWidth) {
  _bitWidth = bitWidth;
  _calEnabled = _checkCalFuse();

  adc_oneshot_chan_cfg_t config;
  config.bitwidth = _bitWidth;

  return adc_oneshot_config_channel(_adc1_handle, _adc1Channel, &config);
}

esp_err_t CppAdc1_oneshot::SetBitWidth(int bitWidth) {
  switch (bitWidth) {
    case 9:
      _bitWidth = ADC_BITWIDTH_9;
      break;
    case 10:
      _bitWidth = ADC_BITWIDTH_10;
      break;
    case 11:
      _bitWidth = ADC_BITWIDTH_11;
      break;
    case 12:
      _bitWidth = ADC_BITWIDTH_12;
      break;
    case 13:
      _bitWidth = ADC_BITWIDTH_13;
      break;
    default:
      _bitWidth = ADC_BITWIDTH_DEFAULT;
      break;
  }
  _calEnabled = _checkCalFuse();

  adc_oneshot_chan_cfg_t config;
  config.bitwidth = _bitWidth;

  return adc_oneshot_config_channel(_adc1_handle, _adc1Channel, &config);
}

esp_err_t CppAdc1_oneshot::SetAttenuation(adc_atten_t attenuation) {
  _adcAttenuation = attenuation;
  _calEnabled = _checkCalFuse();

  adc_oneshot_chan_cfg_t config;
  config.atten = _adcAttenuation;

  return adc_oneshot_config_channel(_adc1_handle, _adc1Channel, &config);
}
