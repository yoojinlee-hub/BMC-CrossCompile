#include <stdio.h>
#include <stdlib.h>


#define raw "ipmitool raw 0x06 0x01"
#define chassis "ipmitool chassis status"
#define log "ipmitool sel list"
#define sdr "ipmitool sdr list"
#define fru "ipmitool fru list"


int main() {
    // IPMI 명령 실행
    char *ipmiCommand;
    FILE *fp;
    char buffer[1024];
    int answer=0;

    printf("choice which command do you want \n");
    printf(" 1 : raw command \n 2 : chassis \n 3 : system event log \n 4: sensor data repository \n 5 : fru list \n");
    scanf("%d",&answer);

    switch(answer){
        case 1:
            ipmiCommand = raw;
            break;
        case 2:
            ipmiCommand = chassis;
            break;
        case 3:
            ipmiCommand = log;
            break;
        case 4:
            ipmiCommand = sdr;
            break;
        case 5:
            ipmiCommand = fru;
            break;
        default: 
            printf("Wrong answer\n");
            break;
    }

    
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

