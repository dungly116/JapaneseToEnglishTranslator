#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "V2ParserNew.cpp"
#include <vector>
using namespace std;
// CS421 File translator.cpp 

// ** Be sure to put the name of the programmer above each function
// ** Be sure to put the corresponding rule with semantic routines
//    above each function

// ** Additions to parser.cpp here:
//    getEword - using the current lexeme, look up the English word
//               in the Lexicon if it is there -- save the result   
//                 in saved_E_word
//    gen(line_type) - using the line type,
//                     display a line of an IR (saved_E_word or saved_token
//                     is used)

// The test driver to start the parser
// Done by  **

void getEword(string &japWord);
void gen(string genWord);

int main()
{
  //- opens the output file translated.txt
  //- opens the input file
  //- calls the <story> to start parsing
  //- closes the input file 
  //- closes traslated.txt
}// end

void getEword(string &japWord){
  string word; //for reading in lexicon.txt
  string saved_E_word; //I don't think need this here, supposed to be in parser.cpp right?
  vector<string> thevector; //declaring vector to store contents of translated.txt

  thevector.push_back("watashi"); //hardcoding in lexicon.txt
  thevector.push_back("I/me");
  thevector.push_back("anata");
  thevector.push_back("you");
  thevector.push_back("kare");
  thevector.push_back("he/him");
  thevector.push_back("kanojo");
  thevector.push_back("she/her");
  thevector.push_back("sore");
  thevector.push_back("it");
  thevector.push_back("mata");
  thevector.push_back("also");
  thevector.push_back("soshite");
  thevector.push_back("then");
  thevector.push_back("shikashi");
  thevector.push_back("however");
  thevector.push_back("dakara");
  thevector.push_back("therefore");


  int counter=0; //keeping track of how many times went through
  for(int i=0;i<thevector.size();i++){
    if(thevector[i]!=word){ // if word is never found counter=vector.size() 
      counter++;  
}
    if(thevector[i]==word){ //checks if japWord is equal to word in vector
      japWord=thevector[i+1]; //if it is then next word is english translation
      return; //returns with the english word found
}

}

  if(counter==thevector.size()){ //in the event that word doesn't exist.
    //if I'm supposed to set the japword as saved_E_word, this is the line to do it
    return; //returns with no english word found
  }

}

void gen(string genWord){

  fout.open("translated.txt", ios::out | ios::app);
  getEword(genWord); 
  fout << genWord << " ";
  fout.close();

  return;
}
