/*
 * bruteforce.C
 *
 *  Created on: 23.01.2021
 *      Author: ubuntu
 */
#include <string>
#include <iostream>
using namespace std;

const string SYMBOLS = "ABCDEFGHIJKLMNOPQRTSTUVWXYZabcdefghijklmopqrstuvwxyz0123456789";

class PwdErraten{

public:



void Bruteforce(string const& chars, size_t max_len, string const& current){
	string next;
	string pwd;
		if (current.length()== max_len){
			return;
		}
			else
			{
				for (auto c : chars)
				{

					 next =current + c;
					 cout<<next<<endl;
					Bruteforce(chars,max_len,next);


			}

		}
	}
};
void main()
{
	PwdErraten test;

	test.Bruteforce(SYMBOLS,4,"");

}
