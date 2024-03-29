#include "2D-matching-algos.h"
#include <time.h>
#include <bits/stdc++.h>

int* dim = new int[2];
vector< vector<matrixType> > txt;// (1000, vector<matrixType>(1000));
vector< vector<matrixType> > patt;// (1000, vector<matrixType>(1000));

vector< pair<int,int> > op;

bool
test_random ()
{
  cout << "Running on random input..." << endl;

  int text_size, pattern_size;
  int i, j;
  int x, y;
  long int clock_cycles;
  string str;
  clock_t begin_time;

  ofstream nv("test-results/naive-random", ios::trunc);
  ofstream bb("test-results/baker_bird-random", ios::trunc);
  ofstream hs("test-results/hashing-random", ios::trunc);
  ofstream by("test-results/byr-random", ios::trunc);

  for (text_size = 2; text_size <= 1024; text_size *= 2)
    {
      txt.resize(text_size);
      for (i = 0; i < text_size; i++)
        {
          txt[i].resize (text_size);
          for (j = 0; j < text_size; j++)
            {
              txt[i][j] = (rand() % 26) + 'a'; //get random character
            }
        }
      for (pattern_size = 1; pattern_size < text_size; pattern_size *= 2)
        {
          patt.resize (pattern_size);
          x = rand() % (text_size - pattern_size + 1);
          y = rand() % (text_size - pattern_size + 1);
          //cout << "\nExpected: (" << x << ", " << y << ")" << endl;
          for (i = 0; i < pattern_size; i++)
            {
              patt[i].resize (pattern_size);
              for (j = 0; j < pattern_size; j++)
                {
                  patt[i][j] = txt[i + x][j + y];
                }
            }

          dim[0] = text_size;
          dim[1] = pattern_size;

          begin_time = clock();
          op.clear ();
          naive (txt, patt, dim, op);
          if (find (op.begin (), op.end (), make_pair (x, y)) == op.end ())
          {
            return false;
          }
          str = to_string ( (long int)( clock () - begin_time ) );
          nv << str << endl;

          begin_time = clock();
          op.clear ();
          baker_bird (txt, patt, dim, op);
          if (find (op.begin (), op.end (), make_pair (x, y)) == op.end ())
          {
            return false;
          }
          str = to_string ( (long int)( clock () - begin_time ) );
          bb << str << endl;

          if (pattern_size > 2 && pattern_size < 32)
            {
              begin_time = clock();
              op.clear ();
              BYR (txt, patt, dim, op);
              if (find (op.begin (), op.end (), make_pair (x, y)) == op.end ())
              {
                return false;
              }
              str = to_string ( (long int)( clock () - begin_time ) );
              by << str << endl;
            }

          if (pattern_size < 32)
            {
              begin_time = clock();
              op.clear ();
              hashing (txt, patt, dim, op);
              if (find (op.begin (), op.end (), make_pair (x, y)) == op.end ())
              {
                return false;
              }
              str = to_string ( (long int)( clock () - begin_time ) );
              hs << str << endl;
            }
          //cout<<endl;
        }
    }

  nv.close ();
  bb.close ();
  hs.close ();
  by.close ();

  return true;
}

void
test_naive ()
{
  cout << "Running on naive's worst case..." << endl;
  cout << "This will take around 2 minutes!" << endl;

  int text_size, pattern_size;
  int i, j;
  int x, y;
  long int clock_cycles;
  string str;
  clock_t begin_time;

  ofstream nv("test-results/naive-naive-worst", ios::trunc);
  ofstream bb("test-results/baker_bird-naive-worst", ios::trunc);
  ofstream hs("test-results/hashing-naive-worst", ios::trunc);
  ofstream by("test-results/byr-naive-worst", ios::trunc);

  for (text_size = 2; text_size <= 512; text_size *= 2)
    {
      txt.resize(text_size);
      for (i = 0; i < text_size; i++)
        {
          txt[i].resize (text_size);
          for (j = 0; j < text_size; j++)
            {
              txt[i][j] = 'a'; //get random character
            }
        }

      for (pattern_size = 1; pattern_size < text_size; pattern_size *= 2)
        {
          patt.resize (pattern_size);
          x = rand() % (text_size - pattern_size + 1);
          y = rand() % (text_size - pattern_size + 1);
          //cout << "\nExpected: (" << x << ", " << y << ")" << endl;
          for (i = 0; i < pattern_size; i++)
            {
              patt[i].resize (pattern_size);
              for (j = 0; j < pattern_size; j++)
                {
                  patt[i][j] = txt[i + x][j + y];
                }
            }

          dim[0] = text_size;
          dim[1] = pattern_size;

          begin_time = clock();
          //cout<<text_size<<" "<<pattern_size<<endl;
          naive (txt, patt, dim, op);
          str = to_string ( (long int)( clock () - begin_time ) );
          nv << str << endl;

          begin_time = clock();
          //cout<<text_size<<" "<<pattern_size<<endl;
          baker_bird (txt, patt, dim, op);
          str = to_string ( (long int)( clock () - begin_time ) );
          bb << str << endl;

          if (pattern_size > 2 && pattern_size < 32)
            {
              begin_time = clock();
              //cout<<text_size<<" "<<pattern_size<<endl;
              BYR (txt, patt, dim, op);
              str = to_string ( (long int)( clock () - begin_time ) );
              by << str << endl;
            }

          if (pattern_size < 32)
            {
              begin_time = clock();
              //cout<<text_size<<" "<<pattern_size<<endl;
              hashing (txt, patt, dim, op);
              str = to_string ( (long int)( clock () - begin_time ) );
              hs << str << endl;
            }
          //cout<<endl;
        }
    }

  nv.close ();
  bb.close ();
  hs.close ();
  by.close ();
}

void
test_binary ()
{
  cout << "Running on binary input..." << endl;

  int text_size, pattern_size;
  int i, j;
  int x, y;
  long int clock_cycles;
  string str;
  clock_t begin_time;

  ofstream nv("test-results/naive-binary", ios::trunc);
  ofstream bb("test-results/baker_bird-binary", ios::trunc);
  ofstream hs("test-results/hashing-binary", ios::trunc);
  ofstream by("test-results/byr-binary", ios::trunc);

  for (text_size = 2; text_size <= 1024; text_size *= 2)
    {
      txt.resize(text_size);
      for (i = 0; i < text_size; i++)
        {
          txt[i].resize (text_size);
          for (j = 0; j < text_size; j++)
            {
              txt[i][j] = (rand() % 2) + 'a'; //get random character
            }
        }
      for (pattern_size = 1; pattern_size < text_size; pattern_size *= 2)
        {
          patt.resize (pattern_size);
          x = rand() % (text_size - pattern_size + 1);
          y = rand() % (text_size - pattern_size + 1);
          //cout << "\nExpected: (" << x << ", " << y << ")" << endl;
          for (i = 0; i < pattern_size; i++)
            {
              patt[i].resize (pattern_size);
              for (j = 0; j < pattern_size; j++)
                {
                  patt[i][j] = txt[i + x][j + y];
                }
            }

          dim[0] = text_size;
          dim[1] = pattern_size;

          begin_time = clock();
          //cout<<text_size<<" "<<pattern_size<<endl;
          naive (txt, patt, dim, op);
          str = to_string ( (long int)( clock () - begin_time ) );
          nv << str << endl;

          begin_time = clock();
          //cout<<text_size<<" "<<pattern_size<<endl;
          baker_bird (txt, patt, dim, op);
          str = to_string ( (long int)( clock () - begin_time ) );
          bb << str << endl;

          if (pattern_size > 2 && pattern_size < 32)
            {
              begin_time = clock();
              //cout<<text_size<<" "<<pattern_size<<endl;
              BYR (txt, patt, dim, op);
              str = to_string ( (long int)( clock () - begin_time ) );
              by << str << endl;
            }

          if (pattern_size < 32)
            {
              begin_time = clock();
              //cout<<text_size<<" "<<pattern_size<<endl;
              hashing (txt, patt, dim, op);
              str = to_string ( (long int)( clock () - begin_time ) );
              hs << str << endl;
            }
          //cout<<endl;
        }
    }

  nv.close ();
  bb.close ();
  hs.close ();
  by.close ();
}

void
test ()
{
  bool passed = false;
  cout << "The tests' clock cycles will be saved on 'test-results' folder";
  cout << endl;
  test_binary ();
  passed = test_random ();
  test_naive ();

  if(passed == true)
    cout << "All Tests Passed" << endl;
  else
    cout << "Failed!" << endl;
}
