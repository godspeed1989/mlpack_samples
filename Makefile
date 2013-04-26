CC=g++

DIR=/myopt/mlpack-1.0.4
LIBS = -L$(DIR)/lib -lmlpack
CPPFLAGS = -I$(DIR)/include -Wall -g
TARGET = timer

LIBS += `xml2-config --libs`
CPPFLAGS += `xml2-config --cflags`

LIBS += -larmadillo

all: $(TARGET)

$(TARGET).o: $(TARGET).cpp

$(TARGET): $(TARGET).o
	$(CC) $+ $(LIBS) -o $@

clean:
	rm -rf *.o $(TARGET)

