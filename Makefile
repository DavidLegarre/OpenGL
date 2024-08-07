TARGET_EXEC := opengl

CC := g++
CFLAGS = -Wall -Wextra -Werror -std=c++20 -pedantic

debug ?= 1
ifeq ($(debug), 1)
	CFLAGS := $(CFLAGS) -g -O0
else
	CFLAGS := $(CFLAGS) -Oz
endif

LDFLAGS := -lm
GLLIBRARIES = -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lglfw3 -lm -lGLU
LDFLAGS += $(GLLIBRARIES)

# dirs
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
LIB_DIR := lib
TESTS_DIR := tests
BIN_DIR := bin


SRC_DIRS := $(SRC_DIR) $(INCLUDE_DIR) $(LIB_DIR)
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS := $(INC_FLAGS) -MMD -MP

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS) dir
	$(CXX) $(OBJS) -o $(TARGET_EXEC) $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c 
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp 
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean run dir
dir:
	mkdir -p $(BIN_DIR)
clean:
	rm -r $(BUILD_DIR)

run: $(BUILD_DIR)/$(TARGET_EXEC) 
	./$(TARGET_EXEC)


-include $(DEPS)
