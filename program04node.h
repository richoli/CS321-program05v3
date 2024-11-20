//
// Created by Roliver on 11/17/2024.
//

#ifndef PROGRAM04NODE_H
#define PROGRAM04NODE_H

#include <String>
#include <set>
#include <iostream>

using namespace std;

class Node {
private:
    // Word value
    string word;

    //List of line numbers that were found containing the word.
    set<int> lineNumber;

public:
    Node(string word); //Creates new node with word provided in parameters.
    Node(); //Creates a new node with an empty string.

    //Adds line number to the list of line numbers
    void addLineNumber(int num);

    //Compares the nodes according to their word content.
    bool operator<(Node & node) const;
    bool operator>(Node & node) const;
    bool operator==(Node & node) const;

    //Prints out the word and the list of numbers.
    friend ostream& operator<<(std::ostream& os,const Node & node);
};

#endif //PROGRAM04NODE_H
