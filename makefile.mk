CXX = g++
CXXFLAGS = -Wall -std=c++11

SRC = Geowar.cpp

OBJ = $(SRC:.cpp=.o)

windows:
	mkdir $(WIN)
	g++ -o Geowar.exe Geowar.cpp

linux:
	mkdir $(LIN)
	g++ -o Geowar Geowar.cpp

web:
	cmd /c start http://localhost:8000/geowar.html
	python -m http.server 8000

exe: $(OBJ)
    $(CXX) $(CXXFLAGS) -o exe $(OBJ)

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f *.o exe
