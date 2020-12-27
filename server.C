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
#include "TASK1.H"

#include <iostream>

using namespace TASK1;
using namespace std;

class myTCPserver : public TCPserver{
public:
	myTCPserver(int port, int maxDataSize): TCPserver(port, maxDataSize){;};
protected:
	string myResponse (string input);

};

int main(){
	srand(time(nullptr));
	myTCPserver srv(2032,25);
	srv.run();
}
/*
 * "PWD[<pwd>]" <pwd> ...passwort
 * "NEWBOX [<pwd lenght>,<alphabet>] "   <pwd lenght> ...
 * 								<alphabet lenght>....
 *
 *
 *
 *
 *
 *
 */


string myTCPserver::myResponse(string input){
	string response("UNKOWN COMMAND");
	bool success = false;
	int a,b;
	int strlenght=0;

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

		response = string ("OKAY");
	}else {
		response = string("UNKOWN COMMAND" ) ;
	}
	return response;	}









