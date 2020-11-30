/*
 * FreeSWITCH Modular Media Switching Software Library / Soft-Switch Application
 * Copyright (C) 2005-2014, Anthony Minessale II <anthm@freeswitch.org>
 *
 * Version: MPL 1.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is FreeSWITCH Modular Media Switching Software Library / Soft-Switch Application
 *
 * The Initial Developer of the Original Code is
 * Anthony Minessale II <anthm@freeswitch.org>
 * Portions created by the Initial Developer are Copyright (C)
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Anthony Minessale II <anthm@freeswitch.org>
 * Richard Screene <richard.screene@thisisdrum.com>
 *
 *
 * globals.h -- Global headers for janus endpoint module
 *
 */
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include  "switch.h"

typedef enum id_type { UNKNOWN, INT, STR } id_type_t;
typedef struct {
	id_type_t type;
	union {
		uint64_t num;
		char     str[128];
	} u;
} janus_id_t;

#define JANUS_ID_INIT {.type = UNKNOWN, .u = 0}

static int equal_id(const janus_id_t *id1, const janus_id_t *id2)
{
	int rc = 0;

	do {
		if (!id1 || !id2)
			break;

		if (id1->type != id2->type)
			break;

		if (INT == id1->type)
		{
			if (id1->u.num == id2->u.num)
				rc++;

			break;
		}
		else if (STR == id1->type)
		{
			if (strlen(id1->u.str) == strlen(id2->u.str))
			{
				if (!strcmp(id1->u.str,id2->u.str))
					rc++;
			}

			break;
		}

	} while(0);

	return rc;
}

#include  "hash.h"

typedef struct {
  switch_memory_pool_t *pModulePool;
  int debug;
  hash_t serverIdLookup;
  switch_time_t started;
  switch_hash_t *pServerNameLookup;

  switch_mutex_t *mutex;
  unsigned int totalCalls;
  unsigned int callsInProgress;
  char guess_ip[80];
  switch_bool_t auto_nat;
} globals_t;

// define as a macro so we can eliminate one nested function
#define DEBUG(details, ...) do { \
	if (globals.debug) { \
		switch_log_printf(details, SWITCH_LOG_INFO, __VA_ARGS__); \
	} else { \
		switch_log_printf(details, SWITCH_LOG_DEBUG, __VA_ARGS__); \
	} \
} while (0)

extern globals_t globals;

#endif //_GLOBALS_H_
/* For Emacs:
 * Local Variables:
 * mode:c
 * indent-tabs-mode:t
 * tab-width:4
 * c-basic-offset:4
 * End:
 * For VIM:
 * vim:set softtabstop=4 shiftwidth=4 tabstop=4 noet:
 */
