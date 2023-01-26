#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

 struct interval
{
    float d1;
    float d2;
    int i;
};
bool compareIntervals(const interval &lhs, const interval &rhs)
{
    return lhs.d1 < rhs.d1;
}

std::vector <interval> cover(float A, float B, std::vector <interval> intervalSet);

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string AB_st;
    float A, B;

    while(std::getline (std::cin, AB_st, '\n')) //!! never stops with terminal input
    {
        std::cout << "\nnew interval: " << "\n";
        std::stringstream ss1(AB_st);
        ss1 >> A; ss1 >> B;

        int n;
        std::string n_st;
        std::getline (std::cin, n_st, '\n');
        std::stringstream ss2(n_st);
        ss2 >> n;

        std::string line;
        std::vector <interval> lines;

        for (int i = 0; i < n; i++)
        {
            std::getline (std::cin, line, '\n');
            std::istringstream iss_string(line);
            std::vector <interval> lineVec;

            interval i1;
            iss_string >> i1.d1;
            iss_string >> i1.d2;
            i1.i = i;
            lines.push_back(i1);
        }

        std::vector <interval> result = cover(A, B, lines);
        for (interval r : result)
        {
            std::cout << r.i << " ";
        }
    }
    return 0;
}

std::vector <interval> cover(float A, float B, std::vector <interval> intervalSet)
{
    std::sort(intervalSet.begin(), intervalSet.end(), compareIntervals);
    float limit = A;
    std::vector <interval> chosenSet;

    interval curr_interval;
    int count{};
    for (int i = 0; i <= intervalSet.size(); i++)
    {
        if (limit >= B && !chosenSet.empty())
        {
            break;
        }

        curr_interval = intervalSet[i];

        if(curr_interval.d2 < limit) {
            // The interval is short and doesn't draw our limit further
            continue;
        }
        if (curr_interval.d1 > limit)
        // The interval leaves us with a discontinuity in the interval
        {
            interval impossible{-1,-1,-1};
            chosenSet = {impossible};
            break;
        } else {
            /* The interval is useful but might overlap with the previous interval */
            if (chosenSet.empty()) {
                limit = curr_interval.d2;
                chosenSet.push_back(curr_interval);
                count += 1;
                continue;
            }
            if (curr_interval.d1 <= std::max(chosenSet[count-1].d1, A) && curr_interval.d2 >= std::min(chosenSet[count-1].d2, B))
            {
                // The interval is overlapped by the next => exchange chosenSet(count) with our new
                chosenSet[count-1] = curr_interval;
                limit = curr_interval.d2;
                continue;
            }
            limit = curr_interval.d2;
            chosenSet.push_back(curr_interval);
            count += 1;
            if (i == intervalSet.size() - 1 && limit < B)
            {
                interval impossible{-1,-1,-1};
                chosenSet = {impossible};
                break;
            }
            // auto next = *(&interval + 1);
        }

        if (limit >= B) break;
    }

    return chosenSet;
}