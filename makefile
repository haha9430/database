main.exe: main.o database.o
	g++ -o main.exe main.o database.o

main.o: main.cpp
	g++ -Werror -c main.cpp

database.o: database.cpp
	g++ -Werror -c database.cpp