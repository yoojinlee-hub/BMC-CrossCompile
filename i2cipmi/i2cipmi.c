#include <stdio.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <unistd.h>
#include <linux/ipmi.h> 

// I2C 장치 파일 열기 및 설정
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

// I2C 장치 파일 닫기
void close_i2c_device(int fd) {
    close(fd);
}

// I2C를 통해 IPMI 명령을 보내는 함수
int send_ipmi_command(int fd, const unsigned char *command, int command_size, unsigned char *response, int response_size) {
    if (write(fd, command, command_size) != command_size) {
        perror("Failed to write IPMI command");
        return -1;
    }

    if (read(fd, response, response_size) != response_size) {
        perror("Failed to read IPMI response");
        return -1;
    }

    return 0;
}

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

    // IPMI LAN 주소 설정 (예시 주소: 0x04)
    struct ipmi_lan_addr lan_addr;
    lan_addr.addr_type = IPMI_LAN_ADDR_TYPE;
    lan_addr.channel = 0; // 채널 번호 설정
    lan_addr.privilege = 0; // Privilege Level 설정
    lan_addr.session_handle = 0; // 세션 핸들 설정
    lan_addr.remote_SWID = 0; // Remote SWID 설정
    lan_addr.local_SWID = 0; // Local SWID 설정
    lan_addr.lun = 0; // LUN 설정

    // IPMI 명령 보내기
    if (send_ipmi_command(fd, ipmi_command, sizeof(ipmi_command), ipmi_response, sizeof(ipmi_response) < 0)) {
        close_i2c_device(fd);
        return 1;
    }

    // 응답 데이터 출력
    printf("IPMI Response Data:\n");
    for (int i = 0; i < sizeof(ipmi_response); i++) {
        printf("Byte %d: %02X\n", i, ipmi_response[i]);
    }

    // I2C 장치 파일 닫기
    close_i2c_device(fd);

    return 0;
}

