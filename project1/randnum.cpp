#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using std::ofstream;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::sort;

//constants
const int HIGH = 100;
const int LOW = -100;

int main (int argc, char *argv[]) {
  //attempting to get command line arguments
  if (argc != 3) {
    cout << "Usage: ./a.out <arg1> <arg2> <arg3>\n";
    exit(0);
  }
  char *arg1 = argv[1];
  char *arg2 = argv[2];

  //create an input text
  ofstream myfile;
  //myfile.open("input.txt");
  //myfile.open(inFile);
  myfile.open(arg1);

  //declare a vector to store randomly generated numbers
  int size = 10;
  vector<float> randomList(size);
  srand (time(NULL));
  for (size_t i = 0; i < size; ++i) {
    randomList[i] = LOW + static_cast<float>(rand()) /(static_cast<float>(RAND_MAX/(HIGH-LOW)));
    cout << "Generated: " << randomList[i] << endl;
    myfile << randomList[i] << endl; //was " "
  }
  myfile.close();
  cout << endl << "RandomList size: " << randomList.size();
  cout << endl << endl;

  //read values from input text into a new vector
  vector<float> test;
  cout << "Read and Print Values from text: " << endl;
  string line = ""; 
  std::ifstream inputfile ("input.txt");
  if (inputfile.is_open()){
    while(getline (inputfile, line)) {
      cout << "LINE: " << line << "\n";//was " "
      float floatLine = stof(line);
      test.push_back(floatLine);
    }
  }
  inputfile.close();
  cout << endl << "Test size: " << test.size();
  cout << endl << endl;

  //sort the vector then print values to new text
  ofstream outfile;
  //outfile.open("output.txt");
  //outfile.open(outFile);
  outfile.open(arg2);
  cout << "Sorted array:" << endl;
  sort (test.begin(), test.end());
  for (size_t i = 0; i < test.size(); ++i){
    //the next two lines still produce the 0s error
    cout << "TEST: " << test[i] << endl;
    outfile << test[i] << endl;
    
    //this if statement stops the 0s error
    //if (test[i] == 0) { /*empty*/  }
    //else {
    //  cout << "TEST: " << test[i] << endl;
    //  outfile << test[i] << endl;
    //}
  }
  outfile.close();
  cout << endl << "Test size after sort: " << test.size() << endl;
  
  return 0;
}
/**Notes
 * Fixed reading in 0s error by not declaring a size for the vector that reads in values
 * from a text file.
 */
