# CPP project for solving Sudoku



Authors: Longhui Yin

Repo: 



This project is for solving sudoku. Please google or go to wiki for more information about sudoku.

Class `Sudoku` represents a sudoku puzzle instance. `solve()` function tries to solve it. We maintain an `Choice` instance, representing all possible numbers to fill into the cell, and eliminate invalid choices as much as possible. When a unique choice is left, we may fill the cell with that choice. We eliminate choices and fill cells according to following naive rules:

- If a cell is already filled, then other cells in the same row/column/block should eliminate choices of the content this cell filled.
- If a cell has a unique choice, then it should be filled with that choice
- If in a row/column/block, there is a unique cell for some number to fill in, then that cell should be filled with that number.
- If in a block, three cells in a row/column may be filled with some number, while not for any other cells in this block, then that number should be in one of them, so other cells of this row/column should eliminate the choice of this number.
- If in a row/column, three cells in a block may be filled with some number, while not for any other cells in this row/column, then that number should be in one of them, so other cells of this block should eliminate the choice of this number.

Class `EventLogger` records all the "reasoning"  when we applied such rules, so that we may output the answer along with a list of reasoning (though annoyingly long, but you may turn off those trivial reasoning lines).

But sure, these rules are far from deriving a complete solution, but it is already capable for some easy mode, or medium mode level sudokus. To solve expert level sudokus, it seems we should run `BFS`, but it is still fine to use the above rules for pruning, that's why I implemented them in the beginning.



For now the structure is a bit messy. You may found the function of class `Position` overlaps with the function of class `Cell`. And the function is still incomplete, as mentioned above. I may try to finish them later, if I still have interest and spare time.