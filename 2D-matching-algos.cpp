#include <string>
#include <vector>
#include "2D-matching-algos.h"
using namespace std;

void naive ( vector< vector<matrixType> > &text, vector< vector<matrixType> > &pattern, int dimensions[2], vector<int> &matches )
{
  int i,j;
  int l,m;

  int span = dimensions[0] - dimensions[1] + 1;

  for (i = 0; i < span; i++)
    {
      for (j = 0; j < span; j++)
        {
          for (l = 0; l < dimensions[1]; l++)
            {
              for (m = 0; m < dimensions[1]; m++)
                {
                  if (text[i+l][j+m] != pattern[l][m])
                    break;
                }
            }

          if (l == dimensions[1] && m == dimensions[1])
            matches.push_back (i*dimensions[0] + j);
        }
    }
}
