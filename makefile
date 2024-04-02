main.exe: main.o database.o database.h
	g++ -o main.exe main.o database.o

main.o: main.cpp
	g++ -Werror -c main.cpp

database.o: database.cpp database.h
	g++ -Werror -c database.cpp
