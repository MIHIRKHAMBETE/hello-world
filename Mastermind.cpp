//
//  main.cpp
//  FinalProject (Mastermind)
//
//  Created by Mihir Khambete on 1/29/18.
//  Copyright © 2018 Mihir Khambete. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <vector>
#include <math.h>
#include <string>
#include <sstream>

using namespace std;

int secret_int(int numdigs = 4){
    int final_int = 0;
    std::vector<int> digits = {1,2,3,4,5,6,7,8,9};
    int index = rand() % digits.size();
    final_int += pow(10,numdigs -1)*digits[index];
    digits.erase(digits.begin()+index);
    digits.push_back(0);
    for(int i = numdigs -2; i >= 0;i--){
        int pick = rand() % digits.size();
        final_int += pow(10,i)*digits[pick];
        digits.erase(digits.begin()+pick);
    }
    return final_int;
}

class Manager
{
    private:
        int hidden = secret_int();
        std::string str_form = std::to_string(hidden);
    public:
        int bulls(std::string guess){
            int same = 0;
            for(int i = 0;i < guess.size();i++){
                if(guess[i] == str_form[i]){
                    same ++;
                }
            }
            return same;
        }
        int cows(std::string guess){
            int match = 0;
            for(int i = 0;i < guess.size();i++){
                char next_digit = str_form[i];
                std::size_t index = guess.find(next_digit);
                if (index!=std::string::npos){
                    match++;
                }
            }
            return match;
        }
    int get_secret_int(){
        return hidden;
    }
};

int main() {
    srand(time(0));
    Manager m;
    cout << "Welcome to Mastermind/Bulls and Cows! \n";
    cout << "Try to guess the secret 4-digit number (all distinct digits) \n";
    int num_guesses = 9;
    bool win = false;
    while (num_guesses > 0){
        std::string input;
        cout << "you have " << num_guesses << " guesses left. \n";
        cout << "---- \n";
        cout << "Enter your next guess \n";
        cin >> input;
        int bull = m.bulls(input);
        int cow = m.cows(input);
        cout << "The number of bulls is " << bull << " and number of cows is " << cow << "\n";
        if(bull == 4){
            win = true;
            break;
        } else {
            if(num_guesses > 1){
                cout << "still got more guesses left! \n";
            } else if(num_guesses == 1){
                cout << "Sorry! Try again \n";
            }
            
        }
        num_guesses--;
    }
    if(win){
        cout << "Good job! \n";
    } else {
        cout << " :(  \n";
    }
    cout << "The secret number was " << m.get_secret_int() << endl;
    return 0;
}
