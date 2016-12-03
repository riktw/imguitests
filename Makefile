RESULT ?= main

IMGUIDIR = imgui
SERIALDIR = serial

SOURCES = \
	  main.cpp \
	  $(IMGUIDIR)/imgui.cpp \
	  $(IMGUIDIR)/imgui_draw.cpp \
	  $(IMGUIDIR)/imgui_demo.cpp \
	  $(IMGUIDIR)/examples/opengl2_example/imgui_impl_glfw.cpp \
	  $(SERIALDIR)/src/serial.cc \
	  $(SERIALDIR)/src/impl/unix.cc \
	  $(SERIALDIR)/src/impl/list_ports/list_ports_linux.cc 

HEADERS = \
	  $(wildcard $(IMGUIDIR)*.h) \
	  $(IMGUIDIR)/examples/opengl2_example/imgui_impl_glfw.h \
	  $(wildcard $(SERIALDIR)/include/serial/*.h) \
	  $(wildcard $(SERIALDIR)/include/serial/impl/*.h)

INCLUDES = \
	 -I$(IMGUIDIR) \
	 -I$(IMGUIDIR)/examples/opengl2_example \
	 -I$(SERIALDIR)/include \
	 -I$(SERIALDIR)/include/serial


LIBS = -lGL `pkg-config --static --libs glfw3` 

CFLAGS += `pkg-config --cflags glfw3` -lGL
CFLAGS += -Wall -O0 -g3 
CFLAGS += $(INCLUDES)

CC = g++

# So that the "build depends on the makefile" trick works no matter the name of
# the makefile
THIS_MAKEFILE := $(lastword $(MAKEFILE_LIST))

all: build

build: $(RESULT)

$(RESULT): $(SOURCES) $(HEADERS) $(THIS_MAKEFILE)
	$(CC) $(CFLAGS) $(SOURCES) $(LIBS) -o $@

%.o: %.cc $(HEADERS) $(THIS_MAKEFILE)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp $(HEADERS) $(THIS_MAKEFILE)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s $(HEADERS) $(THIS_MAKEFILE)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(RESULT)


