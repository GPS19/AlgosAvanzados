/*
Pablo Yamamoto Magaña       - A01022382
Gianluca Beltrán Bianchi    - A01029098
Santiago Kohn Espinosa      - A01029109

Actividad Integradora 1 

This activity is divided in three parts:
 - Part one
    - Find the matching code on a transmission text
 - Part two 
    - Find the largest palindrome for each transmission text
 - Part three
    - Fin the largest substring between both transmission texts
*/

#include "data.h"

using namespace std;

vector<string> readCodes(vector<string> codeFiles) // Function in charge of reading all of the mcodes and sstoring them into a vector
{
    vector<string> codes;
    string line;

    for (string code : codeFiles)
    {
        ifstream MyFile;
        MyFile.open(code);
        getline(MyFile, line, '\n');
        codes.push_back(line);
    }

    return codes;
}

void printPartOne(Transmission T, vector<string> codes) // Function used to print part one of the program, recieves a transmission object and the vector of codes
{
    for (int i = 0; i < codes.size(); i++) // For every code search if it matches with the transmission text
    {
        vector<int> partOne(T.searchCode(codes[i])); // Store results of the search
        if (partOne[0])                              // This means that the code was found so we print true
        {
            cout << "true"
                 << " " << partOne[1] << " " << partOne[2] << endl;
        }
        else
        {
            cout << "false" << endl;
        }
    }
}

void printPartTwo(Transmission T) // Function used to print part two of the program, recieves a transmission object
{
    vector<int> partTwo(T.findLongestPalindrome()); // Store the result of the palindrome search
    for (int i = 0; i < partTwo.size(); i++)
    {
        cout << partTwo[i] << " ";
    }
    cout << endl;
}

void printPartThree(Transmission t1, Transmission t2) // Function used to print part three of the program, recieves two transmission objects to compare them to each other
{
    vector<int> partThree(t1.findLongestCommonSubstring(t2)); // Store the result of the substring search
    for (int i = 0; i < partThree.size(); i++)
    {
        cout << partThree[i] << " ";
    }
    cout << endl;
}

int main()
{
    Transmission transmission1("transmission1.txt"); // Create the first transmission object with the first transmission text
    Transmission transmission2("transmission2.txt"); // Create the second transmission object with the second transmission text

    vector<string> codes(readCodes({"mcode1.txt", "mcode2.txt", "mcode3.txt"})); // Call readCodes, to fill the codes vector

    // Print everything that is needed
    printPartOne(transmission1, codes);
    printPartOne(transmission2, codes);
    cout << endl;
    printPartTwo(transmission1);
    printPartTwo(transmission2);
    cout << endl;
    printPartThree(transmission1, transmission2);
}
