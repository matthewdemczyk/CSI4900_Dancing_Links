main:
	gcc -x c -Wall ./src/main.c -o ./bin/main

ectest:
	gcc -x c -Wall ./src/exact_cover_unit_tests.c -o ./bin/ectest

stest:
	gcc -x c -Wall ./src/sudoku_unit_tests.c -o ./bin/stest

