CC = gcc #Déclaration de variables
DEBUG = yes
SRC = $(wildcard *.c)#Génération de la liste des fichiers sources
EXE = prog
OBJ = $(SRC:.c=.o) 
ifeq ($(DEBUG), yes) #Condtions
$(info "Debug activé")
CFLAGS = -g -Wall -Wextra
else
CFLAGS = -Wall -Wextra
endif

LIB=-lm 

all: $(OBJ)
	@echo "Compilation"
	@$(CC) -o $(EXE) $^ $(LIB)

%.o:%.c
	@$(CC) -c $< $(CFLAGS)

# prog : tp4.o rabbit_simu.o lapin.o
# 	$(CC) tp4.o rabbit_simu.o lapin.o -o prog

# tp4.o : tp4.c tp4.h
# 	$(CC) -c tp4.c


lapin.o : lapin.c lapin.h
	$(CC) -c lapin.c

	
rabbit_simu.o : rabbit_simu.c rabbit_simu.h
	$(CC) -c rabbit_simu.c

clean:
	rm *.o

