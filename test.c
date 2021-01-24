/*
 * test.c
 *
 *  Created on: 24.01.2021
 *      Author: ubuntu
 */




void PwdErraten::Main_Bruteforce()
{
	//Passwort = argv;

	cout<<"Das erratende Passwort lautet:"<<endl;
	cin >> Passwort;

		for(int i=0;i <= 10; i++)
		{
			CallBruteForce(i,0,"");

		}

		return;

}

void PwdErraten::CallBruteForce(int i,int position,string BaseString)
{
	versuche = 0;
	for( int Count = 0; Count < SYMBOLS.length();Count++)
	{
		versuche++;

			if(position <= i)
			{
				CallBruteForce(i,position+1,BaseString + SYMBOLS[Count]);
			}

			if(BaseString + SYMBOLS[Count] ==Passwort)
			{
				//cout <<"Das Passwort ist: " + BaseString + SYMBOLS[Count]<<endl;
				cout << "GUESS["<<BaseString +SYMBOLS[Count]<<"]"<<endl;
				erratenpwd = "GUESS["+BaseString + SYMBOLS[Count]+"]";
				//cout<<erratenpwd;
				//cout<<"Versuche: "<<endl;
				//cout <<versuche <<endl;
				return;

			}

	}

}

string PwdErraten::geterraten()
{
	return erratenpwd;
}

class PwdErraten{

public:
	string erratenpwd;
	string pwd;
	string neupwd;
	string Passwort;
	long versuche;
	void Main_Bruteforce();
	void CallBruteForce(int i,int position,string BaseSteing);
	string geterraten();
};
