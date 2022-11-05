//
//  main.cpp
//  GameOfLife
//
//  Created by Ksenia Arzumanova on 11/2/22.
//

#include <iostream>
using namespace std;
 
// change row and column value to set the canvas size
const int nrow = 5;
const int ncol = 5;

// limit of number of generations
const int max_gen = 10000;
 
// creates row boundary
void row_line()
{
    cout << endl;
    for (int i = 0; i < ncol; i++) {
        cout << " -----";
    }
    cout << endl;
}
 
// returns the count of alive neighbours
int count_live_neighbours(int a[nrow][ncol], int r, int c)
{
    int i, j, count = 0;
    for (i = r - 1; i <= r + 1; i++) {
        for (j = c - 1; j <= c + 1; j++) {
            if ((i == r && j == c) || (i < 0 || j < 0)
                || (i >= nrow || j >= ncol)) {
                continue;
            }
            if (a[i][j] == 1) {
                count++;
            }
        }
    }
    return count;
}
 
int main()
{
    
    int a[nrow][ncol], b[nrow][ncol];
    int i, j;
    int live_neighbors = 0;
    int population_size = 0;
    // Use current time as seed for random generator
    srand(time(0));
 
    // generate population matrix of random live and dead cells
    for (i = 0; i < nrow; i++) {
        for (j = 0; j < ncol; j++) {
            a[i][j] = rand() % 2; // in the range from 0 to 1
            if (a[i][j] == 1)
                population_size++;
        }
    }
 
    // print initial population
    cout << "Initial Generation:";
    row_line();
    for (i = 0; i < nrow; i++) {
        cout << "|";
        for (j = 0; j < ncol; j++) {
            cout << "  " << a[i][j] << "  |";
        }
        row_line();
    }
    
    int gen = 0;
    while (population_size != 0 & gen < max_gen){
        gen++;
        int live_cells = 0;

        // next generation values based on live neighbour count
        for (i = 0; i < nrow; i++) {
            for (j = 0; j < ncol; j++) {
                live_neighbors = count_live_neighbours(a, i, j);
                // cell survives to the next generation
                if (a[i][j] == 1
                    && (live_neighbors == 2
                        || live_neighbors == 3)) {
                    b[i][j] = 1;
                    live_cells++;
                }
                // a cell becomes alive
                else if (a[i][j] == 0
                         && live_neighbors == 3) {
                    b[i][j] = 1;
                    live_cells++;
                }
                // a cell dies or remains dead
                else {
                    b[i][j] = 0;
                }
            }
        }
        population_size = live_cells;
     
        // print next generation
        cout << "\nGeneration " << gen;
        row_line();
        for (i = 0; i < nrow; i++) {
            cout << "|";
            for (j = 0; j < ncol; j++) {
                cout << "  " << b[i][j] << "  |";
            }
            row_line();
        }
        
        // number of generations until complete population death
        if (population_size == 0)
            cout << "Population died out after " << gen << " generations." << endl;
        
        
        // reset 'a' matrix
        for (i = 0; i < nrow; i++) {
            for (j = 0; j < ncol; j++) {
                a[i][j] = b[i][j];
            }
        }
    }
    
 
    return 0;
}
 
