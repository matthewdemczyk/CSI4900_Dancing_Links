ectest:
	gcc -x c -Wall ./src/exact_cover_unit_tests.c -o ./bin/ectest

stest:
	gcc -x c -Wall ./src/sudoku_unit_tests.c -o ./bin/stest

solve:
	gcc -x c -Wall ./src/solve.c -o ./bin/solve

hc_job:
	gcc -x c -Wall ./src/hc_job.c -o ./bin/hc_job -lm

sa_job:
	gcc -x c -Wall ./src/sa_job.c -o ./bin/sa_job -lm

test_solve_time:
	gcc -x c -Wall ./src/test_solve_time.c -o ./bin/test_solve_time -lm