CROSS_COMPILE?=

LIBDIR_APP_LOADER?=../app_loader/lib
INCDIR_APP_LOADER?=../app_loader/include
BINDIR?=../bin

CFLAGS+= -Wall -std=c99 -I$(INCDIR_APP_LOADER) -D__DEBUG -g3 -O2 -mtune=cortex-a8 -march=armv7-a -lm -pthread
LDFLAGS+=-L$(LIBDIR_APP_LOADER) -lprussdrv
OBJDIR=obj
TARGET=$(BINDIR)/main

_DEPS =
DEPS = $(patsubst %,$(INCDIR_APP_LOADER)/%,$(_DEPS))

_OBJ =  buffer_1.o calculations.o pir_ringbuff.o input.o kiss_fftr.o kiss_fft.o 
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))


$(OBJDIR)/%.o: %.c $(DEPS)
	@mkdir -p obj
	$(CROSS_COMPILE)gcc $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	$(CROSS_COMPILE)gcc $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -rf $(OBJDIR)/ *~  $(INCDIR_APP_LOADER)/*~  $(TARGET)
