#!/bin/bash

cat << EOF
bits 32
section .data

EOF

for nf in "${@}"; do
    n="${nf#*:}"
    n=${n//./_DOT_}
    n=${n//\//_SLASH_}
    f="${nf%%:*}"
    echo "global _mem_fs_${n}_start"
    echo "global _mem_fs_${n}_end"
    echo "global _mem_fs_${n}_size"
    echo
    echo "_mem_fs_${n}_start: incbin \"$(readlink -f "${f}")\""
    echo "_mem_fs_${n}_end: dd 0"
    echo "_mem_fs_${n}_size: dd _mem_fs_${n}_end-_mem_fs_${n}_start"
    echo
done
