CFLAGS := -Wextra -Werror -Wall -Wimplicit -pedantic -Wreturn-type -Wformat -std=c89

all: palette_gen palette_read

palette_gen: palette_gen.c palette_load.c
	gcc $(CFLAGS) palette_gen.c palette_load.c -o palette_gen
palette_read: palette_read.c
	gcc $(CFLAGS) palette_read.c -o palette_read

clean:
	rm -rf *.o palette_gen palette_read

