ifeq ($(OS),Windows_NT)
    MY_OS := Windows
else
    MY_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(MY_OS),Windows)
	DEL_COMMAND := del
	DLL_EXTENSION := .dll
	EXE_EXTENSION := .exe
	SLASH := \\
else
	DEL_COMMAND := rm -rf
	DLL_EXTENSION := .so
	EXE_EXTENSION := 
	SLASH := /
endif

CC := gcc
CFLAGS := -pedantic-errors -Wall -Wextra -fmessage-length=0 -I.

DEBUG_PARAMS := -O0 -g3 -fPIC $(CFLAGS)
RELEASE_PARAMS := -O3 -fPIC $(CFLAGS)

SRC_DIR := src

DEBUG_DIR := Debug
DEBUG_SRC_DIR := $(DEBUG_DIR)/$(SRC_DIR)

RELEASE_DIR := Release
RELEASE_SRC_DIR := $(RELEASE_DIR)/$(SRC_DIR)

OBJ_DLL := cec20_test_func.o entry_point.o
OBJ_EXE := cec20_test_func.o main.o

DEBUG_DLL_OBJS := $(patsubst %,$(DEBUG_SRC_DIR)/%,$(OBJ_DLL))
DEBUG_EXE_OBJS := $(patsubst %,$(DEBUG_SRC_DIR)/%,$(OBJ_EXE))
RELEASE_DLL_OBJS := $(patsubst %,$(RELEASE_SRC_DIR)/%,$(OBJ_DLL))
RELEASE_EXE_OBJS := $(patsubst %,$(RELEASE_SRC_DIR)/%,$(OBJ_EXE))


.PHONY: all clean

all: $(DEBUG_DIR)/benchmark$(EXE_EXTENSION) $(DEBUG_DIR)/libbenchmark$(DLL_EXTENSION) $(RELEASE_DIR)/benchmark$(EXE_EXTENSION) $(RELEASE_DIR)/libbenchmark$(DLL_EXTENSION)

$(DEBUG_DIR)/benchmark$(EXE_EXTENSION): $(DEBUG_EXE_OBJS)
	$(CC) $? -o $@ -lm

$(DEBUG_DIR)/libbenchmark$(DLL_EXTENSION): $(DEBUG_DLL_OBJS)
	$(CC) -fPIC $? -shared -o $@

$(DEBUG_SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(DEBUG_PARAMS) -c $< -o $@

$(RELEASE_DIR)/benchmark$(EXE_EXTENSION): $(RELEASE_EXE_OBJS)
	$(CC) $? -o $@ -lm

$(RELEASE_DIR)/libbenchmark$(DLL_EXTENSION): $(RELEASE_DLL_OBJS)
	$(CC) -fPIC $? -shared -o $@

$(RELEASE_SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(RELEASE_PARAMS) -c $< -o $@

clean:
	$(DEL_COMMAND) .$(SLASH)Debug$(SLASH)benchmark$(EXE_EXTENSION)
	$(DEL_COMMAND) .$(SLASH)Debug$(SLASH)libbenchmark$(DLL_EXTENSION)
	$(DEL_COMMAND) .$(SLASH)Debug$(SLASH)src$(SLASH)*.o
	$(DEL_COMMAND) .$(SLASH)Release$(SLASH)benchmark$(EXE_EXTENSION)
	$(DEL_COMMAND) .$(SLASH)Release$(SLASH)libbenchmark$(DLL_EXTENSION)
	$(DEL_COMMAND) .$(SLASH)Release$(SLASH)src$(SLASH)*.o
