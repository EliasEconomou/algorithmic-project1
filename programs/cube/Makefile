
INCLUDE = ../../include
SRC = ../../src

CC = g++
CFLAGS = -std=c++11 -Wall -g -Werror -I$(INCLUDE)
LDFLAGS = -lm

OBJS = cube.o $(SRC)/point_functions.o $(SRC)/hash_table.o $(SRC)/cube_table.o $(SRC)/hash_functions.o $(SRC)/algorithms.o
EXEC = cube.out

# Arguments for make run / make valgrind
ARGS = -i ../../input_small_id -q ../../query_small_id -k 8 -M 150 -probes 2 -o ../../output_cube -N 5 -R 1000


$(EXEC): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

valgrind: $(EXEC)
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./$(EXEC) # ARGS = 
