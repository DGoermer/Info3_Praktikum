/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time
#include <string>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <unistd.h> //contains various constants
#include "SIMPLESOCKET.H"
#include "TASK1.H"
#include <ctime>

using namespace TASK1;
using namespace std;



int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg;
	string newmethode;
	string methode;
	string newmsg;
	string servermsg;
	string newerat;
	std::string::size_type sz;

	char input[] = "NEWUNSAFE[";
	char guess[] = "GUESS[";
	char end[] = "]";
	char komma[] = ",";
	string a,b;
	int brute_zahl;
	//connect to host
	c.conn(host , 2024);

	TASK1::PwdErraten methode_1;
	int i=0;
	string glob_const_symbols=TASK1::SYMBOLS;

	bool goOn=1;
	while(goOn){ // send and receive data
		if((rand() % 20) < i++){
			msg = string("BYEBYE");
			goOn = 0;
		}else{
			msg = string("client wants this");

			if (servermsg == "Generiert.")
			{
				cout<<"Bitte geben sie die länge für das erraten ein"<<endl;
				cin>> brute_zahl;
				do{

						methode=methode_1.Bruteforce(glob_const_symbols,brute_zahl,"");
						cout << "client sends:" <<guess+methode+end << endl;

						c.sendData(guess+methode+end);

						servermsg = c.receive(32);
						cout << "got response:" << servermsg<< endl;

						if(servermsg == "RICHIG")
						{
							cout<<"Geknackt"<<endl;


						}

				}
				while(servermsg == "WRONG");





			}
			else
				{
				cout<<"lange eingeben"<<endl;
				cin>> a;
				cout<<"große eingeben"<<endl;
				cin>> b;
				newmsg=input+a+komma+b+end;

				cout << "client sends:" << newmsg << endl; 	//übergabe von allen möglichkeiten an den server
				c.sendData(newmsg);
				servermsg = c.receive(32);
				cout << "got response:" << servermsg << endl;
				}

		sleep(1);
		}

	}
}


