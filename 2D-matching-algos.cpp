#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>
#include "2D-matching-algos.h"
using namespace std;

void
naive (vector< vector<matrixType> > &text,
       vector< vector<matrixType> > &pattern,
       int dimensions[2], vector< pair<int,int> > &matches)
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
                    goto label;
                }
            }

          if (l == dimensions[1] && m == dimensions[1])
            matches.push_back (make_pair (i, j));

          label: l = 0;
        }
    }
}

void
baker_bird (vector< vector<matrixType> > &text,
            vector< vector<matrixType> > &pattern,
            int dimensions[2], vector< pair<int,int> > &matches)
{

}


/* For this algo to work, maximum dimension of pattern matrix is 31 and
   only binary values are allowed i.e. 0 or 1 */
void
hashing (vector< vector<matrixType> > &text,
         vector< vector<matrixType> > &pattern,
         int dimensions[2], vector< pair<int, int> > &matches)
{
  int i,j;
  int span = dimensions[0] - dimensions[1] + 1;

  uint32_t hash_pattern[ dimensions[1] ];
  uint32_t hash_text[ dimensions[0] ][ span ];
  uint32_t temp;

  /* Preprocessing: Calculating pattern's hash of every row. */
  for (i = 0; i < dimensions[1]; i++)
    {
      hash_pattern[i] = 0;
      for (j = 0; j < dimensions[1]; j++)
        {
          temp = pattern[i][j] & 1;
          hash_pattern[i] |= temp << (dimensions[1] - j - 1);
        }
    }

  /* Preprocessing: Calculating text's hash of every row with length as that
     of pattern. */
  uint32_t bit_reset_mask = 0;
  for (i = 0; i < dimensions[1]; i++)
    bit_reset_mask |= 1 << i;

  for (i = 0; i < dimensions[0]; i++)
    {
      hash_text[i][0] = 0;
      for (j = 0; j < dimensions[1]; j++)
        {
          temp = text[i][j] & 1;
          hash_text[i][0] |= temp << (dimensions[1] - j - 1);
        }

      /* The hash values are a function of previous hash value. */
      for (j = 1; j < span; j++)
        {
          temp = (hash_text[i][j-1] << 1) & bit_reset_mask;
          hash_text[i][j] = temp + (text[i][j + dimensions[1] - 1] & 1);
        }
    }

    /* Preprocessing for KMP algorithm */
    int lps[ dimensions[0] + 1 ];

    i = 0, j = -1;
    lps[i] = j;
    while (i < dimensions[0])
      {
        while (j >= 0 && hash_pattern[i] != hash_pattern[j])
          {
            j = lps[j];
          }
        i++;
        j++;
        lps[i] = j;
      }

    /* Appliying KMP search on columns. */
    for (int column = 0; column < span; column++)
      {
        i = 0; j = 0;
        while (i < dimensions[0])
          {
            while (j >= 0 && hash_text[i][column] != hash_pattern[j])
              j = lps[j];

            i++; j++;

            if (j == dimensions[1])
              {
                matches.push_back (make_pair (i - dimensions[1], column));
                j = lps[j];
              }
          }
      }
}
