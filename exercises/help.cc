#include <iostream>
#include <vector>
#include <fstream> // file stream
#include <sstream>
#include <map>

int main() {

    /* Reading input from file? Set delimiter in getline() to '\r'
     * Reading input from terminal? Set delimiter in getline() to '\n' (default)
     *
     * nr: number of inputs
     * lines: a nested vector with the input sentences, each word or placeholder stored separately
     * unknown: default word to use when a placeholder doesn't have any constraint
     * */

    std::string unknown = "nej";

    int nr;
    std::string nr_st;
    std::getline (std::cin, nr_st, '\n');
    std::stringstream ss(nr_st);
    ss >> nr;

    std::string line;
    std::string word;
    std::vector <std::vector <std::string> > lines;

    for (int i = 0; i < 2*nr; i++)
    {
        std::getline (std::cin, line, '\n');
        std::istringstream iss_string(line);
        std::vector <std::string> lineVec;

        while (iss_string >> word) lineVec.push_back(word);
        lines.push_back(lineVec);
    }

    int restart = false;
    int nrOfRestarts = 0;

    for (int i = 0; i < 2*nr; i = i+2)
    {
        std::vector<std::string> line1 = lines[i];
        std::vector<std::string> line2 = lines[i + 1];
        std::string output;

        std::map<std::string, std::string> patterns1;
        std::map<std::string, std::string> patterns2;

        for (int j = 0; j < line1.size(); j++)
        {
            if (line1[j][0] == '<' && line2[j][0]!= '<')
            {
                if (patterns1.count(line1[j]) == false)
                {
                    // Add placeholder to map if it's unknown
                    patterns1[line1[j]] = line2[j];
                }
                if (patterns1[line1[j]] == line2[j])
                {
                    if (output.empty()) output = line2[j];
                    else output += ' ' + line2[j];
                }
            }
            else if (line2[j][0] == '<' && line1[j][0]!= '<')
            {
                if (patterns2.count(line2[j]) == false)
                    // Add placeholder to map if it's unknown
                {
                    patterns2[line2[j]] = line1[j];
                }
                if (patterns2[line2[j]] == line1[j])
                {
                    if (output.empty()) output = line1[j];
                    else output += ' ' + line1[j];
                }
                else
                {
                    output = '-';
                    break;
                }
            }
            else if (line2[j][0] != '<' && line1[j][0]!= '<')
            {
                if (line2[j] == line1[j])
                {
                    if (output.empty()) output = line1[j];
                    else output += ' ' + line1[j];
                }
                else
                {
                    output = '-';
                    break;
                }
            }
            else if (line2[j][0] == '<' && line1[j][0] == '<')
            {
                /* When both lines stores a placeholder, see if one of them (or both) are known. If neither is known,
                 * we want to want to restart the loop when we've reached the end of the line since we might get new
                 * information later in the line. */

                if (patterns1.count(line1[j]) == true) {
                    if (patterns2.count(line2[j]) == true) {
                        if (patterns2[line2[j]] != patterns1[line1[j]]) {
                            output = '-';
                            break;
                        } else {
                            // hit vill vi komma efter restart
                            output = patterns2[line2[j]];
                        }
                    } else {
                        // we only know patterns1[line1[j]]
                        patterns2[line2[j]] = patterns1[line1[j]];
                        if (output.empty()) output = patterns1[line1[j]];
                        else output += ' ' + patterns1[line1[j]];
                    }
                }
                else if (patterns2.count(line2[j]) == true)
                {
                    // We're only here if pattern1.count isn't true
                    patterns1[line1[j]] = patterns2[line2[j]];
                    if (output.empty()) output = patterns2[line2[j]];
                    else output += ' ' + patterns2[line2[j]];
                } else {
                    // Restart the iteration if neither of the placeholders is known
                    if (output.empty()) output = unknown;
                    else output += ' ' + unknown;
                    restart  = true;
                }
            }
            if (j == line1.size() - 1 && restart)
            {
                if (nrOfRestarts > line1.size())
                {
                    // We've definitely restarted this process enough times now :)
                    break;
                }

                j = -1;
                restart = false;
                nrOfRestarts += 1;
                output = "";
            }
        }
        std::cout << output << '\n';
    }
    return 0;
}