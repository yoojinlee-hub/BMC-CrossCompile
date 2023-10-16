#include <stdio.h>
#include <stdlib.h>

int main() {
    // IPMI 명령 실행
    char *ipmiCommand = "ipmitool raw 0x06 0x01";
    FILE *fp;
    char buffer[1024];

    fp = popen(ipmiCommand, "r");
    if (fp == NULL) {
        perror("Error executing IPMI command");
        return 1;
    }

    // IPMI 명령의 출력을 읽음
    while (fgets(buffer, sizeof(buffer) - 1, fp) != NULL) {
        printf("IPMI Response: %s", buffer);
    }

    pclose(fp);

    return 0;
}

