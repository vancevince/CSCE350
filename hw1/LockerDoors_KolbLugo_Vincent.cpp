/* Copyright 2020
 * Vincent Kolb-Lugo
 * 9/5/21
 *
 * Locker Doors
 *
 * Instructions: 
 *   There are n lockers in a hallway, numbered sequentailly from 1 to n. 
 *   Initially, all the locker doors are closed. You make n passes by
 *   the lockers, each time starting with locker #1. On the ith pass, 
 *   i.e. i = 1, 2, ..., n, you toggle the door every ith locker: if the door
 *   is closed, you open it; if it is open, you close it. After the last 
 *   pass, display the following output:
 *
 *  a) Which locker doors are open and which ones are closed.
 *  b) Give the count of open locker doors.
 *
 * Hint: Accept user input for the number of passes and number of locker doors.
 */
#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main(int argc, char *argv[]) {
  // Get the number of lockers/passes
  int n, passes, pass_count;
  cout << "Enter a number: ";
  cin >> n;
  cout << "Enter the number of passes: ";
  cin >> passes;
  cout << endl;

  // vector lockers represents the number of lockers in the hallway
  // lockers initialized to 0 for "closed"; 1 signals an "open" locker
  vector<int> lockers(n, 0);
  pass_count = 1;

  while (pass_count <= passes) {
    for (size_t i = 0; i < lockers.size(); ++i) {
      if ((i+1) % pass_count == 0) {
        if (lockers[i] == 1)
          lockers[i] = 0;
        else
          lockers[i] = 1;
      }
    }
    ++pass_count;
  }

  // display the number of open lockers and identify each locker
  // also display the number of closed lockers and identify each
  int open = 0;
  int closed = 0;
  for (size_t i =0; i < lockers.size(); ++i) {
    if (lockers[i] == 1)
      ++open;
    else
      ++closed;
  }
  cout << "Number of OPEN LOCKERS: " << open << endl;
  cout << "Opened lockers: ";
  for (size_t i = 0; i < lockers.size(); ++i) {
    if (lockers[i] == 1)
      cout << (i + 1) << " ";
  }
  cout << endl;

  return 0;
}
