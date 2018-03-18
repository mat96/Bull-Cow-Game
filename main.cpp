/*This is the console executable, that makes use of the BullCow class
This acts as the view in MVC patter, and is responsible for all
user interaction. For game logic, see the FBullCow Game class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal Friendly
using FText = std::string;
using int32 = int;

// Decleration
void PrintIntro();
void AskWordLength();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();
FBullCowGame BCGame; // instantiate a new game, we reuse across plays


int main()
{
	
	bool bPlayAgain = false;// assumes users don't want to play again.
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
		
	} while (bPlayAgain);
	
	return 0; // exit the application
}

 void PrintIntro()
{


	std::cout << "Welcome to Bulls & Cows, a fun word game.\n";
	std::cout << "  \\\|/          (__)    " << std::endl;
	std::cout << "       `\\------(oo)    " << std::endl;
	std::cout << "         ||    (__)    " << std::endl;
	std::cout << "         ||w--||       \\|/" << std::endl;
	std::cout << "\\|/" << std::endl;


	AskWordLength();

	std::cout << "************************* Rules ***************************** \n";
	std::cout << "To win the game, you must get " << BCGame.GetHiddenWordLength() << " bulls\n";
	std::cout << "Bulls are letters that are in the word and are in the right position\n";
	std::cout << "Cows are letters that are in the word but are in the wrong place\n";
	std::cout << "The word is ALL lowercase letters\n";
	std::cout << "**************************************************************\n";




	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;
}
 

void PlayGame()
{
	

	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//Loop for the number of turns asking for guesses while the game 
	// is NOT won and there are still tries remaining
	
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) 
	{ 

		

		FText guess = GetValidGuess(); 
		
		
		//Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";

		
	}
	
	PrintGameSummary();
	 return;
}

    // Loop continually until user gets a valid guess       
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	
	do {
		//Get a guess from the player 
		int32 CurrentTry = BCGame.GetCurrentTry();
		
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout<< ". What is your guess? ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidility(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:

			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break; // comes out of switch

		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an Isogram (letters do not repeat themselves)\n\n";
			break;

		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters\n\n";
			
		default:
			//assume the guess is valid
			break;
		}
		

	} while (Status != EGuessStatus::OK);// keep looking until we get no errors
	return Guess;
}
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congrats, you must feel really good about yourself now...\n";
	}
	else
	{
		std::cout << "smh... You'll never figure it out\n";
	}
	return;
}

void AskWordLength()
{

	bool bInvalidAnswer = false;
	FString Answer;

	
		std::cout << "Please chose the length of the words you would like to play with\n";
		std::cout << "The word lenghts are available from 3 - 7\n";
		std::cin >> Answer;
		while(!(Answer == "3" || Answer == "4" || Answer == "5" || Answer == "6" || Answer == "7"))
		{

		std::cout << "Please Enter a valid answer\n";
		std::cin >> Answer;

		}

		BCGame.GetHiddenWord(Answer);
	
	
}

bool AskToPlayAgain()
{
	
	
		std::cout << "Do you want to play again? (y/n)\n";
		FText  Response = "";
		std::getline(std::cin, Response);
		std::cout << std::endl;


		return (Response[0] == 'y') || (Response[0] == 'Y');
	
	
}
