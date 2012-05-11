TIME=/usr/bin/time -p
CFLAGS=-O4
CC=clang
PROGS=\
siracusa-performante \
siracusa-optm-1 \
siracusa-optm-2 \
siracusa-optm-3 \
siracusa-optm-4 \
siracusa-lnds-1 \
siracusa-lnds-2 \

RUNS=\
1000000 \
5000000 \
10000000 \
50000000 \
100000000 \
500000000 \
1000000000 \

all: test

compile: $(PROGS)

clean:
	rm -f $(PROGS) *.txt

test: compile
	for n in $(RUNS); do \
		echo "n = $$n"; \
		cat /dev/null > run-$$n.txt; \
		for prog in $(PROGS); do \
			printf "%20s %10s " $$prog $$n >> run-$$n.txt; \
			$(TIME) ./$$prog $$n > tmp.txt 2>&1; \
			printf "%10s %s %s " `head -1 tmp.txt` $(CC) $(CFLAGS) >> run-$$n.txt; \
			grep real tmp.txt | awk '{print $$2}' >> run-$$n.txt; \
			tail -1 run-$$n.txt; \
			done; \
		echo; \
	done
