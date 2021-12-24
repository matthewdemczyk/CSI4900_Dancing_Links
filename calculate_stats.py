'''
Python script to calculate and compile statistics
from the hill climbing and simulated annealing results
'''


import pandas as pd
import glob
import os


def hamming_distance(puzzle1, puzzle2):
    #transform the puzzles into 0-1 tuples
    puzzle1_01 = [0 if i == '0' else 1 for i in puzzle1]
    puzzle2_01 = [0 if i == '0' else 1 for i in puzzle2]
    ham_dist = 0
    for i in range(81):
        if puzzle1_01[i] != puzzle2_01[i]:
            ham_dist += 1
    return ham_dist


def cost(puzzle):
    return sum([1 for i in puzzle if i != '0'])


def calculate_hill_climb_stats(original_puzzles_path, new_puzzles_path, puzzle_group):
    original_puzzles = []
    with open(original_puzzles_path, 'rt') as f:
        for l in f.readlines():
            original_puzzles.append(l[:-1])

    new_puzzles_lines = []
    with open(new_puzzles_path, 'rt') as f:
        for l in f.readlines():
            new_puzzles_lines.append(l)

    total_hill_climbs = int(''.join([i for i in (new_puzzles_lines[1]).split(':')[1] if i in '1234567890']))
    new_puzzles_lines = new_puzzles_lines[2:] #first 2 lines are the seed and number of hill climbs

    new_puzzles = []
    avg_new_puzzles = []
    max_new_puzzles = []
    for i in new_puzzles_lines:
        line = i[:-1]
        temp_new, temp_avg, temp_max = line.split(',')
        new_puzzles.append(temp_new)
        avg_new_puzzles.append(int(temp_avg)/total_hill_climbs)
        max_new_puzzles.append(int(temp_max))

    #trim original puzzles to the length of computations
    original_puzzles = original_puzzles[:len(new_puzzles)]

    original_cost = [cost(puzzle) for puzzle in original_puzzles]
    new_cost = [cost(puzzle) for puzzle in new_puzzles]
    hamm_distances = [hamming_distance(original_puzzles[i], new_puzzles[i]) for i in range(len(new_puzzles))]
    assert len(new_puzzles) == len(original_puzzles)
    return {
        'Puzzle Group' : puzzle_group,
        'Average Orginal Puzzle Clues' : sum(original_cost)/len(original_cost),
        'Average Minimum Puzzle Clues' : sum(new_cost)/len(new_cost),
        'Average Hamming Distance' : sum(hamm_distances)/len(hamm_distances),
        'Minimum Hamming Distance' : min(hamm_distances),
        'Minumum Puzzle Found' : min(new_cost),
        'Average Hill Climb Result Clues' : sum(avg_new_puzzles)/len(avg_new_puzzles),
        'Maximum Puzzle Found' : max(max_new_puzzles),
        'Average Maximum Puzzle Found' : sum(max_new_puzzles)/len(max_new_puzzles),
        'Number of Puzzles' : len(new_puzzles)
    }


def write_hill_climb_results(results_folder, originals_folder):
    list_results = []
    for fpath in glob.glob(f'{results_folder}/*.txt'):
        base = os.path.basename(fpath)
        list_results.append(calculate_hill_climb_stats(f'{originals_folder}/{base}', f'{results_folder}/{base}', os.path.splitext(base)[0]))
    df = pd.DataFrame(list_results)
    df = df.round(2)
    print(df)
    df.to_csv('hillclimb_results.csv', index = False)


def calculate_simulated_annealing_stats(original_puzzles_path, new_puzzles_path, puzzle_group):
    original_puzzles = []
    with open(original_puzzles_path, 'rt') as f:
        for l in f.readlines():
            original_puzzles.append(l[:-1])

    new_puzzles = []
    with open(new_puzzles_path, 'rt') as f:
        for l in f.readlines():
            new_puzzles.append(l[:-1])
    new_puzzles = new_puzzles[2:]

    #trim original puzzles to the length of computations
    original_puzzles = original_puzzles[:len(new_puzzles)]

    original_cost = [cost(puzzle) for puzzle in original_puzzles]
    new_cost = [cost(puzzle) for puzzle in new_puzzles]
    hamm_distances = [hamming_distance(original_puzzles[i], new_puzzles[i]) for i in range(len(new_puzzles))]
    assert len(new_puzzles) == len(original_puzzles)
    return {
        'Puzzle Group' : puzzle_group,
        'Average Orginal Puzzle Clues' : sum(original_cost)/len(original_cost),
        'Average Minimum Puzzle Clues' : sum(new_cost)/len(new_cost),
        'Average Hamming Distance' : sum(hamm_distances)/len(hamm_distances),
        'Minumum Puzzle Found' : min(new_cost),
        'Number of Puzzles' : len(new_puzzles)
    }

def write_simulated_annealing_results(results_folder, originals_folder):
    list_results = []
    for fpath in glob.glob(f'{results_folder}/*.txt'):
        base = os.path.basename(fpath)
        list_results.append(calculate_simulated_annealing_stats(f'{originals_folder}/{base}', f'{results_folder}/{base}', os.path.splitext(base)[0]))
    df = pd.DataFrame(list_results)
    df = df.round(2)
    print(df)
    df.to_csv('simulated_annealing_results.csv', index = False)


if __name__ == '__main__':
    write_hill_climb_results('./hill_climb_results', './chunked_puzzles_original')
    write_simulated_annealing_results('./simulated_annealing_results', './chunked_puzzles_original')
