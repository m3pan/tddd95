#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <unordered_map>

/*
 * MIN SWAPS TO MAKE PALINDROME
 * Given a string, what is the minimum number of adjacent swaps required to convert a string into a palindrome.
 * If not possible, return -1.
 *
 * https://molchevskyi.medium.com/best-solutions-for-microsoft-interview-tasks-min-swaps-to-make-palindrome-e931689f8cae
 */


bool isPalindrome(std::string const word)
{
    std::string reversed = word;
    std::reverse(reversed.begin(), reversed.end());
    if (reversed == word)
    {
        return true;
    } else {
        return false;
    }
}


bool impossibleToTransform(std::string const word)
{
    /* Count occurrences of the characters in the word to detect whether the word is not possible to transform to a
     * palindrome or not.
     * */

    std::unordered_map<char, int> freq;
    for (char i : word)
    {
        ++freq[i];
    }

    // Count odd occurrences
    int oddCount = 0;
    for (auto &x : freq)
    {
        if (x.second % 2 != 0)
        {
            ++oddCount;
        }
    }

    if (oddCount == 1 && word.length() % 2 == 0 || oddCount > 1)
    {
        return true;
    }
    else {
        return false;
    }
}


int evilStraw(std::string word) {
    int swaps{};
    int wordLength = word.length();

    if (isPalindrome(word))
    {
        return swaps;
    }
    if (impossibleToTransform(word))
    {
        return -1;
    }

    /* If the input string is not a palindrome and possible to transform into one, then we can start swapping adjacent
     * symbols to make it a palindrome. We have two different cases, one when the number of characters are even and
     * one where they are odd. */

    int outerLeft = 0;
    int outerRight = wordLength - 1;

    while (outerLeft <= outerRight) {

        if (word[outerLeft] != word[outerRight]) {
            /* If the mirrored characters doesn't match each other we need to look for the swap which matches left
             * or right with the shortest "swap-distance"*/

            int innerLeft = outerLeft + 1;
            int innerRight = outerRight - 1;

            bool found{};
            while (!found && innerLeft < outerRight && outerLeft < innerRight) {
                // Iterate with the inner indexes from their outer index to the other edge

                if (word[innerLeft] == word[outerRight]) {
                    swaps += (innerLeft - outerLeft);
                    for (int i = innerLeft; i > outerLeft; i--)
                    /* Swap all characters between the outerLeft and the innerLeft index one step to the right */
                    {
                        word[i] = word[i - 1];
                    }
                    word[outerLeft] = word[outerRight];
                    found = true;
                }
                else if (word[innerRight] == word[outerLeft]) {
                    swaps += (outerRight - innerRight);
                    for (int i = innerRight; i < outerRight; ++i)
                    /* Swap all characters between the outerRight and the innerRight index one step to the left */
                    {
                        word[i] = word[i + 1];
                    }
                    word[outerRight] = word[outerLeft];
                    found = true;
                }
                innerLeft++, innerRight--;
            }
        }
        outerLeft++;
        outerRight--;
    }
    return swaps;
}


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

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