
all: myecho

myecho: echo.c
	gcc -o myecho echo.c
clean:
	rm -rf myecho
