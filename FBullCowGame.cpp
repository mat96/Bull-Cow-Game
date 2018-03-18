#pragma once
#include "FBullCowGame.h"
#include <map>
// to make syntax Unreal friendly
#define TMap std::map 
using int32 = int;

FBullCowGame::FBullCowGame() //Constructor
{
	
	Reset();
	
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const { return bGameWon; }


FString FBullCowGame::GetHiddenWord(FString Answer)
{
	FString LengthofWord = Answer;
	 FString Hidden_Word;
	 
	 if (LengthofWord == "3")
	 {
		 Hidden_Word = "ant"; //( this MUST be an isogram
		 
	 }
	 else if (Answer == "4")
	 {
		 Hidden_Word = "late";
		 
	 }
	 else if (LengthofWord == "5")
	 {
		 Hidden_Word = "chair";
	 }
	 else if (LengthofWord == "6")
	 {
		 Hidden_Word = "planet";
		 
	 }
	 else if (LengthofWord == "7")
	 {

		 Hidden_Word = "compute";
		 
	 }


	 MyHiddenWord = Hidden_Word;

	return MyHiddenWord;
	
}



int32 FBullCowGame::GetMaxTries() const { 

	TMap <int32, int32 > WordLengthToMaxTries{ {3,7}, {4, 11}, {5, 15}, {6, 20}, {7, 25} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
	

}


void FBullCowGame::Reset()
{
	
	MyHiddenWord;

	  MyCurrentTry = 1;
	  bGameWon = false;
	
	return;
}



EGuessStatus FBullCowGame::CheckGuessValidility(FString guess) const {
	
	if (!IsIsogram (guess))    
	{
		return EGuessStatus::Not_Isogram;// if the guess isnt an isogram
	}
	else if (!IsLowercase(guess))	//if the guess inst all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (guess.length() != GetHiddenWordLength())//if the guess length is wrong
	{
		
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}

	


	 
}

// Recieves a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
	// incriment the turn number
	MyCurrentTry++;
	// setup a return variable
	FBullCowCount BullCowCount;


	// loop through all letters in the hidden worg
	int32 WordLength = MyHiddenWord.length(); //Length() comes from <string>,, assuming same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++ ) 
	{ 
		
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match then
			if (guess[GChar] == MyHiddenWord[MHWChar]) 
			{
				if (MHWChar == GChar)
				{// if they are in the same place
				 BullCowCount.Bulls++;  // incriment bulls
					 
				}
				else
				{
					BullCowCount.Cows++; // must be cow
					
				}

			}	// incriment t	
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameWon = true;
	}
	else
	{
		bGameWon = false;
	}
	
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const // private class
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	// setup our map
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)  // for all letters of the word...  ":" is word for "in" for ranged based for
	{
		Letter = tolower(Letter);   //handle micxd case
	
			// if the letter is in the map 
		if (LetterSeen[Letter]) { return false; } // This is NOT an Isogram
		else 
		{
			LetterSeen [Letter] = true; //otherwise
		}
			// add the letter to the map as seen

   	}
	

	return true; // for example in cases where /0 is entered 
	
}

bool FBullCowGame::IsLowercase(FString word) const
{
	//Handles string length of
	if (word.length() < 1 || word == "/0") { return true; }
	for (auto Letter : word)
	{
		if (!islower(Letter)) { return false; }
	
	}
	return true;
	
}




