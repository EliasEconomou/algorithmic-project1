
INCLUDE = ../../include
SRC = ../../src

CC = g++
CFLAGS = -Wall -g -Werror -I$(INCLUDE)
LDFLAGS = -lm

OBJS = hypercube.o $(SRC)/point_functions.o
EXEC = hypercube.out

# ARGS = TODO

$(EXEC): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

valgrind: $(EXEC)
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./$(EXEC) # ARGS = 
