IDIR = ../../models/hidapi
ODIR = obj

CC = gcc
CFLAGS = -I$(IDIR) -g -Wall
LIBS = -lpthread

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = HIDScanner.o hidapi.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

ifeq ($(shell uname), Linux)
	CFLAGS += -I/usr/include/libusb-1.0
	LIBS += -lusb-1.0 -lrt
else
	LIBS += -framework IOKit -framework CoreFoundation
endif

$(ODIR)/%.o: src/%.c $(DEPS) $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

hidScan: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(ODIR):
	mkdir $(ODIR)

clean:
	rm -rf $(ODIR) hidScan
