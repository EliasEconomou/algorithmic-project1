
INCLUDE = ../../include
SRC = ../../src

CC = g++
CFLAGS = -Wall -g -Werror -I$(INCLUDE)
LDFLAGS = -lm

OBJS = lsh.o $(SRC)/functions.o $(SRC)/hash_table.o
EXEC = lsh.out

# Arguments for make run / make valgrind
ARGS = -i ../../datasetfile -q queryfile -k 4 -L 5 -o outputfile -N 1 -R 10000

$(EXEC): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

valgrind: $(EXEC)
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./$(EXEC) $(ARGS)
