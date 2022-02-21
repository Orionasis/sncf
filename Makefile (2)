GPP=g++
sources=main.cpp
OBJ=$(sources:.cpp=.o) 

all: line2

line2: $(OBJ)
	$(GPP) $(OBJ)  -o $@

%.o:%.cpp
	$(GPP) -c $< -o $@ 

clean:
	rm -rf *.o line2
