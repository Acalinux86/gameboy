CC=gcc
CFLAGS= -Wall -Wextra -std=c99 -ggdb -MMD -Wno-format-truncation
LIBS=-lm

BUILD=build

SRC=src
MMU=src/mmu
LOG=src/log
CPU=src/cpu

OBJ=obj
OBJ_MMU=obj/mmu
OBJ_LOG=obj/log
OBJ_CPU=obj/cpu

OBJS=\
	$(OBJ)/gb.o \
	$(OBJ_MMU)/mmu.o \
	$(OBJ_LOG)/log.o \
	$(OBJ_CPU)/cpu.o \

LUTS=$(CPU)/opcode_tables.c
OXM=$(CPU)/opcodes.h

.PHONY: all clean

TARGET=$(BUILD)/gb

all: $(TARGET)

$(OBJ) $(OBJ_MMU) $(OBJ_LOG) $(OBJ_CPU) $(BUILD):
	@mkdir -p $@

# Rule to generate the opcode files
$(LUTS) $(OXM): $(CPU)/codegen.py $(CPU)/Opcodes.json | $(OBJ_CPU)
	@echo "Generating opcode tables..."
	python3 src/cpu/codegen.py

$(OBJ)/gb.o: $(SRC)/gb.c $(OXM) | $(OBJ)
	$(CC) $(CFLAGS) -I$(LOG) -I$(MMU) -I$(CPU) -c $< -o $@

$(OBJ_MMU)/mmu.o: $(MMU)/mmu.c | $(OBJ_MMU)
	$(CC) $(CFLAGS) -I$(LOG) -c $< -o $@

$(OBJ_LOG)/log.o: $(LOG)/log.c | $(OBJ_LOG)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_CPU)/cpu.o: $(CPU)/cpu.c $(LUTS) $(OXM) | $(OBJ_CPU)
	$(CC) $(CFLAGS) -I$(LOG) -c $< -o $@

$(TARGET): $(OBJS) | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

debug: build/gb | $(BUILD)
	gf2 $<

clean:
	rm -rf $(OBJ) $(BUILD) gameboy.log $(LUTS) $(OXM)
