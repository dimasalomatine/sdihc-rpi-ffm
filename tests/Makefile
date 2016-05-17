##### Variables

TOP= ..
LIB= $(TOP)/src
INC= $(TOP)/src
BIN= $(TOP)/src
SRC= $(TOP)/src
TST= $(TOP)/test

#SRCDIR = ../src ../test
SRCDIR = ../src
#SRCDIR = src test
INCDIR = -I/usr/include -I../src
# -I/home/dmitry/lwork/lua-5.1.3/src 
# -I../test
#INCDIR = -I/usr/include -Isrc -Itest
CPPFLAGS = -g -Wall -W $(INCDIR) 
LFLAGS = -lm -lpthread -lwiringPi -ldl
# -L/home/dmitry/lwork/lua-5.1.3/src -llua
CC = gcc
CC = g++


##### Files

SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET = sdieh

##### Build rules
default:
	@echo 'Please choose a target: all import depend clean'

all: $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) $(LFLAGS) -o $(TARGET)

import:
	@rm -f *.cpp *~
	@for dir in $(SRCDIR); do find $$dir -name \*.cpp -exec ln -s {} \; ; done
	
depend:
	@makedepend $(INCDIR) -Y -m $(SOURCES) 2> /dev/null

clean:
	@rm -f *.o *.bak *~ *%
	
.PHONY:	default clean


# DO NOT DELETE

sdisys.o: ../src/sdisys.h /usr/include/stdio.h /usr/include/features.h
sdisys.o: /usr/include/stdc-predef.h /usr/include/libio.h
sdisys.o: /usr/include/_G_config.h /usr/include/wchar.h /usr/include/stdlib.h
sdisys.o: /usr/include/alloca.h
params.o: ../src/params.h /usr/include/stdlib.h /usr/include/features.h
params.o: /usr/include/stdc-predef.h /usr/include/alloca.h
params.o: /usr/include/malloc.h /usr/include/stdio.h /usr/include/libio.h
params.o: /usr/include/_G_config.h /usr/include/wchar.h /usr/include/unistd.h
params.o: /usr/include/getopt.h /usr/include/string.h /usr/include/xlocale.h
gyro.o: ../src/gyro.h ../src/gapptypes.h /usr/include/stdio.h
gyro.o: /usr/include/features.h /usr/include/stdc-predef.h
gyro.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
sdi_coref.o: ../src/sdi_coref.h ../src/gapptypes.h ../src/modextern.h
sdi_coref.o: /usr/include/stdio.h /usr/include/features.h
sdi_coref.o: /usr/include/stdc-predef.h /usr/include/libio.h
sdi_coref.o: /usr/include/_G_config.h /usr/include/wchar.h
sdi_coref.o: /usr/include/unistd.h /usr/include/getopt.h
sdi_coref.o: /usr/include/pthread.h /usr/include/endian.h
sdi_coref.o: /usr/include/sched.h /usr/include/time.h /usr/include/stdlib.h
sdi_coref.o: /usr/include/alloca.h /usr/include/semaphore.h
main.o: /usr/include/stdio.h /usr/include/features.h
main.o: /usr/include/stdc-predef.h /usr/include/libio.h
main.o: /usr/include/_G_config.h /usr/include/wchar.h /usr/include/string.h
main.o: /usr/include/xlocale.h ../src/params.h ../src/sdisys.h
main.o: ../src/sdi_coref.h ../src/gapptypes.h ../src/modextern.h
main.o: ../src/gyro.h /usr/include/stdlib.h /usr/include/alloca.h
main.o: /usr/include/unistd.h /usr/include/getopt.h /usr/include/pthread.h
main.o: /usr/include/endian.h /usr/include/sched.h /usr/include/time.h
