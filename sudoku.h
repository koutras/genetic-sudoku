#ifndef SUDOKU_H
#define SUDOKU_H 9
void mutate(int **sudoku,int **templateSudoku,int usingTemplate,int dimension);
void printVector(int *ptr,int dimension);
void printSudoku(int **sudoku,int dimension);
void printPopulation(int ***sudokuList,int popSize,int dimension);
void eraseCounter(int *counter,int dimension);
int evaluateCounter(int *counter,int dimension);
int a2b(int a,int b);
void sudokuEvaluate(int **sudoku,int cellSize,int *finalRes,int usingTemplate,int **templateSudoku);
int selectCanditate(int *fitness, int tournamentSize, int popSize);
void columnToRow(int **A,int **B,int rowA,int colB,int dimension);
void columnCopy(int **A,int **B,int colA,int colB,int dimension);  //copy B's column to A
void rowCopy(int **A,int **B,int rowA,int rowB,int dimension);  //copy B's row to A
void crossoverRow(int **A,int **B,int rowA,int rowB,int dimension,int start,int finish);
void switchRows(int **A,int **B,int row,int ln,int dimension);
void switchColumns(int **A,int **B,int col,int dimension);
void sudokuCopy(int **A,int **B,int dimension);
int sudokuNumber(int **options,int dimension);
int **generateNewSudoku(int dimension,int usingTemplate,int ***templateSudoku);
int ***generatePopulation(int popSize,int dimension,int usingTemplate,int ***templateSudoku);
int isSolution(int aFitness,int ***sudokuList);
void leftShift(int **sudoku,int **templateSudoku,int usingTemplate,int dimension,int line);
void rightShift(int **sudoku,int **templateSudoku,int usingTemplate,int dimension,int line);
int sudokuGame(GtkWindow *window,int seed,int dimension,int tournamentSize,int popSize,float pc,int stoppingGen);

void check(void *ptr);
void makeChildren(int *pid ,int *fitness,int ***sudokuList,int dimension,int cellSize,int ***templateSudoku,int usingTemplate,int popSize);

#endif
