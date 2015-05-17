default: fizzbuzz

fizzbuzz.o: fizzbuzz.c
	gcc -c fizzbuzz.c -o fizzbuzz.o

fizzbuzz: fizzbuzz.o
	gcc fizzbuzz.o -o fizzbuzz

clean:
	-rm -f fizzbuzz.o
	-rm -f fizzbuzz
