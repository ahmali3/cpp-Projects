test: main.o Database.o Menu.o
	g++ -o test main.o Database.o Menu.o

main: main.cpp
	g++ -c main.cpp

Database: Database.h Database.cpp
	g++ -c Database.cpp

Menu: Menu.h Menu.cpp
	g++ -c Menu.cpp

clean:
	rm -f test main.o Database.o Menu.o

CPPFLAGS= -std=c++14 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g
