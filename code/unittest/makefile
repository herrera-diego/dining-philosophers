.DEFAULT_GOAL := all

SRCDIR=src
BINDIR=bin
OBJDIR=obj
LIBDIR=

FUSED_GTEST_DIR = /usr/src/googletest/googletest



# Include directories
INCDIR := \
        -Iinclude/ \
		-I$(FUSED_GTEST_DIR) \
		-I$(FUSED_GTEST_DIR)/src \
		-I../src \

CC=gcc
CXX=g++
CFLAGS =-I$(SRCDIR) $(INCDIR)
CXXFLAGS =-I$(SRCDIR) $(INCDIR)
LDFLAGS =-L$(LIBDIR)
LDLIBS = -lrt -lgtest -lgtest_main -pthread -lcrypto -lssl -lgcrypt -lgpg-error

OUTFILE=unittest

EXCFILE		:= main.*
CODEFILES	:= $(shell find $(SRCDIR) -type f -not -name "$(EXCFILE)")
CFILES 	  	:= $(filter %.c,$(CODEFILES))
CPPFILES  	:= $(filter %.cpp,$(CODEFILES))
SRCFILES	:= $(CFILES) $(CPPFILES)
HDRFILES  	:= $(filter %.h,$(CODEFILES))
OBJFILES  	:= $(subst $(SRCDIR), $(OBJDIR),$(CPPFILES:%.cpp=%.o) $(CFILES:%.c=%.o))
SRCOBJFILES := $(shell find ../obj -type f -not -name "$(EXCFILE)")

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HDRFILES)
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/%.o:  $(SRCDIR)/%.cpp $(HDRFILES)
	mkdir -p $(dir $@)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(OUTFILE): $(OBJFILES) $(SRCOBJFILES)
	mkdir -p $(BINDIR)
	$(CXX) -o $(BINDIR)/$@ $^  $(CFLAGS) $(LDFLAGS) $(LDLIBS)


debug: CXXFLAGS += -DDEBUG -O0 -ggdb3 
debug: CFLAGS += -DDEBUG -O0 -ggdb3 
debug: clean $(OUTFILE)

rebuild: clean $(OUTFILE)

.PHONY: all clean 

all: debug 

clean:
	rm -rf $(OBJDIR)/*
	rm -rf $(BINDIR)/*