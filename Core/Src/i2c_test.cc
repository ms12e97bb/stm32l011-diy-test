#include <string.h>
#include "stm32l0xx_hal.h"
#include "logger.h"

extern I2C_HandleTypeDef hi2c1;

namespace {

template <int N>
[[maybe_unused]] int read_24LC64(uint8_t device_addr, uint16_t mem_addr, uint8_t (&data)[N]) {
	const uint8_t mem_addr_h = (mem_addr >> 8) && 0xff;
	const uint8_t mem_addr_l = (mem_addr >> 0) && 0xff;
    uint8_t wbuf[] = { mem_addr_h, mem_addr_l };
    int ret = HAL_OK;

    ret = HAL_I2C_Master_Transmit(&hi2c1, device_addr & 0xfe, wbuf, sizeof(wbuf), HAL_MAX_DELAY);
    if (ret != HAL_OK) {
    	return ret;
    }
    return HAL_I2C_Master_Receive(&hi2c1, device_addr, data, N, HAL_MAX_DELAY);
}

[[maybe_unused]] int read_24LC64(uint8_t device_addr, uint16_t mem_addr, uint8_t *data, int size) {
	const uint8_t mem_addr_h = (mem_addr >> 8) && 0xff;
	const uint8_t mem_addr_l = (mem_addr >> 0) && 0xff;
    uint8_t wbuf[] = { mem_addr_h, mem_addr_l };
    int ret = HAL_OK;

    ret = HAL_I2C_Master_Transmit(&hi2c1, device_addr & 0xfe, wbuf, sizeof(wbuf), HAL_MAX_DELAY);
    if (ret != HAL_OK) {
    	return ret;
    }
    return HAL_I2C_Master_Receive(&hi2c1, device_addr, data, size, HAL_MAX_DELAY);
}

template <int N>
[[maybe_unused]] int write_24LC64(uint8_t device_addr, uint16_t mem_addr, uint8_t (&data)[N]) {
	const uint8_t mem_addr_h = (mem_addr >> 8) && 0xff;
	const uint8_t mem_addr_l = (mem_addr >> 0) && 0xff;

    uint8_t wbuf[N+2] = { mem_addr_h, mem_addr_l };
    memcpy(wbuf+2, data, N);
    return HAL_I2C_Master_Transmit(&hi2c1, device_addr, wbuf, sizeof(wbuf), HAL_MAX_DELAY);
}

[[maybe_unused]] int write_24LC64(uint8_t device_addr, uint16_t mem_addr, uint8_t *data, int size, uint8_t *buf) {
	const uint8_t mem_addr_h = (mem_addr >> 8) && 0xff;
	const uint8_t mem_addr_l = (mem_addr >> 0) && 0xff;

    buf[0] =  mem_addr_h;
    buf[1] =  mem_addr_l;
    memcpy(buf+2, data, size);
    return HAL_I2C_Master_Transmit(&hi2c1, device_addr, buf, size+2, HAL_MAX_DELAY);
}

[[maybe_unused]] int write_24LC64(uint8_t device_addr, uint8_t *data, int size) {
    return HAL_I2C_Master_Transmit(&hi2c1, device_addr, data, size, HAL_MAX_DELAY);
}

[[maybe_unused]] void test0() {
    uint8_t wbuf[] = {
		0x00,0x01,0x02,0x03,
		0x04,0x05,0x06,0x07,
		0x08,0x09,0x0a,0x0b,
		0x0c,0x0d,0x0e,0x0f,
	};
    int ret = HAL_OK;
	
	ret = HAL_I2C_Mem_Write(&hi2c1, 0xa0, 0x0000, I2C_MEMADD_SIZE_16BIT, wbuf, sizeof(wbuf), HAL_MAX_DELAY);
    if (ret != HAL_OK) {
    	logger("I2C mem write failed:", ret);
    	return;
    }
}

[[maybe_unused]] void test1() {
    uint8_t rbuf[10];
    int ret = HAL_OK;
	
	ret = HAL_I2C_Mem_Read(&hi2c1, 0xa1, 0x0000, I2C_MEMADD_SIZE_16BIT, rbuf, sizeof(rbuf), HAL_MAX_DELAY);
    if (ret != HAL_OK) {
    	logger("I2C mem read failed:", ret);
    	return;
    }
    logger("-----");
    logger("rbuf[0]=", rbuf[0], 0xff);
    logger("rbuf[1]=", rbuf[1], 0xff, 0xff);
    logger("rbuf[2]=", rbuf[2]);
    logger("rbuf[3]=", rbuf[3]);
    logger("rbuf[4]=", rbuf[4]);
    logger("rbuf[5]=", rbuf[5]);
    logger("rbuf[6]=", rbuf[6]);
    logger("rbuf[7]=", rbuf[7]);
    logger("rbuf[8]=", rbuf[8]);
    logger("rbuf[9]=", rbuf[9]);
}

[[maybe_unused]] void test2() {
    uint8_t wbuf[] = {
		0x00,0x01,0x02,0x03,
		0x04,0x05,0x06,0x07,
		0x08,0x09,0x0a,0x0b,
		0x0c,0x0d,0x0e,0x0f,
	};
	uint8_t buf[sizeof(wbuf) + 2];

    for (size_t n = 0; n < sizeof(wbuf); n++) {
    	wbuf[n] = wbuf[n] | 0xe0;
    }
    int ret = HAL_OK;
    ret = write_24LC64(0xa0, 0x0000, wbuf, 16, buf);
    if (ret != HAL_OK) {
    	logger("I2C mem write failed:", ret);
    	return;
    }
}

[[maybe_unused]] void test3() {
    uint8_t rbuf[10];
    int ret = HAL_OK;

	ret = read_24LC64(0xa1, 0x0000, rbuf);
    if (ret != HAL_OK) {
    	logger("I2C mem read failed:", ret);
    	return;
    }
    logger("-----");
    logger("rbuf[0]=", rbuf[0]);
    logger("rbuf[1]=", rbuf[1]);
    logger("rbuf[2]=", rbuf[2]);
    logger("rbuf[3]=", rbuf[3]);
    logger("rbuf[4]=", rbuf[4]);
    logger("rbuf[5]=", rbuf[5]);
    logger("rbuf[6]=", rbuf[6]);
    logger("rbuf[7]=", rbuf[7]);
    logger("rbuf[8]=", rbuf[8]);
    logger("rbuf[9]=", rbuf[9]);
}
} /*namespace*/

void i2c_test() {
	test3();
}


