#include <iostream>
#include <vector>
#include <fstream> // file stream
#include <sstream>
#include <map>

int main() {

    // split input by '\r' and blank space into a nested list
    std::ifstream ifs{"../exercises/input/help.txt"};       // cwd: TDDD95/cmake-build-debug/
    std::string line{};
    std::vector <std::vector<std::string>> lines{};
    std::string word{};


    while (getline(ifs, line, '\r'))
    {
        std::istringstream iss_string(line);
        std::vector <std::string> lineVec{};

        while (iss_string >> word) lineVec.push_back(word);

        lines.push_back(lineVec);
    }

    int nr = std::stoi(lines[0][0]);
    lines.erase(lines.begin(), lines.begin() + 1);

    for (int i = 0; i < nr; i++)
    {
        std::vector<std::string> line1 {lines[i]};
        std::vector<std::string> line2 {lines[i + 1]};
        std::string output{};
        for (int j = 0; j < line1.size(); j++)
        {
            // adds the placeholders to maps
            std::map<char, std::string> patterns1;
            std::map<char, std::string> patterns2;

            if (line1[j][0] == '<' && line2[j][0]!= '<')
            {
                if (patterns1.count(line1[j][1]) == false)
                // if we haven't added the placeholder to the map
                {
                    patterns1[line1[j][1]] = line2[j];
                }
                if (patterns1[line1[j][1]] == line2[j])
                {
                    output += ' ' + line2[j];
                }

            }

            else if (line2[j][0] == '<' && line1[j][0]!= '<')
            {
                if (patterns2.count(line2[j][1]) == false)
                    // if we haven't added the placeholder to the map
                {
                    patterns2[line2[j][1]] = line1[j];
                }
                if (patterns2[line2[j][1]] == line1[j])
                {
                    output += ' ' + line1[j];
                }
            }
        }
        std::cout << output << std::endl;
    }

    return 0;
}