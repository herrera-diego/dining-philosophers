.DEFAULT_GOAL := all


# Include directories
INCDIR := \
		-I$(FUSED_GTEST_DIR) \
		-I$(FUSED_GTEST_DIR)/src \


SRCDIR=src
BINDIR=bin
OBJDIR=obj
LIBDIR=lib
TSTDIR=unittest

CC=gcc
CXX=g++
CFLAGS =-I$(SRCDIR) $(INCDIR)
CXXFLAGS =-I$(SRCDIR) $(INCDIR)
LDFLAGS =-L$(LIBDIR)
LDLIBS = -lrt 
TSTLIBS = -lrt -lgtest -lgtest_main -pthread -lcrypto -lssl -lgcrypt -lgpg-error

OUTFILE=dining-philosopher
TESTFILE=unittest

CODEFILES	:= $(shell find $(SRCDIR) -type f -not -path "$(TSTDIR)/*")
CFILES 	  	:= $(filter %.c,$(CODEFILES))
CPPFILES  	:= $(filter %.cpp,$(CODEFILES))
SRCFILES	:= $(CFILES) $(CPPFILES)
HDRFILES  	:= $(filter %.h,$(CODEFILES))
OBJFILES  	:= $(subst $(SRCDIR), $(OBJDIR),$(CPPFILES:%.cpp=%.o) $(CFILES:%.c=%.o))

EXCFILE		:= main.*
TESTCODEFILES	:= $(shell find $(SRCDIR) -type f -not -name "$(EXCFILE)")
TESTCODEFILES   += $(shell find $(TSTDIR) -type f )
TESTCFILES 	  	:= $(filter %.c,$(TESTCODEFILES))
TESTCPPFILES  	:= $(filter %.cpp,$(TESTCODEFILES))
TESTOBJFILES	:= $(subst $(TSTDIR)/, $(OBJDIR)/, $(subst $(SRCDIR)/, $(OBJDIR)/,$(TESTCPPFILES:%.cpp=%.o) $(TESTCFILES:%.c=%.o)))

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HDRFILES)
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)
$(OBJDIR)/%.o: $(TSTDIR)/%.c $(HDRFILES)
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HDRFILES)
	mkdir -p $(dir $@)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(OBJDIR)/%.o: $(TSTDIR)/%.cpp $(HDRFILES)
	mkdir -p $(dir $@)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(OUTFILE): $(OBJFILES)
	mkdir -p $(BINDIR)
	$(CXX) -o $(BINDIR)/$@ $^  $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

$(TESTFILE): $(TESTOBJFILES)
	echo $(TESTOBJFILES)
	mkdir -p $(BINDIR)
	$(CXX) -o $(BINDIR)/$@ $^  $(CXXFLAGS) $(LDFLAGS) $(TSTLIBS)

# $(OUTFILE): $(OBJFILES)
# 	mkdir -p $(BINDIR)
# 	ar rc $(BINDIR)/$@ $^
# 	ranlib $(BINDIR)/$@

debug: CXXFLAGS += -DDEBUG -O0 -ggdb3 
debug: CFLAGS += -DDEBUG -O0 -ggdb3 
debug: $(OUTFILE)

test: CXXFLAGS += -DDEBUG -O0 -ggdb3 
test: CFLAGS += -DDEBUG -O0 -ggdb3 
test: $(TESTFILE)

rebuild: clean $(OUTFILE)

.PHONY: all clean test

all: $(OUTFILE) 

clean:
	rm -rf $(OBJDIR)/*
	rm -rf $(BINDIR)/*
	