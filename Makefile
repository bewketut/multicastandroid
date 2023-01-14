##########clang default Makefile## #change clang to GCC as choice##
#on last line(cc to GCC):armv7a
##################################
#use mkasftp6 along m4power6 using #*two* different android mobiles or #computer with terminals.
##############################
GCC = gcc -Os
cc=clang -Oz
CFLAGS=-ansi -std=c99  -pedantic -Wall -fno-short-enums -fno-exceptions -march=armv7-a -mthumb -mfpu=vfp -mfloat-abi=softfp -mno-unaligned-access -fno-strict-aliasing -fno-rtti -ffunction-sections -fdata-sections -fno-math-errno
LD_FLAGS=-Wl,-z,noexecstack -Wl,-z,text -Wl,--build-id -Wl,--hash-style=sysv -Wl,--gc-sections
all: mcastcmds-nt3.7ipv6.c mcastcmds-nt3.7.c
	${cc} ${CFLAGS} ${LD_FLAGS} -o mkasftp6 mcastcmds-nt3.7ipv6.c
	${cc} ${CFLAGS} ${LD_FLAGS} -o mkasftp mcastcmds-nt3.7.c
	mkdir -p ~/bin && cp mkasftp* ~/bin/ && chmod a+x ~/bin/mkas* && printf "alias mkasftp='~/bin/mkasftp'; alias mkasftp6='~/bin/mkasftp6'\n" >> ~/.bashrc && cp ~/.bashrc ~/.shrc && printf "Now ready to use mkasftp6 and mkasftp6 android app using *two* different android mobiles or computer with terminals.\n"
