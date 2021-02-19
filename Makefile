CC = gcc
CFLAGS = -pedantic-errors -Wall -Wextra -fmessage-length=0 -I.

DEBUG_PARAMS = -O0 -g3 -fPIC $(CFLAGS)
RELEASE_PARAMS = -O3 $(CFLAGS)

SRC_DIR = src

DEBUG_DIR = Debug
DEBUG_SRC_DIR = $(DEBUG_DIR)/$(SRC_DIR)

RELEASE_DIR = Release
RELEASE_SRC_DIR = $(RELEASE_DIR)/$(SRC_DIR)

OBJ_DLL = cec20_test_func.o entry_point.o
OBJ_EXE = cec20_test_func.o main.o

DEBUG_DLL_OBJS = $(patsubst %,$(DEBUG_SRC_DIR)/%,$(OBJ_DLL))
DEBUG_EXE_OBJS = $(patsubst %,$(DEBUG_SRC_DIR)/%,$(OBJ_EXE))
RELEASE_DLL_OBJS = $(patsubst %,$(RELEASE_SRC_DIR)/%,$(OBJ_DLL))
RELEASE_EXE_OBJS = $(patsubst %,$(RELEASE_SRC_DIR)/%,$(OBJ_EXE))


.PHONY: all clean

all: $(DEBUG_DIR)/benchmark.exe $(DEBUG_DIR)/libbenchmark.dll $(RELEASE_DIR)/benchmark.exe $(RELEASE_DIR)/libbenchmark.dll

$(DEBUG_DIR)/benchmark.exe: $(DEBUG_EXE_OBJS)
	$(CC) $? -o $@

$(DEBUG_DIR)/libbenchmark.dll: $(DEBUG_DLL_OBJS)
	$(CC) -fPIC $? -shared -o $@

$(DEBUG_SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(DEBUG_PARAMS) -c $< -o $@

$(RELEASE_DIR)/benchmark.exe: $(RELEASE_EXE_OBJS)
	$(CC) $? -o $@

$(RELEASE_DIR)/libbenchmark.dll: $(RELEASE_DLL_OBJS)
	$(CC) -fPIC $? -shared -o $@

$(RELEASE_SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(RELEASE_PARAMS) -c $< -o $@

clean:
	del .\Debug\benchmark.exe
	del .\Debug\libbenchmark.dll
	del .\Debug\src\*.o
	del .\Release\benchmark.exe
	del .\Release\libbenchmark.dll
	del .\Release\src\*.o
