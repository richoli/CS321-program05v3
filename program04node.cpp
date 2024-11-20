//
// Created by Roliver on 11/17/2024.
//
#include "Node.h"

Node::Node(string word) {
    this->word = word;
}


Node::Node() {
    word = " ";
}

void Node::addLineNumber(int const num) {
    lineNumber.insert(num);
}

bool Node::operator<(Node & node) const{
    return word < node.word;
}
bool Node::operator>(Node & node) const{
    return word > node.word;
}
bool Node::operator==(Node & node) const{
    return word == node.word;
}

ostream& operator<<(std::ostream& os,const Node & node) {
    os << node.word;
    cout << ":";
    for (auto i : node.lineNumber) {
        cout << " " << i;
    }
    cout << endl;
    return os;
}