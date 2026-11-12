BASENAME   := ogrebattle64
VERSION    := us
BASEROM    := baserom/baserom.$(VERSION).z64
TARGET     := build/$(BASENAME).$(VERSION).z64
ELF        := build/$(BASENAME).elf
LD_SCRIPT  := $(BASENAME).ld

CROSS      ?= mips-linux-gnu-
AS         := $(CROSS)as
LD         := $(CROSS)ld
OBJCOPY    := $(CROSS)objcopy
PYTHON     ?= python3

# Original toolchain: KMC GCC 2.7.2 (cc1) + KMC-era GNU as 2.6. `make toolchain` fetches both.
KMC_DIR    := tools/gcc-2.7.2
KMC_AS     := tools/binutils-2.6/as
# WSL1 can't exec the 32-bit cc1; fall back to qemu (-B avoids an mmap WSL1 lacks).
RUN32      ?= $(shell $(KMC_DIR)/cc1 --version >/dev/null 2>&1 || echo qemu-i386-static -B 0x100000000)
CC1        := $(RUN32) $(KMC_DIR)/cc1
CPP        := cpp -P -undef -nostdinc
CPPFLAGS   := -I include -I src -D_LANGUAGE_C -D__GNUC__=2 -D_MIPS_SZLONG=32 -D_MIPS_SZINT=32
CFLAGS     := -quiet -O2 -G0 -mips3 -mgp32 -mfp32
KMC_ASFLAGS := -EB -mcpu=vr4300 -mips3 -G0

ASFLAGS    := -EB -march=vr4300 -mtune=vr4300 -mabi=32 -mno-shared -G 0 -no-pad-sections -I include
LDFLAGS    := -T $(LD_SCRIPT) -T undefined_funcs_auto.txt -T undefined_syms_auto.txt -T linker_scripts/hardware_regs.ld \
              -Map build/$(BASENAME).map --no-check-sections

C_FILES    := $(shell find src -name '*.c' 2>/dev/null)
ASM_FILES  := $(shell find asm -name '*.s' -not -path 'asm/nonmatchings/*' 2>/dev/null)
BIN_FILES  := $(shell find assets -name '*.bin' 2>/dev/null)
O_FILES    := $(C_FILES:%.c=build/%.o) $(ASM_FILES:%.s=build/%.o) $(BIN_FILES:%.bin=build/%.o)

GCC_URL    := https://github.com/decompals/mips-gcc-2.7.2/releases/download/v0.1/gcc-2.7.2-linux.tar.gz
BINUTILS_URL := https://github.com/decompals/mips-binutils-2.6/releases/download/v0.3/binutils-2.6-linux.tar.gz

.PHONY: all extract extract-assets toolchain clean distclean check
all: check

extract:
	$(PYTHON) -m splat split $(BASENAME).yaml

# Unpack the asset region (LHA members and LZ chunks) to extracted/ (for inspection; not a build input)
extract-assets:
	$(PYTHON) tools/extract_assets.py $(BASEROM) extracted

toolchain: $(KMC_DIR)/cc1 $(KMC_AS)

$(KMC_DIR)/cc1:
	@mkdir -p $(KMC_DIR)
	curl -sSL $(GCC_URL) | tar -xz -C $(KMC_DIR)

$(KMC_AS):
	@mkdir -p $(dir $@)
	curl -sSL $(BINUTILS_URL) | tar -xz -C $(dir $@) as

# Rebuild when any INCLUDE_ASM'd file changes too.
.SECONDEXPANSION:
build/src/%.o: src/%.c $$(wildcard asm/nonmatchings/$$*/*.s) $(KMC_DIR)/cc1 $(KMC_AS)
	@mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) $< > build/src/$*.i
	$(CC1) $(CFLAGS) -o build/src/$*.s build/src/$*.i
	$(KMC_AS) $(KMC_ASFLAGS) -o $@ build/src/$*.s

build/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

build/%.o: %.bin
	@mkdir -p $(dir $@)
	$(OBJCOPY) -I binary -O elf32-tradbigmips -B mips $< $@

$(ELF): $(O_FILES) $(LD_SCRIPT)
	$(LD) $(LDFLAGS) -o $@

$(TARGET): $(ELF)
	$(OBJCOPY) -O binary --pad-to=0x2800000 --gap-fill=0xFF $< $@

check: $(TARGET)
	@sha1sum $(TARGET) | sed 's#$(TARGET)#$(BASEROM)#' | sha1sum -c - \
	  && echo "OK: $(TARGET) matches baserom" \
	  || (echo "MISMATCH"; exit 1)

clean:
	rm -rf build

distclean: clean
	rm -rf asm assets $(LD_SCRIPT) $(BASENAME).d undefined_*_auto.txt
