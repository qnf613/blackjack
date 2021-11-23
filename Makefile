CC = g++
CFLAGS = -I. -Wall -Wextra -Werror -g -pedantic -std=c++11 -fbounds-check -O2
DEPS = YOUR HEADERS HERE
OBJ =  main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

app: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm *.o app
