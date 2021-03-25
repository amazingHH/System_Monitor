CC = gcc
CXX = g++
CFLAGS = -Wall -O -g
TARGET = ./IPC
MKDIR = mkdir
DIR_OBJS = ./obj
DIR_EXEC = ./exec
DIR_SRC = src
OBJECT = obj
EXECUTE = exec
DIRS := $(DIR_OBJS) $(DIR_EXEC)
LIBS = -lpthread
 
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ 
 
%.o:%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@
 
SOURCES = $(wildcard *.c $(DIR_SRC)/*.cpp)
 
OBJS = $(patsubst %.cpp,%.o,$(SOURCES))


$(TARGET):$(OBJS)
	mkdir -p $(DIRS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)
	chmod a+x $(TARGET)
	cp $(DIR_SRC)/*.o $(OBJECT)
	cp $(TARGET) $(DIR_EXEC)
	rm -rf $(DIR_SRC)/*.o
	rm -rf $(TARGET)


clean:
	rm -rf $(DIR_SRC)/*.o
	rm -rf obj
	rm -rf exec


