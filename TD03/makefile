CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lglfw -lGLU -lGL -lm

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

# Fichiers TD 03

# Fichiers exercice 01
OBJ_TD03_EX01= ex01/td03_ex01.o
EXEC_TD03_EX01= td03_ex01.out

# Fichiers exercice 02
OBJ_TD03_EX02= ex02/td03_ex02.o
EXEC_TD03_EX02= td03_ex02.out


# Regles compilation TD 03

all : ex01 #ex02

ex01 : $(OBJDIR)$(OBJ_TD03_EX01)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD03_EX01) -o $(BINDIR)$(EXEC_TD03_EX01) $(LDFLAGS)

ex02 : $(OBJDIR)$(OBJ_TD03_EX02)
	$(CC) $(CFLAGS) $(OBJDIR)$(OBJ_TD03_EX02) -o $(BINDIR)$(EXEC_TD03_EX02) $(LDFLAGS)


clean :
	rm -rf *~
	rm -rf $(SRCDIR)*/*~
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)*

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p `dirname $@`
	$(CC) -o $@ -c $< $(CFLAGS)
