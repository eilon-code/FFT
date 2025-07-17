# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Isrc

# Directories
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
BIN_DIR = bin

# Source Subdirectories
SRC_SUBDIRS = $(SRC_DIR)/complex_numbers $(SRC_DIR)/polynomials
TEST_SUBDIRS = $(TEST_DIR)/complex_tests $(TEST_DIR)/polynomial_tests $(TEST_DIR)/fft_tests

# Source Files
SRC_FILES = $(SRC_SUBDIRS)/Complex.cpp \
            $(SRC_SUBDIRS)/Polynomial.cpp \
            $(SRC_DIR)/FFT.cpp

# Test Files
TEST_FILES = $(TEST_SUBDIRS)/test_complex_1.cpp \
             $(TEST_SUBDIRS)/test_polynomial_1.cpp \
             $(TEST_SUBDIRS)/test_fft_1.cpp \
             $(TEST_DIR)/test.cpp

# Object Files
OBJ_FILES = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES) $(TEST_FILES))

# Executable
TARGET = $(BIN_DIR)/run_tests

.PHONY: all run clean

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compiling .cpp to .o
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean everything
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
