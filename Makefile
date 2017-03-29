CXX = g++
# Update these paths to match your installation
# You may also need to update the linker option rpath, which sets where to look for
# the SDL2 libraries at runtime to match your install
#SDL_LIB = -L/usr/local/lib -lSDL2 -Wl,-rpath=/usr/local/lib -lSDL2_image
# NOTE: remember to run `ldconfig` as root after installing new libs
# FIXME: should use sdl2-config --cflags and sdl2-config --libs
SDL_LIB = -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf
SDL_INCLUDE = -I/usr/local/include -I./include
# You may need to change -std=c++11 to -std=c++0x if your compiler is a bit older
CXXFLAGS = -W -Wall -Wextra -c -std=c++17 -g $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB)
EXE = engine

SUBDIRS = src
BUILD_DIR = build

SOURCES = $(patsubst src/%,%,$(wildcard src/*.cpp))
OBJECTS = $(patsubst %.cpp,%,$(SOURCES))

.PHONY: test

all: $(EXE)

$(EXE): build $(OBJECTS)
	$(CXX) build/*.o -o $@ $(LDFLAGS)
#	$(CXX) $< $(LDFLAGS) -o $@ $< -L./build

$(OBJECTS):
	$(CXX) $(CXXFLAGS) -c src/$@.cpp -o build/$@.o

dev: all
	./$(EXE)

build:
	@mkdir build

clean:
	rm -f $(TARGET)
	rm -f build/*
#find . -name'*orig' | xargs rm

tidy:
	@find ./src/ -name '*orig' | xargs rm

# http://astyle.sourceforge.net/astyle.html
style:
	@astyle --options=.astylerc \
	`ls src/*.h src/*.cpp test/*.cpp ls src/Level/*`



TEST_CXXFLAGS = -std=c++14 $(SDL_INCLUDE) -I./src
TEST_OBJECTS = $(patsubst build/main.o, , $(wildcard build/*.o))

# If you don't use tup:
# test: build $(TEST_OBJECTS)
test:
	tup
	$(CXX) $(TEST_CXXFLAGS) test/utilities_test.cpp $(TEST_OBJECTS) -o run_tests $(LDFLAGS)
	./run_tests

