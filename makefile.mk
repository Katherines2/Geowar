CXX = g++
CXXFLAGS = -Wall -std=c++11

SRC = Geowar.cpp

OBJ = $(SRC:.cpp=.o)

exe: $(OBJ)
    $(CXX) $(CXXFLAGS) -o exe $(OBJ)

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f *.o exe
