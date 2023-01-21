#include <iostream>
#include <vector>
#include <fstream> // file stream
#include <sstream>
#include <map>

int main() {

    // split input by '\r' and blank space into a nested list
    // std::ifstream ifs{"../exercises/input/help.txt"} cwd: TDDD95/cmake-build-debug/
    std::vector <std::vector <std::string> > lines;
    std::string word;
    std::string unknown = "hmm";
    std::string nr_st;
    int nr;
    char ws;

    // std::cin >> nr;
    std::getline (std::cin, nr_st, '\r'); // change to '\r' when reading from file
    std::stringstream ss(nr_st);
    ss >> nr;

    std::cout << "nr: " << nr << std::endl;
    // ws = std::cin.get(); // stream out any whitespace
    std::string line;
    int restart = 0;

    for (int i = 0; i < 2*nr; i++)
    {
        std::getline (std::cin, line, '\r');
        std::istringstream iss_string(line);
        std::vector <std::string> lineVec;

        while (iss_string >> word) lineVec.push_back(word);

        lines.push_back(lineVec);
    }

    for (int i = 0; i < 2*nr; i = i+2)
    {
        std::vector<std::string> line1 = lines[i];
        std::vector<std::string> line2 = lines[i + 1];
        std::string output;

        // adds the placeholders to maps
        std::map<std::string, std::string> patterns1;
        std::map<std::string, std::string> patterns2;

        for (int j = 0; j < line1.size(); j++)
        {
            if (line1[j][0] == '<' && line2[j][0]!= '<')
            {
                if (patterns1.count(line1[j]) == false)
                // if we haven't added the placeholder to the map
                {
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
                    // if we haven't added the placeholder to the map
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
                // kolla först om båda finns, sen om ena finns och typ restart = true om ingen finns?
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
                    // only here if pattern1.count isn't true
                    patterns1[line1[j]] = patterns2[line2[j]];
                    if (output.empty()) output = patterns2[line2[j]];
                    else output += ' ' + patterns2[line2[j]];
                    restart = 1;
                }
                else {
                    // vi känner inte till nån
                    if (output.empty()) output = unknown;
                    else output += ' ' + unknown;
                    restart += 1;
                }
            }
            if (j == line1.size() - 1 && restart == 1)
            {
                j = -1;
                restart = 2;
                output = "";
            }
        }
        std::cout << output << '\n';
    }

    return 0;
}