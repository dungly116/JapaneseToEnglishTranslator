#include<cstdlib>
#include<fstream>
#include<iostream>
#include "ScannerT.cpp"
#include<string>
#include<vector>

using namespace std;

//=================================================
// File parser.cpp written by Group Number: 6
//=================================================

// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

// Tokentype Array
//enum tokentype {CONNECTOR, DESTINATION, ERROR, EOFM, IS, OBJECT, PERIOD, PRONOUN, SUBJECT, WAS, WORD1, WORD2, VERB,VERBNEG, VERBPAST, VERBPASTNEG};
// Other declarations
tokentype currentToken;  //token in queue
tokentype old;
string inputFile;
string currentWord; //current word read from the file
bool isTokenComparatorFree = false; 
bool traceMSG; // turn on or off traceMSGs
ifstream fin;
ofstream fout; //output error messages to a file

void syntaxerror1(tokentype , tokentype );
void syntaxerror2(tokentype , string );
tokentype next_token();
bool match(tokentype );
void story();
void begin_story();
void after_subject();
void be();
void noun();
void tense();
void verb();
void after_noun();

int main()
{
  char traceOpt;
  cout << "Parser Funciton" << endl;
  cout << "Enter Filename of the File you want to parse: " << endl;
  getline(cin,inputFile);
  
  while(traceOpt != 'Y' || 'y' && traceOpt != 'N' || 'n')
  {
	cout << "KEEP TRACK OF PARSING PROCESS? Y / N: ";
	cin >> traceOpt;
	
	if(traceOpt == 'Y' || 'y')
	{
		traceOpt = true;
	}
	else if(traceOpt == 'N' || 'n')
	{
		traceOpt = false;
	}
  }
  
  fin.open(inputFile.c_str());
  fout.open("Errors.txt", ios::out | ios::app); 
  
  story(); //initiates parsing
  cout<<"=====END-Prasering====="<<endl;
  fin.close();
  fout.close();
}

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
void syntaxerror1(tokentype t, string s)
{
  cout << "SYNTAX ERROR: EXPECTING " << convertT(t) << " BUT FOUND " << s << endl;
  
  //Keep track of the file opened by writing it to the error file.
  fout << "Input File" << inputFile << ":" <<endl;
  fout << "SYNTAX ERROR: EXPECTING " << convertT(t) << " BUT FOUND " << s << endl;

	exit(-1);
}

void syntaxerror2(string  w, string s)
{
	cout << "SYNTAX ERROR: UNEXPECTED WORD: " << w << " FOUND IN " << s << endl;

	//Keep track of the file opened by writing it to the error file.
	fout << "Filename: " << inputFile << ":" <<endl;
	fout << "SYNTAX ERROR: UNEXPECTED WORD: " << w << " FOUND IN " << s << endl;

	exit(-1);
}

// ** Need the updated match and next_token (with 2 global vars)

tokentype next_token()
{  
	string w;

	if (!isTokenComparatorFree)
    { 
		fin >> w;
		old=currentToken;
		scanner(currentToken, w);
		isTokenComparatorFree = true;      
		
		cout<<"The current word is " << w<<endl;
		currentWord = w; 
      
		if(traceMSG)
		{
			cout << "Scanner is being called..." << endl; 
		}

		if(currentToken == ERROR)
		{
			cout << "The Word: " << w << " is not found in the language" << endl;
			fout << "Filename: " << inputFile << ":" <<endl;
			fout << "The Word: " << w << " is not found in the language" << endl;
			exit(-1);
		}
    }
	return currentToken; 
}

bool match(tokentype t)
{
	if (next_token() != t)
		syntaxerror1(t, currentWord); 
	else   
		isTokenComparatorFree = false; 
	cout << "Matched " << convertT(t) << endl; 
		return true;           
} 

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function

//STORY FUNCTION
//GRAMMAR: <story>::= <begin_story> {<begin_story>}
void story()
{
	if(traceMSG)
	{
		cout << "===============PROCESSING STORY======================" << endl;
	}

	begin_story();
		
		while(next_token() != EOFM) //while not reaching end of fille
		{
	     	switch(next_token())//look ahead for the next tokentype
			{
				case CONNECTOR:
					begin_story();
					break;
			        default:
				  begin_story();                                 
				 break;
			}
		}

}

//BEGIN_STORY FUNCTION
//GRAMMAR: <begin_story>::=[CONNECTOR]<noun>SUBJECT<after_subject>
void begin_story()
{
	if(traceMSG)
	{
		cout << "======================PROCESSING BEGINNING STORY=====================" << endl;
	}
	
	if(next_token() == CONNECTOR)
	{
		match(CONNECTOR);
	}
	
	noun(); // process noun

	if(next_token() == SUBJECT) // for syntaxerror1 checking
	{
		match(SUBJECT);
	}
	else
	{
		syntaxerror1(SUBJECT, currentWord);
	}
	
	after_subject();
}

//AFTER_SUBJECT FUNCTION
//GRAMMAR: <after_subject>::=<verb><tense> PERIOD | <noun><after_noun>
void after_subject()
{
	if(traceMSG)
	{
		cout << "PROCESSING AFTER SUBJECT" << endl;
	}
	
	switch(next_token())
	{
		case WORD2:
			verb();
		case VERB:
		case VERBNEG:
		case VERBPAST:
		case VERBPASTNEG:
			tense(); 
					
			if(next_token() == PERIOD)
			{
				match(PERIOD);
			}
			else
			{
				syntaxerror1(PERIOD, currentWord);
			}
			break;
				
		case WORD1:
		case PRONOUN:
			noun();
			after_noun();
			break;
  
		default:
			syntaxerror2(currentWord, "after_subject");
   }
}

//AFTER_NOUN FUNCTION
//GRAMMAR: <after_noun>::= <be> PERIOD | DESTINATION <verb><tense> PERIOD| OBJECT [<noun> DESTINATION ] <verb><tense> PERIOD
void after_noun()
{
	if(traceMSG)
	{
		cout << "PROCESSING AFTER NOUN" << endl;
	}
	
	switch(next_token())
	{
		case IS:
		case WAS:
			be();
			if(next_token() == PERIOD)
			{	
				match(PERIOD);
			}
			else
			{
				syntaxerror1(PERIOD, currentWord);
			}
			
			break;
		
		case DESTINATION:
			match(DESTINATION);
			verb();
			tense();
			if(next_token() == PERIOD)
			{
				match(PERIOD);
			}
			else
			{
				syntaxerror1(PERIOD, currentWord);
			}
			
			break;
			
		case OBJECT:
			match(OBJECT);
			if(next_token() == WORD1 || next_token() == PRONOUN)
			{
				noun();
				if(next_token() == DESTINATION)
				{
					match(DESTINATION);
				}
				else
				{
					syntaxerror1(DESTINATION, currentWord);
				}
			}
			
			verb();
			tense();
			
			if(next_token() == PERIOD)
			{
				match(PERIOD);
			}
			else
			{
				syntaxerror1(PERIOD, currentWord);
			}
			
			break;
			default:
				syntaxerror2(currentWord, "afterNOUN");
	}
}

void be()
{
	if(traceMSG)
	{
		cout << "PROCESSING BE" << endl;
	}
	
	switch(next_token())
    {
		case IS:
			match(IS);
			break;
			
		case WAS:
			match(WAS);      
			break;
			
		default:
			syntaxerror2(currentWord, "be");
    }
}

void noun()
{
	if(traceMSG)
	{
		cout << "PROCESSING NOUN" << endl;
	}
	
	switch(next_token())
	{
		case WORD1:
			match(WORD1);
			break;
	
		case PRONOUN:
			match(PRONOUN);
			break;
		
		default:
			syntaxerror2(currentWord, "noun");
			break;
	}	
}

void tense()
{
	if(traceMSG)
	{
		cout << "PROCESSING TENSE" << endl;
	}
	
	switch(next_token())
	{
		case VERB:
			match(VERB);
			break;
			
		case VERBNEG:
			match(VERBNEG);
			break;
			
		case VERBPAST:
			match(VERBPAST);
			break;
			
		case VERBPASTNEG:
			match(VERBPASTNEG);
			break;
			
		default:
			syntaxerror2(currentWord, "tense");
			break;
	}
}

void verb()
{
	if(traceMSG)
	{
		cout << "PROCESSING VERB" << endl;
	}
	
	switch(next_token())
	{
		case WORD2:
			match(WORD2);
			break;
			
		default:
			syntaxerror2(currentWord, "verb");
			break;
	}
}
