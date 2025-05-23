TARGET = patches.elf

CC      ?= clang
LD      ?= ld.lld

CFLAGS   := -target mips -mips2 -mabi=32 -O2 -G0 -mno-abicalls -mno-odd-spreg -mno-check-zero-division \
			-fomit-frame-pointer -ffast-math -fno-unsafe-math-optimizations -fno-builtin-memset \
			-Wall -Wextra -Wno-incompatible-library-redeclaration -Wno-unused-parameter \
			-Wno-unknown-pragmas -Wno-unused-variable -Wno-unused-but-set-variable -Wno-missing-braces \
			-Wno-unsupported-floating-point-opt -Wno-switch -fno-strict-aliasing

CPPFLAGS := -nostdinc -DVERSION_US -DLANG_US -DREFRESH_NTSC -DTARGET_N64 -D_LANGUAGE_C -DMIPS -DLEFTOVERDEBUG \
			-I ../lib/ge/include -I ../lib/ge/include/PR -I ../lib/ge/include/libc -I ../lib/rt64/include
			
LDFLAGS  := -nostdlib -T patches.ld -T syms.ld -Map patches.map --unresolved-symbols=ignore-all --emit-relocs

C_SRCS := $(wildcard *.c)
C_OBJS := $(C_SRCS:.c=.o)
C_DEPS := $(C_SRCS:.c=.d)

$(TARGET): $(C_OBJS) patches.ld syms.ld
	$(LD) $(C_OBJS) $(LDFLAGS) -o $@

$(C_OBJS): %.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -MMD -MF $(@:.o=.d) -c -o $@

clean:
	rm -rf $(C_OBJS) $(TARGET) $(C_DEPS)

-include $(C_DEPS)

.PHONY: clean
