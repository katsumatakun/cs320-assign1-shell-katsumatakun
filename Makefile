
all: myecho myshell lls

myecho: echo.c
	gcc -o myecho echo.c

myshell: myshell.c
	gcc -o myshell myshell.c

pathtest: path_test.c
	gcc -o pathtest path_test.c

lls: lls.c
	gcc -o lls lls.c

clean:
	rm -rf myecho myshell lls pathtest
