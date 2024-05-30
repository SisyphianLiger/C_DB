TARGET = bin/out
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

run: clean default
		./$(TARGET) -f ./mydb.db -n 
		./$(TARGET) -f ./mydb.db -a "Timmy H.,123 Sheshire Ln.,120" 
		./$(TARGET) -f ./mydb.db -a "Timmy H.,123 Sheshire Ln.,120" 
		./$(TARGET) -f ./mydb.db -a "Timmy H.,123 Sheshire Ln.,120" 

default: $(TARGET)

clean:
		rm -f obj/*.o
		rm -f bin/*
		rm -f ./mydb.db

$(TARGET): $(OBJ)
		gcc -o $@ $?

obj/%.o : src/%.c
		gcc -c $< -o $@ -Iinclude

