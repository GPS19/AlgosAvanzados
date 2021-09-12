#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Palindrome
{
public:
    vector<int> palindrome(string &text)
    {
        string spacedText = adaptInitialInput(text);

        return longestPalindromeSubstring(spacedText);
    }

    string adaptInitialInput(string &text)
    {
        string spacedText;

        for (int i = 0; i < text.size(); i++)
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

    vector<int> longestPalindromeSubstring(string &text)
    {
        vector<int> palindromeLenghts(text.size(), 0);
        int center = 0, rightBound = 0;

        for (int i = 1; i < text.size() - 1; i++)
        {
            int mirror = 2 * center - i;

            if (i < rightBound)
            {
                palindromeLenghts[i] = min(rightBound - 1, palindromeLenghts[mirror]);
            }

            int a = i + (1 + palindromeLenghts[i]);
            int b = i - (1 + palindromeLenghts[i]);

            while (text[a] == text[b] && b > -1 && a < text.size())
            {
                palindromeLenghts[i]++;
                a++;
                b--;
            }

            if (i + palindromeLenghts[i] > rightBound)
            {
                center = i;
                rightBound = i + palindromeLenghts[i];
            }
        }

        vector<int>::iterator centerIt = max_element(palindromeLenghts.begin(), palindromeLenghts.end());
        center = distance(palindromeLenghts.begin(), centerIt);

        return {(center - palindromeLenghts[center]) / 2, palindromeLenghts[center]};
    }
};
