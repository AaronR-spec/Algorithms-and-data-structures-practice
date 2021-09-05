#pragma once
#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
/*
    This is the struct used to represent a spot on the chessboard.
    It has its x and y pos which is initalised when created, print() function
    just displays the x,y used for printing the path later.
    
    printPath() prints the vector of Cells called path, this is how we keep track of
    the path that was used to reach this spot. If its the target then the cell previously used
    path will be added making it the smallest path, as it will be the first to reach it (BFS).

*/
struct Cell
{
    int x, y;
    // path to reach that cell
    vector<Cell> path;
    Cell(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    void print()
    {
        cout << "(" << x << ", " << y << ")";

    }
    void printPath()
    {
        cout << "Path: ";
        for (int i = 0; i < path.size(); i++)
        {
            path.at(i).print();
            if (i < path.size() - 1)
            {
                cout << " -> ";
            }
        }
        cout << endl;
    }
};

/*
    Method headers for functions stored in Knight.cpp
*/
void partFive(int knight[2], int target[2]);
bool insideBoard(int x, int y, int size);
void createBoard(int arr[][9]);
bool isTarget(Cell current, int target[2]);
Cell knightShortestPath(int knight[2], int target[2]);
void getAllPaths(queue<Cell>* path, int board[][9], Cell current, int dx[8], int dy[8]);
