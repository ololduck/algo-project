CC=gcc
CCOPTS=-Wall -ansi

OUTDIR=./
OUTBIN=Index
OUT=$(OUTDIR)$(OUTBIN)

RM=rm

SRCD=src/
SRC=$(SRCD)celmot.c $(SRCD)celpos.c $(SRCD)cellule.c

all: release

release: $(SRC)
	$(CC) $(CCOPTS) -o $(OUT) -O3 $(SRCD)main.c $(SRC)

debug: $(SRC)
	$(CC) $(CCOPTS) -o $(OUT) -g $(SRCD)main.c $(SRC)

tests:
	$(CC) $(CCOPTS) -o $(OUTDIR)tests -g $(SRCD)tests.c $(SRC)
	./tests

clean: $(OUT)
	@$(RM) $(OUT)
