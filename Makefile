
all: myecho simple pathtest

myecho: echo.c
	gcc -o myecho echo.c

simple: simple_command.c
	gcc -o simple simple_command.c

pathtest: path_test.c
	gcc -o pathtest path_test.c

clean:
	rm -rf myecho simple pathtest
