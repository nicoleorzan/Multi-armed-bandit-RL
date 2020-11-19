EXE = a.out
CXX = c++
CFLAGS = -I include -g -std=c++11 -Wall -Wextra

SRC = mainNormal.cc src/Bandit.cc src/NormalBandit.cc src/Experiment.cc
OBJ=$(SRC:.cc=.o)
INC = $(wildcard *.h)

all: $(EXE)

clean:
	$(info clean up)
	@rm -rf $(OBJ) $(EXE) src/*~ include/*~ *~ 
	
.PHONY: clean

%.o: %.cc
	$(CXX) -c $< -o $@ $(CFLAGS)

$(EXE): $(OBJ)
	$(CXX) $^ -o $(EXE)

main.o: include/NormalBandit.h include/Bandit.h include/Experiment.h

src/Bandit.o: include/Bandit.h
src/NormalBandit.o: include/Bandit.h include/NormalBandit.h
src/Experiment.o: include/Bandit.h include/Experiment.h
