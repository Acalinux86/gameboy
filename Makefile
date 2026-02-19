CC=cc
CFLAGS= -Wall -Wextra -std=c99 -O0 -ggdb -g3 -MMD -Wno-format-truncation
LIBS=-lm

BUILD=build

SRC=src
MMU=src/mmu
CPU=src/cpu
CART=src/mmu/cart
DISASM=src/cpu/disasm

OBJ=obj
OBJ_MMU=obj/mmu
OBJ_CART=obj/mmu/cart
OBJ_CPU=obj/cpu
OBJ_DISASM=obj/cpu/disasm

OBJS=\
	$(OBJ)/gb.o \
	$(OBJ_MMU)/mmu.o \
	$(OBJ_CPU)/cpu.o \
	$(OBJ_CART)/cart.o \
	$(OBJ_DISASM)/disasm.o \

.PHONY: all clean

TARGET=$(BUILD)/gb

all: $(TARGET)

$(OBJ) $(OBJ_MMU) $(OBJ_CPU) $(OBJ_CART) $(OBJ_DISASM) $(BUILD):
	@mkdir -p $@

$(OBJ)/gb.o: $(SRC)/gb.c | $(OBJ)
	$(CC) $(CFLAGS) -I$(MMU) -I$(CPU) -c $< -o $@

$(OBJ_MMU)/mmu.o: $(MMU)/mmu.c | $(OBJ_MMU)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_CPU)/cpu.o: $(CPU)/sm83_cpu.c | $(OBJ_CPU)
	$(CC) $(CFLAGS) -I$(MMU) -c $< -o $@

$(OBJ_DISASM)/disasm.o: $(DISASM)/disasm.c | $(OBJ_DISASM)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_CART)/cart.o: $(CART)/cart.c | $(OBJ_CART)
	$(CC) $(CFLAGS) -I$(MMU) -c $< -o $@

$(TARGET): $(OBJS) | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

debug: build/gb | $(BUILD)
	gf2 $<

clean:
	rm -rf $(OBJ) $(BUILD) data/disasm/tetris.gbasm
