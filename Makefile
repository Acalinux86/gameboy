CC=gcc
CFLAGS= -Wall -Wextra -Wswitch-enum -std=c99 -ggdb -MMD -Wno-format-truncation
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

.PHONY: all clean

TARGET=$(BUILD)/gb

all: $(TARGET)

$(OBJ) $(OBJ_MMU) $(OBJ_LOG) $(OBJ_CPU) $(BUILD):
	@mkdir -p $@

$(OBJ)/gb.o: $(SRC)/gb.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_MMU)/mmu.o: $(MMU)/mmu.c | $(OBJ_MMU)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_LOG)/log.o: $(LOG)/log.c | $(OBJ_LOG)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_CPU)/cpu.o: $(CPU)/cpu.c | $(OBJ_CPU)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS) | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

debug: build/gb | $(BUILD)
	gf2 $<

clean:
	rm -rf $(OBJ) $(BUILD) gameboy.log
