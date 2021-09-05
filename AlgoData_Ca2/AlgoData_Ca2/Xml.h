#pragma once
#include <iostream>
#include <stdio.h>
#include "Stack.h"
#include <fstream>
#include <string>
#include <map>
#include "TreeIterator.h"
#include "Tree.h"
using namespace std;
/*
    This is the code implementated to complete part 4 -5 of Ca.
    Both the validation and the tree xml is stored here as they both go 
    hand in hand so i didnt sepreate them. 

    All functiality and requirments for both parts have been implemented here.

    Could not use seperate cpp and header file as dispaly uses tempaltes, i could have 
    removed the template but i left it for functality purposes.

*/
/*
    TreeNode struct is used to represent the node of a tree structure.
    Holds the title of the Tag in xml and a map of attributes like id or text

    We then use this to process our tree as this holds all the data we need 
*/
struct TreeNode
{
    string title = "";
    map<string, string> attributes;
};
/*
    Function header decloartions 
*/
bool validateXml(string file);
bool processXml(Stack<string>& xmlElements, string& rootElement, string& element, string& xmlFile);
string readXml(string file);
Tree<TreeNode> buildXmlTree(string file);
void getAllTags(vector<string>& tags, string xmlFile);
void getAllTagsAttributes(vector<TreeNode*>& tags, string xmlFile);
bool dfs(TreeIterator<TreeNode> iter, string target, bool(*func)(TreeNode&, string&));
bool isNode(TreeNode& node, string& target);
int findChar(char target, int startPos, string s);
template<typename T>
void displayTree(TreeIterator<T> iter, string indent);
/*
    Called to check if xml file inputed is valid or not.
    Reads the xml file and returns it as a string for procssing, then is passed along with 
    strings root and elemnet to be used to validate.
    returns the result 

    Parameter: string file
    Return: bool
*/
bool validateXml(string file)
{
    Stack<string> xmlElements;
    string xmlFile = readXml(file);
    string rootElement, element;
    bool vaildate = processXml(xmlElements, rootElement, element, xmlFile);
    return vaildate;
}

/*
    Processes the xml string and iterates string one by one to find opening tag then that tag is added
    to a stack. when a closing tag is found we process the stack by popping the tag corresponing to that
    closed tag, then this processes is continued.
    
    If the stack is not empty meaning we have more to process by the end it means its not valid, or if 
    we havent reached the end and the stack is empty aka processed the root means its invalid,
    or if we havent found a root.

    Time: O(2n)

    Parameter: Stack<string>& xmlElements, string& rootElement, string& element, string& xmlFile
    Return: bool
*/
bool processXml(Stack<string>& xmlElements, string& rootElement, string& element, string& xmlFile)
{
    int count = 0;
    string currentElement;
    char current;
    bool processedRoot = false;
    bool rootFound = false;
    int rootCount = 0;
    // goes through the string char by char
    for (int i = 0; i < xmlFile.size(); i++)
    {

        // current char 
        current = xmlFile.at(i);
        // opening tags get added to the stack
        if (current == '<' && xmlFile.at(i + 1) != '/')
        {
            // element builder
            element = "";
            int j = i + 1;
            for (int j = i + 1; j < xmlFile.size(); j++)
            {
                // current char
                current = xmlFile.at(j);
                // hit the end backet
                if (current == '>' || isspace(current))
                {
                    break;
                }
                // adds current char to the element
                element += xmlFile.at(j);

                // skips i to the j index for further processing
            }
            i = j;

            // number of elements 
            count++;
            if (count == 1 && !rootFound)
            {
                //first element = root element of xml
                rootElement = element;
                rootFound = true;

            }

            // add element to the stack 
            xmlElements.push(element);


        }
        // if we have a closing tag and if we do 
        else if (current == '<' && xmlFile.at(i + 1) == '/')
        {
            element = "";
            for (int j = i + 2; j < xmlFile.size(); j++)
            {
                // current char
                current = xmlFile.at(j);
                // hit the end backet
                if (current == '>')
                {
                    break;
                }
                // adds current char to the element
                element += xmlFile.at(j);

                // skips i to the j index for further processing
                i = j;
            }

            // we now have the closing tag word we pop the stack until the closing tag is not correct
            while (xmlElements.size() != 0)
            {
                // closest opening tag 
                currentElement = xmlElements.front();
                if (currentElement == element)
                {
                    // removes element if the current element in the stack is equal to the closing tag.
                    xmlElements.pop();

                }
                else if (currentElement == rootElement && !processedRoot && rootFound)
                {
                    // we have processed the root
                    processedRoot = true;
                }
                else
                {
                    break;
                }

            }
            // if we have an empty stack and we have reached the end of the file root spaces away means its invalid
            if (xmlElements.size() == 0 && i < xmlFile.size() - rootElement.size() + 1)
            {
                return false;
            }
        }
    }
    // check to see if we processed the root and the size is 0 and that we actually found a root
    return processedRoot && xmlElements.size() == 0 && rootFound ? true : false;
}

/*
    Takes a file apth and processes it into a string and then is returned for processing
    
    Time: O(1)

    Parameters: string file
    Return: string (file)
*/
//https://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c Accessed: 12/12/2020
string readXml(string file)
{
    ifstream ifs(file);
    // goes through file char by cahr and puts it into xml string
    string xml((istreambuf_iterator<char>(ifs)),
        (istreambuf_iterator<char>()));
    // string representing the file entered
    return xml;
}

/*
    Used to build tree with the xml file inputed, we check if the file is valid and if it is we start processing,


    we use getAllTagsAttributes() to get all a vector of treenodes(tags with their attrubutes) that are in the xml file.
    we then add the root which is the first element in the vector and start iterating through them
    if we hit an open tag we append it to the tree and got to the last child and go down the tree.
    else we hit a end and go up.

    We then return the root for iterating later.

    Time: O(n)

    Parmeter: string file
    Return: Tree<TreeNode>

*/
Tree<TreeNode> buildXmlTree(string file)
{
    if (validateXml(file))
    {
        string xmlFile = readXml(file);
        vector<TreeNode*> tags;
        // gets all the treenodes from the file string tags
        getAllTagsAttributes(tags, xmlFile);

        TreeNode node;
        // this is our root as the first item in the vector will be our root
        node.title = tags.at(0)->title;
        node.attributes = tags.at(0)->attributes;
        Tree<TreeNode> root(node);
        TreeIterator<TreeNode> iter(&root);

        for (int i = 1; i < tags.size(); i++)
        {
            node.title = tags.at(i)->title;
            node.attributes = tags.at(i)->attributes;
            // we have dont have a closing
            if (node.title != "" || node.title != " ")
            {
                // we have an opening tag
                if (node.title.at(0) != '/')
                {

                    iter.appendChild(node);
                    iter.childEnd();
                    iter.down();
                }
                else
                {
                    iter.up();
                }
            }

        }
        // return the root for iterating later
        return root;
    }
    else
    {
        // returns root which is empty if its not valid
        cout << "Not a valid XML File" << endl;
        TreeNode node;
        Tree<TreeNode> root(node);
        return root;
    }

}

/*
    Goes through the string and when we hit an opening tag we add to the vecotr passed in.
    We go throuhg and add both the opening and closing tag for processing later.
    We tell opening is '<' and closing as '</'.
    we get tag buy going till we hit '>' or a space indeacting their is an id or class.

    Example of tags after processing:
        Closing -> /Note
        Opening - > Note

    Time: O(n)

    Paremeter: vector<string>& tags, string xmlFile
    Return: None

*/
void getAllTags(vector<string>& tags, string xmlFile)
{
    string element, rootElement;
    bool processedRoot = false;
    bool rootFound = false;
    int count = 0;
    char current;
    for (int i = 0; i < xmlFile.size(); i++)
    {
        // current char 
        current = xmlFile.at(i);
        // opening tags get added to the stack
        if (current == '<' && xmlFile.at(i + 1) != '/')
        {
            // element builder
            element = "";
            int j = i + 1;
            for (int j = i + 1; j < xmlFile.size(); j++)
            {
                // current char
                current = xmlFile.at(j);
                // hit the end backet
                if (current == '>' || isspace(current))
                {
                    break;
                }
                // adds current char to the element
                element += xmlFile.at(j);

                // skips i to the j index for further processing
            }
            i = j;

            // number of elements 
            count++;
            if (count == 1 && !rootFound)
            {
                //first element = root element of xml
                rootElement = element;
                rootFound = true;
            }

            // add element to the stack 
            if (!isspace(xmlFile.at(i - 1)))
            {
                tags.push_back(element);
            }
        }
        // if we have a closing tag and if we do 
        else if (current == '<' && xmlFile.at(i + 1) == '/')
        {
            element = "";
            for (int j = i + 1; j < xmlFile.size(); j++)
            {
                // current char
                current = xmlFile.at(j);
                // hit the end backet
                if (current == '>')
                {
                    break;
                }
                // adds current char to the element
                element += xmlFile.at(j);

                // skips i to the j index for further processing
                i = j;
            }
            tags.push_back(element);
        }
    }
}
/*
    Goes through the string and when we hit an opening tag we add to the vecotr passed in and its id if their to its attriubtes.
    If we hit a closing tag we get the difference betweeen them to have the text of the tag, stored in the cells map as 'Text'.
    Add both opening and closing for processing later to check if it is nested correctly.

    Example of Treenode title after processing: 
        Closing -> /Note
        Opening - > Note

    Time: O(n)

    Paremeter: vector<TreeNode*>& tags, string xmlFile
    Return: None

*/
void getAllTagsAttributes(vector<TreeNode*>& tags, string xmlFile)
{
    string element, rootElement;
    bool processedRoot = false;
    bool rootFound = false;
    char current;
    int endTag = 0;
    TreeNode* node = new TreeNode;
    int index = -1;
    // remove the \n
    xmlFile.erase(std::remove(xmlFile.begin(), xmlFile.end(), '\n'), xmlFile.end());
    for (int i = 0; i < xmlFile.size(); i++)
    {

        // current char 
        current = xmlFile.at(i);
        // opening tags get added to the stack
        if (current == '<' && xmlFile.at(i + 1) != '/')
        {
            // element builder

            // gets the > pos'
            endTag = findChar('>', i, xmlFile);
            int spacePos = findChar(' ', i, xmlFile);
            int wordEndPost = i;
            // we have a space before the end tag
            if (endTag > spacePos)
            {
                element = xmlFile.substr(i + 1, (spacePos - 1) - (i));
                // pos of the equals
                node->title = element;

            }
            else
            {
                // tag of element currently
                element = xmlFile.substr(i + 1, (endTag - 1) - (i));
                node->title = element;
            }
            // we have an id or class
            if (endTag > spacePos)
            {
                // pos of the equals
                int equalsPos = findChar('=', i, xmlFile);

                // between the space and equals (id,class etc);
                string key = xmlFile.substr(spacePos, equalsPos - spacePos);
                // pos of the two " ", the difference between them as a substring will be the id or class 
                int wordStartPos = findChar('"', equalsPos, xmlFile);
                int wordEndPost = findChar('"', wordStartPos + 1, xmlFile);
                string value = xmlFile.substr(wordStartPos, wordEndPost - wordStartPos);
                // one " wont be removed so i have to remove it this way
                value.erase(std::remove(value.begin(), value.end(), '"'), value.end());
                // add it to treenode map
                node->attributes.insert({ key, value });
            }

            // add Treenode to vector after processing
            tags.push_back(node);
            // index in relation to the amount of nodes
            index++;
            i = wordEndPost;

        }
        // if we have a closing tag and if we do 
        else if (current == '<' && xmlFile.at(i + 1) == '/')
        {
            if (i - endTag > 1)
            {
                // text of the tag as pos from as substring with end tag > in opening and < of closing is the text 
                string text = xmlFile.substr(endTag + 1, i - 1 - endTag);
                tags.at(index)->attributes.insert({ "Text", text });
                // incremneted for representing the tag after processing
                index = index + 2;
            }

            element = "";
            for (int j = i + 1; j < xmlFile.size(); j++)
            {
                // current char
                current = xmlFile.at(j);
                // hit the end backet
                if (current == '>')
                {
                    break;
                }
                // adds current char to the element
                element += xmlFile.at(j);

                // skips i to the j index for further processing
                i = j;
            }
            endTag = i + 1;
            node->title = element;
            // we add the closing tag 
            tags.push_back(node);
            //tags.push_back(node);
            index--;
        }
        node = new TreeNode;


    }
}
/*
    Used to travers the tree and search for a target node that is passed by the string target.
    if found we go up the tree to its parent and display it making it that the whole node is displayed instead of just that 
    node or tag. 
    while their is child nodes to process we go through them recursivly and go down the tree, if we hit a deadend we go back
    up the tree and to the next child, this is repeated till no more nodes can be processed.

    At the end the target nodes are dispalyed, i tried making it return true or false but it didnt work recursivly.
    Way i tried it made it that only one node would be displayed so i got it out as i want all the nodes that match to be
    displayed.

    Time: O(n)

    Parmeter: TreeIterator<TreeNode> iter, string target, bool(*func)(TreeNode&, string&
    Return: bool (found of not) 

*/
// https://codeforwin.org/2017/12/pass-function-pointer-as-parameter-another-function-c.html Accessed: 15/12/2020
bool dfs(TreeIterator<TreeNode> iter, string target, bool(*func)(TreeNode&, string&))
{
    /*
       a function that goes through a nodes map and returns true or false if it contains any of it.
   */
    bool found = false;
    TreeNode node;
    node = iter.item();
    if (func(node, target))
    {
        // if its found in a child it will go up to the parent so the whole section is printed
        if (!iter.childValid())
        {
            // go up the tree
            iter.up();
        }
        //cout << "Tag: " << node.title << "\n\tKey: " << attributeIter->first << " Value: " << attributeIter->second<< endl;
        displayTree(iter, " ");
        found = true;

    }

    while (iter.childValid() && !found)
    {
        TreeIterator<TreeNode> newIter(iter);
        newIter.down();
        found = dfs(newIter, target, func);
        iter.childForth();
    }
    // if there is more to process then we found to false so it gets all the possible ones in search
    if (iter.childValid())
    {
        found = false;
    }

    return found;
}
/*
    Used to check if the node we are currently on is the target node, this is passed to the functuon DFS as a 
    reference. 
    We iterate throught the nodes attributes map and if the second value aka the text or id value is the target we 
    return true else we return false

    Time: O(n)

    Parmeter: TreeNode& node, string& target
    Return: bool (is node we want)

*/
bool isNode(TreeNode& node, string& target)
{
    for (auto dfsIter = node.attributes.begin(); dfsIter != node.attributes.end(); dfsIter++)
    {
        if (dfsIter->second == target)
        {
            return true;
        }
    }
    return false;
}
/*
    This method takes in a string and the starting pos you are at in the string and the 
    target char, it iterates till it finds the char and returns the position if it hits the end 
    we return -1.

    Time: O(n)

    Parmeter: char target, int startPos, string s
    Return: int (index of the char)
*/
int findChar(char target, int startPos, string s)
{
    for (int i = startPos; i < s.length(); i++)
    {
        if (s.at(i) == target)
        {
            return i;
        }
    }
    return -1;
}
/*
    Code used to display the tree taking the itereator in, we use this to display the full tree and the 
    tree nodes when found in Dfs. 
    We get the current item and iterate through its attributes and prints them and when we hit leef we 
    go back up but while the iter has child nodes to go to it recursive calls itself and prints them while 
    moving accoss the DList representing the nodes children and going down to its child nodes.


    Parmeter: TreeIterator<T> iter, string indent
    Return: None;
*/
// Code adapted form Diana Bogusevschi's code, Accessed: 12/12/2020
template<typename T>
void displayTree(TreeIterator<T> iter, string indent)
{
    bool valid = false;
    TreeNode node;
    node = iter.item();
    cout << indent << "<" << node.title << " Attributes: ";
    for (auto displayIter = node.attributes.begin(); displayIter != node.attributes.end(); displayIter++)
    {
        cout << "Key: " << displayIter->first << " Value: " << displayIter->second;
    }
    if (iter.childValid())
    {
        valid = true;
        cout << endl;
    }
    else
    {
        cout << "/>" << endl;
    }
    while (iter.childValid())
    {
        TreeIterator<TreeNode> newIter(iter);
        newIter.down();
        displayTree(newIter, indent + "\t");
        iter.childForth();
    }
    if (valid)
    {
        cout << indent << "/>" << endl;
    }
}