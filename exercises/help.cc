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
    std::string unknown = "liu";
    std::string nr_st;
    int nr;
    char ws;

    // std::cin >> nr;
    std::getline (std::cin, nr_st, '\r');
    std::stringstream ss(nr_st);
    ss >> nr;

    std::cout << "nr: " << nr << std::endl;
    // ws = std::cin.get(); // stream out any whitespace
    std::string line;

    for (int i = 0; i < 2*nr; i++)
    {
        std::getline (std::cin, line, '\r');
        std::cout << "line: " << line << std::endl;

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
                if (output.empty()) output = unknown;
                else output += ' ' + unknown;
            }
        }
        std::cout << output << '\n';
    }

    return 0;
}