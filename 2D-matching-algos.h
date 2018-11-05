#ifndef ALGOS_H
#define ALGOS_H

#include <vector>
#include <string>
using namespace std;

typedef char matrixType;

void naive (vector< vector<matrixType> > &text,
            vector< vector<matrixType> > &pattern, int dimensions[2],
            vector< pair<int,int> > &matches);

void hashing (vector< vector<matrixType> > &text,
              vector< vector<matrixType> > &pattern,
              int dimensions[2], vector< pair<int,int> > &matches);

#endif
