#include <stdio.h>
#include <stdbool.h>

#define N 4  // Dimensione della griglia (4x4)

// Funzione per controllare se un numero è valido nella posizione (row, col)
bool isValid(int grid[N][N], int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return false;
    }
    return true;
}

// Funzione per contare quanti edifici sono visibili da una direzione
int countVisible(int arr[N]) {
    int count = 0, max = 0;
    for (int i = 0; i < N; i++) {
        if (arr[i] > max) {
            max = arr[i];
            count++;
        }
    }
    return count;
}

// Funzione per verificare i vincoli delle righe e colonne
bool checkClues(int grid[N][N], int clues[4][N]) {
    int temp[N];

    // Controllo superiore (dall'alto)
    for (int col = 0; col < N; col++) {
        for (int row = 0; row < N; row++) temp[row] = grid[row][col];
        if (clues[0][col] != 0 && countVisible(temp) != clues[0][col])
            return false;
    }

    // Controllo inferiore (dal basso)
    for (int col = 0; col < N; col++) {
        for (int row = 0; row < N; row++) temp[row] = grid[N-1-row][col];
        if (clues[1][col] != 0 && countVisible(temp) != clues[1][col])
            return false;
    }

    // Controllo sinistro
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) temp[col] = grid[row][col];
        if (clues[2][row] != 0 && countVisible(temp) != clues[2][row])
            return false;
    }

    // Controllo destro
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) temp[col] = grid[row][N-1-col];
        if (clues[3][row] != 0 && countVisible(temp) != clues[3][row])
            return false;
    }

    return true;
}

// Risolutore con backtracking
bool solve(int grid[N][N], int row, int col, int clues[4][N]) {
    if (row == N) {
        return checkClues(grid, clues);  // Soluzione completa e valida
    }
    if (col == N) {
        return solve(grid, row + 1, 0, clues);
    }

    for (int num = 1; num <= N; num++) {
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num;

            // Verifica parziale: se una riga/colonna è completa, controlla i vincoli
            bool partial = true;
            if (col == N-1) {
                int temp[N];
                for (int i = 0; i < N; i++) temp[i] = grid[row][i];
                if (clues[2][row] != 0 && countVisible(temp) > clues[2][row]) partial = false;
            }
            if (row == N-1) {
                int temp[N];
                for (int i = 0; i < N; i++) temp[i] = grid[i][col];
                if (clues[0][col] != 0 && countVisible(temp) > clues[0][col]) partial = false;
            }

            if (partial && solve(grid, row, col + 1, clues))
                return true;

            grid[row][col] = 0;  // Backtrack
        }
    }
    return false;
}

// Stampa la griglia
void printGrid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", grid[i][j]);
        printf("\n");
    }
}

// Esempio di utilizzo
int main() {
    int grid[N][N] = {0};

    // Clues: [top, bottom, left, right]
    int clues[4][N] = {{4,3,2,1},{1,2,2,2},{4,3,2,1},{1,2,2,2}};
        //{2, 2, 1, 3},  // top
       // {3, 1, 2, 2},  // bottom
       // {2, 2, 3, 1},  // left
       // {1, 3, 2, 2}   // right
  //  };

    if (solve(grid, 0, 0, clues)) {
        printf("Soluzione trovata:\n");
        printGrid(grid);
    } else {
        printf("Nessuna soluzione possibile.\n");
    }

    return 0;
}   
