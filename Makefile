# Makefile for libGtkmmOpenGL

CC = g++
CFLAGS = -O0 -g -I. -c -DLINUX \
		-I $(shell pkg-config --cflags  gtkmm-2.4) \
		-I $(shell pkg-config --cflags  gtkglext-1.0)
		
OUT = ../Debug/libGtkmmOpenGL.a

OBJS =	GLDrawingArea.o \
		GLStdafx.o \
		GLWindow.o \
		GtkmmOpenGL.o

all:	createLibrary

createLibrary:	$(OBJS)
		ar rcs $(OUT) $(OBJS) 
.cpp.o:
	$(CC) $(CFLAGS) -o $*.o $*.cpp

clean:
	rm -f $(OBJS) $(OUT) *~
