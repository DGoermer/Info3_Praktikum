/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <cstdio>
#include <unistd.h> //contains various constants
#include "SIMPLESOCKET.H"
#include "TASK1.H"
#include <ctime>
using namespace TASK1;
using namespace std;

/*
 *
 * Brute force methode die alle Möglichkeiten durch geht
 *
 *
 *
 *
 *
 *
 * */

int PWDRaten(string const& chars, size_t max_len, string const& cur){
	string meinpwd ="Bbcd";
	clock_t time;
	double duration;

	time = clock();
	if (cur.length()== max_len){
		return 0;
	}
	else {
		for (auto c : chars){
			string next =cur + c;
			cout << next << endl;
			if(next==meinpwd){
				cout<<"Password geknackt"<<endl;
				duration = (clock() - time) / (double) CLOCKS_PER_SEC;
				cout << " Das erraten des Password hat"<< duration << " sekunden gedauert."<<endl;
				exit(1);

			}
			else{
				PWDRaten(chars,max_len,next);
			}
		}
	}


}



int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg;
	string newmsg;
	//connect to host
	c.conn(host , 2024);

	int i=0;


	string symbols=TASK1::SYMBOLS;
	newmsg=PWDRaten(symbols,4,"");

	bool goOn=1;
	while(goOn){ // send and receive data
		if((rand() % 20) < i++){
			msg = string("BYEBYE");
			goOn = 0;
		}else{
			msg = string("client wants this");
		}
		cout << "client sends:" << newmsg << endl;
		c.sendData(newmsg);
		msg = c.receive(32);
		cout << "got response:" << newmsg << endl;
		sleep(1);



	}
}


