#include<iostream>
#include <stdio.h>
#include<fstream>
#include<string>
#include<cstdlib>
#include <ctype.h>

using namespace std;

enum tokentype {CONNECTOR, DESTINATION, ERROR, EOFM, IS, OBJECT, PERIOD, PRONOUN, SUBJECT, WAS, WORD1, WORD2, VERB, VERBNEG, VERBPAST, VERBPASTNEG};
int scanner(tokentype& , string& );
bool mytoken(string );
bool myPeriod(string );
string convertT(tokentype t){
  string a;
  switch(t){
  case CONNECTOR:
    a="CONNECTOR";
    break;
  case DESTINATION:
    a="DESTINATION";
    break;
  case ERROR:
    a="ERROR";
    break;
  case EOFM:
    a="EOFM";
    break;
  case IS:
    a="IS";
    break;
  case OBJECT:
    a="OBJECT";
    break;
  case PERIOD:
    a="PERIOD";
    break;
  case PRONOUN:
    a="PRONOUN";
    break;
  case SUBJECT:
    a="SUBJECT";
    break;
  case WAS:
    a="WAS";
    break;
  case WORD1:
    a="WORD1";
    break;
  case WORD2:
    a="WORD2";
    break;
  case VERB:
    a="VERB";
    break;
  case VERBNEG:
    a="VERBNEG";
    break;
  case VERBPAST:
    a="VERBPAST";
    break;
  case VERBPASTNEG:
    a="VERBPASTNEG";
    break;
  default: 
    a="Nothing";
      break;
  }
  return a;
}
/*int main()
{	 tokentype thetype;
	 ifstream fin;
	 string theword,input;
	 cout<<"Enter Input file: ";
	 getline(cin,input);
	 fin.open(input.c_str());
	 
	 while (thetype!=EOFM){
		 fin>>theword;
		 scanner(thetype,theword);
		 cout<<"The type"<< convertT(thetype) <<"The word"<<theword<<endl; 
	 }
	 fin.close();
	 }*/

int scanner(tokentype& a, string& w)
{	
	bool test1=mytoken(w);
	if(myPeriod(w)==true){
	  a=PERIOD;
	  return 1;
	}
       else if(test1==true)
	  {
	
	    if(w[w.length()-1]=='I'||w[w.length()-1]=='E')
	      {
		  a=WORD2;	  
	      }
	    else 
	      {
		  a=WORD1;		  
	      }
		
		 if (w=="masu")
			a= VERB;
								
		 if(w=="masen")
			a=VERBNEG;
								
		 if(w=="mashita")
			a=VERBPAST;
								
		 if(w=="masendeshita")
		   a= VERBPASTNEG;
			
		 if(w=="desu")
			a= IS;
		
		if(w== "deshita")
		  a= WAS;
			
		 if(w== "o")
			a= OBJECT;
			
		 if(w== "wa")
			a=SUBJECT;
									
		 if(w=="ni")
			a=DESTINATION;
			
		 if(w=="watashi")
			a=PRONOUN;
			
		 if(w=="anata")
			a=PRONOUN;
			
		 if(w=="kare")
			a=PRONOUN;
			
		 if(w=="kanojo")
			a=PRONOUN;
			
		  if(w=="sore")
			a=PRONOUN;
			
		if(w== "mata")
			a=CONNECTOR;
			
		 if(w== "soshite")
			a=CONNECTOR;
			
		if(w== "shikashi")
			a= CONNECTOR;
			 
		if(w=="dakara")
			a=CONNECTOR;
			
		if(w== "eofm")
		 a=EOFM;
	   //================================						
		  return 1;

	  }
	else if (test1==false)
       {
	    a=ERROR;
	    cout<<"Lexical Error: "<< w <<" is not valid token"<<endl;
	    return 1;
   
    }
	return 0;
}//the end
//MAIN FUNCTION
//ASK USER FOR THE FILENAME

bool mytoken(string s){
  /*
    fix : Add q1 with y,d,z,w go to q2
    fix: Add q1 with n go to Q1
    fix:  
   */

        int flag=0;
        int state = 0;
        int charpos = 0;
    
	if(s=="eofm")
	  return true;
	 while (s[charpos] != '\0')
    {
      //     cout<<s[charpos]<<"       "<<state<<endl;
           if(s[s.length()-1]=='I'||s[s.length()-1]=='E')
	     s[s.length()-1]=tolower(s[s.length()-1]);
		
	   bool list1=s[charpos]=='a'||s[charpos]=='e'||s[charpos]=='i'||s[charpos]=='o'||s[charpos]=='u';
		bool list2=s[charpos]=='b'||s[charpos]=='g'||s[charpos]=='h'||s[charpos]=='k'||s[charpos]=='m'||s[charpos]=='n'||s[charpos]=='p'||s[charpos]=='r';
		bool list3=s[charpos]=='b'||s[charpos]=='g'||s[charpos]=='h'||s[charpos]=='k'||s[charpos]=='m'||s[charpos]=='p'||s[charpos]=='r';
		bool list4=s[charpos]=='d'||s[charpos]=='y'||s[charpos]=='j'||s[charpos]=='w'||s[charpos]=='z';
                bool list5=s[charpos]=='b'||s[charpos]=='g'||s[charpos]=='h'||s[charpos]=='k'||s[charpos]=='m'||s[charpos]=='p'||s[charpos]=='r'||s[charpos]=='d'||s[charpos]=='y'|s[charpos]=='z'||s[charpos]=='w';
		//==========From state 0===============
		if(flag==0&&state==0&&s[charpos]=='c')
		{
			state=5;
			flag=1;
		}

	   	 else if(flag==0&&state==0&&s[charpos]=='s')
		{
			state=3;
			flag=1;

		}

		else if(flag==0&&state==0&&s[charpos]=='t')
		{
			state=6;
			flag=1;
		}
		else if(flag==0&&state==0&&list1)
		{
			state=1;
			flag=1;
		}

		else if(flag==0&&state==0&&list2)
		{
			state=2;
			flag=1;
          	}
		else if(flag==0&&state==0&&list4)
		{
			state=4;
			flag=1;
		}
		//============From state 1============

		if(flag==0&&state==1&&s[charpos]=='n')
		{
			state=1;
			flag=1;
		}

		else if(flag==0&&state==1&&s[charpos]=='s')
		{
			state=3;
			flag=1;
		}
		else if(flag==0&&state==1&&s[charpos]=='c')
		{
			state=5;
			flag=1;
		}
		else if(flag==0&&state==1&&s[charpos]=='t')
		{
			state=6;
			flag=1;
		}

		else if(flag==0&&state==1&& list5 )
		{
			state=2;
			flag=1;
		}
		else if(flag==0&&state==1&& list1)
		  {
		    state=1;
		    flag=1;
		  }

		//==========From State 2============

	        if(flag==0&&state==2&& list1)
		{
			state=1;
			flag=1;
		}
		else if(flag==0&&state==2&&s[charpos]=='y')
		{
			state=4;
			flag=1;
		}
		//=========From State 3===========
	         if(flag==0&&state==3&& list1)
		{
			state=1;
			flag=1;
		}
		else if(flag==0&&state==3&&s[charpos]=='h')
		{
			state=4;
			flag=1;
		}
		//=========From State 4===========
	        if(flag==0&&state==4&& list1)
		{
			state=1;
			flag=1;
		}
		//=========From State 5===========
		 if(flag==0&&state==5&& s[charpos]=='h')
		{
			state=4;
			flag=1;
		}
		//=========From State 6===========
		 if(flag==0&&state==6&& list1)
		{
			state=1;
			flag=1;
		}
		else if(flag==0&&state==6&&s[charpos]=='s')
		{
			state=4;
			flag=1;
		}
		//=========From State 7===========
	        if(flag==0&&state==7&& s[charpos]=='s')
		{
			state=3;
			flag=1;
		}
		else if(flag==0&&state==7&& s[charpos]=='t')
		{
			state=6;
			flag=1;
		}
		else if(flag==0&&state==7&& s[charpos]=='c')
		{
			state=5;
			flag=1;
		}
		else if(flag==0&&state==7&& list2)
		{
			state=2;
			flag=1;
		}
		else if(flag==0&&state==7&& list1)
		{
			state=1;
			flag=1;
		}
		else if(flag==0&&state==7&& list4)
		{
			state=4;
			flag=1;
		}
		if(flag==0)
		{
		  //	  cout<<"Stuck at state: "<<state<<" ";
			return false;
		}
		flag=0;
		charpos++;
    }//end of while
	 // where did I end up????
  if (state == 0||state==1) return(true);  // end in a final state
   else return(false);

}

bool myPeriod(string s){
	int state = 0;
	int charpos = 0;
	while (s[charpos] != '\0') {
		if(state==0 && s[charpos]=='.')
			state=1;
		else if (state==1)
			return false;
		charpos++;
	}
	if(state ==1) return (true);
	else return (false);
}


