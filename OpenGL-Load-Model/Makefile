CPP      = g++
OBJ      = main
LINKOBJ  = main
LIBS     = -lGL -lGLU -lglut
BIN      = load_model
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

main: main.cpp
	$(CPP) main.cpp -o main -std=c++11 -lGL -lGLU -lglut
	./main
	make clean
