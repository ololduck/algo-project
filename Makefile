CC=gcc
CCOPTS=-Wall -ansi

OUTDIR=./
OUTBIN=Index
OUT=$(OUTDIR)$(OUTBIN)

SRCD=src/
SRC=$(SRCD)celmot.c $(SRCD)celpos.c $(SRCD)cellule.c

all: release

release: $(SRC) bump_version
	$(CC) $(CCOPTS) -o $(OUT) -O3 $(SRCD)main.c $(SRC)

debug: $(SRC) bump_version
	$(CC) $(CCOPTS) -o $(OUT) -g $(SRCD)main.c $(SRC)

tests:
	$(CC) $(CCOPTS) -o $(OUTDIR)tests -g $(SRCD)tests.c $(SRC)
	./tests

bump_version: $(SRCD)version.h
	gitversion_c.py $(SRCD)version.h
