#include "project2_first.h"

using namespace std; 
#include <iostream>
#include <fstream> 
#include <string>

Dictionary::Dictionary(){
   //default constructor just because
}

Dictionary::Dictionary(string fname, int tsize){
    //the constructor for the dictionary class 
}


 bool find(string word){
   //boolean for finding word 
   //return true if found, false if not 
   return 0; //just for now
 }
 
 //writeToFile 
 void writeToFile(string fName){
    //use the fstream 
 }

 //readFromFile 
 static Dictionary readFromFile(string fName){
     Dictionary d; 
     //read from the file 
     return d; //just for now
 } 

 int main (int argc, char* argv[]){

  //set up the fstream object and the string 
  ifstream readWriteObject; 
  string line; 
  
  //make sure to pass the smaller dataset for dev purposes 
  readWriteObject.open(argv[1]); 

  int wordsReadIn = 0; 

  while(!readWriteObject.eof()){
   getline(readWriteObject, line); 
   //count the words
   if(line.compare("")!=0) // might or might not need this 
    ++wordsReadIn;
  } //end of while 

  cout<<"Number of Words = "<<wordsReadIn<<endl;

  //close the file at the end 
  readWriteObject.close(); 

  return 0; 
 }
