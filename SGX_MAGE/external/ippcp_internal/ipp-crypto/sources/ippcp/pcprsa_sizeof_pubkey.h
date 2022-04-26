/*******************************************************************************
* Copyright 2013-2021 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/*
//
//  Purpose:
//     Cryptography Primitive.
//     RSA Functions
//
*/

/* compute size of RSA public key context */
static int cpSizeof_RSA_publicKey(int rsaModulusBitSize, int publicExpBitSize)
{
   int pubExpLen = BITS_BNU_CHUNK(publicExpBitSize);
   int modulusLen32 = BITS2WORD32_SIZE(rsaModulusBitSize);
   int montNsize;
   rsaMontExpGetSize(modulusLen32, &montNsize);

   return (Ipp32s)sizeof(IppsRSAPublicKeyState)
        + pubExpLen*(Ipp32s)sizeof(BNU_CHUNK_T)
        + (Ipp32s)sizeof(BNU_CHUNK_T)-1 /* alignment */
        + montNsize;
}
