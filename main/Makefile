# Define the compiler and the linker. The linker must be defined since
# the implicit rule for linking uses CC as the linker. g++ can be
# changed to clang++.
CXX = gcc
CC  = gcc

# Define preprocessor, compiler, and linker flags. Uncomment the # lines
# if you use clang++ and wish to use libc++ instead of GNU's libstdc++.
# -g is for debugging.
#CPPFLAGS =  -std=c++11
CXXFLAGS =  -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast -lm
#CXXFLAGS += -std=c++11 
CXXFLAGS += -g
LDFLAGS =   -g
#CPPFLAGS += -stdlib=libc++
#LDFLAGS +=  -stdlib=libc++
#CXXFLAGS += -stdlib=libc++

# Targets
PROGS = PIR

all: $(PROGS)

# Targets rely on implicit rules for compiling and linking
PIR: input.o buffer.o calculations.o kiss_fft.o kiss_fftr.o 
# Phony targets
.PHONY: all clean

# Standard clean
clean:
	rm -f *.o $(PROGS)

# Generate dependencies in *.d files
%.d: %.c
	@set -e; rm -f $@; \
         $(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

# Include the *.d files
SRC = $(wildcard *.c)
include $(SRC:.c=.d)
