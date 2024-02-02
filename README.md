# MPU6050 Driver for BeagleBone Linux

This repository contains a C file driver for interfacing with the MPU6050 accelerometer and gyroscope sensor on the BeagleBone Blacck Linux platform. The MPU6050 sensor module provides both acceleration and gyroscope data, making it suitable for various motion sensing applications.

## Features
- **I2C Communication**: Utilizes the I2C protocol for communication between the BeagleBone and the MPU6050 sensor.
- **Raw Data Retrieval**: Provides functions for reading raw accelerometer and gyroscope data.
- **Parameter Configuration**: Configures sensor parameters such as accelerometer and gyroscope full-scale range.

## Connections

Connct the VCC, ground, SCL and SDA pins of MPU6050 to the 3.3V, Ground, I2C2-SDA(pin 20) and I2C2-SCL(pin 19) on the Beagle Bone Black as shown in the schematic. 

## Schematic:
![image](https://github.com/sandeshbjain/MPU6050-Beaglebone-Linux/assets/31760278/f1ce634a-7791-4280-8966-7ee0a8bb323e)
Image Source: https://www.teachmemicro.com/beaglebone-black-mpu6050-i2c-tutorial-part-2/

![image](https://github.com/sandeshbjain/MPU6050-Beaglebone-Linux/assets/31760278/b5091bb9-dce1-4f0f-af47-aecee88cdd58)

## Usage
1. **Compilation**: Compile the C file using gcc.
   ```bash
   gcc -C MPU6050.c -o MPU6050






