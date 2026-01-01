CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

SRCDIR := src
OBJDIR := build
BINDIR := bin
EXEEXT := .exe

TARGET := $(BINDIR)\nes$(EXEEXT)
TEST_TARGET := $(BINDIR)\run_tests$(EXEEXT)

SRCS := \
    $(SRCDIR)\main.cpp \
    $(SRCDIR)\cpu\cpu.cpp \
    $(SRCDIR)\cpu\instructions\lda.cpp \
    $(SRCDIR)\cpu\instructions\misc.cpp \
    $(SRCDIR)\memory\memory.cpp

OBJS := \
    $(OBJDIR)\main.o \
    $(OBJDIR)\cpu\cpu.o \
    $(OBJDIR)\cpu\instructions\lda.o \
    $(OBJDIR)\cpu\instructions\misc.o \
    $(OBJDIR)\memory\memory.o

TEST_SRCS := tests\instruction_test.cpp
TEST_OBJS := $(OBJDIR)\tests\instruction_test.o

.PHONY: all clean run test

all: $(TARGET)

$(TARGET): $(OBJS)
	if not exist $(BINDIR) mkdir $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)\main.o: $(SRCDIR)\main.cpp
	if not exist $(OBJDIR) mkdir $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)\cpu\cpu.o: $(SRCDIR)\cpu\cpu.cpp
	if not exist $(OBJDIR)\cpu mkdir $(OBJDIR)\cpu
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)\cpu\instructions\lda.o: $(SRCDIR)\cpu\instructions\lda.cpp
	if not exist $(OBJDIR)\cpu\instructions mkdir $(OBJDIR)\cpu\instructions
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)\cpu\instructions\misc.o: $(SRCDIR)\cpu\instructions\misc.cpp
	if not exist $(OBJDIR)\cpu\instructions mkdir $(OBJDIR)\cpu\instructions
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)\memory\memory.o: $(SRCDIR)\memory\memory.cpp
	if not exist $(OBJDIR)\memory mkdir $(OBJDIR)\memory
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(OBJDIR)\tests\instruction_test.o: tests\instruction_test.cpp
	if not exist $(OBJDIR)\tests mkdir $(OBJDIR)\tests
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_OBJS)
	if not exist $(BINDIR) mkdir $(BINDIR)
	$(CXX) $(CXXFLAGS) $(OBJDIR)\cpu\cpu.o $(OBJDIR)\cpu\instructions\lda.o $(OBJDIR)\cpu\instructions\misc.o $(OBJDIR)\memory\memory.o $(TEST_OBJS) -o $(BINDIR)\run_tests.exe
	$(BINDIR)\run_tests.exe