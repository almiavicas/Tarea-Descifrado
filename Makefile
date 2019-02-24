#Compilador
COMP = gcc -c
LINK = gcc

OBJDIR = objects
#Programas intermedios
OBJECTS = $(OBJDIR)/ordered_list.o $(OBJDIR)/schema.o $(OBJDIR)/main.o
DEPEND = $(OBJDIR)/main.o

#Programa
PROGRAM = program

.PHONY: all clean

all: $(PROGRAM)

clean:
	rm $(PROGRAM)
	rm $(OBJECTS)
	rmdir $(OBJDIR)

$(PROGRAM): $(OBJECTS)
	$(LINK) -o $(PROGRAM) $(DEPEND)

$(OBJDIR)/main.o: main.c $(OBJDIR) ordered_list.c schema.c
	$(COMP) -o $(OBJDIR)/main.o main.c

$(OBJDIR)/ordered_list.o: ordered_list.c $(OBJDIR) ordered_list.h error.h
	$(COMP) -o $(OBJDIR)/ordered_list.o ordered_list.c

$(OBJDIR)/schema.o: schema.c $(OBJDIR) schema.h
	$(COMP) -o $(OBJDIR)/schema.o schema.c

$(OBJDIR):
	mkdir $(OBJDIR)
