//
// Created by kaipo on 10/18/2024.
//
#ifndef NODE_H
#define NODE_H

#include <String>
#include <set>
#include <iostream>

using namespace std;

class Node {
private:

    // Name of state
    string stateName;

    // City coordinates
    double lat;
    double lon;

public:
    Node(string cityName, double lat, double lon); //Creates new node with word provided in parameters.
    Node(); //Creates a new node with a nameless state and


    //Adds cityName to node.
    void addCityName(string stateName);

    //Adds coordinates to node.
    void addCoordinates(double lat, double lon);

    //Compares the nodes according to their coordinates.
    bool operator<(Node & node) const;
    bool operator>(Node & node) const;
    bool operator==(Node & node) const;

    //Prints out the name of the state and its coordinates.
    friend ostream& operator<<(std::ostream& os,const Node & node);
};



#endif //NODE_H
