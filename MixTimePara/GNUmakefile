OBJS = MixPara_Submodule6.o 
EXE =  MixPara_Submodule6
OBJS2 = RootConvert.o 
EXE2 =  RootConvert
OBJS3 = RootConvert_OnePairsModuleDiff.o 
EXE3 =  RootConvert_OnePairsModuleDiff


ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)

INCFLAGS = -I$(ROOTSYS)/include -std=c++11
LDFLAGS = -L$(ROOTSYS)/lib  -std=c++11

#CXX = gcc -m32 -D_FILE_OFFSET_BITS=64 -D_LARGE_FILE
#####CXX = g++ -g -m32 -D_FILE_OFFSET_BITS=64  -D_LARGEFILE_SOURCE  -D_LARGEFILE64_SOURCE
#CXX = g++ -m32 -D_FILE_OFFSET_BITS=64 -D_LARGE_FILE
CXX = g++ 
FLAGS =  -Wall -g $(INCFLAGS) $(LDFLAGS)

COMPILE = $(CXX) $(FLAGS) -c 

all: $(EXE) $(EXE2) $(EXE3)

$(EXE): $(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(ROOTFLAGS) $(ROOTLIBS)
$(EXE2): $(OBJS2)
	$(CXX) -o $(EXE2) $(OBJS2) $(ROOTFLAGS) $(ROOTLIBS)
$(EXE3): $(OBJS3)
	$(CXX) -o $(EXE3) $(OBJS3) $(ROOTFLAGS) $(ROOTLIBS)

%.o: %.cxx
	$(COMPILE)  $< 

clean:
	rm -f $(EXE) $(EXE2) $(EXE3)
	rm -f $(OBJS) $(OBJS2) $(OBJS3)
