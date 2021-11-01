
INCLUDE = ../../include
SRC = ../../src

CC = g++
CFLAGS = -std=c++11 -Wall -g -Werror -I$(INCLUDE)
LDFLAGS = -lm

OBJS = lsh.o $(SRC)/functions.o $(SRC)/hash_table.o $(SRC)/hash_functions.o $(SRC)/algorithms.o
EXEC = lsh.out

# Arguments for make run / make valgrind
ARGS = -i ../../input_small_id -q ../../query_small_id -k 4 -L 5 -o ../../outputfile -N 1 -R 10000

$(EXEC): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

valgrind: $(EXEC)
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./$(EXEC) $(ARGS)
