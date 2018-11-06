#include<bits/stdc++.h>
#include<cstring>

using namespace std;

// int trie[1000000][26];
// int failure[1000000];
// vector< int > output;

int total = 1;

  void build(vector<char> &str , vector< vector<int> > &trie )
  {
    int curr=0;
    for(int i=0 ; i < str.size() ; i++)
    {
      int ch = str[i] - 'a' ;
      if( trie[curr][ch] == -1 )
      {
        trie[curr][ch]=total;
        total++;
      }
      curr = trie[curr][ch];
    }
  }

  void ahoCorasick( vector < vector<char> > &textArray , int numStrings , vector< vector<int> > &trie , vector <int> &failure )
  {
    // memset(trie , -1 , sizeof(trie) );

    //Build the trie data structure
    //i.e. transition states
    for(int i = 0 ; i < numStrings ; i++)
    {
      build(textArray[i] , trie);
    }

    //add a transition edge from all the node at the starting state i.e. 0
    //to starting state itself
    for(int i = 0 ; i < 26 ; i++)
    {
      if( trie[0][i] == -1 )
        trie[0][i]=0;
    }

    // memset( failure , -1 , sizeof(failure) );

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

            failure[ trie[state][i] ] = trie[fail][i];

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

    textArrayPrime.resize(numStrings);

    for(int i = 0 ; i < numStrings ; i++)
      textArrayPrime[i].resize(numStrings);

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



int main()
{
vector< vector <char> > text;
vector< vector <char> > pattern;
vector< vector <int> > textArray;
vector< vector <int> > patternArray;
vector< pair<int , int> > output;
vector< vector<int> > trie ;
vector< int > failure;  

 
 int dimensions[2];

 cout<<"Enter Dimensions : "<<endl;
 cout<<"Text : ";
 cin>>dimensions[0];
 cout<<"Pattern : ";
 cin>>dimensions[1];

 trie.resize( dimensions[0]*dimensions[0] );
 failure.resize( dimensions[0]*dimensions[0] );
 text.resize(dimensions[0] );
 pattern.resize(dimensions[1]);


 for(int i =0 ; i < dimensions[0]*dimensions[0] ; i++ )
 	{
 		trie[i].resize(26 , -1);
 		fill(trie[i].begin(), trie[i].end() , -1 );
 	}
 
 fill( failure.begin() , failure.end() , -1 );
 
 
 cout<<endl<<"Enter Text : "<<endl;
 for (int i = 0; i < dimensions[0]; i++)
   {
     text[i].resize (dimensions[0]);
     for (int j = 0; j < dimensions[0]; j++)
       {
         cin >> text[i][j];
       }
   }

 cout<<"Enter Pattern : "<<endl;
 for (int i = 0; i < dimensions[1]; i++)
   {
     pattern[i].resize (dimensions[1]);
     for (int j = 0; j < dimensions[1]; j++)
       {
         cin >> pattern[i][j];
       }
   }

   ahoCorasick(pattern , dimensions[1]  , trie , failure );
   makeTA(text , dimensions[0] , textArray  , trie , failure );
   makeTA(pattern , dimensions[1] , patternArray , trie , failure );
   
   for(int i = 0 ; i < dimensions[0] ; i++ )
      kmp_substring( patternArray[ dimensions[1]-1 ] , textArray[i] , i+1 , dimensions[1]  , output);



  // cout<<"Text :"<<endl;
  // cout<<"\t  ";
  // for(int i =0 ; i < dimensions[0] ; i++)
  //   cout<<i+1<<" ";

  // for(int i =0 ; i < dimensions[0] ; i++ )
  //   {
  //     cout<<endl<<"\t"<<i+1<<" ";
  //     for(int j = 0 ; j < dimensions[0] ; j++)
  //       cout<<text[i][j]<<" ";
  //   }

  // cout<<endl<<endl<<"Pattern : ";
  // for(int i =0 ; i < dimensions[1] ; i++ )
  //   {
  //     cout<<endl;
  //     for(int j = 0 ; j < dimensions[1] ; j++)
  //       cout<<pattern[i][j]<<" ";
  //   }
  //   cout<<endl<<endl;


  if(output.size() == 0)
    cout<<"No Match Found "<<endl;
  else
    for(auto it = output.begin() ; it != output.end() ; it++ )
      cout<<"Found at Row : "<<it->first <<" Column : "<<it->second <<endl;

      // for (int i = 0; i < dimensions[0]; i++)
      //   {
      //     cout<<endl;
      //     for (int j = 0; j < dimensions[0]; j++)
      //       {
      //         cout << textArray[i][j]<<" ";
      //       }
      //   }
      
      // cout<<"Enter Pattern : "<<endl;
      // for (int i = 0; i < dimensions[1]; i++)
      //   {
      //     cout<<endl;
      //     for (int j = 0; j < dimensions[1]; j++)
      //       {
      //         cout << patternArray[i][j]<<" ";
      //       }
      //   }

 return 0 ;
}
