
INCLUDE = ../../include
SRC = ../../src

CC = g++
CFLAGS = -Wall -g -I$(INCLUDE)
LDFLAGS = -lm

OBJS = hypercube.o $(SRC)/functions.o
EXEC = hypercube.out

# ARGS = 

$(EXEC): $(OBJS) $(LIBS)
	$(CC) $(OBJS) $(LIBS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

valgrind: $(EXEC)
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./$(EXEC) # ARGS = 
