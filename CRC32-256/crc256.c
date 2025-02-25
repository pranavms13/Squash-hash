// Copyright (c) 2019, The CCLib Developers
//
// Please see the included LICENSE file for more information.

#include <stdint.h>
// Comment these to improve performance but remove the feature associated with it
//#define MIXING     // Mix CRC32s, when enabled, every bit of the output is dependent on every bit of the input
//#define PROCESS16  // Process 16 byte blocks in addition to 32 byte blocks
//#define PROCESS8   // Process 8  byte blocks in addition to 32 byte blocks
//#define PROCESS4   // Process 4  byte blocks in addition to 32 byte blocks
	           // to process 4 byte, 8 byte, 16 byte and 32 byte blocks, all have to be enabled.



uint32_t crc32c_table[256] = {
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
	0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
	0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
	0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
	0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
	0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
	0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
	0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
	0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
	0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
	0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
	0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
	0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
	0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
	0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
	0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
	0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
	0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
	0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
	0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
	0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
	0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
	0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
	0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
	0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,
	0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
	0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
	0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
	0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
	0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
	0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
	0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
	0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
	0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
	0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
	0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
	0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
	0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
	0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

uint32_t crc32r(uint32_t msg) { //CRC32-return
	uint32_t crc = 0xFFFFFFFF;
#if defined(__aarch64__) && defined(__ARM_FEATURE_CRC32)
	__asm__("crc32w %w0,%w0,%w1\n":"+r"(crc):"r"(msg));
#else
	crc=crc32c_table[msg&0xff]^(msg>>8);
	crc=crc32c_table[crc&0xff]^(crc>>8);
	crc=crc32c_table[crc&0xff]^(crc>>8);
	crc=crc32c_table[crc&0xff]^(crc>>8);
#endif
	return crc^0xFFFFFFFF;
}

void crc32p(uint32_t* in, uint32_t* out) { // CRC32-Pointer
#if defined(__aarch64__) && defined(__ARM_FEATURE_CRC32)
	__asm__("crc32w %w0,%w0,%w1\n":"+r"(*out):"r"(*in));
#else
	*out=crc32c_table[(*in )&0xff]^((*in )>>8);
	*out=crc32c_table[(*out)&0xff]^((*out)>>8);
	*out=crc32c_table[(*out)&0xff]^((*out)>>8);
	*out=crc32c_table[(*out)&0xff]^((*out)>>8);
#endif
}

void crc32i(uint32_t* out) { // CRC32-Inplace
#if defined(__aarch64__) && defined(__ARM_FEATURE_CRC32)
	__asm__("crc32w %w0,%w0,%w1\n":"+r"(*out):"r"(*in));
#else
	*out=crc32c_table[(*out)&0xff]^((*out)>>8);
	*out=crc32c_table[(*out)&0xff]^((*out)>>8);
	*out=crc32c_table[(*out)&0xff]^((*out)>>8);
	*out=crc32c_table[(*out)&0xff]^((*out)>>8);
#endif
}

void crc256(uint8_t* in, uint32_t len, uint8_t* out){
	uint8_t   temp[32] = {0};
	uint32_t* in_32    = (uint32_t*)in;
	uint32_t  i        = 0;

	uint64_t* tmp_64_0 = (uint64_t*)temp;
	uint64_t* tmp_64_1 = (uint64_t*)&temp[8];
	uint64_t* tmp_64_2 = (uint64_t*)&temp[16];
	uint64_t* tmp_64_3 = (uint64_t*)&temp[24];

	uint32_t* tmp_32_0 = (uint32_t*)temp;
	uint32_t* tmp_32_1 = (uint32_t*)&temp[8];
	uint32_t* tmp_32_2 = (uint32_t*)&temp[16];
	uint32_t* tmp_32_3 = (uint32_t*)&temp[24];
	uint32_t* tmp_32_4 = (uint32_t*)temp;
	uint32_t* tmp_32_5 = (uint32_t*)&temp[8];
	uint32_t* tmp_32_6 = (uint32_t*)&temp[16];
	uint32_t* tmp_32_7 = (uint32_t*)&temp[24];
	#ifdef MIXING
	uint32_t* out_32_0 = (uint32_t*)&out[ 2];
	uint32_t* out_32_1 = (uint32_t*)&out[ 6];
	uint32_t* out_32_2 = (uint32_t*)&out[10];
	uint32_t* out_32_3 = (uint32_t*)&out[14];
	uint32_t* out_32_4 = (uint32_t*)&out[18];
	uint32_t* out_32_5 = (uint32_t*)&out[22];
	uint32_t* out_32_6 = (uint32_t*)&out[26];
	#endif
	uint64_t* out_64_0 = (uint64_t*)&out;
	uint64_t* out_64_1 = (uint64_t*)&out[8];
	uint64_t* out_64_2 = (uint64_t*)&out[16];
	uint64_t* out_64_3 = (uint64_t*)&out[24];

	len>>=2;

	for(;i<len;i+=8){
		crc32p(&in_32[i  ],tmp_32_0);
		crc32p(&in_32[i+1],tmp_32_1);
		crc32p(&in_32[i+2],tmp_32_2);
		crc32p(&in_32[i+3],tmp_32_3);
		crc32p(&in_32[i+4],tmp_32_4);
		crc32p(&in_32[i+5],tmp_32_5);
		crc32p(&in_32[i+6],tmp_32_6);
		crc32p(&in_32[i+7],tmp_32_7);
		*out_64_0 ^= *tmp_64_0; *out_64_1 ^= *tmp_64_1;
		*out_64_2 ^= *tmp_64_2; *out_64_3 ^= *tmp_64_3;
		#ifdef MIXING
		crc32i(out_32_0);
		crc32i(out_32_1);
		crc32i(out_32_2);
		crc32i(out_32_3);
		crc32i(out_32_4);
		crc32i(out_32_5);
		crc32i(out_32_6);
		#endif
	}
	#ifdef PROCESS16
	if(len&4){
		crc32p(&in_32[i  ],tmp_32_0);
		crc32p(&in_32[i+1],tmp_32_1);
		crc32p(&in_32[i+2],tmp_32_2);
		crc32p(&in_32[i+3],tmp_32_3);
		*out_64_0 ^= *tmp_64_0; *out_64_1 ^= *tmp_64_1;
		# ifdef MIXING
		crc32i(out_32_0);
		crc32i(out_32_1);
		crc32i(out_32_2);
		# endif
		i+=4;
	}
	#endif
	#ifdef PROCESS8
	if(len&2){
		crc32p(&in_32[i  ],tmp_32_0);
		crc32p(&in_32[i+1],tmp_32_1);
		*out_64_0 ^= *tmp_64_0;
		# ifdef MIXING
		crc32i(out_32_0);
		# endif
		i+=2;
	}
	#endif
	#ifdef PROCESS4
	if(len&1){
		crc32p(&in_32[i  ],tmp_32_0);
		*out_64_0 ^= *tmp_64_0;
	}
	#endif
}

#define TEST_CRC256
#ifdef TEST_CRC256

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZE_64     536870912  // 1<<29 * 8 byte
#define SIZE_256    SIZE_64>>2 // 1<<27
#define SIZE_32_32  SIZE_64>>4 // 1<<25
#define LOG_S_32_32 25         // Log2(SIZE_32_32)
#define ITERATIONS  8192       // 1<<13, approximately 10 minutes on E2-1225v2
#define CPS         3.2        // Cycles per second, default: 3.2GHz

int main(){
	uint32_t* cache    = (uint32_t*)calloc(SIZE_64,8);
	uint8_t*  cache_8  = (uint8_t*)cache;
	uint64_t* cache_64 = (uint64_t*)cache;
	uint32_t  stime    = 0;
	uint32_t  etime    = 0;
	double    rate     = 0;
	uint64_t* out_64   = (uint64_t*)cache;

	cache_64[0] = 0x8ccc5467f6bd9249; cache_64[1] = 0xddaadef338d9fdc7;
	cache_64[2] = 0x39720ddd40fd8a32; cache_64[3] = 0x8473643dec63477e;
	for(uint32_t x=0;x<32;x++)
		for(uint32_t i=32;i<SIZE_32_32;i++) cache[i+(x<<LOG_S_32_32)] = (cache[i-32+(x<<LOG_S_32_32)]<<x)^i^crc32r(cache[i-32+(x<<LOG_S_32_32)]);

	stime = (uint32_t)time(NULL);
	for(uint32_t j=0;j<ITERATIONS;j++) crc256(cache_8, SIZE_256, cache_8);
	etime = (uint32_t)time(NULL);
	etime = etime-stime;
	rate  = (double)ITERATIONS/etime;
	rate  = rate*SIZE_64*8/1000000000; // GB/s
	printf("CRC256 calculation took %us\n",etime);
	printf("Processing %fGB/s\n",rate);
	printf("\tHash uses %f cycles per byte\n",(double)CPS/rate);
	printf("\tHash processes %f bytes per cycle\n",(double)rate/CPS);
	printf("CRC256 Result: %016jx.%016jx.%016jx.%016jx\n",out_64[0],out_64[1],out_64[2],out_64[3]);
}

#endif
