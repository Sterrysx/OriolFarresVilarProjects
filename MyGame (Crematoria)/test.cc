#include <iostream>
using namespace std;

int round = 0;
pair<int, int> left_sun = {0,0}; 
pair<int, int> right_sun = {40,80};   

void advance_sun() {
    right_sun.first += 2;
    left_sun.second += 2;
    if (round%20 == 0)  {
        if (round%40 == 0) {
            left_sun = {0,0};
            right_sun = {40,80};
        }
        else {
            left_sun = {0,40};
            right_sun = {80,0};
        }
    }
}

int main() {
    int round = 0;
    while (round < 120) {

        
    }

}