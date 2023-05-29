##########clang default Makefile## #change clang to GCC as choice##
#on last line(cc to GCC):armv7a
##################################
#use mkasftp6 along m4power6 using #*two* different android mobiles or #computer with terminals.
##############################
GCC = gcc -Os
cc=clang -Oz
CFLAGS=-ansi -std=c99  -pedantic -Wall -fno-short-enums -fno-exceptions -march=armv7-a -mthumb -mfpu=vfp -mfloat-abi=softfp -mno-unaligned-access -fno-strict-aliasing -fno-rtti -ffunction-sections -fdata-sections -fno-math-errno
LD_FLAGS=-Wl,-z,noexecstack -Wl,-z,text -Wl,--build-id -Wl,--hash-style=sysv -Wl,--gc-sections
all: mkastkmds-nt3.7ipv6.c mkastkmds-nt3.7.c mcastcmds-nt3.7ipv6.c mcastcmds-nt3.7.c
	${cc} ${CFLAGS} ${LD_FLAGS} -o mkasftcp6 mkastkmds-nt3.7ipv6.c
	${cc} ${CFLAGS} ${LD_FLAGS} -o mkasftcp mkastkmds-nt3.7.c
	${cc} ${CFLAGS} ${LD_FLAGS} -o mkasfudp6 mcastcmds-nt3.7ipv6.c
	${cc} ${CFLAGS} ${LD_FLAGS} -o mkasfudp mcastcmds-nt3.7.c
	mkdir -p ~/bin && cp mkas* ~/bin/ && chmod a+x ~/bin/mkas* && mkdir -p /sdcard/m4power6 && mkdir -p /sdcard/m4power6/mkasftp &&  printf "alias m4='~/bin/mkasftcp'; alias m6='~/bin/mkasftcp6'; alias ..='cd ..'; alias mkf='~/bin/mkasfudp'; alias mkf6='~/bin/mkasfudp6';cd /sdcard/m4power6/mkasftp;\n" >> ~/.shrc && cp ~/.bashrc ~/.bashrc~ && cp ~/.shrc ~/.bashrc && printf "Now ready to use mkasftcp6 and mkasfudp6 android app using *two* different android mobiles or computer with terminals. old ~/.bashrc is ~/.bashrc~. run alias\n";

