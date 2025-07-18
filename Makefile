# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall

# Directories
CODE_DIR := src
TEST_DIR := tests
BUILD_DIR := build
BIN_DIR := bin

# Find source and header files
CODE_SRCS := $(shell find $(CODE_DIR) -name "*.cpp")
CODE_HDRS := $(shell find $(CODE_DIR) -name "*.h")
TEST_SRCS := $(shell find $(TEST_DIR) -name "*.cpp")
TEST_HDRS := $(shell find $(TEST_DIR) -name "*.h")

# Objects from src/
CODE_OBJS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(CODE_SRCS))

# Objects from tests/ — each becomes a standalone test
TEST_BINS := $(patsubst $(TEST_DIR)/%.cpp, $(BIN_DIR)/%, $(TEST_SRCS))

# Include directories
INCLUDES := $(shell find $(CODE_DIR) $(TEST_DIR) -type d)
CXXFLAGS += $(foreach d, $(INCLUDES), -I$d)

# Phony targets
.PHONY: all clean run_tests

# Default target
all: $(TEST_BINS)

# Build object files from code
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link test executables
$(BIN_DIR)/%: $(BUILD_DIR)/$(TEST_DIR)/%.o $(CODE_OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile test sources
$(BUILD_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run all tests
run_tests: all
	@echo "Running all tests:"
	@for test in $(TEST_BINS); do \
		echo "[Running $$test]"; \
		./$$test || exit 1; \
	done

# Clean build
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
