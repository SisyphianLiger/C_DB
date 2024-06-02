TARGET = bin/out
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

run: clean default
		./$(TARGET) -f ./mydb.db -n 
		./$(TARGET) -f ./mydb.db -a "Timmy H.,123 Sheshire Ln.,1" 
		./$(TARGET) -f ./mydb.db -a "Jake H.,123 Sheshire Ln.,2" 
		./$(TARGET) -f ./mydb.db -a "Jason H.,123 Sheshire Ln.,3" 
		./$(TARGET) -f ./mydb.db -u "Timmy H." "9" 
		./$(TARGET) -f ./mydb.db -u "Timmy" "9" 
		./$(TARGET) -f ./mydb.db -l 

default: $(TARGET)

clean:
		rm -f obj/*.o
		rm -f bin/*
		rm -f ./mydb.db

$(TARGET): $(OBJ)
		gcc -o $@ $?

obj/%.o : src/%.c
		gcc -c $< -o $@ -Iinclude

