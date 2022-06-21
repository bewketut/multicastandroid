##########clang default Makefile## #change clang to GCC as choice##
#on last line(cc to GCC):armv7a#
##############################
GCC = gcc -Os
cc=clang -Oz
CFLAGS=-ansi -std=c99  -pedantic -Wall -fno-short-enums -fno-exceptions -march=armv7-a -mthumb -mfpu=vfp -mfloat-abi=softfp -mno-unaligned-access -fno-strict-aliasing -fno-rtti -ffunction-sections -fdata-sections -fno-math-errno
LD_FLAGS=-Wl,-z,noexecstack -Wl,-z,text -Wl,--build-id -Wl,--hash-style=sysv -Wl,--gc-sections
all: mcastcmds-nt3.7.c
	${cc} ${CFLAGS} ${LD_FLAGS} -o mkasftp $<
