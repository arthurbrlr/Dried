CC = g++
CFLAGS = -std=c++17 -stdlib=libc++ -Iheaders -Iimgui -Ilua
EXEC = run
SRCDIR := .
OBJDIR := .
SRCS   := $(shell find $(SRCDIR) -name "*.cpp")
OBJ_FILES = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
LIBS = -llua -lpthread -lglfw3 -lGLEW -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo


all : $(EXEC)
all :
	./run

debug: CFLAGS += -DDEBUG
debug: all

clean :
	rm $(EXEC) $(OBJ_FILES)

iClean :
	rm -f ./*.ppm ./*.jpeg

w:
	rm -f ./src/World/*.o
w: all

$(EXEC) : $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

install :
	cp $(EXEC) $(INSTALL_DIR)
