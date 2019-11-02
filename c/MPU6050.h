/*
 * MPU6050.h
 *
 * Created: 9/14/2019 6:57:19 PM
 *  Author: sberk
 */ 


#ifndef MPU6050_H_
#define MPU6050_H_

#include "I2C.h"

#define MPU6050_ADDRESS		0X68

//configuration addresses
#define SMPLRT_DIV			0x19
#define CONFIG				0x1A
#define GYRO_CONFIG			0x1B
#define ACCEL_CONFIG		0x1C
#define INT_PIN_CFG			0x37
#define INT_ENABLE			0x38

//accelerometer addresses
#define ACCEL_X_MSB			0x3B
#define ACCEL_X_LSB			0x3C
#define ACCEL_Y_MSB			0x3D
#define ACCEL_Y_LSB			0x3E
#define ACCEL_Z_MSB			0x3F
#define ACCEL_Z_LSB			0x40

//gyroscope addresses
#define GYRO_X_MSB			0x43
#define GYRO_X_LSB			0x44
#define GYRO_Y_MSB			0x45
#define GYRO_Y_LSB			0x46
#define GYRO_Z_MSB			0x47
#define GYRO_Z_LSB			0x48

//function prototypes
void MPU6050Init();
void GyroInit();

uint16_t GetXAccelData();
uint16_t GetYAccelData();
uint16_t GetZAccelData();

uint16_t GetXGyroData();
uint16_t GetYGyroData();
uint16_t GetZGyroData();

//for debugging
uint8_t accelConfigReg = 0x00;
uint8_t gyroConfigReg = 0x00;

uint8_t regCheck = 0x00;


//function implementation
void MPU6050Init(){
	
	//sets sample rate of accel and gyro to 1kHz, disable fsync
	//gyro bandwith to 44Hz and accel bandwidth to 42Hz
	WriteRegisterSingleByte(MPU6050_ADDRESS, CONFIG, 0x03); //could be 0x07
	
	regCheck = ReadRegisterSingleByte(MPU6050_ADDRESS, CONFIG);
	
	//200Hz sample rate
	//gyroscope output rate / (1 + smplrt_div)
	WriteRegisterSingleByte(MPU6050_ADDRESS, SMPLRT_DIV, 0x04);
	
	//get GYRO_CONFIG Register to clear bits
	gyroConfigReg = ReadRegisterSingleByte(MPU6050_ADDRESS, GYRO_CONFIG);
	
	//clear self test and FS_SEL Bits, lower 3 bits are reserved
	// +- 250 degrees/s
	gyroConfigReg &= ~0xF8;
	
	WriteRegisterSingleByte(MPU6050_ADDRESS, GYRO_CONFIG, gyroConfigReg);
	
	//get ACCEL_CONFIG Register to clear bits
	accelConfigReg = ReadRegisterSingleByte(MPU6050_ADDRESS, ACCEL_CONFIG);
	
	//clear self test and AFS bits, lower 3 bits
	//+- 2g
	accelConfigReg &= ~0xF8;
	
	WriteRegisterSingleByte(MPU6050_ADDRESS, ACCEL_CONFIG, accelConfigReg);
	
	//configure i2c slave interrupt
	//might not need this code
	
	//interrupt pin active high, push full, and cale on read of INT_STATUS
	//enable I2C_BYPASS_EN so other chips can join i2c bus and be controlled by master
	WriteRegisterSingleByte(MPU6050_ADDRESS, INT_PIN_CFG, 0x02);
	
	//enable data ready interrupt
	WriteRegisterSingleByte(MPU6050_ADDRESS, INT_ENABLE, 0x01);
	
	
}

void GyroInit() {
	//_delay_ms(150);	
	i2c_start();
	i2c_write_address(0x68);
	i2c_write_address(0x19);
	i2c_write_data(0x07);
	uint8_t value = ReadRegisterSingleByte(0x68, 0x19);
	i2c_stop();

	i2c_start();
	i2c_write_address(0x68);
	i2c_write_address(0x6B);
	i2c_write_data(0x01);
	i2c_stop();

	i2c_start();
	i2c_write_address(0x68);
	i2c_write_address(0x1A);
	i2c_write_data(0x00);
	i2c_stop();

	i2c_start();
	i2c_write_address(0x68);
	i2c_write_address(0x1B);
	i2c_write_data(0x18);
	i2c_stop();
}



uint16_t GetXAccelData(){
	return ReadRegisterMultipleBytes(MPU6050_ADDRESS, ACCEL_X_MSB, ACCEL_X_LSB);
}

uint16_t GetYAccelData(){
	return ReadRegisterMultipleBytes(MPU6050_ADDRESS, ACCEL_Y_MSB, ACCEL_Y_LSB);	
}

uint16_t GetZAccelData(){
	return ReadRegisterMultipleBytes(MPU6050_ADDRESS, ACCEL_Z_MSB, ACCEL_Z_LSB);	
}

uint16_t GetXGyroData(){
	return ReadRegisterMultipleBytes(MPU6050_ADDRESS, GYRO_X_MSB, GYRO_Y_MSB);
}

uint16_t GetYGyroData() {
	return ReadRegisterMultipleBytes(MPU6050_ADDRESS, GYRO_Y_MSB, GYRO_Y_LSB);
}


uint16_t GetZGyroData(){
	return ReadRegisterMultipleBytes(MPU6050_ADDRESS, GYRO_Z_MSB, GYRO_Z_LSB);
}


#endif /* MPU6050_H_ */