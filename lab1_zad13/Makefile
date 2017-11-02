CC=gcc
CFLAGS=-fPIC -Wall -c -I
LFLAGS=-shared 
SRC=./src
LIB=${PWD}/lib
#w celu umozliwienia dzialania programu bez uprawnien administratora zapisuje biblioteke w pwd/lib. Program mozna wywolac z dowolnego miejsca.
BIN=./bin
INC=./include
LIBNAME=sysusrinfolib

zad13: $(LIBNAME).so
	$(CC) $(SRC)/main.c -L. $(LIB)/$(LIBNAME).so -o $(BIN)/zad13
	export LD_LIBRARY_PATH="$(LIB):$(LD_LIBRARY_PATH)"
$(LIBNAME).so:	func.o
	$(CC) $(LFLAGS) func.o -o $(LIB)/$(LIBNAME).so
	rm *.o
func.o: 
	$(CC) $(CFLAGS) $(INC) $(SRC)/func.c
clean:	
	rm $(BIN)/zad13 $(LIB)/$(LIBNAME).so 
