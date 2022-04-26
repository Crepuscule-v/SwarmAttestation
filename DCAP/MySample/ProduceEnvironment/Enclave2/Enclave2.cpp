#include "Enclave2_t.h"
#include "sgx_trts.h"
#include "sgx_error.h"
#include "sgx_report.h"
#include "sgx_utils.h"
#include "sgx_tseal.h"
#include "sgx_mage.h"
#include "sgx_eid.h"

#include <stdio.h>      /* vsnprintf */
#include <stdarg.h>
#include <string>

unsigned char mr_list[2][67];   // 以字符串形式存储 measurement, 方便比较

// 用于输出
void printf(const char *fmt, ...) {
    char buf[BUFSIZ] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    e2_ocall_print_string(buf);
}

// 将字节形式的 measurement 转化为 字符串形式
void convert_mr(unsigned char *raw_mr, unsigned char *new_mr) {
    unsigned char highByte, lowByte;

    for (int i = 0; i < 32; i ++) {
        highByte = raw_mr[i] >> 4;
        lowByte = raw_mr[i] & 0x0f;

        // measurement 中同时包括字母和数字
        if (highByte + 48 < 58) {
            new_mr[i * 2] = highByte + 48;
        }
        else {
            new_mr[i * 2] = highByte + 87;
        }

        if (lowByte + 48 < 58) {
            new_mr[i * 2 + 1] = lowByte + 48;
        }
        else {
            new_mr[i * 2 + 1] = lowByte + 87;
        }
    }
    new_mr[64] = '\0';
}

// enclave 内生成 report 并传给外层 APP
uint32_t enclave_create_report(const sgx_target_info_t* p_qe3_target, sgx_report_t* p_report) {
    sgx_report_data_t report_data = { 0 };
    // Generate the report for the app_enclave
    sgx_status_t  sgx_error = sgx_create_report(p_qe3_target, &report_data, p_report);
    return sgx_error;
}

uint32_t get_measurement_by_mage() {
    sgx_measurement_t mr[2];        // 暂时以两个 enclave 为例
    uint64_t mage_size = sgx_mage_get_size();
    printf("Measurement of other enclaves in group are as follows :\n");
    for (uint64_t i = 0; i < mage_size; i++) {
        printf("Enclave %d:\n\t", i);
        if (SGX_SUCCESS != sgx_mage_derive_measurement(i, &mr[i])) {
            printf("failed to generate mage measurement\n");
            continue;
        }
        convert_mr(mr[i].m, mr_list[i]);
        printf("%s\n", mr_list[i]);
    }
    return SGX_SUCCESS;
}

uint32_t enclave_verify_quote(void *measurement_ptr, int *ret)
{
    get_measurement_by_mage();
    unsigned char *measurement = (unsigned char *)measurement_ptr;
    unsigned char target_mr[65];

    convert_mr(measurement, target_mr);
    printf("Received Measurement in hex is as follows : \n\t");
    printf("%s\n", target_mr);

    // 暂时未编号，两个 measurement 只要有一个对上则视为成功
    if ((!strcmp((char *)mr_list[0], (char *)target_mr)) || (!strcmp((char *)mr_list[1], (char *)target_mr))) {
        *ret = 1;
    }
    else {
        *ret = 0;
    }
    // printf("ret is : %d\n", *ret);
    return SGX_SUCCESS;
}