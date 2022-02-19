CC = g++
INCLUDES = -I/usr/include/GL
LIBS = -Wl,-rpath=/usr/local/cs/lib64 -lglut -lGL -lGLU
STD = -std=c++17

# On cs32.seas.ucla.edu or lnxsrv06 or lnxsrv07 or lnxsrv09, uncomment the following three lines
#CC = g32
#STD = 

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS = $(wildcard *.h)

.PHONY: default all clean

PRODUCT = SuperPeachSisters

all: $(PRODUCT)

%.o: %.cpp $(HEADERS)
	$(CC) -c $(STD) $(INCLUDES) $< -o $@

$(PRODUCT): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LIBS) -o $@

clean:
	rm -f *.o
	rm -f $(PRODUCT)
