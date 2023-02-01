#ifndef ASTAR_HPP_INCLUDED
#define ASTAR_HPP_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <cstdio>

using namespace std;

class Maze{

    public:
        int s_row;
        int s_col;
        int e_row;
        int e_col;
        int row;
        int col;

        int dim;

        char maze[500][500];
        char openedList[500][500];
        bool closedList[500][500];

        int length;
        int spLength;

        void aStarSearch(int x, int y);

        int xx[4];
        int yy[4];

        friend ostream& operator<<(ostream& output, const Maze&);

        Maze()
        {
            this->s_row = 0;
            this->s_col = 0;
            this->e_row = 0;
            this->e_col = 0;
            this->dim = 0;
            this->spLength = 500*500;
            this->length = 0;

            for ( int i = 0; i < dim; ++i ) {
                for ( int j = 0; j < dim; ++j ) {
                    this->maze[i][j] = 0;
                    this->closedList[i][j] = false; 
                    this->openedList[i][j] = maze[i][j];
                }
            }

            xx[0] = 1;
            xx[1] = 0;
            xx[2] = -1;
            xx[3] = 0;

            yy[0] = 0;
            yy[1] = 1;
            yy[2] = 0;
            yy[3] = -1;

        }

        Maze(const Maze &m)
        {
            this->s_row = m.s_row;
            this->s_col = m.s_col;
            this->e_row = m.e_row;
            this->e_col = m.e_col;
            this->dim = m.dim;
            this->spLength = 500*500;
            this->length = 0;

            for ( int i = 0; i < dim; ++i ) {
                for ( int j = 0; j < dim; ++j ) {
                    maze[i][j] = m.maze[i][j];
                    closedList[i][j] = false; 
                    openedList[i][j] = maze[i][j];
                }
            }
            xx[0] = 1;
            xx[1] = 0;
            xx[2] = -1;
            xx[3] = 0;

            yy[0] = 0;
            yy[1] = 1;
            yy[2] = 0;
            yy[3] = -1;
        }
};

bool load_string(const string& str, Maze& grid);


#endif // ASTAR_HPP_INCLUDED

