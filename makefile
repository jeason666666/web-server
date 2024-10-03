CC := gcc
CXX := g++

CXX_FLAGS := -std=c++20
CXX_FLAGS += -lpthread
CXX_FLAGS += -L/lib64/mysql -lmysqlclient
CXX_FLAGS += -Ithirdlib
CXX_FLAGS += -g  # for debug

SRC_PATH := src
INC_PATH := include
BUILD_PATH := build

SRC := $(shell find $(SRC_PATH) -type f -name "*.cc")
INC := $(shell find $(INC_PATH) -type f -name "*.h")

main:main.cc
	$(CXX) main.cc $(SRC) -I$(INC_PATH) -o $(BUILD_PATH)/main $(CXX_FLAGS)

test:test.cc
	$(CXX) test.cc $(SRC) -I$(INC_PATH) -o $(BUILD_PATH)/test $(CXX_FLAGS)

run:
	./build/main

trun:
	./build/test

tgdb:
	gdb ./build/test

gdb:
	gdb ./build/main

update:
	scl enable devtoolset-11 bash

count:
	wc -l $(SRC) $(INC)

runtest:
	./build/test

.PHONY:clean
clean:
	rm -rf $(BUILD_PATH)/main $(BUILD_PATH)/test
