#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <queue>
#include <time.h>
#include "2D-matching-algos.h"
using namespace std;



//By me From
  int total ;

  void ahoCorasick( vector < vector<char> > &textArray , int numStrings , vector< vector<int> > &trie , vector <int> &failure , vector <int> &out)
  {
    //Build the trie data structure
    //i.e. transition states
    for(unsigned long int j = 0 ; j < numStrings ; j++)
    {
      int curr=0;
      for(int i=0 ; i < textArray[j].size() ; i++)
      {
        int ch = textArray[j][i] - 'a' ;
        if( trie[curr][ch] == -1 )
        {
          trie[curr][ch]=total;
          total++;
        }
        curr = trie[curr][ch];
      }
      out[curr] |= (1 << j);
    }

    //add a transition edge from all the node at the starting state i.e. 0
    //to starting state itself
    for(int i = 0 ; i < 26 ; i++)
    {
      if( trie[0][i] == -1 )
        trie[0][i]=0;
    }

    queue <int> level;

    //Nodes that are directly linked from the starting node
    //push them into queue
    for(int i = 0 ; i < 26 ; i++)
    {
      if( trie[0][i] != 0 )
      {
          failure[ trie[0][i] ] = 0;
          level.push(trie[0][i]);
      }
    }

    // Failure function
    // find the ancestor of the node where
    // this node has to go after fail
    // i.e. if there is any prefix above this node

    while(level.size())
    {
      int state = level.front();
      level.pop();

      for(int i = 0 ; i < 26 ; i++)
      {
          if( trie[state][i] != -1 )
          {
            int fail = failure[state];

            while( trie[fail][i] == -1 )
              fail = failure[fail];

            fail = trie[fail][i];
            failure[ trie[state][i] ] = fail;
 
            out[trie[state][i]] |= out[fail];

            level.push( trie[state][i] );
          }
      }
    }//while of level

  }//ahoCorasick

  int nextState(int currState, char nextInput , vector < vector<int>> &trie , vector <int> &failure )
  {
      int nextState = currState;
      int ch = nextInput - 'a';

      // If transition is not defined, use failure function
      while ( trie[nextState][ch] == -1 )
          nextState = failure[nextState];

      return trie[nextState][ch];
  }

  void makeTA( vector < vector<char> > &textArray , int numStrings , vector< vector <int> >  &textArrayPrime , vector <vector <int> > &trie , vector<int> &failure )
  {
    for(int i = 0 ; i < numStrings ; i++)
      textArrayPrime[0][i] =  nextState( 0 , textArray[0][i] , trie , failure);

    for(int i = 0 ; i < numStrings ; i++ )
    {
      for(int j = 1 ; j < numStrings ; j++ )
      {
          textArrayPrime[j][i] =   nextState( textArrayPrime[j-1][i] , textArray[j][i] , trie , failure ) ;
      }
    }

  }


  void make_pie_table(vector<int> &substr, int m, int pie_table[])
  {
      int prev_match = 0;
      pie_table[0] = 0;
      int i = 1;
      for ( ; i < m ; )
      {
          if ( substr[i] != substr[prev_match] )
          {
              if (prev_match == 0)
              {
                  pie_table[i] = 0;
                  i++;
              }
              else
                  prev_match = pie_table[prev_match - 1];
          }
          else
          {
              prev_match++;
              pie_table[i++] = prev_match;
          }
      }
  }


  void kmp_substring(vector<int> &substr, vector<int> &str , int row ,int dimension , vector< pair<int, int> > &output )
  {
    int m = substr.size();
    int n = str.size();

    int sub_index = 0;
    int pie_table[m];
      make_pie_table(substr, m, pie_table);

      int flag = 0  ;
      for(int str_index = 0 ; str_index < n ; )
      {
          if( substr[ sub_index ] == str[ str_index ])
          {
              str_index++;
              sub_index++;
          }
        else if (str_index < n && substr[ sub_index ] != str[ str_index ])
        {
              if (sub_index != 0)
                  sub_index = pie_table[sub_index - 1];
              else
                  str_index++ ;
          }
          if (sub_index == m)
            {
             // cout<<"Found at Row : "<<row<<" Column : "<<str_index - sub_index<<endl;
             output.push_back(make_pair(row-(dimension-1) , str_index - sub_index + 1) );
             sub_index = pie_table[sub_index - 1] ;
            }
        }
  }

void
baker_bird (vector< vector<matrixType> > &text,
            vector< vector<matrixType> > &pattern,
            int dimensions[2], vector< pair<int,int> > &matches)
{
  total = 1;
  vector< vector <int> > textArrayPrime( dimensions[0], vector<int> (dimensions[0]) );
  vector< vector <int> > patternArrayPrime( dimensions[1], vector<int> (dimensions[1]) );
  vector< vector<int> > trie( dimensions[0]*dimensions[0] , vector<int> (26, -1) ) ;
  vector< int > failure( dimensions[0]*dimensions[0], -1 );
  vector <int > out(dimensions[0]*dimensions[0]);

  ahoCorasick(pattern , dimensions[1]  , trie , failure , out);
  makeTA(text , dimensions[0] , textArrayPrime  , trie , failure );
  makeTA(pattern , dimensions[1] , patternArrayPrime, trie , failure );

  for(int i = 0 ; i < dimensions[0] ; i++ )
    kmp_substring( patternArrayPrime[ dimensions[1]-1 ] , textArrayPrime[i] , i+1 , dimensions[1]  , matches);

}

//Till Here

//BYR

bool search(  vector <char> &arr , unsigned int k , int *col , vector < vector <int> > &trie , vector <int> &failure , vector <int> &out ) 
{ 
  int currentState = 0;
  int i = 0 ; 
  for(i = 0 ; i <(*col) && i < arr.size() ; i++)
    currentState = nextState(currentState , arr[i] , trie , failure); 
  
    for ( ; i < arr.size(); ++i) 
    { 
        currentState = nextState(currentState, arr[i] , trie , failure); 
  
        if (out[currentState] == 0) 
             continue; 
  
        if (out[currentState] & (1 << k)) 
        { 
              (*col) = i;
              return true ; 
        } 
    } 
    return false ;
}


void BYR(vector< vector<matrixType> > &text,
       vector< vector<matrixType> > &pattern,
       int dimensions[2], vector< pair<int,int> > &matches)
{
  total = 1;
  int n = dimensions[0]; 
  int m = dimensions[1];
  vector< vector<int> > trie( dimensions[0]*dimensions[0] , vector<int> (26, -1) ) ;
  vector< int > failure( dimensions[0]*dimensions[0], -1 );
  vector <int > out(dimensions[0]*dimensions[0]+1);

  ahoCorasick(pattern , m , trie , failure , out);

  int nextline = 0 ; 
  int col ; 
  for( int row = m-1 ; row < n ; row=row+m )
  {  
        col = 0;  
    for( int i = 0 ; i <= m ; i++ )
    {
      if( search( text[row] , i , &col , trie , failure , out) )
      {
        for( int j = 0 ; j < i ; j++)
        {
          if(!search(  text[row-i+j] , j , &col , trie , failure , out) )
            {
              nextline = 1;
              break;
            }
        }
        for( int j = 1 ; j < m-i ; j++)
        {
          if( (row+j >= n) || !search( text[ row+j ] , i+j , &col , trie , failure , out) )
          {
            nextline = 1;
            break;
          }
        }
        if (nextline==0)
          {
            matches.push_back( make_pair(row-i+1 , col-m+1  ) );
          }
        else
          nextline=0;  
      }
    }
  }
}

//TIll here



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
