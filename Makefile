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

ASFLAGS    := -EB -march=vr4300 -mtune=vr4300 -mabi=32 -mno-shared -G 0 -I include
LDFLAGS    := -T $(LD_SCRIPT) -T undefined_funcs_auto.txt -T undefined_syms_auto.txt -T linker_scripts/hardware_regs.ld \
              -Map build/$(BASENAME).map --no-check-sections

ASM_FILES  := $(shell find asm -name '*.s' 2>/dev/null)
BIN_FILES  := $(shell find assets -name '*.bin' 2>/dev/null)
O_FILES    := $(ASM_FILES:%.s=build/%.o) $(BIN_FILES:%.bin=build/%.o)

.PHONY: all extract clean distclean check
all: check

extract:
	$(PYTHON) -m splat split $(BASENAME).yaml

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
