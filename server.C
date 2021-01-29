/*
 * server.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses

#include "SIMPLESOCKET.H"

#include "SHA256.H"
#include <iostream>
#include "TASK1.H"
#include <string>
#include <iostream>

#include <cstdio>      /* printf, NULL */
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

#include <string>
#include <iostream>

#include <cstdio>      /* printf, NULL */
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

#include <unistd.h>

#include "SHA256.H"
#include "TASK1.H"





using namespace TASK1;
using namespace std;
/**
 *
 * \brief KLasse myTCPserver
 * Mit dieser klasse wird ein TCP Server erstellt.
 *
 */
class myTCPserver : public TCPserver{
public:
	/**
	 *
	 *Konstruktor (int port, int maxDataSize)
	 *		Mit dem Konstruktor wird Objekt der Klasse erstellt.
 	 *		int port <-- Portnummer des TCP Servers
 	 *		int maxDataSize <-- Hier die maximale Anzahl der Chars angegeben, welche in einer Übertragung übertragen werden sollen.
	 *
	 */
	myTCPserver(int port, int maxDataSize): TCPserver(port, maxDataSize){;};
protected:

	/**
	 *
	 *
	 *  \brief   myTCPserver::myResponse
	 *
	 * Hier wurde das Serverseitige Protokoll implementiert.
	 *
	 *  UNSAFE:
	 *
	 *  NEWUNSAFE[int pwdlänge,int alphabetlänge]
	 *  Mithilfe dieser Eingabe wird ein Passwort erstellt, welches NICHT mit SHA256 verschlüsselt wurde.
	 *  Als Eingabe Parameter werden hier die länge des Passwortes (mindestens 4 lang) und die größe des Alphabeths (mindestens 1) benötigt.
	 *
	 *  GUESSUNAFE[pwd]
	 *
	 *  Mithilfe dieser Eingabe wird dem Server ein Passwort übergeben, welches mit dem zuvor in NEWUNSAFE verglichen wird.
	 *  wenn dieses indentisch ist, gibt der Server "RIGHT" aus. Falls dies nicht der Fall ist wird "WRONG" ausgegeben.
	 *
	 *
	 * SAFE:
	 *
	 * NEWSAFE[int pwdlänge,int alphabetlänge]
	 * Mithilfe dieser Eingabe wird ein Passwort erstellt, welches durch SHA256 verschlüsselt ist.
	 * Als Eingabe Parameter werden hier die länge des Passwortes (mindestens 4 lang) und die größe des Alphabeths (mindestens 1) benötigt.
	 *
	 * GUESSSAFE[pwd]
	 * Mithilfe dieser Eingabe wird dem Server ein Passwort übegeben, welches dann durch SHA256 in ein Hash-Wert umgewandelt wird,
	 * um es mit dem Abgespeicherten Hash-Wert zu vergleichen.
	 * wenn dieses indentisch ist, gibt der Server "RIGHT" aus. Falls dies nicht der Fall ist wird "WRONG" ausgegeben.
	 *
	 */
	string myResponse (string input);

};
string globe_pwd="";
int serverport  =2034;
BlackBoxSafe* ptr_BBS =nullptr;
int main(){


	cout << endl << " Hallo ! " << endl << " Bitte geben sie die Portnummer ein :  " ;
	cin >> serverport;
	srand(time(nullptr));
	myTCPserver srv(serverport,25);
	srv.run();




}



string myTCPserver::myResponse(string input){
	string loc_var_response("UNKNOWN COMMAND");
	bool loc_var_success = false;
	int loc_var_a,loc_var_b;
	int loc_var_strlenght=0;
	string loc_var_guess="";



	if (input.compare(0,4,"PWD[") == 0){
		//password received
		char loc_var_pwd[32];

		sscanf(input.c_str(),"PWD[%s]",loc_var_pwd);					// Ab hier wird das Passwort aus der Übertragung gefiltert
		//pwd[input.size()- 1 ] = '\0';
		loc_var_strlenght = strlen(loc_var_pwd)-1;
		cout<< "pwd länge:" <<loc_var_strlenght << endl;
		loc_var_pwd[loc_var_strlenght]='\0';
		cout << "pwd received : '" <<loc_var_pwd << "'" << endl;

		loc_var_success = rand ()%2;									// Ab hier nur Random Success oder FAILED
		if(loc_var_success){loc_var_response = string("SUCCESS");}
		else {
			loc_var_response= string ( "FAILED");}
	}else if ( input.compare ( 0,7,"NEWBOX[")== 0 ){

		// init new password guessing game
		// ...
		sscanf ( input.c_str(),"NEWBOX[%d,%d]",&loc_var_a,&loc_var_b);

		cout << "pwd lenght = "  << loc_var_a << " alphabet lenght= " <<loc_var_b <<endl;

		loc_var_response = string ("OKAY");}

	else if ( input.compare ( 0,10,"NEWUNSAFE[")== 0 ){
		sscanf ( input.c_str(),"NEWUNSAFE[%d,%d]",&loc_var_a,&loc_var_b);

	BlackBoxUnsafe ptr_bbu (loc_var_a,loc_var_b);
	globe_pwd=ptr_bbu.pwd_;

	cout <<" Länge des PWD:" << loc_var_a <<  "    Alphabet:" << loc_var_b << endl
			<<"Das generierte PWD:    " <<globe_pwd << endl << endl << endl ;

	loc_var_response= string("Generiert.");
	}


	else if ( input.compare ( 0,8,"NEWSAFE[")== 0 ){
			sscanf ( input.c_str(),"NEWSAFE[%d,%d]",&loc_var_a,&loc_var_b);
			delete ptr_BBS;
		ptr_BBS= new BlackBoxSafe(loc_var_a,loc_var_b);
		cout << " das PWD :" << ptr_BBS->pwd_;


		cout <<" Länge des PWD:" << loc_var_a <<  "    Alphabet:" <<loc_var_b << endl
				<<"Der generierte SHA:    " <<ptr_BBS->BlackBoxSafe_sha << endl << endl << endl ;

		loc_var_response= string("Generiert.");
	//TASK1::demoTASK1_01();
}


	else if (input.compare(0,10,"GUESSSAFE[") == 0){
		char local_guess [32]="";
				sscanf(input.c_str(),"GUESSSAFE[%s]",local_guess);
				loc_var_strlenght = strlen(local_guess)-1;

						local_guess[loc_var_strlenght]='\0';


			cout <<" Das eingegangende PWD : \t" << local_guess ;

			loc_var_response= ptr_BBS->check(local_guess);

	}

	else if (input.compare(0,12,"GUESSUNSAFE[") == 0){
		char guess [32]="";
		sscanf(input.c_str(),"GUESSUNSAFE[%s]",guess);
		loc_var_strlenght = strlen(guess)-1;

				guess[loc_var_strlenght]='\0';

				if(guess==globe_pwd){
				cout << "RICHTIG " << endl ;
				loc_var_response=string("RIGHT");
				}
				else{cout << "FALSCH" << endl;
				loc_var_response= string("WRONG");
				}
	}


	else {
		loc_var_response = string("UNKOWN COMMAND" ) ;
	}
	return loc_var_response;	}










