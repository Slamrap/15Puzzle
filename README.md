# 15 Puzzle Game
In this puzzle the goal is to reach the final state, from an initial configuration. 
</br>For this the user chooses one of the search algorithms available, as well as which heuristic he intends to use. 
</br>The result obtained will have the necessary movements to reach the final state from the given initial configuration, as well as other useful 
statistics.

## Compilation:
```
$ git clone https://github.com/Slamrap/15Puzzle.git
$ cd 15Puzzle
$ make 
```

## Execution:
```
$ ./15Puzzle
```

## Example:
### `Input:`
```
$ ./15Puzzle
Initial Configuration: 2 8 7 3 0 4 10 12 1 5 13 14 11 9 6 15
Final Configuration: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 0

This puzzle has solution. 

+-----------------------+                                                                                               
|                       |                                                                                               
|       Algorithms      |                                                                                               
|                       |                                                                                               
+-----------------------+                                                                                               
|        1. DFS         |                                                                                               
+-----------------------+                                                                                               
|        2. BFS         |                                                                                               
+-----------------------+                                                                                               
|        3. IDFS        |                                                                                               
+-----------------------+                                                                                               
|        4. GREEDY      |                                                                                               
+-----------------------+                                                                                               
|        5. A*          |                                                                                               
+-----------------------+                                                                                               
Select one of the options above [1-5]: 5


+---------------------------------+                                                                                     
|                                 |                                                                                     
|            Heuristics           |                                                                                     
|                                 |                                                                                     
+---------------------------------+                                                                                     
|     1. Nº pieces out of place   |                                                                                      
+---------------------------------+                                                                                     
|     2. Manhattan Distance       |                                                                                     
+---------------------------------+                                                                                     
Select one of the options above [1-2]: 2
```
### `Output:`
```
Searching for path to solution...                                                                                       
Using A* Algorithm with Heuristic - Manhattan Distance                                                                  
Solution found!   
                                                                                                                          
List of moves: [DOWN, DOWN, RIGHT, RIGHT, UP, UP, LEFT, DOWN, DOWN, RIGHT, UP, RIGHT, UP, LEFT, UP, LEFT, LEFT, 
DOWN, RIGHT, DOWN, LEFT, DOWN, RIGHT, RIGHT, UP, UP, UP, RIGHT, DOWN, LEFT, DOWN, LEFT, DOWN, RIGHT, RIGHT]                     
Depth: 35                                                                                                               
Number of generated nodes: 30575                                                                                        
Elapsed time to find solution: 0.984375 seconds 
```
