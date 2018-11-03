#!/bin/bash

syms= files=
if [ "${#}" -gt 0 ]; then
    # B, D, R, T but not a, r, or t
    syms=$(nm ${@} \
        | grep "\<[BDRT]\>" \
        | grep -v "sym_table_lookup" \
        | awk '{if(NF==3){print $1":"$3}}')
    files=$(nm ${@} \
        | grep "_mem_fs_.*_start" \
        | awk '{if(NF==3){print $1":"$3}}' \
        | sed 's/:_mem_fs_\(.*\)_start$/:\1/' \
        | sed 's/_DOT_/./g' \
        | sed 's/_SLASH_/\//g')
    fsizes=$(nm ${@} \
        | grep "_mem_fs_.*_size" \
        | awk '{if(NF==3){print $1":"$3}}' \
        | sed 's/:_mem_fs_\(.*\)_size$/:\1/' \
        | sed 's/_DOT_/./g' \
        | sed 's/_SLASH_/\//g')
fi

cat << EOF
#include "sym_table.h"

struct sym_table_t sym_table[] = {
$(for s in $syms; do echo "  {\"${s#*:}\", (void*)0x${s%%:*}},"; done)
$(for s in $files; do echo "  {\"${s#*:}\", (void*)0x${s%%:*}},"; done)
$(for s in $fsizes; do echo "  {\"${s#*:}_size\", (void*)0x${s%%:*}},"; done)
  {NULL,NULL}
};

EOF
