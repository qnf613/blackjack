CC = g++
CFLAGS = -I. -Wall -Wextra -Werror -g -std=c++11 -fbounds-check -O2
DEPS = utils.h logic.hpp
OBJ =
MAIN =  main.o
TEST = test.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

app: $(MAIN) $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

apptest: $(TEST) $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm *.o app apptest
