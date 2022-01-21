CC:=gcc
BIN:=mqttsub
SRC:=$(wildcard *.c)
OBJ:=$(SRC:.c=.o)
LDFLAGS:= -Ilib/ -lmosquitto -lssl -lcrypto -luci -lcurl
CPPFLAGS:= 
CFLAGS:= -DWITH_TLS -DWITH_TLS_PSK

PREFIX?=/usr

.PHONY: all clean install uninstall

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS)
clean:
	$(RM) $(BIN) $(OBJ)