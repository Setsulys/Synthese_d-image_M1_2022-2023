CC      = gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lglfw -lGLU -lGL -lm

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

# Fichiers TD 01
OBJ_TD01_EX03 = ex03/td01_ex03.o
EXEC_TD01_EX03 = td01_ex03.out
# Fichiers exercice 02
OBJ_TD01_EX02= ex02/td01_ex02.o
EXEC_TD01_EX02= td01_ex02.out
# Fichiers exercice 04
OBJ_TD01_EX04= ex04/td01_ex04.o
EXEC_TD01_EX04= td01_ex04.out
# Regles compilation TD 01

all :

ex02 : $(OBJDIR)$(OBJ_TD01_EX02)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD01_EX02) -o $(BINDIR)$(EXEC_TD01_EX02) $(LDFLAGS)

ex03 : $(OBJDIR)$(OBJ_TD01_EX03)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD01_EX03) -o $(BINDIR)$(EXEC_TD01_EX03) $(LDFLAGS)

ex04 : $(OBJDIR)$(OBJ_TD01_EX04)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD01_EX04) -o $(BINDIR)$(EXEC_TD01_EX04) $(LDFLAGS)

clean :
	rm -rf *~
	rm -rf $(SRCDIR)*/*~
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)*

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p `dirname $@`
	$(CC) -o $@ -c $< $(CFLAGS)
