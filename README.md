# About
Code written for course CSI4900 (Honours Project) by Matthew Demczyk. Code implements Algorithm X and the Dancing Links data structure as defined in Donald Knuth's The Art of Computer Programming, Volume 4, Fascicle 5.

# File Descriptions
All source files are in ./src/

**ExactCover.c** : functions to solve exact cover problems using Dancing Links and Algorithm X.

**exact_cover_unit_tests.c** : 3 unit tests for the functions in *ExactCover.c*

**Sudoku.c** : Functions that use functions from *ExactCover.c* to solve Sudoku problems

**sudoku_unit_tests.c** : Still need to implement this. But will include unit tests for *Sudoku.c* functions.

**main.c** : Currently prints out time to solve a single puzzle. Will later implement some application of *Sudoku.c*

# Building Instructions
Create an empty folder ./bin/ then:

Run
 >```make main```

 >```make ectest```

 >```make stest```

 to compile *main.c*, *exact_cover_unit_tests.c* or *sudoku_unit_tests.c* respectively