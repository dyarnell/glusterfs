/*
  Copyright (c) 2006-2011 Gluster, Inc. <http://www.gluster.com>
  This file is part of GlusterFS.

  GlusterFS is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published
  by the Free Software Foundation; either version 3 of the License,
  or (at your option) any later version.

  GlusterFS is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see
  <http://www.gnu.org/licenses/>.
*/

#ifndef __CLEAR_H__
#define __CLEAR_H__

#ifndef _CONFIG_H
#define _CONFIG_H
#include "config.h"
#endif

#include "compat-errno.h"
#include "stack.h"
#include "call-stub.h"
#include "locks.h"

typedef enum {
        CLRLK_INODE,
        CLRLK_ENTRY,
        CLRLK_POSIX,
        CLRLK_TYPE_MAX
} clrlk_type;

typedef enum {
        CLRLK_BLOCKED = 1,
        CLRLK_GRANTED,
        CLRLK_ALL,
        CLRLK_KIND_MAX
} clrlk_kind;

typedef enum {
        KW_TYPE,
        KW_KIND,
        /*add new keywords here*/
        KW_MAX
} clrlk_opts;

struct _clrlk_args;
typedef struct _clrlk_args clrlk_args;

struct _clrlk_args {
        int type;
        int kind;
        char *opts;
};

int
clrlk_get__kind (char *kind);
int
clrlk_get_type (char *type);
int
clrlk_get_lock_range (char *range_str, struct gf_flock *ulock,
                      gf_boolean_t *chk_range);
int
clrlk_parse_args (const char* cmd, clrlk_args *args);

int
clrlk_clear_posixlk (xlator_t *this, pl_inode_t *pl_inode, clrlk_args *args,
                     int *blkd, int *granted, int *op_errno);
int
clrlk_clear_inodelk (xlator_t *this, pl_inode_t *pl_inode, pl_dom_list_t *dom,
                     clrlk_args *args, int *blkd, int *granted, int *op_errno);
int
clrlk_clear_entrylk (xlator_t *this, pl_inode_t *pl_inode, pl_dom_list_t *dom,
                     clrlk_args *args, int *blkd, int *granted, int *op_errno);
int
clrlk_clear_lks_in_all_domains (xlator_t *this, pl_inode_t *pl_inode,
                                clrlk_args *args, int *blkd, int *granted,
                                int *op_errno);
#endif /* __CLEAR_H__ */
