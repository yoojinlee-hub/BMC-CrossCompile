#include <stdio.h>
#include <freeipmi/freeipmi.h>

int main() {
    int rv;
    struct ipmi_ctx ctx;
    struct ipmi_rs *rsp;
    
    // IPMI 라이브러리 초기화
    if ((rv = ipmi_ctx_create(&ctx)) < 0) {
        fprintf(stderr, "ipmi_ctx_create failed\n");
        return 1;
    }

    // IPMI 명령 설정
    struct ipmi_rq req;
    ipmi_rq_initialize(&req);
    req.msg.netfn = IPMI_NETFN_APP;
    req.msg.cmd = IPMI_GET_DEVICE_ID;
    req.msg.data_len = 0;
    req.msg.data = NULL;
    
    // IPMI 명령 보내기
    rv = ipmi_cmd_raw_ipmi(&ctx, &req, &rsp);
    if (rv < 0) {
        fprintf(stderr, "ipmi_cmd_raw_ipmi failed: %s\n", ipmi_ctx_strerror(&ctx));
        return 1;
    }

    // 응답 확인
    if (rsp->ccode != 0) {
        fprintf(stderr, "IPMI command failed with completion code 0x%02x\n", rsp->ccode);
        return 1;
    }

    // 응답 데이터 처리
    printf("IPMI Response Data:\n");
    for (int i = 0; i < rsp->data_len; i++) {
        printf("0x%02x ", rsp->data[i]);
    }
    printf("\n");

    // 메모리 정리
    ipmi_rs_free(rsp);
    ipmi_ctx_close(&ctx);
    
    return 0;
}

