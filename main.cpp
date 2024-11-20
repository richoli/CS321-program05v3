#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <typeinfo>
#include "genBST.h"
#include "Node.h"

using namespace std;
double distance ( double lat1, double lon1, double lat2,  double lon2)
{
    const double r = 3956;
    const double deg_to_radians = M_PI / 180;
    lat1 = lat1 * deg_to_radians;
    lat2 = lat2 * deg_to_radians;
    lon1 = lon1 * deg_to_radians;
    lon2 = lon2 * deg_to_radians;
    double d;
    d = r * acos(sin(lat1) * sin(lat2) + cos(lat1)* cos(lat2)*cos(lon1-lon2));
    return d;
}




/**
 * This option allows the user to directly compute the distances between two sets of coordinates
 */
void option_1 () {
    double lat1, lon1, lat2, lon2;
    cout << "Enter the coordinates of the first point:" << endl;
    cin >> lat1 >> lon1;
    cout << "Enter the coordinates of the second point:" << endl;
    cin >> lat2 >> lon2;
    cout << "Distance between points (" << lat1 << "," << lon1 << ") and ("<< lat2 << "," << lon2 << ") is " << distance(lat1, lon1, lat2, lon2) << endl;
}

/**
 * This option allows the user to directly enter a single set of coordinates, and return the nearest
 * city, with its distance from that location.
 */
template<class T>
void option_2 (BST<T>* tree) {
    double lat, lon;
    cout << "Enter the coordinates (lat, lon)" << endl;
    cout << "Enter the latitude: ";
    cin >> lat;
    cout << "\nEnter the longitude: ";
    cin >> lon;
}

/**
 * Prompts the user to provide the name of the city and its coordinates (lat,lon).
 * Inserts city into the tree (if it isn't there already).
 * User has two options:
 *        -Find the nearest (other) city in the tree and report its distance from the given city.
 *        -Find and list the names and distances of all cities within a user-provided
 *         distance r in miles from the given city.
 */

template<class T>
void option_3choice1(BST<T>* tree) {
    cout << "lol" << endl;
}

template<class T>
void option_3choice2(BST<T>* tree) {
    cout << "lol" << endl;
}

template<class T>
void option_3choiceSet(BST<T>* tree) {
    bool valid = true;
    int choice;
    while (valid) {
        cout << "======================================================\n(1) Find the nearest (other) city in the tree.\n(2) List the names of all the cities and their distances from a given distance r.\n======================================================\n"
                "Select an option (1-2): ";
        cin >> choice;
        switch (choice) {
            case 1:
                option_3choice1(tree);
                valid = false;
                break;
            case 2:
                option_3choice2(tree);
                valid = false;
                break;
            default:
                cout << "\n\n\n\n";
                cout << "Invalid option, please try again..." << endl;
                break;

        }

    }

}



template<class T>
void option_3 (BST<T>* tree) {
    string stateName;
    double lat,lon;
    cout << "Enter the name of the state:" << endl; ;
    cin >> stateName;
    cout << "Enter it's latitude: " << endl;
    cin >> lat;
    cout << "Enter it's longitude: " << endl;
    cin >> lon;

    Node state(stateName,lat,lon);
    Node* result = tree->search(state);
    // if (result == NULL) {
    //     tree->insert(state);
    //     option_3choiceSet(tree);
    // }
    // else {
    //     cout << "City already exists, please provide another city." << endl;
    // }
    if (result == nullptr) {
        cout << "City already exists." << endl;
    }
    option_3choiceSet(tree);
}

void read_file() {
    ifstream inputFile("states.txt");
    string line;
    while(getline(inputFile, line)) {
        if (line.find('#') == string::npos) {
            cout << line << endl;
        }

    };
}



struct State {
    std::string name;
    double latitude;
    double longitude;
};

//
// std::vector<State> readStates(const std::string& filename) {
//     std::vector<State> states;
//     std::ifstream file(filename);
//
//     if (!file.is_open()) {
//         std::cerr << "Could not open the file!" << std::endl;
//         return states;
//     }
//
//     std::string line;
//     while (std::getline(file, line)) {
//         if (line.find('#') == string::npos) {
//             std::stringstream ss(line);
//             std::string stateName;
//             double latitude, longitude;
//
//             // Read all parts of the state name until we get to the latitude and longitude
//             std::getline(ss, stateName, ','); // Assuming comma separates name from latitude/longitude
//
//             // Read latitude and longitude
//             ss >> latitude;
//             ss.ignore(1, ',');  // Ignore the comma after latitude
//             ss >> longitude;
//
//             states.push_back({stateName, latitude, longitude});
//         }
//     }
//
//     return states;
// }


void splitState(string line, string& stateName, double& lat, double& lon) {
    int position = 0;
    while (!std::isdigit(line[position])) {
        stateName += line[position];
        position++;
    }
    line.erase(0, position);
    while (line.find(' ')!= string::npos) {
        int p2 = line.find(' ');
        string latString = line.substr(0, p2);
        lat = stod(latString);
        line.erase(0, p2 + 1);
    }
    lon = stod(line);
};

template<class T>
void fillUpTree(BST<T>*tree) {
    string line;
    ifstream inputFile("states.txt");
    while (getline(inputFile,line)) {
        if (line.find('#') == string::npos) {
            string stateName;
            double lat, lon;
            splitState(line, stateName, lat, lon);
            Node node(stateName,lat,lon);
            tree->insert(node);
        }
    }
}

template<class T>
void runProgram(BST<T>*tree) {
    bool state = true;
    while (state) {
        int option;
        cout << "\n----------- [ Options ] ----------- \n(1) Calculate Distance between two cities.\n(2) Find the nearest city from a given set of coordinate. \n(3) Find the nearest city or the nearest set of cities "
                "from the city provided."
                "\n(4) Exit Program.\n-----------------------------------\nSelect an option (1-4): ";
        cin >> option;
        switch (option) {
            case 1:
                option_1();
            break;
            case 2:
                option_2(tree);
            break;
            case 3:
                option_3(tree);
            break;
            case 4:
                state = false;
                break;
            case 5:
                tree->breadthFirst();
            default:
                cout << "Invalid option: Please try again.\n\n\n" << endl;
            break;
        }
    }
}

int main() {
    string line;
    BST<Node> states;
    fillUpTree(&states);
    states.breadthFirst();
    runProgram(&states);
    return 0;
}

















// bool state = true;
// while (state) {
//     int option;
//     cout << "\n----------- [ Options ] ----------- \n(1) Calculate Distance between two cities.\n(4) Exit Program.\n-----------------------------------\nEnter the a number : ";
//     cin >> option;
//     switch (option) {
//         case 1:
//             option_1();
//         break;
//         case 2:
//             option_2(&states);
//         break;
//         case 3:
//             option_3(&states);
//         break;
//         case 4:
//             state = false;
//         default:
//             cout << "\n\n\nInvalid option: Please try again." << endl;
//         break;
//     }
// }