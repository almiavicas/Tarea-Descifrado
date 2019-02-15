#Compilador
COMP = cc -c
LINK = cc

OBJDIR = objects
#Programas intermedios
OBJECTS = $(OBJDIR)/ordered_list.o $(OBJDIR)/schema.o $(OBJDIR)/main.o

#Programa
PROGRAM = program

.PHONY: all clean

dependencies:
	$(COMP) ordered_list.c ordered_list.h

all: $(PROGRAM)

clean:
	rm $(PROGRAM)
	rm $(OBJECTS)
	rmdir $(OBJDIR)

$(PROGRAM): $(OBJECTS)
	$(LINK) $(OBJECTS) -o $(PROGRAM)

$(OBJDIR)/main.o: main.c $(OBJDIR) ordered_list.h schema.h
	$(COMP) main.c -o $(OBJDIR)/main.o

$(OBJDIR)/ordered_list.o: ordered_list.c $(OBJDIR) ordered_list.h
	$(COMP) ordered_list.c -o $(OBJDIR)/ordered_list.o

$(OBJDIR)/schema.o: schema.c $(OBJDIR) schema.h
	$(COMP) schema.c -o $(OBJDIR)/schema.o

$(OBJDIR):
	mkdir $(OBJDIR)