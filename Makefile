
all: myecho simple

myecho: echo.c
	gcc -o myecho echo.c

simple: simple_command.c
	gcc -o simple simple_command.c
clean:
	rm -rf myecho simple
