#!/bin/sh

output_file="config.ninja"

cflag_lib=`pkg-config --cflags json-c 2>/dev/null`
linkflag_lib=`pkg-config --libs json-c 2>/dev/null || echo '-ljson-c'`

cflag_lib_test=`pkg-config --cflags check 2>/dev/null`
linkflag_lib_test=`pkg-config --libs check 2>/dev/null || echo '-lcheck'`

# Use clang if found
which clang >/dev/null 2>&1
if [ $? -eq 0 ]; then
	compiler='clang'
else
	compiler='gcc'
fi

echo "compiler = $compiler" > $output_file
echo "cflags_user = $CFLAGS" >> $output_file
echo "linkflags_user = $LDFLAGS" >> $output_file
echo "cflags_lib_test = $cflag_lib_test" >> $output_file
echo "linkflags_lib_test = $linkflag_lib_test" >> $output_file
echo "cflags_lib = $cflag_lib" >> $output_file
echo "linkflags_lib = $linkflag_lib" >> $output_file
