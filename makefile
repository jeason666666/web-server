CC := gcc
CXX := g++

CXX_FLAGS := -std=c++17 -lpthread

SRC_PATH := src
INC_PATH := include
BUILD_PATH := build

SRC := $(wildcard $(SRC_PATH)/*.cc)
INC := $(wildcard $(INC_PATH)/*.h)

main:main.cc
	$(CXX) main.cc $(SRC) -I$(INC_PATH) -o $(BUILD_PATH)/main $(CXX_FLAGS)

test:test.cc
	$(CXX) test.cc $(SRC) -o $(BUILD_PATH)/test $(CXX_FLAGS)

run:
	./build/main

runtest:
	./build/test


update:
	scl enable devtoolset-9 bash

.PHONY:clean
clean:
	rm -rf $(BUILD_PATH)/main $(BUILD_PATH)/test
