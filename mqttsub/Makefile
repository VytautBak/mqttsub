CC:=gcc
BIN:=mqttsub
SRC:=$(wildcard *.c)
OBJ:=$(SRC:.c=.o)
LDFLAGS:= -luci -lcurl
CPPFLAGS:= 

PREFIX?=/usr

.PHONY: all clean install uninstall

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS)
clean:
	$(RM) $(BIN) $(OBJ)