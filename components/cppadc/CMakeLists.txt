include($ENV{IDF_PATH}/tools/cmake/version.cmake)

set(srcs "src/adc/cppadc_unit_1.cpp"
    "src/adc/cppadc_unit_2.cpp")

idf_component_register(SRCS ${srcs}
    INCLUDE_DIRS "include/adc"
    REQUIRES "driver"
    PRIV_REQUIRES "esp_adc"
    REQUIRES "esp_event")