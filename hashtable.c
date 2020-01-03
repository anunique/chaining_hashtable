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
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#include "crc32.h"

/*
ht_find
	internal function to find a key inside of the hashtable
*/
inline ht_node *ht_find(ht_db *db, char *key, char *key_eof, ht_node ***parent)
{
	uint64_t size = key_eof - key;
	uint64_t hash = weedit_crc32(0xffffffff, (uint8_t*)key, size) ^ 0xffffffff;
	ht_node *node = db->node[hash & HT_HASHMASK];
	*parent = &db->node[hash & HT_HASHMASK];
	if (!node)
	{
		return 0;
	}
	while (node)
	{
		if (size == (node->size & HT_SIZEMASK))
		{
			if (0 == memcmp(&node->key, key, size))
			{
				return node;
			}
		}
		*parent = &node->next;
		node = node->next;
	}
	return 0;
}

/*
ht_createdb
	Creates an empty database object.

RETURN VALUE:
	FAILURE: 0
	SUCCESS: pointer to a database object
*/
ht_db *ht_createdb(void)
{
	return calloc(1, sizeof(ht_db));
}

/*
ht_deletedb
	Deletes a db and frees the whole memory used by all nodes.

PARAMETERS:
	pointer to a pointer to a database object
*/
void ht_deletedb(ht_db **thisdb)
{
	ht_db *db = *thisdb;
	for (int i = 0; i < HT_HASHSIZE; i++)
	{
		ht_node *node = db->node[i];
		while (node) {
			ht_node *this = node;
			node = this->next;
			free(this);
		}
	}
	free(db);
	*thisdb = 0;
}

/*
ht_insert
	insert a key incl value to the hashtable

PARAMETERS:
	db:			pointer to a database object
	key:		start pointer of the key
	key_eof:	end pointer of the key + 1
	value:		pointer to the value to add. if value is 0 the node is only marked as "KEY" and no data is stored inside of it
	update:		updates the value if the exists if set to 1

RETURN VALUES :
	HT_ERROR_EXISTS		: key exists
	HT_ERROR_OK			: key successfully deleted
	HT_ERROR_NOMEM		: ran out of memory, cannot insert the key
*/
uint64_t ht_insert(ht_db *db, char *key, char *key_eof, void **value, int update)
{
	ht_node **parent;
	ht_node *node = ht_find(db, key, key_eof, &parent);
	uint64_t size = key_eof - key;
	if (node)
	{
		if (value)
		{
			if ((node->size & HT_GOTVALUE) && (!update))
			{
				return HT_ERROR_EXISTS;
			}
			node->value = *value;
			node->size |= HT_GOTVALUE;

		}
		return HT_ERROR_OK;
	}
	node = calloc(1, sizeof(ht_node) + size);
	if (!node)
		return HT_ERROR_NOMEM;
	if (value)
	{
		node->size = size | HT_GOTVALUE;
		node->value = *value;
	}
	else
		node->size = size;
	memcpy(&node->key, key, size);
	*parent = node;
	return HT_ERROR_OK;
}

/*
ht_delete
	delete a key from the hashtable and free its memory

PARAMETERS:
	db:			pointer to a database object
	key:		start pointer of the key
	key_eof:	end pointer of the key + 1

RETURN VALUES :
	HT_ERROR_NOTFOUND	: key doesnt exist
	HT_ERROR_OK			: key successfully deleted
*/
uint64_t ht_delete(ht_db *db, char *key, char *key_eof)
{
	ht_node **parent;
	ht_node *node = ht_find(db, key, key_eof, &parent);
	if (!node)
		return HT_ERROR_NOTFOUND;
	*parent = node->next;
	free(node);
	return HT_ERROR_OK;
}

/*
ht_get
	query the database for a key and its value

PARAMETERS:
	db:			pointer to a database object
	key:		start pointer of the key
	key_eof:	end pointer of the key + 1
	value:		pointer for a return value

RETURN VALUES:
	HT_RESULT_NOTFOUND	: key doesnt exist
	HT_RESULT_GOTVALUE	: key exists and value is set to the key value
	HT_RESULT_ISKEY		: key exists but no value
*/
uint64_t ht_get(ht_db *db, char *key, char *key_eof, void **value)
{
	ht_node **parent;
	ht_node *node = ht_find(db, key, key_eof, &parent);
	if (!node)
		return HT_RESULT_NOTFOUND;
	if (node->size & HT_GOTVALUE)
	{
		*value = node->value;
		return HT_RESULT_GOTVALUE;
	}
	return HT_RESULT_ISKEY;
}
