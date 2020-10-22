#ifndef PROJECT2FIRST
#define PROJECT2FIRST

using namespace std; 
#include <string>

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