.DEFAULT_GOAL := all


# Include directories
INCDIR := \
		-I.. \

SRCDIR=src
BINDIR=bin
OBJDIR=obj
LIBDIR=lib

CC=gcc
CXX=g++
CFLAGS =-I$(SRCDIR) $(INCDIR)
CXXFLAGS =-I$(SRCDIR) $(INCDIR)
LDFLAGS =-L$(LIBDIR)
LDLIBS = -lrt 

OUTFILE=dining-philosopher

EXCDIR 		:= unittest
CODEFILES	:= $(shell find $(SRCDIR) -type f -not -path "$(EXCDIR)/*")
CFILES 	  	:= $(filter %.c,$(CODEFILES))
CPPFILES  	:= $(filter %.cpp,$(CODEFILES))
SRCFILES	:= $(CFILES) $(CPPFILES)
HDRFILES  	:= $(filter %.h,$(CODEFILES))
OBJFILES  	:= $(subst $(SRCDIR), $(OBJDIR),$(CPPFILES:%.cpp=%.o) $(CFILES:%.c=%.o))





$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HDRFILES)
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/%.o:  $(SRCDIR)/%.cpp $(HDRFILES)
	mkdir -p $(dir $@)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(OUTFILE): $(OBJFILES)
	mkdir -p $(BINDIR)
	$(CXX) -o $(BINDIR)/$@ $^  $(CFLAGS) $(LDFLAGS) $(LDLIBS)

# $(OUTFILE): $(OBJFILES)
# 	mkdir -p $(BINDIR)
# 	ar rc $(BINDIR)/$@ $^
# 	ranlib $(BINDIR)/$@

debug: CXXFLAGS += -DDEBUG -O0 -ggdb3 
debug: CFLAGS += -DDEBUG -O0 -ggdb3 
debug: $(OUTFILE)

rebuild: clean $(OUTFILE)

.PHONY: all clean 

all: $(OUTFILE) 

clean:
	rm -rf $(OBJDIR)/*
	rm -rf $(BINDIR)/*
	