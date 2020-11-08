#ifndef DICTIONARY_H
#define DICTIONARY_H

using namespace std;
#include "hash24.h" 
#include <iostream>
#include <string>
#include <vector> 
#include <utility>


class Dictionary {
 
 private: 
  //save the initial hash
  Hash24 primaryHash; 
  //Hash Table Vector
  vector<pair<string, pair<vector<string>*,Hash24>>> hashtable; 

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