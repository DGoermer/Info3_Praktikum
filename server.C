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
string pwd="";
int serverport  =2034;
BlackBoxSafe* BBS =nullptr;
int main(){


	cout << endl << " Hallo ! " << endl << " Bitte geben sie die Portnummer ein :  " ;
	cin >> serverport;
	srand(time(nullptr));
	myTCPserver srv(serverport,25);
	srv.run();




}



string myTCPserver::myResponse(string input){
	string response("UNKNOWN COMMAND");
	bool success = false;
	int a,b;
	int strlenght=0;
	string guess="";



	if (input.compare(0,4,"PWD[") == 0){
		//password received
		char pwd[32];

		sscanf(input.c_str(),"PWD[%s]",pwd);					// Ab hier wird das Passwort aus der Übertragung gefiltert
		//pwd[input.size()- 1 ] = '\0';
		strlenght = strlen(pwd)-1;
		cout<< "pwd länge:" <<strlenght << endl;
		pwd[strlenght]='\0';
		cout << "pwd received : '" <<pwd << "'" << endl;

		success = rand ()%2;									// Ab hier nur Random Success oder FAILED
		if(success){response = string("SUCCESS");}
		else {
			response= string ( "FAILED");}
	}else if ( input.compare ( 0,7,"NEWBOX[")== 0 ){

		// init new password guessing game
		// ...
		sscanf ( input.c_str(),"NEWBOX[%d,%d]",&a,&b);

		cout << "pwd lenght = "  << a << " alphabet lenght= " <<b <<endl;

		response = string ("OKAY");}

	else if ( input.compare ( 0,10,"NEWUNSAFE[")== 0 ){
		sscanf ( input.c_str(),"NEWUNSAFE[%d,%d]",&a,&b);

	BlackBoxUnsafe bbu (a,b);
	pwd=bbu.pwd_;

	cout <<" Länge des PWD:" << a <<  "    Alphabet:" << b << endl
			<<"Das generierte PWD:    " <<pwd << endl << endl << endl ;

	response= string("Generiert.");
	}


	else if ( input.compare ( 0,8,"NEWSAFE[")== 0 ){
			sscanf ( input.c_str(),"NEWSAFE[%d,%d]",&a,&b);
			delete BBS;
		BBS= new BlackBoxSafe(a,b);
		cout << " das PWD :" << BBS->pwd_;


		cout <<" Länge des PWD:" << a <<  "    Alphabet:" << b << endl
				<<"Der generierte SHA:    " <<BBS->BlackBoxSafe_sha << endl << endl << endl ;

		response= string("Generiert.");
	//TASK1::demoTASK1_01();
}


	else if (input.compare(0,10,"GUESSSAFE[") == 0){
		char guess [32]="";
				sscanf(input.c_str(),"GUESSSAFE[%s]",guess);
				strlenght = strlen(guess)-1;

						guess[strlenght]='\0';


			cout <<" Das eingegenangende PWD : \t" << guess ;

			response= BBS->check(guess);

	}

	else if (input.compare(0,12,"GUESSUNSAFE[") == 0){
		char guess [32]="";
		sscanf(input.c_str(),"GUESSUNSAFE[%s]",guess);
		strlenght = strlen(guess)-1;

				guess[strlenght]='\0';

				if(guess==pwd){
				cout << "RICHTIG " << endl ;
				response=string("RIGHT");
				}
				else{cout << "FALSCH" << endl;
				response= string("WRONG");
				}
	}


	else {
		response = string("UNKOWN COMMAND" ) ;
	}
	return response;	}










