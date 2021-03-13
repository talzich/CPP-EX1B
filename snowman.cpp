#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <array>

#include "snowman.hpp"

using namespace std;
using namespace ariel;

// This method checks the validity of the input
int check_validity(long int number)
{
    string input = to_string(number);
    if (input.size() != INPUT_LENGTH)
    {
        return 0;
    }

    for (int i = 0; i < INPUT_LENGTH; i++)
    {
        if (input.at(i) < '1' || input.at(i) > '4')
        {
            return 0;
        }
    }
    return 1;
}

namespace ariel
{

    /* 
    This method takes the input snowman() received and fetches all the necessary
    parts from the parts vector, puts them in their corresponding locations in an array
    and returns that array
    */
    array<string, NUM_OF_PARTS> fetch_parts(const long int input)
    {

        array<string, NUM_OF_PARTS> build;   // The array that will be returned
        string str_input = to_string(input); // Easy way to iterate through the digits of a number

        int i = 0;
        int j = 0;
        // Placing the parts in their correct locations
        for (auto &e : build)
        {
            j = get_index(str_input.at(i));
            e = parts[i][j];
            i++;
        }
        return build;
    }

    // This function will take a char representation of a single digit from the input
    // snowman() received and returns a int representation of the same digit
    int get_index(char digit)
    {
        int index = digit - '0' - 1;
        return index;
    }

    string snowman(long int number)
    {
        if (check_validity(number) == 0)
        {
            throw invalid_argument("Invalid input: " + to_string(number));
        }

        string output;
        array<string, NUM_OF_PARTS> broken = fetch_parts(number);

        output += (broken[HAT] + "\n");                                                 // Placing hat
        output += broken[LEFT_ARM].at(UPPER);                                           // Placing upper left arm
        output += ("(" + broken[LEFT_EYE] + broken[NOSE] + broken[RIGHT_EYE] + ")");    // Placing face and frame
        output += broken[RIGHT_ARM].at(UPPER);                                          // Placing upper right arm and frame
        output += "\n";
        output += broken[LEFT_ARM].at(LOWER);                                           // Placing upper left arm and frame
        output += ("(" + broken[TORSO] + ")");                                          // Placing torso and frame
        output += broken[RIGHT_ARM].at(LOWER);                                          // Placing upper right arm and frame
        output += "\n";
        output += (WS + "(" + broken[BASE] + ")" + "\n");

        return output;
    }
}
