OBJS = $(wildcard .$(wildcard src/*.cpp)/*.cpp)
CXX = g++
DEBUG = -g
CXXFLAGS = -std=c++11 
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(OBJS)
	@echo Building main
	$(CXX) $(CXXFLAGS) -o run $(OBJS) $(LIBS)

tetris: $(OBJS)
	@echo Building tetris
	$(CXX) $(CXXFLAGS) -o tetris $(OBJS) $(LIBS)
