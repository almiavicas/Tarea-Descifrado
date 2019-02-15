#Compilador
COMP = gcc -c
LINK = gcc

OBJDIR = objects
#Programas intermedios
OBJECTS = $(OBJDIR)/ordered_list.o $(OBJDIR)/schema.o $(OBJDIR)/main.o

#Programa
PROGRAM = program

.PHONY: all clean

all: $(PROGRAM)

clean:
	rm $(PROGRAM)
	rm $(OBJECTS)
	rmdir $(OBJDIR)

$(PROGRAM): $(OBJECTS)
	$(LINK) -o $(PROGRAM) $(OBJECTS)

$(OBJDIR)/main.o: main.c $(OBJDIR) ordered_list.h schema.h
	$(COMP) -o $(OBJDIR)/main.o main.c

$(OBJDIR)/ordered_list.o: ordered_list.c $(OBJDIR) ordered_list.h
	$(COMP) -o $(OBJDIR)/ordered_list.o ordered_list.c

$(OBJDIR)/schema.o: schema.c $(OBJDIR) schema.h
	$(COMP) -o $(OBJDIR)/schema.o schema.c

$(OBJDIR):
	mkdir $(OBJDIR)