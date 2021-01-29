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
#include <sys/time.h>
#include <fstream>
#include <sstream>

using namespace TASK1;
using namespace std;
int globe_const_serverport;
string globe_const_host;
int globe_const_alphabetlaenge;

int globe_const_pwdlaenge;
TCPclient c;
int bruteforce(int loc_var_length,string loc_var_alphabet, int loc_var_alphabetlaenge,
		TCPclient loc_var_connection, string loc_var_partofpwd,int loc_var_number , int loc_var_counter, bool &loc_var_pfound);





int main(int argc, char *argv[]) {
	globe_const_serverport = (unsigned short) atoi(argv[3]);
	globe_const_alphabetlaenge=(unsigned short) atoi(argv[4]);
	globe_const_pwdlaenge = (unsigned short) atoi(argv[5]);

	string wahl;
	cout << " Willkommen im Client ! " << endl << "Bitte geben sie den Port des Servers ein:  ";
	cin >> globe_const_serverport;

	srand(time(NULL));


	int loc_var_number = 0;


	globe_const_host = "localhost";


	//connect to host
	c.conn(globe_const_host , globe_const_serverport);
	begin:

	int loc_var_versuche = 0;

	bool loc_var_pfound = 0;

	string loc_var_alphabet= "ABCDEFGHIJKLMNOPQRTSTUVWXYZabcdefghijklmopqrstuvwxyz0123456789";
	stringstream loc_var_ss;

	string loc_var_servermsg;


	/*
		 *
		 * Passwortlänge und Alphabetlänge werden abgefragt für die Passwort Erzeugung
		 *
		 * */
	cout<<"Bitte geben sie Pwdlaenge ein"<<endl;
	cin>>globe_const_pwdlaenge;
	cout<<"Bitte geben sie alphabetlange ein"<<endl;
	cin>> globe_const_alphabetlaenge;



	if (globe_const_alphabetlaenge >=loc_var_alphabet.length())

	{
		globe_const_alphabetlaenge=loc_var_alphabet.length()-1;
	}


		loc_var_ss.str("");
		fstream f;
		f.open("PASSWORTAUSWERTUNG_BOXSAFE.dat",ios::out|ios::app);		//Datei zum beschreiben wird geöffnet damit alle Ergebnis saubergemäß abgespeichert werden
		f<<"Passwortlaenge "<<"Alphabetgröße "<<"versuche "<<"\n";
	for(int i=1;i<globe_const_pwdlaenge;i++)
	{
		for(int j = 1;j<=globe_const_alphabetlaenge;j++)
		{

				while(1)
				{
									loc_var_ss.str("");
									loc_var_ss<<"NEWSAFE["<<globe_const_pwdlaenge<<","<<globe_const_alphabetlaenge<<"]";
									//ss<<"NEWUNSAFE["<<pwdlaenge<<","<<alphabetlaenge<<"]";
									c.sendData(loc_var_ss.str());
									loc_var_servermsg =c.receive(32);
									loc_var_ss.str("");

									cout<< loc_var_servermsg;




									if (loc_var_servermsg == "Generiert.")
									{
										break;
									}

									else
									{

										continue;

									}
				}
					/*
					 * Bruteforce wird ausgeführt wenn ein Passwort generiert ist
					 *
					 */
					loc_var_ss.str("");
					loc_var_number++;

					loc_var_versuche=bruteforce(globe_const_pwdlaenge,loc_var_alphabet,globe_const_alphabetlaenge,c,"",0,0,loc_var_pfound);


					//cout <<"Versuche"<<versuche<<endl;

					loc_var_pfound=0;
					/*
					 *
					 * Erratendes Passwort wird ausgegeben und anschließend wird ma gefragt ob ein neues Passwort erzeuget werden soll
					 */
					cout<<"Passwortnummer: \t"<<loc_var_number<<" Länge: \t"<<globe_const_pwdlaenge<<" Alphabetlänge \t"<<globe_const_alphabetlaenge<<" Versuche \t"<<loc_var_versuche<<endl;

					cout <<"Wollen sie ein neues PASSWORT erraten JA oder das PROGRAMM beenden NEIN"<<endl;
					cin>> wahl;

					f<<globe_const_pwdlaenge<<"\t\t"<<globe_const_alphabetlaenge<<"\t\t"<<loc_var_versuche<<"\n ";

					if((wahl=="JA")||(wahl=="ja"))
					{
						goto begin;	// Springt an den Anfang des Programms zur wiederholten Ausführung
					}

					else
					{
						f.close();	//Ergebnis wird in einer Datei abgespeichert
						exit(0);
					}






		}



	}

}/**

	/brief Bruteforce ist eine Funktion für die automatische Testung aller möglichen Passwörter. Die Passwortlänge wird durch die Variable
	 * length übergeben und die Alphbezgröße wird durch alphabetlaenge übergeben.
*/

int bruteforce(int loc_var_length,string loc_var_alphabet, int loc_var_alphabetlaenge,
		TCPclient c, string loc_var_partofpwd,int loc_var_number , int loc_var_counter, bool &loc_var_pfound)
{
	string loc_var_lang= "ABCDEFGHIJKLMNOPQRTSTUVWXYZabcdefghijklmopqrstuvwxyz0123456789";
	loc_var_number++;
	stringstream loc_var_pwd;
	string loc_var_newpwd;
	string loc_var_serverans;
	for(int i=0;i<loc_var_alphabetlaenge;i++)
	{
		loc_var_newpwd = loc_var_partofpwd+loc_var_lang[i];	//Buchstaben addition

		loc_var_pwd<<"GUESSSAFE["<<loc_var_newpwd<<"]";
		//pwd<<"GUESSUNSAFE["<<loc_var_newpwd<<"]";
		c.sendData(loc_var_pwd.str());
		loc_var_counter++;
		loc_var_pwd.str("");
		loc_var_serverans=c.receive(16);
		cout <<loc_var_serverans<<endl;



		if(loc_var_serverans=="RIGHT")	//Rückgabe wenn das Passwort erraten worden ist
		{
			loc_var_pfound=1;
			cout<<"das erratende Passwort ist : \t"<<loc_var_newpwd<<endl;
			cout <<"Gebrauchte Versuche: \t"<<loc_var_counter<<"."<<endl;


			return loc_var_counter;

		}

		if(loc_var_length<=loc_var_number)
		{

		}

		else
		{
			loc_var_counter =bruteforce(loc_var_length,loc_var_alphabet,loc_var_alphabetlaenge,c,loc_var_partofpwd+loc_var_lang[i],loc_var_number,loc_var_counter,loc_var_pfound);
			if(loc_var_pfound)
			{
			return loc_var_counter;
			}
		}


	}
	return loc_var_counter;
}



