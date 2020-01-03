/********************************************************************************************
* basic chaining hashtable implementation v1.00                                             *
*                                                                                           *
* Copyright (c) 2019, <anunique at gmail dot com>                                           *
* All rights reserved.                                                                      *
*                                                                                           *
* Redistribution and use in source and binary forms, with or without                        *
* modification, are permitted provided that the following conditions are met:               *
*                                                                                           *
*   * Redistributions of source code must retain the above copyright notice,                *
*     this list of conditions and the following disclaimer.                                 *
*   * Usage in NON-PROFIT software is PERMITTED as long as the source code                  *
*     of the software is OPEN SOURCE. If we meet some day, and you think                    *
*     this stuff is worth it, you can BUY ME A BEER in return.                              *
*   * Usage in PROPRIETARY software is PROHIBITED. CONTACT ME if you want to                *
*     use it anyways and i bet we will come to an agreement.                                *
*                                                                                           *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"               *
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE                 *
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE                *
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE                  *
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR                       *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF                      *
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS                  *
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN                   *
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)                   *
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE                *
* POSSIBILITY OF SUCH DAMAGE.                                                               *
*                                                                                           *
* have fun and w0000h00000 -CW- loves you all                                               *
********************************************************************************************/

#include <stdint.h>

//feel free to change HT_HASHSIZE but always keep it to a multiple of 2!
#define HT_HASHSIZE 0x100000
#define HT_HASHMASK (HT_HASHSIZE - 1)

//error codes
#define HT_ERROR_OK	       0
#define HT_ERROR_EXISTS    1
#define HT_ERROR_NOMEM     2
#define HT_ERROR_NOTFOUND  3

//result codes for ht_get
#define HT_RESULT_ISKEY    2
#define HT_RESULT_GOTVALUE 1
#define HT_RESULT_NOTFOUND 0

//internal stuff, dont touch it
#define HT_GOTVALUE 0x8000000000000000
#define HT_SIZEMASK 0x7fffffffffffffff

//basic data structures, leave these alone
typedef struct ht_node {
	struct ht_node *next;
	void *value;
	uint64_t size;
	unsigned char key;
} ht_node;

typedef struct  {
	ht_node *node[HT_HASHSIZE];
} ht_db;

//check .c file for comments
ht_db *ht_createdb(void);
void ht_deletedb(ht_db **db);
uint64_t ht_insert(ht_db *db, char *new_key, char *new_key_eof, void **value, int update);
uint64_t ht_delete(ht_db *db, char *key, char *key_eof);
uint64_t ht_get(ht_db *db, char *key, char *key_eof, void **value);
