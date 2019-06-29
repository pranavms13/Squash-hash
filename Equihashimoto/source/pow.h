// Copyright (c) 2019, The CCLib Developers
//
// Please see the included LICENSE file for more information.


#ifndef POW_H
#define POW_H

void crc32p(uint32_t* in, uint32_t* out);
void crc32i(uint32_t* in);
void calcDatasetItem(uint8_t* seed, uint32_t itemNumber, uint64_t* out);
void calcDataset(uint8_t* cache, uint64_t* out);
void squash_pow_full(uint8_t* header, uint64_t nonce, uint64_t* dataset, uint8_t* result);
void squash_pow_light(uint8_t* header, uint64_t nonce, uint8_t* cache, uint8_t* result);
void get_seedhash(uint64_t block_number, uint8_t* seed);

#endif
