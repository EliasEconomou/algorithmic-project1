#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <algorithm>
#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <vector>

void hello();
void goodbye(int);

//Parse dataset and return a vector of dataset's vectors.
std::vector<std::vector<double>> parsing_lsh(void);



#endif