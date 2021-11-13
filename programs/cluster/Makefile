
INCLUDE = ../../include
SRC = ../../src

CC = g++
CFLAGS = -std=c++11 -Wall -g -Werror -I$(INCLUDE)
LDFLAGS = -lm

OBJS = cluster.o $(SRC)/point_functions.o $(SRC)/cluster_methods.o $(SRC)/hash_table.o $(SRC)/cube_table.o $(SRC)/hash_functions.o $(SRC)/algorithms.o
EXEC = cluster.out

# Arguments for make run / make valgrind
# Το complete στις παραμέτρους του cluster είναι "optional" για το αν το αρχείο θα τυπώνει τα διανύσματα του κάθε cluster η όχι
ARGS = -i ../../dataset.txt -c ../../cluster.conf -o ../../outputfile -complete -m Classic

$(EXEC): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

valgrind: $(EXEC)
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./$(EXEC) $(ARGS)
