CFLAGS= -Oz -fno-short-enums -fno-exceptions -march=armv7-a -mthumb -mfpu=vfp -mfloat-abi=softfp -mno-unaligned-access -fno-strict-aliasing -fno-rtti -ffunction-sections -fdata-sections -fno-math-errno
LD_FLAGS= -Wl,-z,noexecstack -Wl,-z,text -Wl,--build-id -Wl,--icf=safe -Wl,--hash-style=sysv -Wl,--gc-sections

all: mcastcmds-nt3.5.c
	clang -o mkasftp  -Oz -fno-short-enums -fno-exceptions -march=armv7-a -mthumb -mfpu=vfp -mfloat-abi=softfp -mno-unaligned-access -fno-strict-aliasing -fno-rtti -ffunction-sections -fdata-sections -fno-math-errno $<