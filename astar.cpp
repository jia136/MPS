#include "astar.hpp"

/*functions that loads starting problem from string
  and gives us all relevant informations about are
  problem( coordinates of start and destination and
  position of barrier )*/
bool load_string(const string& str, Maze& grid)
{
    istringstream iss(str);
    grid.dim = 0;
    grid.s_row = -1;
    grid.s_col = -1;
    grid.e_row = -1;
    grid.e_col = -1;
    string buf;
    int i  = 0;

    while(iss >> buf)
    {
        buf[buf.size()] ='\0';
        i = 0;
        while(buf[i]!='\0')
        {
            grid.maze[grid.dim][i] = buf[i];

            if(buf[i] == 'S')
            {
                grid.s_row = grid.dim;
                grid.s_col = i;
            }
            if(buf[i] == 'E')
            {
                grid.e_row = grid.dim;
                grid.e_col = i;
            }

            i++;
        }

        grid.dim++;

    }
    return true;
}

/*overloading  << for representation of the starting maze*/
ostream& operator<<(ostream& output, const Maze& grid)
{
    for(int i = 0; i != grid.dim; i++)
    {
        for(int j = 0; j != grid.dim; j++)
        {
            output << grid.maze[i][j];
        }
        output << endl;
    }
    return output;
}

/* brute force path finder */
void Maze::aStarSearch(int x, int y)
{
    if (x == e_row && y == e_col){
        if (length < spLength ) {
            spLength = length;              
            for ( int i = 0; i < dim; ++i ){
                for ( int j = 0; j < dim; ++j ){
                    if (closedList[i][j] == true )
                    {
                        openedList[i][j] = 'X';
                    }
                    else
                    {
                        openedList[i][j] = maze[i][j];
                    }
                }
            }
        }
        return;
    }

    closedList[x][y] = true;
    length++;

    for(int i = 0; i < 4; i++)
    {
        row = x + xx[i];
        col = y + yy[i];
        if(maze[row][col] != '1')
        {
            if(closedList[row][col] != true)
            {
                if (!(row < 0 || col < 0 || row >= dim || col >= dim)) {
                    aStarSearch(row, col);
                }
            }
        }
    }

    closedList[x][y] = false;
    length--;
}

