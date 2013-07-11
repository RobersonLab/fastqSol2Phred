CXX = g++

# Any custom compiler flags here ( -g, -march, -mtune, -m64, etc)
# For 64-bit compilation add -m64 to CXXFLAGS
CXXFLAGS = 
# --------------------------------------------------------------------
# Do not edit below this line
# --------------------------------------------------------------------

CXXFLAGS += -O3 -I. -Wall
OUTPUT = fastqSol2Phred

SRC = main.cpp

HDR = 

OBJ = $(SRC:.cpp=.o)

all : $(OUTPUT) 

$(OUTPUT) : $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(OBJ)

$(OBJ) : $(HDR)

.cpp.o : 
	$(CXX) $(CXXFLAGS) -c $*.cpp
.SUFFIXES : .cpp .c .o $(SUFFIXES)

.PHONEY : clean install uninstall

clean:
	rm -f *.o $(OUTPUT)

install:
	install -m 0755 ./$(OUTPUT) /usr/local/bin

uninstall:
	rm /usr/local/bin/$(OUTPUT)
