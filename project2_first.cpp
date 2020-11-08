#include "dictionary.h"
#include "hash24.h"
#include <fstream>
using namespace std; 


 int main (int argc, char* argv[]){
   
 //use ifstream to get the size:
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
  //close the file at the end 
  readWriteObject.close(); 

  //now create the dictionary object using the size you got from here:
  Dictionary d (argv[1], wordsReadIn);

    //write it to file passed in arg 2
    d.writeToFile(argv[2]); 
  return 0; 
 }
