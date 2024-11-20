//
// Created by kaipo on 10/18/2024.
//


#include <cmath>
#include "Node.h"

Node::Node(string cityName, double lat, double lon) {
    this->stateName = cityName;
    this->lat = round(lat * 100.0)/100.0;
    this->lon = round(lon * 100.0)/100.0;
}

Node::Node() {
    stateName = "";
    lat = 0.0;
    lon = 0.0;
}

void Node::addCityName(string cityName) {
    this->stateName = cityName;
}

void Node::addCoordinates(double lat, double lon) {
    this->lat = lat;
    this->lon = lon;
}

bool Node::operator>(Node & node) const{
    return lat > node.lat || lat == node.lat;
}
bool Node::operator<(Node & node) const{
    return lon > node.lon || lon == node.lon;
}

bool Node::operator==(Node & node) const{
    return lat == node.lat && lon == node.lon;
}

ostream& operator<<(std::ostream& os,const Node & node) {
    os << node.stateName;
    cout << " " << node.lat << " " << node.lon;
    cout << endl;
    return os;
}