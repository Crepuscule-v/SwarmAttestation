/**
 * App 支持 ：
 * 1. 从 enclave 内部获取 report，然后生成对应的 quote
 * 2. 将传来的 report 传入到 enclave 中进行验证，获得验证结果
 */

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <assert.h>
#include <fstream>

#include "sgx_uae_launch.h"
#include "sgx_urts.h"
#include "sgx_report.h"
#include "sgx_dcap_ql_wrapper.h"
#include "sgx_pce.h"
#include "sgx_error.h"
#include "sgx_quote_3.h"
#include "sgx_ql_quote.h"
#include "sgx_dcap_quoteverify.h"

#include "Enclave2_u.h"

#define SGX_AESM_ADDR "SGX_AESM_ADDR"
#define ENCLAVE_PATH "libenclave2.so"

using namespace std;

// get report from enclave
bool get_app_enclave_report(sgx_target_info_t qe_target_info, sgx_report_t *app_report, sgx_enclave_id_t eid)
{
    bool ret = true;
    uint32_t retval = 0;
    sgx_status_t sgx_status = SGX_SUCCESS;
    sgx_status = Enclave2_enclave_create_report(eid, &retval, &qe_target_info, app_report);
    if ((SGX_SUCCESS != sgx_status) || (0 != retval)) 
    {
        printf("\nCall enclave_create_report() failed\n");
        ret = false;
    }

    return ret;
}

// generate quote
int generate_quote(sgx_enclave_id_t eid)
{
    int ret = 1;
    quote3_error_t qe3_ret = SGX_QL_SUCCESS;
    uint32_t quote_size = 0;
    uint8_t* p_quote_buffer = NULL;
    sgx_target_info_t qe_target_info;
    sgx_report_t app_report;
    sgx_quote3_t *p_quote;
    FILE *fptr = NULL;

    printf("\nStep1: Call sgx_qe_get_target_info:");
    qe3_ret = sgx_qe_get_target_info(&qe_target_info);
    if (SGX_QL_SUCCESS != qe3_ret) {
        printf("Error in sgx_qe_get_target_info. 0x%04x\n", qe3_ret);
                ret = 0;
        goto CLEANUP;
    }
    printf("succeed!");

    printf("\nStep2: Call get_app_enclave_report:");
    if(true != get_app_enclave_report(qe_target_info, &app_report, eid)) {
        printf("\nCall to get_app_enclave_report() failed\n");
        ret = 0;
        goto CLEANUP;
    }

    printf("succeed!");
    printf("\nStep3: Call sgx_qe_get_quote_size:");
    qe3_ret = sgx_qe_get_quote_size(&quote_size);
    if (SGX_QL_SUCCESS != qe3_ret) {
        printf("Error in sgx_qe_get_quote_size. 0x%04x\n", qe3_ret);
        ret = 0;
        goto CLEANUP;
    }

    printf("succeed!");
    p_quote_buffer = (uint8_t*)malloc(quote_size);
    if (NULL == p_quote_buffer) {
        printf("Couldn't allocate quote_buffer\n");
        ret = 0;
        goto CLEANUP;
    }
    memset(p_quote_buffer, 0, quote_size);

    // Get the Quote
    printf("\nStep4: Call sgx_qe_get_quote:");
    qe3_ret = sgx_qe_get_quote(&app_report,
        quote_size,
        p_quote_buffer);
    if (SGX_QL_SUCCESS != qe3_ret) {
        printf( "Error in sgx_qe_get_quote. 0x%04x\n", qe3_ret);
        ret = 0;
        goto CLEANUP;
    }
    printf("succeed!");

    p_quote = (sgx_quote3_t*)p_quote_buffer;

    // 将 quote 写入到 quote.data
    fptr = fopen("./quote.dat","wb");
    if(fptr)
    {
        fwrite(p_quote, quote_size, 1, fptr);
        fclose(fptr);
    }

CLEANUP:
    if (NULL != p_quote_buffer) {
        free(p_quote_buffer);
    }
    return ret;
}

// 从 quote 文件中读取 quote, 存入 vector 中
vector<uint8_t> readBinaryContent(const string& filePath)
{
    ifstream file(filePath, ios::binary);
    if (!file.is_open())
    {
        printf("Error: Unable to open quote file %s\n", filePath.c_str());
        return {};
    }

    file.seekg(0, ios_base::end);
    streampos fileSize = file.tellg();

    file.seekg(0, ios_base::beg);
    vector<uint8_t> retVal(fileSize);
    file.read(reinterpret_cast<char*>(retVal.data()), fileSize);
    file.close();
    return retVal;
}

// 对收到的其它 enclave 的 report 进行验证
int quoteVerify(string quote_path, sgx_enclave_id_t eid)
{
    quote_path = "./quote.dat";
    int ret = 0;
    vector<uint8_t> quote;
    quote = readBinaryContent(quote_path);
    sgx_status_t sgx_ret = SGX_SUCCESS;
    uint32_t retval = 0;

    // 只传入 measurement 
    uint8_t* mr_pos = quote.data() + 112;
    uint8_t measurement[32];
    for (int i = 0; i < 32; i ++) {
        measurement[i] = *mr_pos ++;        // 读取 measurement，以字节流的形式
    }

    sgx_ret = Enclave2_enclave_verify_quote(eid, &retval, &measurement, &ret);      // 调用 ecall 函数
    if ((SGX_SUCCESS != sgx_ret) || (0 != retval)) {
        printf("\nCall to enclave_verify_qutoe() failed\n");
        ret = 0;
    }
    return ret;
}

void e2_ocall_print_string(const char *str) {
    printf("%s", str);
}

int main()
{
    // create enclave
    sgx_status_t sgx_status = SGX_SUCCESS;
    sgx_enclave_id_t eid = 0;
    int launch_token_updated = 0;
    sgx_launch_token_t launch_token = { 0 };
    sgx_status = sgx_create_enclave(ENCLAVE_PATH, SGX_DEBUG_FLAG, &launch_token, &launch_token_updated, &eid, NULL);

    if (SGX_SUCCESS != sgx_status) {
        printf("Error, call sgx_create_enclave fail [%s], SGXError:%04x.\n", __FUNCTION__, sgx_status);
        sgx_destroy_enclave(eid);
        return -1;
    }

    printf("Quote Generating ...\n");
    if (generate_quote(eid)) {
        printf("Quote generated successfully!\n");
    }
    else {
        printf("Quote generated failed!\n");
    }
    printf("Quote Verifing ...\n");
    string quote_path = "TempVal";
    if (quoteVerify(quote_path, eid)) {
        printf("Quote Verify successfully!\n");
    }
    else {
        printf("Quote Verify failed!\n");
    }
    return 0;
}
