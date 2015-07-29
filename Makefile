# Include files
SOURCESMAIN= InputReader.cpp
# Compiler
# --------
CC=g++

CFLAGS=  -O3

# Linker flags
# ------------
LDFLAGS= 

OBJECTSMAIN=$(SOURCESMAIN:.cpp=.o)

EXECUTABLE=InputReader

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTSMAIN)
	$(CC) $(OBJECTSMAIN) -o $@ $(LDFLAGS) 

$(OBJECTSMAIN): %.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f $(EXECUTABLE) $(OBJECTSMAIN)