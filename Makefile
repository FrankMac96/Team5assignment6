all: build doc

build: game

doc: 
	@doxygen -g my_proj.conf

game: main.o game.o othello.o
	g++ main.o game.o othello.o -o game

main.o: main.cc
	g++ -c main.cc

game.o: game.cc game.h
	g++ -c game.cc 

othello.o: othello.cc othello.h piece.h colors.h
	g++ -c othello.cc 

clean:
	rm my_proj.conf game main.o game.o othello.o

