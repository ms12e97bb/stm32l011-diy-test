#include "stm32l0xx_hal.h"
#include "logger.h"
#include "adc_test.h"

extern ADC_HandleTypeDef hadc;

namespace {

[[maybe_unused]] void test0() {
	int ret = HAL_OK;

	ret = HAL_ADC_Start(&hadc);
    if (ret != HAL_OK) {
    	logger("ADC start failed:", ret);
    	return;
    }

    ret = HAL_ADC_PollForConversion(&hadc, 10);
    if (ret != HAL_OK) {
    	logger("ADC polling failed:", ret);
    	return;
    }

    const uint32_t val = HAL_ADC_GetValue(&hadc);
    logger("ADC value:", val);

    HAL_ADC_Stop(&hadc);
}


void test1() {
	 HAL_ADC_Start_IT(&hadc);
}

} /* namespace */

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    if (hadc->Instance == ADC1) {
        const uint32_t val = HAL_ADC_GetValue(hadc);
        logger("ADC value:", val);
        HAL_ADC_Stop_IT(hadc);
    }
}

void adc_test() {
	test1();
}


