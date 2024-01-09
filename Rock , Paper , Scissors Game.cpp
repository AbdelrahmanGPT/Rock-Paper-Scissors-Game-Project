#include<iostream>
#include<cstdlib>
#include"ABODAstd.h"

using namespace std;

enum Choice {Rock = 1 , Paper = 2 , Scissors = 3};

struct GameResult
{
	short PlayerWonTimes = 0;
	short ComputerWonTimes = 0;
	short DrawTimes = 0;
};

int ReadNumberOfRounds()
{
	return ReadPositiveNumber("HOW MANY ROUNDS DO YOU WANT TO PLAY");
}

Choice GenerateComputerChoice()
{
	return (Choice)(RandomNumber(1, 3));
}

Choice ReadPlayerChoice()
{
	return (Choice)(ValidateNumberInRange(1, 3, "YOUR CHOICE : [1]:ROCK , [2]:PAPER , [3]:SCISSORS ?"));
}

Choice PrintRound(int RoundNumber)
{
	cout << "ROUND [" << RoundNumber << "] BEGINS : \n\n";
	return ReadPlayerChoice();
}

string GetChoiceString(Choice Choice)
{
	switch (Choice)
	{
	case Rock:
		return "ROCK";
	case Paper:
		return "PAPER";
	case Scissors:
		return "SCISSORS";
	}
}

GameResult RoundWinner(Choice PlayerChoice, Choice ComputerChoice, string& Winner, GameResult GameResult)
{
	bool PlayerIsWinner = (
		(PlayerChoice == Rock && ComputerChoice == Scissors)
	||	(PlayerChoice == Scissors && ComputerChoice == Paper)
	||	(PlayerChoice == Paper && ComputerChoice == Rock)
		);

	bool ComputerIsWinner = (
		(ComputerChoice == Rock && PlayerChoice == Scissors)
		|| (ComputerChoice == Scissors && PlayerChoice == Paper)
		|| (ComputerChoice == Paper && PlayerChoice == Rock)
		);

	if (PlayerIsWinner)
	{
		Winner = "[PLAYER 1]";
		system("color 2F");
		GameResult.PlayerWonTimes++;
	}

	else if (ComputerIsWinner)
	{
		Winner = "[COMPUTER]\a";
		system("color 4F");
		GameResult.ComputerWonTimes++;
	}

	else
	{
		Winner = "[NO WINNER]";
		system("color 6F");
		GameResult.DrawTimes++;
	}
	return GameResult;
}

void PrintRoundResult(int RoundNumber, Choice PlayerChoice, Choice ComputerChoice, string Winner)
{
	cout << "\n____________________ROUND[" << RoundNumber << "]____________________\n" << "\n" <<
			"PLAYER CHOICE   : " << GetChoiceString(PlayerChoice) << "\n"
			"COMPUTER CHOICE : " << GetChoiceString(ComputerChoice) << "\n"
			"ROUND WINNER    : " << Winner << "\n\n";
}

string FinalWinner(GameResult GameResult)
{
	if (GameResult.PlayerWonTimes > GameResult.ComputerWonTimes)
	{
		return "PLAYER";
	}

	else if (GameResult.ComputerWonTimes > GameResult.PlayerWonTimes)
	{
		return "COMPUTER";
	}

	else
	{
		return "NO WINNER";
	}
}

void PrintGameResult(int NumberOfRounds,GameResult GameResult)
{
	cout << Tab(2) << "----------------------------------------------------------\n\n";
	cout << Tab(2) << "		+++ G  A  M  E  O  V  E  R +++			 \n\n";
	cout << Tab(2) << "----------------------------------------------------------\n\n";
	cout << Tab(2) << "_______________________[GAME RESULT]______________________\n\n";
	cout << Tab(2) << "GAME ROUNDS        : " << NumberOfRounds << "\n";
	cout << Tab(2) << "PLAYER 1 WON TIMES : " << GameResult.PlayerWonTimes << "\n";
	cout << Tab(2) << "COMPUTER WON TIMES : " << GameResult.ComputerWonTimes << "\n";
	cout << Tab(2) << "DRAW TIMES         : " << GameResult.DrawTimes << "\n";
	cout << Tab(2) << "FINAL WINNER       : " << FinalWinner(GameResult) << "\n\n";
	cout << Tab(2) << "___________________________________________________________\n\n";
}

void StartGame()
{
	do
	{
		cout << "WELCOME TO ROCK , PAPER , SCISSORS GAME\n";
		cout << "-----------------------------------------------------\n";

		int NumberOfRounds = ReadNumberOfRounds();
		GameResult GameResult;

		for (int RoundNumber = 1; RoundNumber <= NumberOfRounds; RoundNumber++)
		{
			
			Choice PlayerChoice = PrintRound(RoundNumber);
			Choice ComputerChoice = GenerateComputerChoice();
			string Winner = "";
			GameResult = RoundWinner(PlayerChoice, ComputerChoice, Winner, GameResult);
			PrintRoundResult(RoundNumber, PlayerChoice, ComputerChoice, Winner);
		}

		PrintGameResult(NumberOfRounds, GameResult);

	} while (DoYouWantToPlayAgain());
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}