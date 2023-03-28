#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

bool isPalindrome(std::string const str)
{
    std::string rev = str;
    std::reverse(rev.begin(), rev.end());
    if (rev == str)
    {
        return true;
    } else {
        return false;
    }
}

int evilStraw(std::string input)
{
    int swaps{};
    int wordLength = input.size();

    // Check if the string already is a palindrome
    if (isPalindrome(input))
    {
        return swaps;
    }

    /* If the input string is not a palindrome, then we can start swapping adjacent symbols to make it a palindrome.
     * We have two different cases, one when the number of characters are even and one where they are odd. */

    if (wordLength % 2)
    {
        /* If the number of characters are odd, we ignore the one in the middle */


    } else {
        /* If the number of characters are even, we ignore the one in the middle and we start searching for a character
         * mismatch in the string*/

        bool mismatch{};
        int i{-1};
        while(!mismatch)
        {
            i++;
            if (input[i] != input[(wordLength-1) - i])
            {
                mismatch = true;
            }
        }

    }
    return swaps;
}


int main(){
    int nrTestCases{};
    std::cin >> nrTestCases;
    for (int c = 0; c < nrTestCases; c++)
    {
        std::string inputString{};
        std::cin >> inputString;

        int swaps{};
        swaps = evilStraw(inputString);
        if (swaps == -1)
        {
            std::cout << "Impossible" << std::endl;
        } else {
            std::cout << swaps << std::endl;
        }
    }
    return 0;
}