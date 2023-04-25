#include <iostream>
#include <map>
#include <cmath>
#include <vector>
#include <utility>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <list>
#include <numeric>
#include <random>
#include <set>


std::string solve(){
    int x_1, y_1, x_2, y_2, x_3, y_3;
    std::string angleClassification{};
    std::string relLengthClassification{};
    std::cin >> x_1 >> y_1 >> x_2 >> y_2 >> x_3 >> y_3;

    // Determine if the points generate a valid triangle
    double area1 = abs((x_1*(y_2 - y_3) + x_2*(y_3 - y_1) + x_3*(y_1 - y_2)) / 2);

    double side1 = sqrt((x_2-x_1)*(x_2-x_1) + (y_2-y_1)*(y_2-y_1));
    double side2 = sqrt((x_3-x_2)*(x_3-x_2) + (y_3-y_2)*(y_3-y_2));
    double side3 = sqrt((x_1-x_3)*(x_1-x_3) + (y_1-y_3)*(y_1-y_3));

    double s = (side1 + side2 + side3) / 2;
    double area2 = sqrt(s * (s-side1) * (s-side2) * (s-side3));


    if (!area1 && !area2) {
        return "not a triangle";
    }

    // To determine if a triangle is scalene or isosceles, we check if any two sides of the triangle have the same
    // length. If all three sides have different lengths, then the triangle is scalene. Otherwise, if at least two
    // sides have the same length, the triangle is isosceles.


    // Determine if the triangle is scalene or isosceles
    if (side1 != side2 && side2 != side3 && side1 != side3) {
        relLengthClassification = "scalene";
    } else {
        relLengthClassification = "isosceles";
    }


    // To determine if a triangle is right, obtuse, or acute, we need to use the Pythagorean theorem to check if the
    // square of the longest side is equal to the sum of the squares of the other two sides. If the square of the
    // longest side is greater than the sum of the squares of the other two sides, the triangle is obtuse. If the
    // square of the longest side is equal to the sum of the squares of the other two sides, the triangle is right.
    // Otherwise, the triangle is acute.

    // std::vector sides = {side1, side2, side3};
    // std::sort(sides.begin(), sides.end());

    if (side1 >= side2 && side1 >= side3) {
        longestSide = side1;
    } else if (side2 >= side1 && side2 >= side3) {
        longestSide = side2;
    } else {
        longestSide = side3;
    }
    double val1 = longestSide * longestSide;
    double val2 = side1 * side1 + side2 * side2 + side3 * side3 - longestSide * longestSide;
    if (abs(val1 - val2) < 0.0001) {
        angleClassification = "right";
    } else if (val1 > val2) {
        angleClassification = "obtuse";
    } else {
        angleClassification = "acute";
    }

    return relLengthClassification + " " + angleClassification + " " + "triangle";
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int testCases{};
    std::cin >> testCases;
    for (int t = 1; t <= testCases; t++)
    {
        std::string output = solve();
        std::cout << "Case #" << t << ": " << output << "\n";
    }
    return 0;
}