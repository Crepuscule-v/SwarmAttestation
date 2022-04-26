/*
 * Copyright (C) 2011-2021 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 * File: qcnl_config.cpp 
 *  
 * Description: Read configuration data
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <curl/curl.h>
#include <algorithm>
#include "qcnl_config.h"

using namespace std;

static struct init_solib { 
    init_solib() { 
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }
} _init_solib;

QcnlConfig::QcnlConfig():_server_url("https://localhost:8081/sgx/certification/v3/"),
        _use_secure_cert(true),
        _collateral_service_url(_server_url),
        _collateral_version("3.0"),
        _retry_times(0),
        _retry_delay(0)
{
    // read configuration File
    bool use_collateral_service = false;
    ifstream ifs("/etc/sgx_default_qcnl.conf");
    if (ifs.is_open())
    {
        string line;
        auto f = [](unsigned char const c) { return std::isspace(c); }; 
        while(getline(ifs, line)){
            line.erase(std::remove_if(line.begin(), line.end(), f), line.end());
            if(line[0] == '#' || line.empty())
                continue;
            size_t pos = line.find("=");
            string name = line.substr(0, pos);
            string value = line.substr(pos + 1);
            if (name.compare("PCCS_URL") == 0) {
                _server_url = value;
            }
            else if (name.compare("USE_SECURE_CERT") == 0 && 
                    (value.compare("FALSE") == 0 || value.compare("false") == 0)){
                _use_secure_cert = false;
            }
            else if (name.compare("COLLATERAL_SERVICE") == 0) {
                use_collateral_service = true;
                _collateral_service_url = value;
            }
            else if (name.compare("PCCS_API_VERSION") == 0) {
                _collateral_version = value;
            }
            else if (name.compare("RETRY_TIMES") == 0) {
                try {
                    string::size_type sz;
                    _retry_times = stoi(value, &sz);
                }
                catch (const invalid_argument& e) {
                    continue;
                }
            }
            else if (name.compare("RETRY_DELAY") == 0) {
                try {
                    string::size_type sz;
                    _retry_delay = stoi(value, &sz);
                }
                catch (const invalid_argument& e) {
                    continue;
                }
            }
            else {
                continue;
            }
        }
        ifs.close();
    }
    if (!use_collateral_service) {
        _collateral_service_url = _server_url;
    }
}
