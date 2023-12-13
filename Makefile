CXX = g++
CXXFLAGS = -std=c++11
SRCS = Geowar.cpp
TARGET = geowar

Windows:
ifeq ($(OS),Windows_NT)
	TARGET := $(TARGET).exe
	CXXFLAGS += -DWINDOWS
	LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
endif

Linux:
ifeq ($(OS),Linux)
	CXXFLAGS += -DLINUX
	LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
endif

Web:
ifeq ($(OS),Emscripten)
	CXX = emcc
	TARGET := index.html
	CXXFLAGS += --preload-file assets -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2
endif

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: clean

clean:
	rm -rf $(WIN)
	rm -rf $(LIN)
