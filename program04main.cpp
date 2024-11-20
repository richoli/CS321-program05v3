//
// Created by Roliver on 11/17/2024.
//
#include <algorithm>
#include <iostream>
#include "genBST.h"
#include "Node.h"
#include <fstream>
#include <cctype>

void splitLine( string line, vector<string>& tokens, char delimiter);
void cleanWord(string& word, vector<string> tokens);
void cleanWord(string& word);

/**
 * Takes one word containing a "-" in between and splits it into more words, and
 * adds those words unto the vector of tokens
 *
 * @param word containing "-" symbol
 * @param tokens vector of tokens from the parsed line.
 * @param delimiter splits the given line.
 */
void splitWord(string word, vector<string>& tokens, char delimiter) {
    while (word.find(delimiter) != string::npos) {

        //finds the position of the delimeter within the line
        int position = word.find(delimiter);

        //Creates a from the beginning of the line to the position of the delimiter.
        string token = word.substr(0, position);

        //removes the word from the line (from the start of the line, up to the position of the delimiter).
        word.erase(0, position + 1);
            //adds word to vector.
            tokens.push_back(token);
        }
    tokens.push_back(word);
};

/**
 * Splits the line into tokens(words) based on a given delimeter, and adds
 * them into a vector containing all the tokens of that line.
 *
 * @param line line to be split into tokens
 * @param tokens vector containing tokens from split line
 * @param delimiter splits the line
 */
void splitLine( string line, vector<string>& tokens, char delimiter) {

    //continue to split the line until the delimiter is no longer found.
    while (line.find(delimiter) != string::npos) {

        //finds the position of the delimeter within the line
        int position = line.find(delimiter);

        //Creates a from the beginning of the line to the position of the delimiter.
        string token = line.substr(0, position);

        //removes the word from the line (from the start of the line, up to the position of the delimiter).
        line.erase(0, position + 1);

        //checks to see if there are empty subtrings (ex. from tabs at the start of the line)
        if(!token.empty()) {

            // removes the "-" from the end of the word.
            cleanWord(token);

            if (token.find('-')!=string::npos) {
                splitWord(token, tokens, delimiter);
            }
            else {
                //adds word to vector.
                tokens.push_back(token);
            }

        }
    }

    cleanWord(line);
    if (line.find('-')!=string::npos) {
        splitWord(line, tokens, '-');
    }
    else {
        //adds word to vector.
        tokens.push_back(line);
    }
};

/**
 * Removes punctuations attached to a given word.
 * @param word to be cleaned
 */
void cleanWord(string& word) {

    while ('-' == word[word.size() - 1] || '-'  == word[0] || '.' == word[word.size() - 1] || '.' == word[0] || '!' == word[word.size() - 1] ||
    '!' == word[0] || ',' == word[word.size() - 1] || ','== word[0] || '?' == word[word.size() - 1] || '?'== word[0] || '\"' == word[word.size() - 1] || '\"'== word[0]){
        if ('-' == word[word.size() - 1]) {
            word = word.substr(0, word.size() - 1);
        }
        if ('-'  == word[0]) {
            word = word.substr(1, word.size() - 1);
        }
        else if ('.' == word[word.size() - 1]) {
            word = word.substr(0, word.size() - 1);
        }
        else if ('.' == word[0]) {
            word = word.substr(1, word.size() - 1);
        }
        else if ('!' == word[word.size() - 1]) {
            word = word.substr(0, word.size() - 1);
        }
        else if ('!' == word[0]) {
            word = word.substr(1, word.size() - 1);
        }
        else if (',' == word[word.size() - 1]) {
            word = word.substr(0, word.size() - 1);
        }
        else if (','== word[0]) {
            word = word.substr(1, word.size() - 1);
        }
        else if ('?' == word[word.size() - 1]) {
            word = word.substr(0, word.size() - 1);
        }
        else if ('?'== word[0]) {
            word = word.substr(1, word.size() - 1);
        }
        else if ('\"' == word[word.size() - 1]) {
            word = word.substr(0, word.size() - 1);
        }
        else if ('\"'== word[0]) {
            word = word.substr(1, word.size() - 1);
        }

    }
}

int main()
{

    ifstream inputFile("light_brigade.txt"); // Open the file

    if (!inputFile) { // Check if the file opened successfully
        cerr << "Error opening file!" << endl;
        return 1; // Exit with error code
    }

    string line; // line to be parsed.
    int lineNum = 0; // Marks line number
    BST<Node> wordTree;
    Node* match;
    while (getline(inputFile, line)) { // Read line by line
        vector<string> tokens; //contains tokens
        lineNum++;

        //Ignores empty lines and comments.
        if (line.find('#') == string::npos && !line.empty()) {

            //converts all the words in a given line into lower case.
            transform(line.begin(), line.end(), line.begin(), ::tolower);

            //splits line.
            splitLine(line, tokens, ' ');

            //Adds each word found in the line to the tree.
            for (auto i : tokens) {
                Node node(i);

                match = wordTree.search(node);

                //Checks to see if there is already a duplicate of the Node in the tree.
                if(match != nullptr) {

                    //If so, it adds the found line number unto the set of line numbers in that given node.
                    match->addLineNumber(lineNum);
                }
                else {

                    //Otherwise it creates a new node(word) in the tree and adds the current line number to that node.
                    node.addLineNumber(lineNum);
                    wordTree.insert(node);
                }
            }
        }
    }

    wordTree.inorder(); // Inorder traversal (Prints out Words alphabetically and their corresponding line numbers)
    inputFile.close(); // Close the file
    return 0; // Successful execution
}

