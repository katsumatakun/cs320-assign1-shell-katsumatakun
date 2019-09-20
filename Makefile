
all: myecho simple lls

myecho: echo.c
	gcc -o myecho echo.c

simple: simple_command.c
	gcc -o simple simple_command.c

pathtest: path_test.c
	gcc -o pathtest path_test.c

lls: lls.c
	gcc -o lls lls.c

clean:
	rm -rf myecho simple lls pathtest
