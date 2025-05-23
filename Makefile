# Compiler and settings
CXX := g++
NUM_CORES := $(shell nproc)
CXXFLAGS := -std=c++20 -Ofast -flto -march=x86-64 -mtune=native -ffunction-sections -fdata-sections -ftree-vectorize -MMD -MP -Wall -Wextra -ffast-math -funsafe-math-optimizations -fno-exceptions -fno-rtti \
            -fomit-frame-pointer -fno-stack-protector -ffp-contract=fast -fopenmp -funroll-loops -fprefetch-loop-arrays  -fno-math-errno -fno-ident \
			-falign-functions=64 -falign-loops=64 -falign-jumps=64 -mavx2 -mfma -mbmi2 -DNDEBUG -pthread # -fprofile-use




LDFLAGS := -flto
TARGET := main
SRC := main.cpp
OBJ := $(SRC:.cpp=.o)
DEP := $(OBJ:.o=.d)
MAKEFLAGS += -j$(NUM_CORES)
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEP)

clean:
	rm -f $(TARGET) *.o *.d

.PHONY: all clean
