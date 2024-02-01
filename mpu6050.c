#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>

int fd;

#define MPU6050_REG_ACC_X_HIGH          0x3B // 6 registers(8 bit each) starting from 0x3B store accx_high, accx_low, accy_high, accy_low, accz_high, accz_low respectively
#define MPU6050_REG_GYR_X_HIGH          0x43 // 6 registers(8 bit each) starting from 0x43 store gyrx_high, gyrx_low, gyry_high, gyry_low, gyrz_high, gyrz_low respectively

#define MPU6050_ACCEL_CONFIG        0x1C //register 28
#define MPU6050_GYRO_CONFIG         0x1B //register 27

#define MPU6050_SLAVE_ADDR 0x68
#define MPU6050_POWER 0x6B

static void mpu6050_write(uint8_t addr, uint8_t value){
	uint8_t buf[2];
	buf[0]= addr;
	buf[1]=value;
	int ret;
	if((ret = write(fd,buf,2))<=0){
		printf("WRITE FAILED!!! \n");
	}

	usleep(500);

}

void mpu6050_init(){
	// Turn off sleep mode of MPU6050 !!warning!! 0x00 shouldnt be written directly. Right way is Read, modify, write
	mpu6050_write(MPU6050_POWER, 0x00);

	//Acclerator Configuration
	mpu6050_write(MPU6050_ACCEL_CONFIG, 0x08); //set bit3 to 1 => Full scale range = +-4g

	//Gyroscope Configuration
	mpu6050_write(MPU6050_GYRO_CONFIG, 0x10); // set nit4 t0 1 => Full scale range = +-1000 degree/second


}



void mpu6050_read(uint8_t addr, int* buf){
	int ret;
	char read_buffer[6];
	//read "len" bytes
	for(int i=0;i<6;i++){	//read 6 consecutive registers for X,Y,Z directions
		//send the address to be read from
		ret = write(fd, &addr,1);
		if(ret <=0)
			printf("Address Read failed(0)\n");
		ret = read(fd,&read_buffer[i],1);
		if(ret <=0)
			printf("Address Read failed(1)\n");
		addr++;
	}

	buf[0] = ((int)(read_buffer[0]<<8) | (int)read_buffer[1]);
	buf[1] = ((int)(read_buffer[2]<<8) | (int)read_buffer[3]);
	buf[2] = ((int)(read_buffer[4]<<8) | (int)read_buffer[5]);

	usleep(500);

}


int main(){

	int acc[3], gyro[3];

	//Open the i2c device file
	if((fd=open("/dev/i2c-2",O_RDWR))<0){ // Access I2C-2 with read and write permission
		printf("Cant Open I2C file\n");
		return -1;
	}


	//Set the I2C device as Slave and write the slave address
	if (ioctl(fd,I2C_SLAVE,MPU6050_SLAVE_ADDR) < 0) { //BeagleBone MCU as Master and MPU6050 device as slave
		printf("Failed to set I2C slave address.\n");
	    close(fd);
	    return -1;
	}


	mpu6050_init();

	while(1){

		mpu6050_read(MPU6050_REG_ACC_X_HIGH, acc);
		mpu6050_read(MPU6050_REG_GYR_X_HIGH, gyro);
		printf("ACC_x = %.3f, ACC_y = %.3f, ACC_z = %.3f, GY_x = %.3f, GY_y = %.3f, GY_z = %.3f \n", acc[0]/65536.0, acc[1]/65536.0, acc[2]/65536.0, gyro[0]/65536.0,gyro[1]/65536.0,gyro[2]/65536.0);

		usleep(500000);
	}




	return 0;
}


/*			Compilation and run commands below
Save the file as MPU6050.c
Open terminal in the respective directory after making the connections
Run - gcc -C MPU6050.c -o MPU6050
Run - ./MPU6050 								*/

