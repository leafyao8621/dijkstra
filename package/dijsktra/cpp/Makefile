CPP = g++
SRC = src/test.cpp $(wildcard src/*/*.cpp)
OBJ = $(SRC:.cpp=.o)
FLAGS = -Wall -Wextra -Werror -pedantic
BIN = test

%.o: %.cpp
	$(CPP) $(FLAGS) -g -c $< -o $@

$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o $(BIN)

.PHONY: clean
clean:
	@rm $(OBJ)
	@rm $(BIN)
