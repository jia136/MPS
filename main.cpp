#include <iostream>
#include <time.h>

#include "astar.hpp"

using namespace std;

void vShowMeTheWay(char sp[500][500], int dim)
{
    ofstream outfile;
    outfile.open("res.txt");
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            outfile << sp[i][j];
        }
        outfile << endl;
    }
    outfile.close();
}

int main(int argc, char* argv[])
{
    int tc;
    int SPtid = 7;
    int shortestPath;
    int xxx[6] = {0,1,-1,0,0,1};
    int yyy[6] = {0,0,0,-1,2,1};
    bool safe_flag[6] = {false, false, false, false, false, false};

    double s = omp_get_wtime();

    if(argc < 2)
    {
        cout << "Arguments needed" << endl;
        return -1; /* if there is not filename in programs' arguments program stops */
    }

    if(argc == 3)
    {
        tc = strtol ( argv [2] , NULL , 10);
        if (tc > 6 || tc < 0)
        {
            cout << "Invalid thread count, setting thread count to default value 6" << endl;
            tc = 6;
        }
    }
    else
    {
        cout << "example:./exe input_file.txt num_of_threads, default value 1" << endl;
        tc = 1; 
    }

    ifstream file_exmp(argv[1]);
    stringstream ss;
    ss << file_exmp.rdbuf();
    string G_str = ss.str();
    file_exmp.close();

    Maze tmp;
    load_string(G_str, tmp);

    shortestPath = tmp.dim * tmp.dim;

    if(tmp.maze[tmp.s_row][tmp.s_col] == 'S' && tc < 5)
        safe_flag[0] = true;
    else if(tmp.maze[tmp.s_row - 1][tmp.s_col + 1] == '0' && tc >= 5)
        safe_flag[0] = true;
    if (tmp.maze[tmp.s_row+1][tmp.s_col] == '0')
        safe_flag[1] = true;
    if (tmp.maze[tmp.s_row-1][tmp.s_col] == '0')
        safe_flag[2] = true;
    if (tmp.maze[tmp.s_row][tmp.s_col-1] == '0')
        safe_flag[3] = true;
    if (tmp.maze[tmp.s_row][tmp.s_col+2] == '0')
        safe_flag[4] = true;
    if (tmp.maze[tmp.s_row+1][tmp.s_col+1] == '0')
        safe_flag[5] = true;

    if(tc == 1)
    {
        Maze problem(tmp);
        problem.aStarSearch(problem.s_row, problem.s_col);
        problem.maze[tmp.s_row][tmp.s_col] = 'S';
        
        if(problem.spLength < shortestPath)
        {
            vShowMeTheWay(problem.openedList, problem.dim);
            cout << "Maze solved. Path Length: "<< problem.spLength << endl;
        }
        else
        {
            cout << "No solution found" << endl;
        }
    }
    else
    {
#pragma omp parallel num_threads(tc)
{
        int tid = omp_get_thread_num();
        int problem_s_row = tmp.s_row + xxx[tid];
        int problem_s_col = tmp.s_col + yyy[tid];

        tmp.maze[problem_s_row][problem_s_col] = '1';
        if(tc >= 5)
        {
            if(tid == 0)
            {
                problem_s_row = tmp.s_row - 1;
                problem_s_col = tmp.s_col + 1;
                tmp.maze[problem_s_row][problem_s_col] = '1';
                tmp.maze[tmp.s_row][tmp.s_col+1] = '1';
            }
        }
#pragma omp barrier

        Maze problem(tmp);
        problem.s_row = problem_s_row;
        problem.s_col = problem_s_col;
        if(safe_flag[tid] == true)
            problem.aStarSearch(problem.s_row, problem.s_col);

        if(tc >= 5)
        {
            if(tid == 0 || tid == 4 || tid == 5)
            {
                problem.spLength = problem.spLength + 2;
            }
            else
            {
                problem.spLength = problem.spLength + 1;
            }
        }
        else
        {
            if(tid != 0)
            {
                problem.spLength = problem.spLength + 1;
            }
        }

#pragma omp critical
{
        if( shortestPath > problem.spLength ){
            shortestPath = problem.spLength;
            SPtid = tid;
        }
}
#pragma omp barrier
        if (tid == SPtid)
        {
            problem.openedList[problem.s_row][problem.s_col] = 'X';
            problem.openedList[tmp.s_row][tmp.s_col] = 'S';
            if(tc >= 5)
            {
                if(tid == 0 || tid == 4 || tid == 5)
                {
                    problem.openedList[tmp.s_row][tmp.s_col+1] = 'X';
                }
            }
            vShowMeTheWay(problem.openedList, problem.dim);
            cout << "Maze solved. Path Length: "<< problem.spLength<< endl;
        }
        else if(SPtid == 7)
        {
            cout << "No solution found" << endl;
        }
}//pragma
    }
    s = omp_get_wtime() - s;
    std::cout << "Maze solved in: " << s<< "s.\n";
    return 0;
}

