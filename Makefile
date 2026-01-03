CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

SRCDIR := src
TESTDIR := tests
OBJDIR := build
BINDIR := bin

ifeq ($(OS),Windows_NT)
    EXEEXT := .exe
    MKDIR = if not exist $1 mkdir $1
    RM = if exist $1 rmdir /S /Q $1
else
    EXEEXT :=
    MKDIR = mkdir -p $1
    RM = rm -rf $1
endif

TARGET := $(BINDIR)/nes$(EXEEXT)
TEST_TARGET := $(BINDIR)/run_tests$(EXEEXT)


SRCS := \
    $(wildcard $(SRCDIR)/*.cpp) \
    $(wildcard $(SRCDIR)/cpu/*.cpp) \
    $(wildcard $(SRCDIR)/cpu/instructions/*.cpp) \
    $(wildcard $(SRCDIR)/memory/*.cpp)

OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

TEST_SRCS := \
	$(wildcard $(TESTDIR)/*.cpp)  \
	$(wildcard $(TESTDIR)/instructions/*.cpp)
	
TEST_OBJS := $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/tests/%.o,$(TEST_SRCS))

.PHONY: all clean run test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(call MKDIR,$(BINDIR))
	$(CXX) $(CXXFLAGS) $^ -o $@


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(call MKDIR,$(dir $@))
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(OBJDIR)/tests/%.o: $(TESTDIR)/%.cpp
	$(call MKDIR,$(dir $@))
	$(CXX) $(CXXFLAGS) -c $< -o $@


test: $(TEST_OBJS) $(OBJS)
	$(call MKDIR,$(BINDIR))
	$(CXX) $(CXXFLAGS) $(filter-out $(OBJDIR)/main.o,$(OBJS)) $(TEST_OBJS) -o $(TEST_TARGET)
	$(TEST_TARGET)

run: $(TARGET)
	$(TARGET)

clean:
	$(call RM,$(OBJDIR))
	$(call RM,$(BINDIR))
