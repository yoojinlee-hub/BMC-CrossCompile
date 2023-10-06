#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>

// Terrible portability hack between arm-linux-gnueabihf-gcc on Mac OS X and native gcc on raspbian.
#ifndef I2C_M_RD
#include <linux/i2c.h>
#endif

typedef unsigned char   u8;

// Global file descriptor used to talk to the I2C bus:
int i2c_fd = -1;
// Default RPi B device name for the I2C bus exposed on GPIO2,3 pins (GPIO2=SDA, GPIO3=SCL): 
const char *i2c_fname = "/dev/i2c-6";

// Returns a new file descriptor for communicating with the I2C bus:
int i2c_init(void) {
    if ((i2c_fd = open(i2c_fname, O_RDWR)) < 0) {
        char err[200];
        sprintf(err, "iw__open('%s') in i2c_init", i2c_fname);
        perror(err);
        return -1;
    }

    // NOTE we do not call ioctl with I2C_SLAVE here because we always use the I2C_RDWR ioctl operation to do
    // writes, reads, and combined write-reads. I2C_SLAVE would be used to set the I2C slave address to communicate
    // with. With I2C_RDWR operation, you specify the slave address every time. There is no need to use normal write()
    // or read() syscalls with an I2C device which does not support SMBUS protocol. I2C_RDWR is much better especially
    // for reading device registers which requires a write first before reading the response.

    return i2c_fd;
}

void i2c_close(void) {
    close(i2c_fd);
}

// Write to an I2C slave device's register:
int i2c_write(u8 slave_addr, u8 reg, u8 *data) {
    int retval;
    u8 outbuf[3];

    struct i2c_msg msgs[1];
    struct i2c_rdwr_ioctl_data msgset[1];

    outbuf[0] = reg;
    outbuf[1] = data[0];
    outbuf[2] = data[1];

    msgs[0].addr = slave_addr;
    msgs[0].flags = 0;
    msgs[0].len = 2;
    msgs[0].buf = outbuf;

    msgset[0].msgs = msgs;
    msgset[0].nmsgs = 1;

    if (ioctl(i2c_fd, I2C_RDWR, &msgset) < 0) {
        perror("iw__ioctl(I2C_RDWR) in i2c_write");
        return -1;
    }

    return 0;
}

// Read the given I2C slave device's register and return the read value in `*result`:
int i2c_read(u8 slave_addr, u8 reg, u8 *result) {
    int retval;
    u8 outbuf[1], inbuf[1];
    struct i2c_msg msgs[2];
    struct i2c_rdwr_ioctl_data msgset[1];

    msgs[0].addr = slave_addr;
    msgs[0].flags = 0;
    msgs[0].len = 1;
    msgs[0].buf = outbuf;

    msgs[1].addr = slave_addr;
    msgs[1].flags = I2C_M_RD | I2C_M_NOSTART;
    msgs[1].len = 1;
    msgs[1].buf = inbuf;

    msgset[0].msgs = msgs;
    msgset[0].nmsgs = 2;

    outbuf[0] = reg;

    inbuf[0] = 0;

    *result = 0;
    if (ioctl(i2c_fd, I2C_RDWR, &msgset) < 0) {
        perror("ioctl(I2C_RDWR) in i2c_read");
        return -1;
    }

    *result = inbuf[0];
    return 0;
}

//Read function Made by YJ..
int yj_read(){
    int fd;
    int i2c_addresses[] = {0x48, 0x49, 0x4a, 0x4d}; // 여러 개의 I2C 주소
    char data[2];
    int T=0;

    // I2C 장치 파일 열기
    fd = open("/dev/i2c-6", O_RDWR);
    if (fd < 0) {
        printf("iw:Failed to open /dev/i2c-6\n");
        return 1;
    }

    for (int i = 0; i < sizeof(i2c_addresses) / sizeof(i2c_addresses[0]); i++) {
        // I2C 장치 주소 설정
        if (ioctl(fd, I2C_SLAVE, i2c_addresses[i]) < 0) {
            printf("iw:Failed to set I2C address(data from 0x%02X)... errno : %d\n",i2c_addresses[i], errno);
            close(fd);
            return 1;
        }

        // 데이터 읽기
        if (read(fd, data, sizeof(data)) != sizeof(data)) {
            printf("iw:Failed to read data (data from 0x%02X)... errno : %d\n",i2c_addresses[i], errno);
            close(fd);
            return 1;
        }

	T = ((data[0]&0xFF)<<4)|((data[1]>>4)&0x0F);
		
        // 읽은 데이터 출력
        printf("iw:Data from 0x%02X: %02X %02X\n", i2c_addresses[i], data[0], data[1]);
	printf("%d\n",T);
	printf("%d\n",T*625 );
    }

    // I2C 장치 파일 닫기
    close(fd);

    return 0;
}
/*********************************************************
 *
 *
 *
 * ******************************************************/
int main(void){
	u8 slave_addr = 0x48;
	u8 w_reg = 0x03;
	u8 data[2] = {0xAA, 0x00};

	i2c_init();

	i2c_write(slave_addr, w_reg, data);
	//i2c_read(slave_addr, w_reg, data);
	
	i2c_close();

	printf("Made by YJ==\n");

}


