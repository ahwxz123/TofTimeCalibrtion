OBJ = TimeCalibraw.o
EXE =  TimeCalibraw
OBJ2 = RingTimeCalib_FOVcut_V2.o 
EXE2 =  RingTimeCalib_FOVcut_V2
OBJ3 = RingTimeCalib_FOVcut.o 
EXE3 =  RingTimeCalib_FOVcut
OBJ4 = TimeCalibraw_tof.o
EXE4 =  TimeCalibraw_tof


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

all: $(EXE) $(EXE2) $(EXE3) $(EXE4)

$(EXE): $(OBJ)
	$(CXX) -o $(EXE) $(OBJ) $(ROOTFLAGS) $(ROOTLIBS) -lSpectrum
$(EXE2): $(OBJ2)
	$(CXX) -o $(EXE2) $(OBJ2) $(ROOTFLAGS) $(ROOTLIBS) -lSpectrum
$(EXE3): $(OBJ3)
	$(CXX) -o $(EXE3) $(OBJ3) $(ROOTFLAGS) $(ROOTLIBS) -lSpectrum
$(EXE4): $(OBJ4)
	$(CXX) -o $(EXE4) $(OBJ4) $(ROOTFLAGS) $(ROOTLIBS) -lSpectrum

%.o: %.cxx
	$(COMPILE)  $< 

clean:
	rm -f $(EXE) $(EXE2) $(EXE3) $(EXE4)
	rm -f $(OBJ) $(OBJ2) $(OBJ3) $(OBJ4)
