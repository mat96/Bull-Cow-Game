/*The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>

//Make syntac Unreal Friedly
using FString = std::string;
using int32 = int;


struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;

};

enum class EGuessStatus 
{
	    Invalid_Status,
		OK,
		Wrong_Length,
		Not_Lowercase,
		Not_Isogram,
};



class FBullCowGame
{
public:// this is the public interface
	FBullCowGame(); // Constructor (same name ass the class)
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidility(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);
	void SetHiddenWord(int32 Answer);



	FString MyHiddenWord;
	

	

	//Helper functions,
private:
	// See constructor for initialisation 
	int32 MyCurrentTry;
	bool bGameWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	
	

};