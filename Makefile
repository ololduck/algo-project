CC=gcc
CCOPTS=-Wall -ansi

OUTDIR=./
OUTBIN=Index
OUT=$(OUTDIR)$(OUTBIN)

RM=rm

SRCD=src/
SRC=$(SRCD)structs/celmot.c $(SRCD)structs/celpos.c $(SRCD)structs/cellule.c $(SRCD)hachage.c $(SRCD)parsing.c $(SRCD)wordqueries.c

all: release

release: $(SRC)
	$(CC) $(CCOPTS) -o $(OUT) -O3 $(SRCD)main.c $(SRC)

debug: $(SRC)
	$(CC) $(CCOPTS) -o $(OUT) -g $(SRCD)main.c $(SRC)

tests: $(SRC)
	for f in `ls tests`; do $(CC) $(CCOPTS) -o $(OUTDIR)tests/$$f -g tests/$$f $(SRC) && ./$(OUTDIR)tests/$$f; done

clean: $(OUT)
	@$(RM) $(OUT)
