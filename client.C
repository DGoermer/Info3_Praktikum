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
int serverport;
string host;
int duration;
int alphabetlaenge;

int pwdlaenge;
TCPclient c;
int bruteforce(int length,string alphabet, int alphabetlaenge,
		TCPclient connection, string partofpwd,int number , int counter, bool &pfound);





int main(int argc, char *argv[]) {
	serverport = (unsigned short) atoi(argv[3]);
	alphabetlaenge=(unsigned short) atoi(argv[4]);
	pwdlaenge = (unsigned short) atoi(argv[5]);
	duration = (unsigned short) atoi(argv[3]);
	int wiederholungen = 10;
	cout << " Willkommen im Client ! " << endl << "Bitte geben sie den Port des Servers ein:  ";
	cin >> serverport;

	srand(time(NULL));





	host = "localhost";

	/*string msg;
	string newmethode;
	string methode;
	string newmsg;
	string pwd;
	string auswahl;
	string servermsg;
	string newerat;
	std::string::size_type sz;

	char input[] = "NEWSAFE[";
	char guess[] = "GUESSSAFE[";
	char end[] = "]";
	char komma[] = ",";
	string a,b;
	int brute_zahl;*/
	//connect to host
	c.conn(host , serverport);

	//TASK1::PwdErraten PWDmethode;
	int versuche;
	int number = 0;
	bool pfound = 0;

	string alphabet= "ABCDEFGHIJKLMNOPQRTSTUVWXYZabcdefghijklmopqrstuvwxyz0123456789";
	stringstream ss;
	string tmp;
	timeval start,end;
	int time;
	long avaragetime = 0;
	int averagetries = 0;
	string servermsg;
	cout<<"Bitte geben sie Pwdlaenge ein"<<endl;
	cin>>pwdlaenge;
	cout<<"Bitte geben sie alphabetlange ein"<<endl;
	cin>> alphabetlaenge;



	if (alphabetlaenge >=alphabet.length())

	{
		alphabetlaenge=alphabet.length()-1;
	}

		ss.str("");
	for(int i=1;i<pwdlaenge;i++)
	{
		for(int j = 1;j<=alphabetlaenge;j++)
		{
			for(int k=0;k<wiederholungen;k++)
			{
				while(1)
				{

				if (servermsg == "Generiert."){

					ss.str("");
					number++;

					versuche=bruteforce(pwdlaenge,alphabet,alphabetlaenge,c,"",0,0,pfound);
					//cout <<"Versuche"<<versuche<<endl;

				}
				else
				{


				ss.str("");
				ss<<"NEWSAFE["<<pwdlaenge<<","<<alphabetlaenge<<"]";
				c.sendData(ss.str());
				servermsg =c.receive(32);
				sleep(1);
				}
				}



			sleep(0);

		}
	}

	return 0;

}
}
int bruteforce(int length,string alphabet, int alphabetlaenge,
		TCPclient c, string partofpwd,int number , int counter, bool &pfound)
{
	string lang= "ABCDEFGHIJKLMNOPQRTSTUVWXYZabcdefghijklmopqrstuvwxyz0123456789";
	number++;
	stringstream pwd;
	string newpwd;
	string serverans;
	for(int i=0;i<alphabetlaenge;i++)
	{
		newpwd = partofpwd+lang[i];

		pwd<<"GUESSSAFE["<<newpwd<<"]";

		c.sendData(pwd.str());
		counter++;
		c.receive(20);
		sleep(0);


	if(serverans=="RICHTIG")
	{
		pfound=1;
		cout<<partofpwd+alphabet[i];
		return counter;
	}
	if(length<=number)
	{

	}
	else
	{
		counter =bruteforce(length,alphabet,alphabetlaenge,c,partofpwd+lang[i],number,counter,pfound);
		if(pfound)
		{
			return counter;
		}
	}

	sleep(0);
	}
	return counter;
}



