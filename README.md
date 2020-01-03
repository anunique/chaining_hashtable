# chaining_hashtable
a chaining hashtable i wrote for testing purposes

### Usage:
```
ht_db *db = ht_createdb();
if (!db)
  return 0;
char *key = "test";
char *key_eof = key + strlen(key);
void *value = 1;
ht_insert(db, key, key_eof, &value, 0);
ht_get(db, key, key_eof, &value);
ht_deletedb(&db);
```

### Creates an empty database object.
```
ht_db *ht_createdb(void);

RETURN VALUE:
	FAILURE: 0
	SUCCESS: pointer to a database object
```
### Deletes a db and frees the whole memory used by all nodes.
```
void ht_deletedb(ht_db **thisdb);

PARAMETERS:
	pointer to a pointer to a database object
```
### insert a key incl value to the hashtable
```
uint64_t ht_insert(ht_db *db, char *key, char *key_eof, void **value, int update);


PARAMETERS:
	db:		pointer to a database object
	key:		start pointer of the key
	key_eof:	end pointer of the key + 1
	value:		pointer to the value to add. if value is 0 the node is only marked as "KEY" and no data is stored inside of it
	update:		updates the value if the exists if set to 1

RETURN VALUES :
	HT_ERROR_EXISTS		: key exists
	HT_ERROR_OK		: key successfully deleted
	HT_ERROR_NOMEM		: ran out of memory, cannot insert the key
```
### delete a key from the hashtable and free its memory
```	
uint64_t ht_delete(ht_db *db, char *key, char *key_eof);

PARAMETERS:
	db:		pointer to a database object
	key:		start pointer of the key
	key_eof:	end pointer of the key + 1

RETURN VALUES :
	HT_ERROR_NOTFOUND	: key doesnt exist
	HT_ERROR_OK		: key successfully deleted
```
### query the database for a key and its value
```	
uint64_t ht_get(ht_db *db, char *key, char *key_eof, void **value);
  query the database for a key and its value

PARAMETERS:
	db:		pointer to a database object
	key:		start pointer of the key
	key_eof:	end pointer of the key + 1
	value:		pointer for a return value

RETURN VALUES:
	HT_RESULT_NOTFOUND	: key doesnt exist
	HT_RESULT_GOTVALUE	: key exists and value is set to the key value
	HT_RESULT_ISKEY		: key exists but no value
```

### license
```
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
```
