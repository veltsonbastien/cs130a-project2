#ifndef PROJECT2FIRST
#define PROJECT2FIRST

#include <string>
//include fstream for the read and write
#include <fstream> 
using namespace std; 

class Dictionary {
 
 private: 
  


 public: 
 //default (probably) just for dev purposes
 Dictionary(); 

 //constructor with string fname and int tsize
 Dictionary(string fname, int tsize); 

 //boolean for finding word 
 bool find(string word); 
 
 //writeToFile 
 void writeToFile(string fName); 

 //readFromFile 
 static Dictionary readFromFile(string fName); 


};



#endif