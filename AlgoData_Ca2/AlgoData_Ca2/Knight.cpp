#include "Knight.h"

/*
    This is called from the menu, calls knightShortestPath(knight, target) which returns
    the target cell if found making it that its path stored in its struct is the 
    shortest path to reach it from knights starting pos.

    It then calls the foundCells printPath() function to display the path in the terminal.

    Parameter: int knight[2], int target[2]
    return: none;
*/
void partFive(int knight[2], int target[2])
{
    // check if the found array is empty ------------->
    Cell foundCell = knightShortestPath(knight, target);
    // uses the cells struct print method to display path
    foundCell.printPath();
}
/*
    Takes in 2D array of size 9 and then initalises all the spaces to 0. 
    This is used to see if we have visted the space yet, 0 = not visted, 1 = have visted.

    Simple loop to go through the 2D matrix level 

    Time: O(2n)

    Parameter: int arr[][9]
    return: none;
*/
void createBoard(int arr[][9])
{
    for (int i = 1; i <= 8; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            arr[i][j] = 0;
        }
    }
}
/*
    Checks to see if the x, y pos is inside the board as if it isnt we return false.
    This is used when prossessing the knights moves, we cant have it going out of bounds when 
    traversing the board. 

    Checks all four corners.
    
    Time: O(1)

    Parameter: int x, int y, int size
    return: bool;
*/
bool insideBoard(int x, int y, int size)
{
    // all four border checks
    if (x >= 1 && x <= size && y >= 1 && y <= size)
    {
        return true;
    }
    return false;
}
/*
    This is used to check if the cell we are currently on in processing is the one we are 
    looking for aka the target cell, if so we return true, else returns false.

    Checks if the x, y of current is same as target pos, represented in a int array size 2. 

    Time: O(1)

    Parameter: Cell current, int target[2]
    return: bool;
*/
bool isTarget(Cell current, int target[2])
{
    if (current.x == target[0] && current.y == target[1])
    {
        return true;
    }
    return false;

}
/*
    This is used to get all the Knights current avaiable paths and if any are inside the board 
    and havent visted yet ( board x,y is equal to 0) we then add that to queue and mark as visted (1)

    Adds the current x,y to the array of possible moves to get the knights pos after move, iterates through them 
    and processses them. 

    Adds the cells path to the next cells path this is to keep track of the cells path while traversing the board.

    Takes in path pointer that is the queue holding all the cells needed to be processed, the board, current cell we 
    are on, knights moves x and y.

    Time: O(1)

    Parameter: queue<Cell>* path, int board[][9], Cell current, int dx[8], int dy[8])
    return: None;
*/
void getAllPaths(queue<Cell>* path, int board[][9], Cell current, int dx[8], int dy[8])
{
    int x, y;
    for (int i = 0; i < 8; i++)
    {
        // possible position we can reach
        x = current.x + dx[i];
        y = current.y + dy[i];

        // if spot we havent reached yet now can be reached
        // have to check if its in the board or not as it will throw exception
        if (insideBoard(x, y, 8) && board[x][y] == 0) {
            // marks it as reached
            board[x][y] = 1;
            current.x = x;
            current.y = y;
            // add current x,y after processing to cell path so we can track moves
            current.path.push_back(current);
            // adds current cell to path so we can process it later
            path->push(current);
        }
    }
}
/*
    Take the knights pos and target pos and does a BFS search to find the target pos. 
    dx,dy arrays used to store and process the knights possible moves from current positon.

    initalises the board and calls function to fill it with zero's to repersent we havent visted that cell yet.

    We use queue to store the cells able to vist and pop , process each of them and if its the target we 
    return else we go through the possible moves the knight can take and we add them to the queue for processing.
    This is a standard BFS search implementation.

    We return the target cell when found as it will the current cell we are on, making its path in the struct 
    the shortest path able to reach it as the way BFS works makes this possible.

    Time: O(N)

    Parameter: int knight[2], int target[2]
    return: Cell;
*/
// Dijkstra's Algorithm: https://www.includehelp.com/cpp-tutorial/dijkstras-algorithm.aspx  Acessed: 15/12/2020
// BFS: https://www.softwaretestinghelp.com/cpp-bfs-program-to-traverse-graph/ Acessed: 15/12/2020
// using bfs as its not weighted meaning bfs works as it each step only costs '1'
// Code adapted from logic taken from https://www.youtube.com/watch?v=DD-_hZwEkXY Acessed: 15/12/2020
Cell knightShortestPath(int knight[2], int target[2])
{
    // knights possible steps.
    int dx[] = { -2, -1, 1, 2, -2, -1, 1, 2 };
    int dy[] = { -1, -2, -2, -1, 1, 2, 2, 1 };

    // chess board
    int board[9][9];
    createBoard(board);
    // starting pos of the knight marked as visted as we start here
    board[knight[0]][knight[0]] = 1;

    // queue of the cells we have visited
    queue<Cell> path;
    Cell current(knight[0], knight[1]);
    // either knight or target is out of bounds from the start
    if (!insideBoard(knight[0], knight[1], 8) || !insideBoard(target[0], target[1], 8))
    {
        cout << "Outside of the board, Please pick a cell within (1 - 8)" << endl;
        return current;
    }
    // add current cell x,y to cells path (track for itself)
    current.path.push_back(current);
    // add current knight pos to the queue
    path.push(current);
    while (!path.empty())
    {
        // gets current cell and stores it
        current = path.front();
        // removes cell after stored
        path.pop();
        // we have reached our target
        if (isTarget(current, target))
        {
            // returns cells when found so we can print the cell from other function
            cout << endl <<"Spot reached!" << endl;
            return current;

        }
        // goes through all the different ways we can move
        getAllPaths(&path, board, current, dx, dy);
    }
    // if not found returns cell
    return current;
}
