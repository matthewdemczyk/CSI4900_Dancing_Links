# About
Code written for course CSI4900 (Honours Project) by Matthew Demczyk in Fall 2021, supervised by Professor Lucia Moura at the University of Ottawa. Code implements Algorithm X and the Dancing Links data structure as defined in Donald Knuth's The Art of Computer Programming, Volume 4, Fascicle 5. Also implements hill climbing and simulated annealing heuristic searches to generate new puzzles with as few clues as possible.

# C Code Descriptions
All C source files are in ./src/

**ExactCover.c** : functions to solve exact cover problems using Dancing Links and Algorithm X.

**exact_cover_unit_tests.c** : 3 unit tests for the functions in *ExactCover.c*.

**Sudoku.c** : Functions that use functions from *ExactCover.c* to solve Sudoku problems.

**sudoku_unit_tests.c** : Unit tests for *Sudoku.c* functions.

**test_solve_time.c** : Function to print out time that it takes to solve one 17-clue puzzle using *Sudoku.c*.

**solve.c** : Code used to solve a large file of puzzles using *Sudoku.c*. Currently solves the expert puzzles in ./original_puzzles/expert.txt , but you can modify the code to solve any file of puzzles.

**opt.c** : Hill climbing and simulated annealing heuristic searches are in this file. Uses *Sudoku.c* to determine if puzzles have a unique solution during the searches.

**hc_job.c** : Code that was ran on the 20 virtual machines to generate puzzles via hill climbing. The generated puzzles can be found in ./hill_climb_results/ . Before using this, you will need to create a file called inpuzzles.txt in the directory you run this from, which is a list of completely solve sudoku puzzles that the hill climbing will be performed on.

**sa_job.c** : Code that was ran on the 20 virtual machines to generate the puzzles found in ./simulated_annealing_results/ . Before using this, you will need to create a file called inpuzzles.txt in the directory you run this from, which is a list of completely solve sudoku puzzles that the simulated annealing will be performed on.

# Puzzle Folder Descriptions

*./hill_climb_results/* : Puzzles generated with the hill climbing heuristic search.

*./simulated_annealing_results/* : Puzzles generated with the simulated annealing heuristic search.

*./chunked_puzzles/* : Solved puzzles that were broken up into 20 groups to be run on each of the 20 virual machines the test were run on.

*./chunked_puzzles_originals/* : Original (unsolved, incomplete) puzzles that were broken up into 20 groups to be run on each of the 20 virual machines the test were run on.

*./original_puzzles/* : Same puzzles as in *./chunked_puzzles_originals/* but not chunked into 5 files for each difficulty.

*./solved_puzzles/* : Same puzzles as in *./chunked_puzzles/* but not chunked into 5 files for each difficulty.

# Other Files and Folder

*./bin/* : Compiled C source code from *./src/*

*./memdump/* : Created by the memdump function in *ExactCover.c*, this is the contents of a dancing links data structure when memdump is called. This was used in debugging/testing.

*calculate_stats.py* : Python script to calculate statistics from the generated puzzles from hill climbing and simulated annealing. This script creates the *hillclimb_results.csv* and *simulated_annealing_results.csv* files.

*sudoku17.txt* : The archived collection of 17-clue puzzles collected by Gordon Royle. Retrieved from here https://web.archive.org/web/20190903212614/http://staffhome.ecm.uwa.edu.au/~00013890/sudoku17

*sudoku17_solutions.txt* : All of the *sudoku17.txt* puzzles solved during *sudoku_unit_tests.c*.

# Building Instructions

Run

>```make ectest```

>```make stest```

>```make solve```

>```make test_solve_time```

>```make hc_job```

>```make sa_job```

 to compile *exact_cover_unit_tests.c*, *sudoku_unit_tests.c*, *solve.c*, *test_solve_time.c*, *hc_job.c*, *sa_job.c*, respectively