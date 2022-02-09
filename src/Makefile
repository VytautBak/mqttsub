CC:=gcc
BIN:=mqttsub
SRC:=$(wildcard *.c)
OBJ:=$(SRC:.c=.o)
LDFLAGS:= -lmosquitto -lssl -lcrypto -luci -lcurl -largp -lsqlite3 -ljson-c
CPPFLAGS:= 
CFLAGS:= 


.PHONY: all clean install uninstall

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS)
clean:
	$(RM) $(BIN) $(OBJ)
