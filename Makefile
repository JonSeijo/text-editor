# Adaptado de http://stackoverflow.com/a/30142139

GPP = g++
# Agregar -Wall
FLAGS = -std=c++11
LIBS= -lsfml-graphics -lsfml-window -lsfml-system

# Final binary
BIN = editor

# Put all auto generated stuff to this build dir.
BUILD_DIR = ./build

# List of all .cpp source files.
# CPP = main.cpp $(wildcard dir1/*.cpp) $(wildcard dir2/*.cpp)
CPP = Editor.cpp $(wildcard *.cpp)

# All .o files go to build dir.
OBJ = $(CPP:%.cpp=$(BUILD_DIR)/%.o)

# Gcc/Clang will create these .d files containing dependencies.
DEP = $(OBJ:%.o=%.d)

# Default target named after the binary.
$(BIN) : $(BUILD_DIR)/$(BIN)

# Actual target of the binary - depends on all .o files.
$(BUILD_DIR)/$(BIN) : $(OBJ)
# Create build directories - same structure as sources.
	@mkdir -p $(@D)
# Just link all the object files.
	$(GPP) $(FLAGS) $^ -o $@ $(LIBS)
# Solo por conveniencia, para poder hacer ./editor facilmente
	@mv $(BUILD_DIR)/$(BIN) $(BIN)

# Include all .d files
-include $(DEP)

# Build target for every single object file.
# The potential dependency on header files is covered
# by calling `-include $(DEP)`.
$(BUILD_DIR)/%.o : %.cpp
	@mkdir -p $(@D)
# The -MMD flags additionaly creates a .d file with
# the same name as the .o file.
	$(GPP) $(FLAGS) -MMD -c $< -o $@

.PHONY : clean
clean :
# This should remove all generated files.
	-rm -f $(BUILD_DIR)/$(BIN) $(OBJ) $(DEP)
	rm -f editor
