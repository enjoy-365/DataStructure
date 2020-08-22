CC = g++
CXXFLAGS = -g -Wall -std=c++11

SRCS := $(wildcard src/*.cc)
OBJS := $(SRCS:.CC=.O)
BIN = ./bin/
INC = ./include/
LIB = ./lib/ -lpthread

CPPFLAGS += -I$(INC)

TARGET = print_hello
$(TARGET): (OBJS)
    $(CC) $(CXXFLAGS) $(CPPFLAGS) -o $(BIN)$(TARGET) $(OBJS) -L$(LIBS)

clean:
    rm $(BIN)$(TARGET) $(OBJS)
