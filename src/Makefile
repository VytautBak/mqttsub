CC:=gcc
BIN:=mqttsub
SRC:=$(wildcard *.c)
OBJ:=$(SRC:.c=.o)
LDFLAGS:= -lmosquitto -lssl -lcrypto -luci -lcurl -largp -lsqlite3 -lcjson
CPPFLAGS:= 
CFLAGS:= -g

PREFIX?=/usr

.PHONY: all clean install uninstall

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -g $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS)
clean:
	$(RM) $(BIN) $(OBJ)
