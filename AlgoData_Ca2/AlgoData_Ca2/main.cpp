#include "Queue.h"
#include "Stack.h"
#include "TreeIterator.h"
#include "Xml.h"
#include "Knight.h"
/*
    Function header decloartions
*/
void startMenu();
int printMenu();
void partOne();
void partTwo();
void partThree();
string getFileName();
bool validXml(string file);
void partFour();
void partFive();
/*
    main method
*/
int main()
{   
    // calls the menu 
    startMenu();
    return 0;
}
/*
    This is the first thing a user would see, it holds all the ca's questions.
    Takes users input by calling printMenu and runs functions based on the input.

    Parmeters: None
    Return Type: None;
*/
void startMenu() 
{
    int userInput;
    while (true) 
    {
        userInput = printMenu();
        switch (userInput) 
        {
        case 1:
            partOne();
            break;
        case 2:
            partTwo();
            break; 
        case 3:
            partThree();
            break; 
        case 4:
            partFour();
            break;
        case 5:
            partFive();
            break;
        case 6:
            cout << endl << "GoodBye..." << endl;
            return;

            break;
        default:
            cout << endl << "Invalid Input (1-5)" << endl;
        }
    
    }
}
/*
    This prints the menu that the user see's and prompts them for a selction.
    Input is then returned for furture processing.


    Parmeters: None
    Return Type : int (user's input);
*/
int printMenu() 
{
    cout << "\n1. Queue\n2. Stack\n3. XML Validation\n4. XML Tree\n5. Chess Knight\n6. Exit\nOption: ";
    int userInput;
    cin >> userInput;
    return userInput;
}
/*
    Part one which is the use of a Queue implementation. 
    Here user can use all the functions outlined in the ca doc.
    
    Functions: Enqueue, Dequeue, Size, Clear

    Parmeters: None
    Return Type : None;
*/
void partOne() 
{
    int size = 0;
    cout << "\nSize of Integer Queue: ";
    cin >> size;
    Queue<int>* queue = new Queue<int>(size);
    int userInput, value;
    while(true)
    {
        cout << "\n1. Enqueue\n2. Dequeue\n3. Size\n4. Clear\n5. Back\nOption: ";
        cin >> userInput;
            switch (userInput)
            {
            case 1:
                cout << "\nValue: ";
                cin >> value;
                queue->Enqueue(value);
                break;
            case 2:
                value = queue->Dequeue();
                cout << "Value " << value << " was removed" << endl;
                break;
            case 3:
                value = queue->size();
                cout << "Size of Queue: " << value << endl;
                break;
            case 4:
                queue->clear();
                cout << "Queue cleared..." << endl;
                break;
            case 5:
                cout << endl << "GoodBye..." << endl;
                return;
                break;
            default:
                cout << endl << "Invalid Input (1-5)" << endl;
            }
    
    }

}
/*
    Part Two which is the use of a Stack implementation. 
    Here user can use all the functality of the Stack outlined in ca doc.

    Functions: Push, Pop, Front, Size, Clear

    Parmeters: None
    Return Type : None;
*/
void partTwo() 
{
    Stack<int> stack;
    int userInput, value;
    while (true)
    {
        cout << "\nInteger Stack\n1. Push\n2. Pop\n3. Front\n4. Size\n5. Clear\n6. Back\nOption: ";
        cin >> userInput;
        switch (userInput)
        {
        case 1:
            cout << "\nValue: ";
            cin >> value;
            stack.push(value);
            break;
        case 2:
            value = stack.pop();
            cout << "\nValue " << value << " was removed\n";
            break;
        case 3:
            value = stack.front();
            cout << "\nValue " << value << " is on top\n";
            break;
        case 4:
            value = stack.size();
            cout << "\nSize of Stack: " << value << endl;
            break;
        case 5:
            stack.clear();
            cout << "\nStack cleared..." << endl;
            break;
        case 6:
            cout << endl << "GoodBye..." << endl;
            return;
            break;
        default:
            cout << endl << "Invalid Input (1-5)" << endl;
        }
    }
}
/*
    Part Three which is the use of a Stack to validate a Xml file.
    Here user can enter the file name or path and displays valid or invalid.

    Parmeters: None
    Return Type : None;
*/
void partThree() 
{
    string file = getFileName();
    if (validXml(file))
    {
        cout << "\nXml File is Valid!\n";
    }
    else 
    {
        cout << "\nXml File is Invalid!\n";
    }
}
/*
    Prompts the user for file name/path then it gets returned for future processing.
    Have to use cin >> ws to clear the cin buffer as we use int before, string input we use getline().

    Parmeters: None
    Return Type : string;
*/
string getFileName() 
{
    string fileName = "";
    cout << "\nFile Path/Name: ";
    cin >> ws;
    getline(cin, fileName);
    return fileName;
}
/*
    Takes file name and calls validateXml() which returns true or false if checked as valid.
    That is then returned to function that has called this method.

    Parmeters: string (file name)
    Return Type : bool;
*/
bool validXml(string file) 
{
    bool xmlValid = false;
    xmlValid = validateXml(file);
    return xmlValid;
}
/*
    Takes file name and calls validXml() and if that is true it processed the file into a tree structure,
    by using buildXmlTree which is held in Xml.h.
    Gives user options for DFS search and Display.
    
    DFS: if found displays the node that inputed search was found and its parent/siblin nodes.
    Display: Displays the whole tree structor of the xml, title and attriubutes .

    Parmeters: None
    Return Type : None
*/
void partFour() 
{
    string file = getFileName();
    if (!validXml(file))
    {
        cout << "\nXml File is Invalid!\n";
        return;
    }
    Tree<TreeNode> root(buildXmlTree(file)); 
    TreeIterator<TreeNode> iter(&root);
    string target;
    int userInput;
    while (true) 
    {
        cout << "\n1. Depth First Search\n2. Display Tree\n3. Back\nOption: ";
        cin >> userInput;
        switch (userInput)
        {
        case 1:
            cout << "\nSearch For: ";
            cin >> ws;
            getline(cin, target);
            dfs(iter, target, &isNode);
            break;
        case 2:
            displayTree(iter, " ");
            break;
        case 3:
            cout << "\nReturning..";
            return;
            break;
        default:
            cout << endl << "Invalid Input (1-5)" << endl;
        }
    }
}
/*
    Prompts the user for the knights x,y starting pos and the target spot they would like to reach. 
    calls PartFive() that processes and prints the path using the struct Cell functions. 

    Parmeters: None
    Return Type : None
*/
void partFive() 
{
    int knight[2];
    int target[2];

    cout << "\nEnter Knight X Position: ";
    cin >> knight[0];
    cout << "\nEnter Knight Y Position: ";
    cin >> knight[1];
    cout << "\nEnter Target X Position: ";
    cin >> target[0];
    cout << "\nEnter Target Y Position: ";
    cin >> target[1];

    partFive(knight, target);
}
