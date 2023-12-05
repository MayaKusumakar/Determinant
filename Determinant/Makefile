determinant.out: main.o matrix.o 
	gcc -g -Wall -Werror -o determinant.out main.o matrix.o -lm

matrix.o: matrix.c matrix.h
	gcc -g -Wall -Werror -c -o matrix.o matrix.c -lm

main.o: main.c matrix.h
	gcc -g -Wall -Werror -c -o main.o main.c -lm

clean:
	rm -f *.out *.o

run: determinant.out
	./determinant.out