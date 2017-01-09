CXX = g++
# Update these paths to match your installation
# You may also need to update the linker option rpath, which sets where to look for
# the SDL2 libraries at runtime to match your install
#SDL_LIB = -L/usr/local/lib -lSDL2 -Wl,-rpath=/usr/local/lib -lSDL2_image
SDL_LIB = -L/usr/local/lib -lSDL2 -lSDL2_image
SDL_INCLUDE = -I/usr/local/include -I./include
# You may need to change -std=c++11 to -std=c++0x if your compiler is a bit older
CXXFLAGS = -W -Wall -c -std=c++14 -g $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB)
EXE = engine

SUBDIRS = src
BUILD_DIR = build

SOURCES = $(patsubst src/%,%,$(wildcard src/*.cpp))
OBJECTS = $(patsubst %.cpp,%,$(SOURCES))


all: $(EXE)

$(EXE): build $(OBJECTS)
	$(CXX) build/*.o -o $@ $(LDFLAGS)
#	$(CXX) $< $(LDFLAGS) -o $@ $< -L./build

$(OBJECTS):
	$(CXX) $(CXXFLAGS) -c src/$@.cpp -o build/$@.o

#dev: build
#	$(CXX) $(CXXFLAGS) $(wildcard src/*.cpp) \
#	-o $(EXE) $(LDFLAGS)

#dev:
#	$(CXX) $(CXXFLAGS) $(wildcard src/*.cpp) $< -o $(EXE) $(LDFLAGS)

build:
	@mkdir build

clean:
	rm -f $(TARGET)
	rm -f build/*
#find . -name'*orig' | xargs rm

# http://astyle.sourceforge.net/astyle.html
style:
	@astyle --options=.astylerc \
	`ls src/*.h src/*.cpp`

TEST_CXXFLAGS = -std=c++14 $(SDL_INCLUDE) -I./src
dev:
	$(CXX) $(TEST_CXXFLAGS) test/level_test.cpp build/Level.o build/LevelLoader.o -o run_tests $(LDFLAGS)
	./run_tests

