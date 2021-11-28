/**
 * Copyright 2021
 * Vince Kolb-Lugo
 * 10/20/2021
 *
 * Implement a QuickSort Algorithm
 * Requirements:
 *   - must read an input ASCII file that contains unsorted floating-point
 *     numbers separated by a blank space
 *   - Choose a pivot using the median-of-tree method
 *   - must produce an output ASCII file that contains the sorted floating-point
 *     numbers separated by a blank space
 *   - input and output filenames must be passed as command line arguments
 *   - must output execution time in milliseconds
 */
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::sort;
using std::swap;
using std::string;
using std::ofstream;
using namespace std::chrono;

//insertion sort for small partitions
void InsertionSort(vector<float> &array, int start, int end) {
  for (int j = start; j < end; ++j) {
    for (int i = j; i < end; ++i) {
      if (array[i+1] < array[i]) swap (array[i], array[i+1]);
    }
  }
}

// before fucntion didn't have start and end params
int Partition(vector<float> &array, int start, int end) {

  //int partition;
  float left = array[start];// grab the left-most element
  float right = array[end];// grab the right-most element
  float mid = array[(start+end)/2];// grab the middle element

  //helper array: sorts the three values
  vector<float> helper = {left, mid, right};
  sort (helper.begin(), helper.end());
  
  //reset array's left-most, middle, and right-most values
  array[start] = helper[0];
  array[(start+end)/2] = helper[1];
  array[end] = helper[2];

  //swap the middle value with middle value with array[array.size()-1]
  swap (array[end-1] , array[(start+end)/2]);
  
  //set up the pivot and the counters
  float pivot = helper[1];
  int i = start;
  int j = end-1;
  while(i<j) {
    do{--j;} while(array[j] > pivot);
    do{++i;} while(array[i] < pivot);
    swap (array[i], array[j]);
  }
  //cout << "Pivot: " << pivot << endl;
  //cout << endl << "I: " << array[i] << endl;
  //cout << "J: " << array[j] << endl;
  swap (array[i], array[j]);// swap the i and j values
  swap (array[i], array[end-1]);// swap the i and pivot

  //return partition;
  return i;
}

void QuickSort(vector<float> &array, int start, int end){
  if (end <= start) return;
  if (end <= start + 2) {//use insertion sort instead of quicksort
    InsertionSort(array, start, end);
    return;
  }

  int split = Partition(array, start, end);

  QuickSort(array, start, split-1);//left partition
  QuickSort(array, split+1, end);//right partition
}

void QuickSort(vector<float> &array) {
  QuickSort(array,0, array.size()-1);
}


//Constants
const int HIGH = 100;
const int LOW = -100;
const int SIZE = 10;//change to 1000 before submitting

int main(int argc, char *argv[]) {
  //MOVE VARIABLE DECLARATIONS AND INITIALIZATIONS HERE

  //capture command line arugements
  if (argc != 3) {
    cout << "Usage: ./a.out <arg1> <arg2>\n";
    exit(0);
  }
  char *arg1 = argv[1];
  char *arg2 = argv[2];

  //create the input and output text files
  ofstream inFile;
  ofstream outFile;
  inFile.open(arg1);
  outFile.open(arg2);

  //generate random values and store in inFile
  vector<float> test (SIZE);
  srand (time(NULL));
  for (size_t i = 0; i < test.size(); ++i) { 
    test[i] = LOW + static_cast<float>(rand()) /(static_cast<float>(RAND_MAX/(HIGH-LOW)));
    inFile << test[i] << endl;
    cout << "Rand num generated: " << test[i] << endl;
  }
  inFile.close();

  //USED FOR TESTING PURPOSES
  //Presort
  //cout << "Presort Order: " << endl;
  //for (size_t i = 0; i < test.size(); ++i)
  //  cout << test[i] << " ";
  //cout << endl << endl;

  //read values from input text in a new vector
  vector<float> solution;
  string line = "";
  std::ifstream inputfile(arg1);
  if (inputfile.is_open()) {
    while (getline (inputfile, line)) {
      float floatLine = stof(line);
      solution.push_back(floatLine);
      cout << "Read from file: " << floatLine << endl;
    }
  }
  inputfile.close();

  //sort the new vector
  auto start = high_resolution_clock::now();
  QuickSort(solution);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  
  //USED FOR TESTING PURPOSES
  //Postsort and calculate exection time
  //auto start = high_resolution_clock::now();
  //QuickSort(test);
  //auto stop = high_resolution_clock::now();
  //auto duration = duration_cast<milliseconds>(stop - start);

  //write sorted vector to outputfile
  for (size_t i = 0; i < solution.size(); ++i) {
    outFile << solution[i] << endl;
    cout << "Solution: " << solution[i] << endl;
  }
  outFile.close();

  cout << endl << "Sort time: " << duration.count() << " milliseconds" << endl << endl;

  //USED FOR TESTING PURPOSES
  //cout << "Postsort Order: ";
  //for (size_t i = 0; i < test.size(); ++i)
  //  cout << test[i] << endl;
  //cout << endl << endl;
  //cout << "Sort time: " << duration.count() << " milliseconds." << endl << endl; 

  return 0;
}
