##### Variables

SRCDIR = ../src ../test
#SRCDIR = src test
INCDIR = -I/usr/include -I../src -I../test
#INCDIR = -I/usr/include -Isrc -Itest
CPPFLAGS = -g -Wall -W $(INCDIR) 
LFLAGS = -lm -lpthread -lwiringPi
CC = gcc

##### Files

SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c,%.o,$(wildcard *.c))
TARGET = sdieh

##### Build rules

all: $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) $(LFLAGS) -o $(TARGET)

import:
	@rm -f *.c *~
	@for dir in $(SRCDIR); do find $$dir -name \*.c -exec ln -s {} \; ; done

depend:
	@makedepend $(INCDIR) -Y -m $(SOURCES) 2> /dev/null

clean:
	@rm -f *.o *.bak *~ *%

##### End of Makefile
# DO NOT DELETE

aaa.o: ../src/aaa.h /usr/include/stdio.h /usr/include/features.h
aaa.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
main.o: /usr/include/stdio.h /usr/include/features.h /usr/include/libio.h
main.o: /usr/include/_G_config.h /usr/include/wchar.h ../src/params.h
main.o: ../src/sdisys.h ../src/aaa.h
motorctrl.o: /usr/include/stdio.h /usr/include/features.h
motorctrl.o: /usr/include/libio.h /usr/include/_G_config.h
motorctrl.o: /usr/include/wchar.h ../src/motorctrl.h
params.o: ../src/params.h /usr/include/stdlib.h /usr/include/features.h
params.o: /usr/include/alloca.h /usr/include/malloc.h /usr/include/stdio.h
params.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
sdi_coref.o: ../src/sdi_coref.h /usr/include/stdio.h /usr/include/features.h
sdi_coref.o: /usr/include/libio.h /usr/include/_G_config.h
sdi_coref.o: /usr/include/wchar.h
sdisys.o: ../src/sdisys.h /usr/include/stdio.h /usr/include/features.h
sdisys.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
