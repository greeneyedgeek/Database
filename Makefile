# define the C compiler to use
CC       = gcc
# define comipler flags
CFLAGS   = -std=c11 -Wall -fmax-errors=10 -Wextra
# define library paths in addition to /usr/lib
LFLAGS   =
# define libraries to use
LIBS     = stdio stdbool stdlib string
# define the object files that this project needs
OBJFILES = database.o command_processor.o
# define the name of the executable file
MAIN     = database

# all of the below is generic - one typically only adjusts the above
all: $(MAIN)

$(MAIN): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJFILES)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJFILES) $(MAIN)

launch: $(MAIN)
	./$(MAIN)
