CC = gcc
TARGET = server 
SRC = main.c
     
CFLAGS =
FLAGS =
LIBS =  -lpthread


OBJ = $(SRC:%.cpp=%.o)

%.cpp.o: 
	$(CC) -c $(CFLAGS) $<  -o $@ 
$(TARGET): $(OBJ)
	$(CC) $(FLAGS)  -o $(TARGET) $(OBJ) $(LIBS)
clean:
	rm *.o $(TARGET) 
