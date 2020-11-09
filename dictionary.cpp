#include "dictionary.h"
#include "hash24.h"
#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <utility>
#include <cstring>

using namespace std; 


Dictionary::Dictionary(){


}

Dictionary::Dictionary(string fname, int tsize){
  //the Constructor for the Dictionary class: 

  if(tsize == 0) return;

  //FIRST, we need to declare all of our variables we'll need for stats printing: 
    Hash24 currentHash; 
  //Max Collisions as a pair:
    pair<int,vector<string>> maxCollisions; maxCollisions.first = 0;  
  //all the counts: 
    int zeroWords=0, oneWord=0, twoWords=0, threeWords=0, fourWords=0, fiveWords=0,
        sixWords=0, sevenWords=0, eightWords=0, nineWords=0, tenWords=0, 
        elevenWords=0, twelveWords=0, thirteenWords=0, fourteenWords=0, fifteenWords=0,
        sixteenWords=0, seventeenWords=0, eighteenWords=0, nineteenWords=0, twentyWords=0;

  //all the tries: 
    int oneTry=0, twoTries=0, threeTries=0, fourTries=0, fiveTries=0,
        sixTries=0, sevenTries=0, eightTries=0, nineTries=0, tenTries=0, 
        elevenTries=0, twelveTries=0, thirteenTries=0, fourteenTries=0, fifteenTries=0,
        sixteenTries=0, seventeenTries=0, eighteenTries=0, nineteenTries=0, twentyTries=0;

  //int averageTried needs to be based on this from example 
  //((3141)+(808*2)+(220*3)+(57*4)+(7*5)+(7*6)+(1*7))/((3141+808+220+57+7+7+1))
    double averageHashesTried = 0.0;

  //we also need a vector of vector<string> because we need an inital vector to play around with
    vector<vector<string>> tempVector(tsize); 
    for(vector<string> v: tempVector){
      v.resize(0); //resize each to zero
    }

  //while here, we will also resize  our Dictionary's vector to our size
    hashtable.resize(tsize);  
    for(int i = 0; i<tsize; i++){
    //initially set some values to make sure: 
    //set primary hash table string to blank
     hashtable.at(i).first = ""; 
    //set secondary hash table vector to null
    hashtable.at(i).second.first = nullptr;
    }

  //SECOND we begin hashing: 

  //2a) Reading from the File
  //use ifstream to get the size:
      ifstream readObject; 
      string line;  
  //make sure to pass the smaller dataset (PA_2_dataset_10000.txt) for dev purposes: 
      readObject.open(fname); 
      while(!readObject.eof()){
  //ALL THE MAGIC HAPPENS BETWEEN HERE vvv
      getline(readObject, line); 
  //set the index for this line using the Dictionary's hash:
      int indexToAdd = (primaryHash.hash(line))%tsize;
  //now I have the index, put this word at that index in both tempVector and hashtable as it's value 
      tempVector.at(indexToAdd).push_back(line); 
      //before adding to hashtable's value, make sure that it's empty
      if(hashtable.at(indexToAdd).first.compare("") == 0){
        //that means it's the first value we're adding
        hashtable.at(indexToAdd).first = line; 
      }

  //AND HERE! ^^^
  //close the file at the end 
      //readObject.clear();
      //readObject.close(); 
      } //end of while loop

  //START THE SECOND PASS 
  for(int i = 0; i<tsize; i++){
    
    //do some pre-lim checks
    if(tempVector.at(i).size() == 0){
      //the vector is empty, don't waste your time just update zeroWords count and continue 
      zeroWords++;
      continue; 
    } else if (tempVector.at(i).size() == 1){
      //the vector only has one input, you don't need to hash anything
      oneWord++;
      continue;
    }

    //set an int for how many collisions happened on the trials of this pass 
    int collisionCounter = 0; 

    //update the max counter if need be 
    if( tempVector.at(i).size() > maxCollisions.first ){
      maxCollisions.first = tempVector.at(i).size();
      maxCollisions.second = tempVector.at(i);  
    }

    //check if we're updating one of the count variables for stats 
    if(tempVector.at(i).size()>=1 && tempVector.at(i).size()<=20){
     //i'm able to update one of the variables for stats 
      switch(tempVector.at(i).size()) {
        case 2:
          twoWords++;
          break;
        case 3:
          threeWords++;
          break;
        case 4:
          fourWords++;
          break;
        case 5:
          fiveWords++;
          break;
        case 6:
          sixWords++;
          break;
        case 7:
          sevenWords++;
          break;
        case 8:
          eightWords++;
          break;
        case 9:
          nineWords++;
          break;
        case 10:
          tenWords++;
          break;
        case 11:
          elevenWords++;
          break;
        case 12:
          twelveWords++;
          break;
        case 13:
          thirteenWords++;
          break;
        case 14:
          fourteenWords++;
          break;
        case 15:
          fifteenWords++;
          break;
        case 16:
          sixteenWords++;
          break;
        case 17:
          seventeenWords++;
          break;
        case 18:
          eighteenWords++;
          break;
        case 19:
          nineteenWords++;
          break;
        case 20:
          twentyWords++;
          break; 
      }//end of switch statement 
    }//checking if i need to do the switch statement or not
    
    //now we know we're going to need a secondary hash, so we initialize this vector 
    hashtable.at(i).second.first = new vector<string>((tempVector.at(i).size()-1)*(tempVector.at(i).size()-1)); 
     
    //have a boolean that will be checking for collisions 
    bool collision = true; 

    //have a while loop (or maybe do while)
    while(collision){
     //try a new hash function for each of the values 
     Hash24 tryHash; 

     //cout<<"WHAT'S THE HASH?";
    // tryHash.dump();


     //have a vector for storing the values 
     vector<int> hashIndexes; 
     for(int j = 1; j < tempVector.at(i).size(); j++){
       hashIndexes.push_back(tryHash.hash(tempVector.at(i).at(j))%( (tempVector.at(i).size()-1)*(tempVector.at(i).size()-1) ));
      // cout<<"TRYING HASH FOR WORD: "<<tempVector.at(i).at(j)<<" AND GOT: "<<tryHash.hash(tempVector.at(i).at(j))%( (tempVector.at(i).size()-1)*(tempVector.at(i).size()-1) )<<endl;
     }//end of for, now I have a vector of hash indexes 

     //this is a temp boolean to help the for loop report a collision
     bool collisionInside = false; 

     //use a double for to see if there's any duplicates again (aka hashes)
     for(int m = 0; m < hashIndexes.size(); m++){
      if(collisionInside) break; 
      int valueToComp = hashIndexes.at(m); 
      for(int n = 0; n < hashIndexes.size(); n++){
        if(n == m) continue; 
        if(hashIndexes.at(n) == hashIndexes.at(m)){
         //set our flag to true 
          // cout<<"FOR THIS THERE SHOULD BE A COLLISSION"<<endl;
          collisionInside = true; 
          break; 
          //next 
        }//end of if checking if there's a collision 
      }//end of inner for 
     }//end of outer for 

     if(collisionInside){ 
         //we have a collision, first update the counter:
        collisionCounter++; 
        //next we say that our while iterator is still true 
        collision = true; //i don't think we need this
        continue; //i am still unsure if this works the way that i wanted it o
     }//end of what to do if there's a collision


     //if we reach here, there's no collision 
     //so first, update the main collision counter if we have to: 
     if(collisionCounter>=0 && collisionCounter<=20){
     //i'm able to update the tries variable for stats 
      switch(collisionCounter) {
        case 1:
          twoTries++;
          break;
        case 2:
          threeTries++;
          break;
        case 3:
          fourTries++;
          break;
        case 4:
          fiveTries++;
          break;
        case 5:
          sixTries++;
          break;
        case 6:
          sevenTries++;
          break;
        case 7:
          eightTries++;
          break;
        case 8:
          nineTries++;
          break;
        case 9:
          tenTries++;
          break;
        case 10:
          elevenTries++;
          break;
        case 11:
          twelveTries++;
          break;
        case 12:
          thirteenTries++;
          break;
        case 13:
          fourteenTries++;
          break;
        case 14:
          fifteenTries++;
          break;
        case 15:
          sixteenTries++;
          break;
        case 16:
          seventeenTries++;
          break;
        case 17:
          eighteenTries++;
          break;
        case 18:
          nineteenTries++;
          break;
        case 19:
          twentyTries++;
          break; 
        default:
          oneTry++; 
      }//end of switch statement 
    }//checking if i need to do the switch statement or not
    
    //now I need to set the secondary hash function of my table to whatever one was used here
    hashtable.at(i).second.second = tryHash; 

    // cout<<"WHAT'S THE HASH?";
    // tryHash.dump();
    // cout<<"CHECK HASH IN HASHTABLE";
    // (hashtable.at(i).second.second).dump();

    //now I can put everything in using that hash
    for(int p = 1; p<tempVector.at(i).size(); p++){
      hashtable.at(i).second.first->at(tryHash.hash( tempVector.at(i).at(p) )%((tempVector.at(i).size()-1)*(tempVector.at(i).size()-1))) = tempVector.at(i).at(p);
    } 

    //everything is set and added, therefore we are good to break out of this while
    collision = false; 
    break; 

    }//end of the while checking for collisions 

  } //end of the for loop for the second pass

  //AT THIS POINT YOU SHOULD HAVE ALL THE STATS AND FACTS TO PRINT OUT WHAT'S NEEDED
  //Dump the hash: 
    primaryHash.dump(); 

  //Number of words:
    cout<<"Number of Words = "<<tsize<<endl; 

  //Table Size 
    cout<<"Table size = "<<tsize<<endl; 

  //Max collisions 
    cout<<"Max collisions = "<<maxCollisions.first<<endl; 

  //primary slots counts 
  cout<<"# of primary slots with 0 words = "<<zeroWords<<endl; 
  cout<<"# of primary slots with 1 words = "<<oneWord<<endl; 
  cout<<"# of primary slots with 2 words = "<<twoWords<<endl; 
  cout<<"# of primary slots with 3 words = "<<threeWords<<endl; 
  cout<<"# of primary slots with 4 words = "<<fourWords<<endl; 
  cout<<"# of primary slots with 5 words = "<<fiveWords<<endl; 
  cout<<"# of primary slots with 6 words = "<<sixWords<<endl; 
  cout<<"# of primary slots with 7 words = "<<sevenWords<<endl; 
  cout<<"# of primary slots with 8 words = "<<eightWords<<endl; 
  cout<<"# of primary slots with 9 words = "<<nineWords<<endl; 
  cout<<"# of primary slots with 10 words = "<<tenWords<<endl; 
  cout<<"# of primary slots with 11 words = "<<elevenWords<<endl; 
  cout<<"# of primary slots with 12 words = "<<twelveWords<<endl; 
  cout<<"# of primary slots with 13 words = "<<thirteenWords<<endl; 
  cout<<"# of primary slots with 14 words = "<<fourteenWords<<endl; 
  cout<<"# of primary slots with 15 words = "<<fifteenWords<<endl; 
  cout<<"# of primary slots with 16 words = "<<sixteenWords<<endl; 
  cout<<"# of primary slots with 17 words = "<<seventeenWords<<endl; 
  cout<<"# of primary slots with 18 words = "<<eighteenWords<<endl; 
  cout<<"# of primary slots with 19 words = "<<nineteenWords<<endl; 
  cout<<"# of primary slots with 20 words = "<<twentyWords<<endl; 

  //words in the slot with most collisions 
  cout<<"**Words in the slot with most collisions ***"<<endl; 
  for(string s: maxCollisions.second){
   cout<<s<<endl;
  }

  cout<<"# of secondary hash tables trying 1 hash functions = "<<oneTry<<endl; 
  cout<<"# of secondary hash tables trying 2 hash functions = "<<twoTries<<endl;
  cout<<"# of secondary hash tables trying 3 hash functions = "<<threeTries<<endl;
  cout<<"# of secondary hash tables trying 4 hash functions = "<<fourTries<<endl;
  cout<<"# of secondary hash tables trying 5 hash functions = "<<fiveTries<<endl;
  cout<<"# of secondary hash tables trying 6 hash functions = "<<sixTries<<endl;
  cout<<"# of secondary hash tables trying 7 hash functions = "<<sevenTries<<endl;
  cout<<"# of secondary hash tables trying 8 hash functions = "<<eightTries<<endl;
  cout<<"# of secondary hash tables trying 9 hash functions = "<<nineTries<<endl;
  cout<<"# of secondary hash tables trying 10 hash functions = "<<tenTries<<endl;
  cout<<"# of secondary hash tables trying 11 hash functions = "<<elevenTries<<endl;
  cout<<"# of secondary hash tables trying 12 hash functions = "<<twelveTries<<endl;
  cout<<"# of secondary hash tables trying 13 hash functions = "<<thirteenTries<<endl;
  cout<<"# of secondary hash tables trying 14 hash functions = "<<fourteenTries<<endl;
  cout<<"# of secondary hash tables trying 15 hash functions = "<<fifteenTries<<endl;
  cout<<"# of secondary hash tables trying 16 hash functions = "<<sixteenTries<<endl;
  cout<<"# of secondary hash tables trying 17 hash functions = "<<seventeenTries<<endl;
  cout<<"# of secondary hash tables trying 18 hash functions = "<<eighteenTries<<endl;
  cout<<"# of secondary hash tables trying 19 hash functions = "<<nineteenTries<<endl;
  cout<<"# of secondary hash tables trying 20 hash functions = "<<twentyTries<<endl; 

  //the average tries 
  averageHashesTried = 
  static_cast<double>(1*oneTry + 2*twoTries + 3*threeTries + 4*fourTries + 5*fiveTries
  +6*sixTries + 7*sevenTries + 8*eightTries + 9*nineTries + 10*tenTries
  +11*elevenTries + 12*twelveTries + 13*thirteenTries + 14*fourteenTries
  +15*fifteenTries + 16*sixteenTries + 17*seventeenTries + 18*eighteenTries 
  +19*nineteenTries + 20*twentyTries)/static_cast<double>(oneTry+twoTries+threeTries+fourTries+fiveTries+sixTries+
                                      sevenTries+eightTries+nineTries+tenTries+elevenTries+twelveTries
                                      +thirteenTries+fourteenTries+fifteenTries+sixteenTries+
                                      seventeenTries+eighteenTries+nineteenTries+twentyTries); 

  cout<<"Average # of hash functions tried = "<<averageHashesTried<<endl; 


  // cout<<endl<<endl<<"PRINTING OUT HASH TABLE"<<endl; 
  
  // //int howmuchtoprint2 = 0; 
  // for(pair<string, pair<vector<string>*,Hash24>> p: hashtable){
  //   if((p.first).compare("hello")==0){
  //   cout<<"PRIMARY ENTRY:"<<p.first<<"    ";
  //   }
  // }

  // for(pair<string, pair<vector<string>*,Hash24>> p: hashtable){
  //   if(p.second.first != nullptr){
  //   for(string s: *(p.second.first)){
  //     if(s.compare("hello")==0)
  //     cout<<s<<",";
  //   }
  //   }
  // }

}

 bool Dictionary::find(string word){
   //boolean for finding word return true if found, false if not 
   //Does the hash of this word, equal to the word

   if(hashtable.size() == 0 || (hashtable.at(primaryHash.hash(word)%(hashtable.size())).second.first != nullptr) && (hashtable.at(primaryHash.hash(word)%(hashtable.size())).second.first->size()) == 0 ){cout<<"I got a zero somewhere"<<endl; return false;}
   if((hashtable.at(primaryHash.hash(word)%(hashtable.size())).first).compare(word) != 0 ){
    if(hashtable.at(primaryHash.hash(word)%(hashtable.size())).second.first != nullptr && 
       hashtable.at(primaryHash.hash(word)%(hashtable.size())).second.first->at( 
      (hashtable.at(primaryHash.hash(word)%(hashtable.size())).second.second).hash(word)%
      (hashtable.at(primaryHash.hash(word)%(hashtable.size())).second.first->size())).compare(word) == 0 ){    
      cout<<word<<" found"<<endl;
      return true; 
    }
      cout<<word<<" not found"<<endl;
      return false;
   }
    cout<<word<<" found"<<endl;
    return true; 

   }

 //writeToFile 
 void Dictionary::writeToFile(string fName){
   //set up the file
    fstream output; 
    output.open(fName, ios::out|ios::binary); 

    //write out the size of the table 
    int sizeOfTable = hashtable.size(); 
    output.write((char*)&sizeOfTable, sizeof(sizeOfTable)); 

    //next let's get the primary hash 
    output.write((char*)&(primaryHash), sizeof(primaryHash));


   //  for(int i = 0; i<hashtable.size(); i++){
     for(int i = 0; i<sizeOfTable; i++){
 
        string& primaryString = hashtable.at(i).first; 

        size_t primaryStringLength = primaryString.size(); 
        output.write((char*)&primaryStringLength,sizeof(primaryStringLength));
    
        if(primaryStringLength == 0) { continue; }

        //write string: 
        output.write(primaryString.c_str(), primaryStringLength);

      
      //get table size if it exists
      if(hashtable.at(i).second.first != nullptr){
        int secondaryTableSize = hashtable.at(i).second.first->size(); 
       // cout<<"secondary table size: "<<secondaryTableSize<<endl;
        output.write((char*)&secondaryTableSize, sizeof(secondaryTableSize)); 
        } else{
         int secondaryTableSize = 0; 
         output.write((char*)&secondaryTableSize, sizeof(secondaryTableSize)); 
       //  cout<<"secondary table size: "<<secondaryTableSize<<endl;
         continue;
        }

    
    // //iterate through second table: 
        for(int j = 0; j<hashtable.at(i).second.first->size(); j++){
          string& secondaryString = hashtable.at(i).second.first->at(j); 

          //write out the length
          size_t secondaryStringLength = secondaryString.size(); 
          output.write((char*)&secondaryStringLength,sizeof(secondaryStringLength));

          //if that word's length is zero, write that and a blank, and continue:
          if(secondaryStringLength == 0){ continue; }

          //write string: 
          output.write(secondaryString.c_str(), secondaryStringLength);
    
        } //end of for loop

          //write the hash function
          output.write((char*)&(hashtable.at(i).second.second), sizeof(hashtable.at(i).second.second)); 

       } //end of outer for iterating through all the elements of the primary hash  

    // //close the file 
     output.close();
 }
 

//readFromFile binary
 Dictionary Dictionary::readFromFile(string fName){
  Dictionary d; //implemented default just for this
  fstream input;
  input.open(fName, ios::in);
  input.seekg(0);

 
  //must read stuff in, in the order that it was written, first up the size
  int tableSize;
  input.read((char*)&(tableSize), sizeof(tableSize));
  d.hashtable.resize(tableSize);

  //next the initial hash for that Dictionary 
  input.read((char*)&d.primaryHash, sizeof(d.primaryHash));


    for(int i = 0; i<tableSize; i++){
        size_t primaryStringLength; 
        input.read((char*)&primaryStringLength, sizeof(primaryStringLength)); 

       // cout<<"Primary String Length: "<<primaryStringLength<<endl;
       
       //if zero, set the string to blank 
        if(primaryStringLength == 0){
          d.hashtable.at(i).first = ""; 
          continue;
        }

       //write the string 
        string primaryString; 
        primaryString.resize(primaryStringLength);
        input.read(&primaryString[0], primaryStringLength);
        
        d.hashtable.at(i).first = primaryString; 
       // cout<<"Primary String:"<<primaryString<<endl;

        //next thing should be the length of the secondary VECTOR: 
        int secondaryLength;
        input.read((char*)&secondaryLength, sizeof(secondaryLength));
    
        
        //cout<<"THE SECONDARY VECTOR LENGTH IS: "<<secondaryLength<<endl; 

        //if I get zero, that means no vector, that means make it null 
        if(secondaryLength == 0){
          d.hashtable.at(i).second.first = nullptr; //just make sure to set it to null in case it wasn't before 
          continue; //continue on because we're done with this iteration 
        }

       //if it didn't continue, that means we can create a new vector of secondary length
       d.hashtable.at(i).second.first = new vector<string>(secondaryLength); 
 
        for(int j = 0; j<secondaryLength; j++){
          size_t secondaryWordLength; 
          input.read((char*)&secondaryWordLength, sizeof(secondaryWordLength));

          if(secondaryWordLength == 0){
              d.hashtable.at(i).second.first->at(j) = ""; //set it to blank then continue 
              continue; 
           }

          //a word is there so set it
          string secondaryWord; 
          
          //set length of current word to length i read in 
          secondaryWord.resize(secondaryWordLength); 
          input.read(&secondaryWord[0], secondaryWordLength);

          //set it in the secondary vector 
          d.hashtable.at(i).second.first->at(j) = secondaryWord; 
          
        }//end of inner for reading in everything

         //after this we should've written in all words, so now we make sure to get that hash 
        input.read((char*)&(d.hashtable.at(i).second.second), sizeof(d.hashtable.at(i).second.second)); 
        
  //       //we should be good to go
      } //end of outer for iterating through all the elements of the primary hash  
  
  //  //literally hoping everything is fine 
  
   input.close(); 


  return d; 
 }
