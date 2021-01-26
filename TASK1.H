/*
 * TASK1.H
 *
 *  Created on: 10.09.2019
 *      Author: aml
 */


/**
 *
 * \file TASK1.H
 *
 * \brief Contains namespace TASK1. Namespace TASK1 contains the implementation
 * of check sum calculation.
 *
 */



#ifndef TASK1_H_
#define TASK1_H_

#include <string>
#include "SHA256.H"

using namespace std;

/**
 *
 * \namespace TASK1
 *
 * \brief Contains the implementation
 * of check sum calculation.
 *
 */
namespace TASK1{



/**
 *
 * \var const string SYMBOLS
 *
 *	\brief This contains all possible characters a password can contain
 *
 */
const string SYMBOLS = "ABCDEFGHIJKLMNOPQRTSTUVWXYZabcdefghijklmopqrstuvwxyz0123456789";

/**
 *
 * \var const unsigned int MINIMAL_PWD_LENGTH
 *
 * \brief Defines the minimal length of a password
 *
 */
const unsigned int MINIMAL_PWD_LENGTH = 4;

/**
 *
 * \class IBlackBox
 *
 *	\brief Interface class for password check classes.
 *
 */
class IBlackBox{
public:
	virtual string input(string strPwd) = 0;
	virtual string getSymbols() = 0;
};


/**
 *
 * \class BlackBoxUnsafe
 *
 * \brief Implements a unsafe password checker where the
 * password is stored as plan text.
 *
 */
class BlackBoxUnsafe : public IBlackBox{
public:
				   BlackBoxUnsafe(int pwdLength, int symbSetSize);
	virtual string input(string strPwd);
			string getSymbols();

			string pwd_;

protected:
	string randomPwd(int pwdLength);
	char * charSymbArray_;
	int    lengthSymbArray_;
};






/**
 * \brief BlackBoxSafe
 *  Mit der Klasse wird ein schwieriger zu knackendes Passwort implementiert.
 *  Hier ist das Klartextpasswort eine private variable.
 *  Von außen kann nur auf die Checksumme (SHA256) zugegriffen werden.
 */

class BlackBoxSafe : public BlackBoxUnsafe{

public:
	BlackBoxSafe(int pwdLength, int symbSetSize) : BlackBoxUnsafe(pwdLength, symbSetSize){
		BlackBoxSafe_pwd=pwd_;
		BlackBoxSafe_sha= sha256 (pwd_); };


/**
 * \brief Blackboxsafe::check(string pwd)
 * Mithilfe dieser Methode wird das eingegebene Passwort in eine Prüfsumme gewandelt, welche anschließend mit
 * der in der Klasse hinterlegten Prüfsumme verglichen wird.
 * Wenn die beiden Prüfsummen gleich sind, wird ein "RIGHT" zurück gegeben. Falls dies nicht der Fall ist, wird ein
 * "WRONG" zurückgegeben.
 *
 */
	string check (string input);
	string BlackBoxSafe_sha;


private :
	string BlackBoxSafe_pwd;
};













/**
 *
 * \brief Simple demonstration of calculating
 * the check sum for a given string.
 *
 */
void demoTASK1_00();

/**
 *
 * \brief Simple demonstration of using the password checker.
 *
 */
void demoTASK1_01();

} // end namespace TASK1


#endif /* TASK1_H_ */
