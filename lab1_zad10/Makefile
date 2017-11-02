OBJ= main.o
#parametry wywołania
FLAGS = -Wall
#rodzaj kompilatora
CC = gcc


#kompilacja programu, $@ oznacza nazwę programu(zad7)
who: $(OBJ)
	$(CC) $(OBJ) -o $@

#tworzenie obiektów z plików *.c bez linkowania $< oznacza nazwe pliku, który wywołał akcję
%.o:%.c
	$(CC) $(FLAGS) -c $<

#czyszczenie w przypadku niepoprawnego wywołania którejkolwiek z komend
clean:
	rm *.o $@
