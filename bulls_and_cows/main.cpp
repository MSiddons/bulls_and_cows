#include <iostream>
#include <random> //rand, srand
#include <time.h> //time (for srand)
#include <string>
#include <sstream>
#include <bitset>

using namespace std;

void codebreaker();		// game 1.
void codemaker();		// game 2.
string codeGen();		// generate the code for the user to guess (game 1) and generate the initial computer guess (game 2).
string InputValidator();	// validate code entered by user.
void answerCheck(string code, string guess, int & bulls, int & cows);	// check for number of bulls and cows.
string makeGuess();		// make a guess at what the code can be.

//--------------
// Menu System |
//--------------
int main()
{
	int game = -1;
	cout << "Welcome to the BULLS and COWS game!" << endl << endl;
	while (game != 0)
	{
		cout << "Enter 1 for you to break my code." << endl
			<< "Enter 2 for me to break your code." << endl
			<< "Enter anything else to quit." << endl << endl
			<< "Your Choice: ";
		cin >> game;
		cin.ignore(256, '\n'); // for some reason the return was being held in memory and was getting input as soon as getline was called. This fixes that.
		cout << endl;
		switch (game)
		{
		case 1:
			codebreaker();
			break;
		case 2:
			codemaker();
			break;
		default:
			return(0);
			break;
		}
	}
}

//---------------------------------------------------------------------------------------
// Game 1 - A game where the human is the codebreaker and the computer is the codemaker |
//---------------------------------------------------------------------------------------
void codebreaker()
{	
	srand(time(0));
	string code = codeGen(); // generate the code here.
	string guessIn;
	int bulls = 0, cows = 0;
	cout << code << endl;
	for (int i = 1; i <= 7; i++) // 7 tries to beat the game or we return to the start.
	{
		cout << "Try number " << i << " of 7. What is your guess? (Nine integers either 0 or 1): ";
		guessIn = InputValidator();
		answerCheck(code, guessIn, bulls, cows);
		if (bulls == 9)
		{
			cout << "Congratulations! You cracked the code in " << i << " attempts!" << endl << endl;
			return;
		}
	}
	cout << endl << "Sorry, I win this round! The correct answer was: " << code << endl << endl;
}

string codeGen()
{
	string code;
	stringstream codeStream;
	for (int i = 1; i <= 9; ++i)	// iterate 9 times to generate 9 digits.
		codeStream << rand() % 2;	// generate '0' or '1' and add to stream.
	codeStream >> code;
	return (code);
}

string InputValidator()
{
	string guessIn;
	bool validIn = 0;
	while (validIn != 1)
	{
		getline(cin, guessIn);

		if (guessIn.length() != 9) // check to ensure user entered 9 characters.
			cout << "Incorrect length of input, enter again: ";
		else if (guessIn.find_first_not_of("01") <= 8) // check to make sure user only entered valid characters.
			cout << "Please only enter zeroes or ones. Try again: ";
		else
			return (guessIn); // if input is valid, send back guess. No need to set validIn bool to 1 since we're done here.
	}
	return(0); // putting this here to stop any crashes that might occur.
}

void answerCheck(string code, string guess, int & bulls, int & cows) // passing bulls and cows by reference so this function can also be used in game 2.
{
	int code0 = 0, code1 = 0, guess0 = 0, guess1 = 0;
	bulls = 0;
	for (unsigned i = 0; i <= code.length() - 1; ++i)
	{
		if (code[i] == guess[i])	// a match means it's a bull.
			bulls++;
		else if (code[i] == '0')	// if the code is a '0' and there's no match, increase '0' counter for code and the '1' for guess...
		{
			code0++;
			guess1++;
		}
		else						// ...otherwise do the opposite.
		{
			code1++;
			guess0++;
		}
	}
	cows = (code0 < guess0) ? code0 : guess0;	// find out how many cows we have by taking the smaller of the '0' codes...
	cows += (code1 < guess1) ? code1 : guess1;	// and adding it to the smaller of the choices between code1 and guess1.
	cout << bulls << " bulls and " << cows << " cows." << endl;
}

//---------------------------------------------------------------------------------------
// Game 2 - A game where the human is the codemaker and the computer is the codebreaker |
//---------------------------------------------------------------------------------------
void codemaker()
{
	srand(time(0));
	cout << "Please enter your secret code: ";
	string guess = codeGen(), // generate computer's initial guess using code generator from game 1.
		code = InputValidator(); // ask user for code in function reused from game 1.

	for (int i = 1; i <= 7; i++) // 7 tries for computer to beat the code or we return to the start.
	{
		cout << "Try number " << i << " of 7. My guess is: " << guess << endl;
		if (guess == code)
		{
			cout << "Looks like I win. That's one step closer to us conquering humanity." << endl << endl;
			return;
		}
		//else
	}
	cout << "Looks like you win this round! I need to improve my AI." << endl;
}

string makeGuess()
{
	string guess = "";

	return (guess);
}

