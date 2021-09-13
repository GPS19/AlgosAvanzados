#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Palindrome
{
public:
    vector<int> palindrome(string &text) // Method used to intialize palindrome
    {
        string spacedText = adaptInitialInput(text); // Adapt the input string so that it can be used acordingly

        return longestPalindromeSubstring(spacedText);
    }

    string adaptInitialInput(string &text)
    {
        string spacedText;

        for (int i = 0; i < text.size(); i++) // Add a space between all characters unless current char or previous char is a space itself
        {
            if (text[i] != ' ' and text[i - 1] != ' ')
            {
                spacedText.push_back(' ');
            }
            spacedText.push_back(tolower(text[i]));
        }
        spacedText.push_back(' ');

        return spacedText;
    }

    vector<int> longestPalindromeSubstring(string &text) // Main method for finding the longest palindrome
    {
        vector<int> palindromeLenghts(text.size(), 0);
        int center = 0, rightBound = 0; // Keep two pointers, one to the center of the largest palindrome and the other to the right bound of the palindrome, index where it ends

        for (int i = 1; i < text.size() - 1; i++) // Iterate trhough the lenght of the text
        {
            int mirror = 2 * center - i; // Precalculate mirror value of current char

            if (i < rightBound) // If current index inside of the biggest palindrome
            {
                palindromeLenghts[i] = min(rightBound - 1, palindromeLenghts[mirror]); // Update the value of the biggest palindrome at thhis index
            }

            int a = i + (1 + palindromeLenghts[i]); // Pointer that expands to the right searching for mathcing chars
            int b = i - (1 + palindromeLenghts[i]); // Pointer that expands to the left searching for mathcing chars

            while (text[a] == text[b] && b > -1 && a < text.size()) // While the characters are maching at both pointers and the pointers have not exceeded their bounds keep going
            {
                palindromeLenghts[i]++; // If the chars are matching increase palindrome length
                a++;
                b--;
            }

            if (i + palindromeLenghts[i] > rightBound)
            {
                center = i;
                rightBound = i + palindromeLenghts[i];
            }
        }

        vector<int>::iterator centerIt = max_element(palindromeLenghts.begin(), palindromeLenghts.end()); // Get the biggest palindrome from palindrome lenghts vector
        center = distance(palindromeLenghts.begin(), centerIt);                                           // Calculate center of the palindrome

        return {(center - palindromeLenghts[center]) / 2, palindromeLenghts[center]}; // Return the initial position and the length of the palindrome
    }
};
