
CXX      = g++
LINK     = g++
#CXXFLAGS = -O3 -Xptxas -v -Xptxas -dlcm=ca -arch=sm_20 -m64 
#CXXFLAGS = -O3 -Xptxas -v -Xptxas -dlcm=ca -arch=sm_20 -m64 -DDOUBLE
#CXXFLAGS = -O3 -Xptxas -v -Xptxas -dlcm=ca -arch=sm_20 -m64 -DPROFILE
#CXXFLAGS = -O3 -Xptxas -v -Xptxas -dlcm=ca -arch=sm_20 -m64 -DPROFILE -DDOUBLE
#CXXFLAGS = -g -DDEBUG_ATPG -Wall #Turn on debugging
CXXFLAGS =
INCPATH  =
#LIBS     = -lreadline -lcurses
DEL_FILE = rm -f

####### Files

HEADERS = graph.h 

SOURCES = main.cpp graph.cpp

OBJECTS = main.o graph.o

TARGET  = bezier

####### Implicit rules

.SUFFIXES: .o .cpp 

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<


####### Build rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LINK) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS) $(INCPATH)

$(OBJECTS): $(HEADERS) Makefile

clean:
	@$(DEL_FILE) $(OBJECTS) $(TARGET)

