#include "stm32l0xx_hal.h"
#include "logger.h"

extern I2C_HandleTypeDef hi2c1;


void test0() {
    uint8_t wbuf[] = { 0x00, 0x00  /*,0xAA*/ };
    uint8_t rbuf[1];
    int ret = HAL_OK;

    ret = HAL_I2C_Master_Transmit(&hi2c1, 0xa0, wbuf, sizeof(wbuf), HAL_MAX_DELAY);
    if (ret != HAL_OK) {
    	logger("I2C write failed:", ret);
    	return;
    }

    HAL_Delay(10);  // 書き込み後のディレイ

    ret = HAL_I2C_Master_Receive(&hi2c1, 0xa1, rbuf, sizeof(rbuf), HAL_MAX_DELAY);
    if (ret != HAL_OK) {
    	logger("I2C read failed:", ret);
    	return;
    }
    logger("rbuf[0]=", rbuf[0]);
}

void test1() {
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

void test2() {
    uint8_t rbuf[32];
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

    logger("rbuf[14]=", rbuf[14]);
    logger("rbuf[15]=", rbuf[15]);
    logger("rbuf[16]=", rbuf[16]);
    logger("rbuf[17]=", rbuf[17]);
}

void i2c_test() {
	test2();
}


