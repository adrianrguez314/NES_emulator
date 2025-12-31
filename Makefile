CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

SRCDIR := src
OBJDIR := build
BINDIR := bin

ifeq ($(OS),Windows_NT)
    EXEEXT := .exe
    MKDIR = if not exist "$1" mkdir "$1"
    RMOBJ = if exist "$(OBJDIR)" rmdir /S /Q "$(OBJDIR)"
    RMBIN = if exist "$(BINDIR)" rmdir /S /Q "$(BINDIR)"
    RUN = $(TARGET)
else
    EXEEXT :=
    MKDIR = mkdir -p "$1"
    RMOBJ = rm -rf "$(OBJDIR)"
    RMBIN = rm -rf "$(BINDIR)"
    RUN = ./$(TARGET)
endif

TARGET := $(BINDIR)/nes$(EXEEXT)

SRCS := $(wildcard $(SRCDIR)/*.cpp $(SRCDIR)/cpu/*.cpp $(SRCDIR)/memory/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	@if not exist "$(BINDIR)" mkdir "$(BINDIR)"
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-$(RMOBJ)
	-$(RMBIN)

run: $(TARGET)
	$(RUN)
