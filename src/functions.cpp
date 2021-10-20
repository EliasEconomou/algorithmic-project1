#include <iostream>
using namespace std;

#include "stdio.h"
#include "../include/functions.hpp"

void hello() {
    cout << "Hello cpp" << endl; 
}

void goodbye(int n) {
    for( int i = 0; i < n; ++i )
    cout << "Goodbye" << endl;
}