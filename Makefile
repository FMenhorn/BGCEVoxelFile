# Include files
SOURCESMAIN= InputReader.cpp

SOURCESBASIC= VtkWriter.cpp TpdWriter.cpp
# Compiler
# --------
CC=g++

CFLAGS=  -O3 -std=c++0x

# Linker flags
# ------------
LDFLAGS= 

OBJECTSMAIN=$(SOURCESMAIN:.cpp=.o)

OBJECTSBASIC=$(SOURCESBASIC:.cpp=.o)

EXECUTABLE=InputReader

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTSBASIC) $(OBJECTSMAIN)
	$(CC) $(OBJECTSBASIC) $(OBJECTSMAIN) -o $@ $(LDFLAGS) 

$(OBJECTSMAIN): %.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTSBASIC): %.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f $(EXECUTABLE) $(OBJECTSBASIC) $(OBJECTSMAIN)
