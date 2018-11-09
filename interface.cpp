#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "2D-matching-algos.h"
#include "test.h"
using namespace std;

int* dimensions = new int[2];
vector< vector<matrixType> > text;
vector< vector<matrixType> > pattern;

vector< pair<int,int> > matches;

string options[] = { "0", "Naive 2-D Matching Algorithm",
                     "Baker Bird Matching Algorithm",
                     "x", "2-D Matching using Hash values",
                     "Test running time for these Algorithms" };

void fetch_input (int);
void display_results ();

int
main ()
{
  char choice;

  do
    {
      cout << "\033[2J\033[1;1H";
      cout << "\033[1;34m********************************************************************************\n\033[0m";
      cout << "                 \033[1;36m2-D String Matching and Pattern Identification\n\033[0m";
      cout << "\033[1;34m********************************************************************************\n\033[0m";

      cout << "\n\n\033[1;32mOptions:\n";
      cout << "1. " << options[1] << endl;
      cout << "2. " << options[2] << endl;
      cout << "3. " << options[3] << endl;
      cout << "4. " << options[4] << endl;
      cout << "5. " << options[5] << endl;
      cout << "6. Quit\n";
      cout << "\n\033[1;31mChoose an option (1-6): \033[0m";

      cin >> choice;

      int input_choice;
      if (choice >= '1' && choice <= '4')
        {
          cout << "\n\n\033[1;32mChoose an option to provide input to "
               << options[(int)choice-48] << ":\n";
          cout << "1. Provide custom input\n";
          cout << "2. Generate random input\n";
          cout << "3. Naive worst case\n";
          cout << "\n\033[1;31mChoose an option: ";

          cin >> input_choice;
          cout << "\n";

          fetch_input (input_choice);
        }

      cout << "\033[1;33m";
      const clock_t begin_time = clock();
      switch (choice)
        {
          case '1': naive (text, pattern, dimensions, matches);
                    cout << "Clock Cycles Taken: " << (long int)( clock () - begin_time );
                    if(input_choice != 3)
                      display_results ();
                    break;

          case '2': baker_bird (text, pattern, dimensions, matches);
                    cout << "Clock Cycles Taken: " << (long int)( clock () - begin_time );
                    if(input_choice != 3)
                      display_results ();
                    break;

          case '3': BYR (text, pattern, dimensions, matches);
                    cout << "Clock Cycles Taken: " << (long int)( clock () - begin_time );
                    if(input_choice != 3)
                      display_results ();
                    break;

          case '4': hashing (text, pattern, dimensions, matches);
                    cout << "Clock Cycles Taken: " << (long int)( clock () - begin_time );
                    if(input_choice != 3)
                      display_results ();
                    break;

          case '5': test ();
                    break;

          default : cout << "\n\033[1;31mWrong input!\n";
                    break;
        }

      cout << "\n\033[1;33mEnter any key to continue.\n";
      char any;
      cin >> any;

    } while (choice != '6');

  return 0;
}

void
fetch_input (int choice)
{
  cout << "\033[1;33m";
  cout << "\nEnter order of text matrix (e.g. 10): ";
  cin >> dimensions[0];

  char c;
  text.resize (dimensions[0]);
  if (choice == 1)
    {
      cout << "Enter elements of text matrix:\n";
      for (int i = 0; i < dimensions[0]; i++)
        {
          text[i].resize (dimensions[0]);
          for (int j = 0; j < dimensions[0]; j++)
            {
              cin >> text[i][j];
            }
        }
    }
  else if (choice == 2)
    {
      for (int i = 0; i < dimensions[0]; i++)
        {
          text[i].resize (dimensions[0]);
          for (int j = 0; j < dimensions[0]; j++)
            {
              text[i][j] = (rand() % 26) + 'a'; //get random character
              // cout<<text[i][j]<<endl;
            }
        }
    }
  else if (choice == 3)
    {
      for (int i = 0; i < dimensions[0]; i++)
        {
          text[i].resize (dimensions[0]);
          for (int j = 0; j < dimensions[0]; j++)
            {
              text[i][j] = 'a'; //get random character
            }
        }
    }

  cout << "\nEnter order of pattern matrix: ";
  cin >> dimensions[1];

  pattern.resize (dimensions[1]);
  if (choice == 1)
    {
      cout << "\nEnter elements of pattern matrix:\n";
      for (int i = 0; i < dimensions[1]; i++)
        {
          pattern[i].resize (dimensions[1]);
          for (int j = 0; j < dimensions[1]; j++)
            {
              cin >> pattern[i][j];
            }
        }
    }

  if (choice == 2 || choice == 3)
    {
      int x = rand() % (dimensions[0] - dimensions[1] + 1);
      int y = rand() % (dimensions[0] - dimensions[1] + 1);
      cout << "\nExpected: (" << x << ", " << y << ")" << endl;
      for (int i = 0; i < dimensions[1]; i++)
        {
          pattern[i].resize (dimensions[1]);
          for (int j = 0; j < dimensions[1]; j++)
            {
              pattern[i][j] = text[i + x][j + y];
            }
        }
    }
}

void
display_results ()
{
  int number_of_matches = matches.size ();
  if (number_of_matches == 0)
    {
      cout << "\n\033[1;31mNo matches found." << endl;
      return;
    }

  cout << "\n\033[1;32mMatches found at the folowing indicies:" << endl;
  int i;
  for (i = 0; i < number_of_matches; i++)
    {
      cout << "(" << matches[i].first << ", " << matches[i].second << ")\n";
    }

  matches.clear ();
}
