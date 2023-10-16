#include <stdio.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <unistd.h>
#include <linux/ipmi.h> 

/*************************
 * 
 * 
 * // I2C 장치 파일 열기 및 설정
 * 
 * 
 * 
**************************/
int open_i2c_device(const char *device, int address) {
    int fd = open(device, O_RDWR);
    if (fd < 0) {
        perror("Failed to open I2C device");
        return -1;
    }
    
    if (ioctl(fd, I2C_SLAVE, address) < 0) {
        perror("Failed to set I2C address");
        close(fd);
        return -1;
    }
    
    return fd;
}
/**************************
 * 
 * 
 * // I2C 장치 파일 닫기
 * 
 * 
 * 
***************************/
void close_i2c_device(int fd) {
    close(fd);
}

/*************************
 * 
 * 
 * // I2C Read function (musik)
 * 
 * 
 * 
*************************/
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

/*************************
 * 
 * // Write to an I2C slave device's register:
 * 
 * 
**************************/
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


/*****************
 * 
 * Main
 * 
 * ? : data byte 2 안에 원하는 command를 어떻게 전달 할 것인가
 * ***************/
int main() {
    const char *i2c_device = "/dev/i2c-6";
    int i2c_address = 0x48; // I2C 장치의 주소
    int fd;
    unsigned char ipmi_command[] = {0x06, 0x01}; // 예시 IPMI 명령
    unsigned char ipmi_response[8]; // IPMI 응답 데이터 버퍼

    // I2C 장치 열기 및 설정
    fd = open_i2c_device(i2c_device, i2c_address);
    if (fd < 0) {
        return 1;
    }



    // I2C 장치 파일 닫기
    close_i2c_device(fd);

    return 0;
}

