#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <array>
#include <gsl/gsl>

#include "snowman.hpp"

using namespace std;
using namespace ariel;

int check_validity(long int number){
    string input = to_string(number);
    if (input.size() != INPUT_LENGTH){return 0;}
        
    for (int i = 0; i < INPUT_LENGTH; i++)
    {
        if (input.at(i) < '1' || input.at(i) > '4'){return 0;}
            
    }
    return 1;
}

namespace ariel{

    /* 
    This method takes the input snowman()received and fetches all the necessary
    parts from the parts matrix, puts them in their corresponding locations in an array
    and returns that array
    */
    array<string, NUM_OF_PARTS> fetch_parts(const long int input){

    array<string, NUM_OF_PARTS> build;
    string str_input = to_string(input);
    
    int i = 0;
    int j = 0;
    for(auto& e : build){
        j = get_index(str_input.at(i));
        e = gsl::at(gsl::at(parts, i), j);
        i++;
    }
    return build;
}

    int get_index(char digit){
    int index = digit - '0' - 1;
    return index;
}

    string snowman(long int number){
        if(check_validity(number) == 0){
            throw invalid_argument("Invalid input: " + to_string(number));
        }
        
        string output;
        array<string, NUM_OF_PARTS> parts = fetch_parts(number);

        output += ( parts[HAT]+"\n" ); // Placing hat
        output += parts[LEFT_ARM].at(UPPER); // Placing upper left arm
        output += ( "(" + parts[LEFT_EYE] + parts[NOSE] + parts[RIGHT_EYE] + ")" ); // Placing face and frame
        output += parts[RIGHT_ARM].at(UPPER); // Placing upper right arm and frame
        output += "\n";
        output += parts[LEFT_ARM].at(LOWER); // Placing upper left arm and frame
        output += ( "(" + parts[TORSO] + ")" ); // Placing torso and frame
        output += parts[RIGHT_ARM].at(LOWER); // Placing upper right arm and frame
        output += "\n";
        output += (WS + "(" + parts[BASE] + ")" + "\n");

        return output;
    }
}

// int produce_valid_input(){
//     int c;
//     string input = "";
//     for (int i = 0; i < 8; i++){
//         c = 1 + (rand() % 4); // Generating a random digit between 1 and 4 
//         input += to_string(c);; // Converting the random digit to a char and concatinating it to the string 
//     }
//     return stoi(input);
// }

// int main() {
// 	cout << ariel::snowman(11114411) << endl;   /* Should print:
// _===_
// (.,.)
// ( : )
// ( : )
// 	*/
// 	cout << ariel::snowman(33232124) << endl;   /* Should print:
//    _
//   /_\
// \(o_O)
//  (] [)>
//  (   )
// 	*/

//     cout << ariel::snowman(42121344) << endl; 
//     cout << ariel::snowman(11343321) << endl; 
// 	try {
//         cout << ariel::snowman(100) << endl;
// 		cout << ariel::snowman(5) << endl;   // Exception - not a valid code
         
//         cout << ariel::snowman(123412341234) << endl; 
//         cout << ariel::snowman(-5) << endl; 
//         cout << ariel::snowman(12368885) << endl;

// 	} catch (exception& ex) {
// 	 	cout << "caught exception: " << ex.what() << endl;  // should print "Invalid code '5'"
// 	}

//     cout << ariel::snowman(12341234) << endl;

//     int input;
//     for(int i = 0; i < 25; i++){
//         input = produce_valid_input();
//         cout << snowman(input) << endl; 
//     }
// }
