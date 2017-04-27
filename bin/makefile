# ROOTSYS should be defined in the shell
ROOTCONFIG:= $(ROOTSYS)/bin/root-config
ROOTCFLAGS:= $(shell $(ROOTCONFIG) --cflags)
ROOTLDFLAGS:= $(shell $(ROOTCONFIG) --ldflags)
ROOTLIBS:= $(shell $(ROOTCONFIG) --libs)
ROOTGLIBS:= $(shell $(ROOTCONFIG) --glibs)

# Compiler
CXX             = g++
LD              = g++

# Flags -g turns on debugging capability for gdb
CXXFLAGS        = -g -O -Wall -fPIC $(ROOTCFLAGS)
LDFLAGS         = -O $(ROOTLDFLAGS)

# Note: -lTreePlayer
GLIBS           = $(ROOTGLIBS) -lTMVA

# Source files and corresponding object files
SRCPATH         = src
SRCS            = $(wildcard $(SRCPATH)/*.cxx)
OBJS            = $(SRCS:.cxx=.o)

# Ditto package path
DITTOPATH       := $(shell echo $(DITTOPATH))
DITTOPATHINC    = -I$(DITTOPATH)/src/
DITTOOBJ        = $(DITTOPATH)/src/Ditto.o

# Executable name is the shell "$PACKAGENAME"
EXEC            := $(shell echo $(DITTOPATH)/bin/$(BINARYNAME))

# Main target
$(EXEC): $(OBJS) $(DITTOOBJ)
	$(LD) $(LDFLAGS) $(GLIBS) $(OBJS) $(DITTOOBJ) -o $(EXEC)

# Ditto object
$(DITTOOBJ): check-ditto
	$(CXX) -c $(CXXFLAGS) $(DITTOPATHINC) $(DITTOPATH)/$(SRCPATH)/Ditto.cxx -o $@

# To create object files
%.o: %.cxx
	$(CXX) -c $(CXXFLAGS) $(DITTOPATHINC) $< -o $@

# Clean
clean:
	rm -f $(DITTOPATH)/src/Ditto.o $(EXEC) $(OBJS)

# Check Ditto package path set
check-ditto:
ifndef DITTOPATH
	$(error DITTOPATH is not set! source /wherever/your/Ditto/package/is/Ditto/bin/setup.sh)
endif
