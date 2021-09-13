#include <iostream>
#include <vector>
#include <fstream>
#include "boyerMoore.h"
#include "longestPalindrome.h"
#include "longestCommonSubstring.h"

using namespace std;

#pragma once
class Transmission
{
public:
    vector<string> transmission;

    Transmission(string fileName) // Read the transmission text and store each line in a vector
    {
        ifstream MyFile;
        MyFile.open(fileName);
        string line;

        while (!MyFile.eof())
        {
            getline(MyFile, line, '\n');
            transmission.push_back(line);
        }
    }

    vector<int> searchCode(string code) // Method used to search for the matching code in the text, using Boyer Moore algorithm
    {
        Search searcher; // Initialize Search object with Boyer Moore method
        vector<int> ans;
        for (int i = 0; i < transmission.size(); i++) // For every line of transmission call Boyer Moore
        {
            vector<int> a(searcher.boyerMoore(transmission[i], code));

            if (!a.empty()) // If the string was matched return
            {
                ans.push_back(1);
                ans.push_back(i);
                ans.push_back(a[0]);
                return ans;
            }
        }

        if (ans.empty())
        {
            ans.push_back(0);
        }

        return ans;
    }

    vector<int> findLongestPalindrome() // Method used to search for the largest palindrome in the text
    {
        Palindrome longestPalindrome; // Initialize longest palindrome object
        vector<int> ans(3, 0);
        for (int i = 0; i < transmission.size(); i++) // For every line of transmission call longest plaindrome
        {
            vector<int> a = longestPalindrome.palindrome(transmission[i]);

            if (ans[2] < a[1]) // Check if last palindrome found is bigger than the biggest palindrome up to this point, if it is, replace
            {
                ans[0] = i;
                ans[1] = a[0];
                ans[2] = a[1];
            }
        }

        return ans;
    }

    vector<int> findLongestCommonSubstring(Transmission t2) // Method used to search for the longest common substring between both transmission files
    {
        LCS longesCSubstring; // Initialize LCS
        vector<int> ans(3, 0);

        for (int i = 0; i < transmission.size(); i++) // For every line of transmission 1 search for a match with all of the lines of transmission 2
        {
            for (int j = 0; j < t2.transmission.size(); j++)
            {
                vector<int> a(longesCSubstring.longestCommonSubstring(transmission[i], t2.transmission[j]));
                if (a.at(0) > ans.at(2)) // If last substring found is bigger than the previous biggest, replace biggest substring
                {
                    ans.at(0) = i;
                    ans.at(1) = a.at(1);
                    ans.at(2) = a.at(0);
                }
            }
        }

        return ans;
    }
};
