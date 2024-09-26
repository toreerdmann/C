

all: bin/mkmap bin/find_sqr

bin/mkmap: src/mkmap.c
	mkdir -p bin
	cc src/mkmap.c -o bin/mkmap

bin/find_sqr: src/main.c
	mkdir -p bin
	cc src/main.c -o bin/find_sqr

test1: bin/mkmap bin/find_sqr
	./bin/mkmap 10 10 10 | ./bin/find_sqr

test2: bin/mkmap bin/find_sqr
	./bin/mkmap 100 100 50 | ./bin/find_sqr

test3: bin/mkmap bin/find_sqr
	./bin/mkmap 1000 1000 500 | ./bin/find_sqr > result
	cat result | tr '.ox' '012' | sed 's/./& /g' > result2
	Rscript -e 'png("out.png"); image(matrix(scan("result2"), 1000)); dev.off()'
	rm result result2
	feh out.png && rm out.png


fclean:
	rm bin/*
