#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "2D-matching-algos.h"
using namespace std;

int* dimensions = new int[2];
vector< vector<matrixType> > text;
vector< vector<matrixType> > pattern;

vector<int> matches;

string options[] = { "0", "Naive 2-D Pattern Matching Algorithm", "x", "x", "x" };

void fetch_input (int);

int
main ()
{
  int choice;

  do
    {
      cout << "\033[2J\033[1;1H";
      cout << "\033[1;36m********************************************************************************\n\033[0m";
      cout << "                \033[1;4;32m2-D String Matching and Pattern Identification\n\033[0m";
      cout << "\033[1;36m********************************************************************************\n\033[0m";

      cout << "\n\n\033[1;34mOptions:\n";
      cout << "1. Naive 2-D Pattern Matching Algorithm\n";
      cout << "2. \n";
      cout << "3. \n";
      cout << "4. \n";
      cout << "5. Quit\n";
      cout << "\nChoose an option (1-5): \033[0m";

      cin >> choice;

      if (choice >= 1 && choice <= 3 )
        {
          int input_choice;

          cout << "\n\n\033[1;35mChoose an option to provide input to " << options[choice] << ":\n";
          cout << "1. Provide custom input\n";
          cout << "2. Generate xyx distribution\n";
          cout << "\nChoose an option: ";

          cin >> input_choice;
          cout << "\n";

          fetch_input (input_choice);
        }

      switch (choice)
        {
          case 1: naive (text, pattern, dimensions, matches);
                  cout <<"\n"<< matches[0];
                  exit(1);
                  break;
        }

    } while (choice != 5);
}

void
fetch_input (int choice)
{
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

  if (choice == 2)
    {
      cout<<"x";
    }
}
