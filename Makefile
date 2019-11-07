CC = gcc
RM = rm -f
# déclaration des options du compilateur
CFLAGS = -Wall -g 
CPPFLAGS = -I
LDFLAGS = -lm
# définition des fichiers et dossiers
PROGNAME = som
VERSION = 1.0
distdir = $(PROGNAME)-$(VERSION)
#HEADERS = 
SOURCES = data.c main.c
OBJ = $(SOURCES:.c=.o)
all: $(PROGNAME)
$(PROGNAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROGNAME)
%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ 
clean:
	@$(RM) -r $(PROGNAME) $(OBJ) *~