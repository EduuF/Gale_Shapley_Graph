#Para escrever comentários ##
############################# Makefile ##########################
all: tp01
tp01: main.o
        # O compilador faz a ligação entre os dois objetos
	g++ -o tp01.exe main.cpp
#-----> Distancia com o botão TAB ### e não com espaços
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm *.o
