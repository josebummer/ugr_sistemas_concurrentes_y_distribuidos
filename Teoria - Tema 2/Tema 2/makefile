SRC = src
INC =
OBJ = obj
BIN = bin
LIB =

all: $(BIN)/prod-consFIFO $(BIN)/prod-consLIFO $(BIN)/fumadores $(BIN)/ej14-1 $(BIN)/ej14-2 $(BIN)/ej16a $(BIN)/ej16b $(BIN)/ej16c $(BIN)/ej17a $(BIN)/ej17b

$(BIN)/prod-consFIFO: $(OBJ)/prod-consFIFO.o
	g++ -o $(BIN)/prod-consFIFO $(OBJ)/prod-consFIFO.o -lrt -lpthread

$(OBJ)/prod-consFIFO.o: $(SRC)/prod-consFIFO.cpp
	g++ -g -c $(SRC)/prod-consFIFO.cpp -o $(OBJ)/prod-consFIFO.o

$(BIN)/ej14-1: $(OBJ)/ej14-1.o
	g++ -o $(BIN)/ej14-1 $(OBJ)/ej14-1.o -lrt -lpthread

$(OBJ)/ej14-1.o: $(SRC)/ej14-1.cpp
	g++ -g -c $(SRC)/ej14-1.cpp -o $(OBJ)/ej14-1.o

$(BIN)/ej14-2: $(OBJ)/ej14-2.o
		g++ -o $(BIN)/ej14-2 $(OBJ)/ej14-2.o -lrt -lpthread

$(OBJ)/ej14-2.o: $(SRC)/ej14-2.cpp
		g++ -g -c $(SRC)/ej14-2.cpp -o $(OBJ)/ej14-2.o

$(BIN)/ej16a: $(OBJ)/ej16a.o
	g++ -o $(BIN)/ej16a $(OBJ)/ej16a.o -lrt -lpthread

$(OBJ)/ej16a.o: $(SRC)/ej16a.cpp
	g++ -g -c $(SRC)/ej16a.cpp -o $(OBJ)/ej16a.o

$(BIN)/ej16b: $(OBJ)/ej16b.o
	g++ -o $(BIN)/ej16b $(OBJ)/ej16b.o -lrt -lpthread

$(OBJ)/ej16b.o: $(SRC)/ej16b.cpp
	g++ -g -c $(SRC)/ej16b.cpp -o $(OBJ)/ej16b.o

$(BIN)/ej16c: $(OBJ)/ej16c.o
	g++ -o $(BIN)/ej16c $(OBJ)/ej16c.o -lrt -lpthread

$(OBJ)/ej16c.o: $(SRC)/ej16c.cpp
	g++ -g -c $(SRC)/ej16c.cpp -o $(OBJ)/ej16c.o

$(BIN)/ej17a: $(OBJ)/ej17a.o
	g++ -o $(BIN)/ej17a $(OBJ)/ej17a.o -lrt -lpthread

$(OBJ)/ej17a.o: $(SRC)/ej17a.cpp
	g++ -g -c $(SRC)/ej17a.cpp -o $(OBJ)/ej17a.o

$(BIN)/ej17b: $(OBJ)/ej17b.o
	g++ -o $(BIN)/ej17b $(OBJ)/ej17b.o -lrt -lpthread

$(OBJ)/ej17b.o: $(SRC)/ej17b.cpp
	g++ -g -c $(SRC)/ej17b.cpp -o $(OBJ)/ej17b.o

$(BIN)/prod-consLIFO: $(OBJ)/prod-consLIFO.o
	g++ -o $(BIN)/prod-consLIFO $(OBJ)/prod-consLIFO.o -lrt -lpthread

$(OBJ)/prod-consLIFO.o: $(SRC)/prod-consLIFO.cpp
	g++ -g -c $(SRC)/prod-consLIFO.cpp -o $(OBJ)/prod-consLIFO.o

$(BIN)/fumadores: $(OBJ)/fumadores.o
	g++ -o $(BIN)/fumadores $(OBJ)/fumadores.o -lrt -lpthread

$(OBJ)/fumadores.o: $(SRC)/fumadores.cpp
	g++ -g -c $(SRC)/fumadores.cpp -o $(OBJ)/fumadores.o

clear:
	rm bin/* obj/*
