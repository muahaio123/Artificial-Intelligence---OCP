// YOUR NAME: Thanh Long Le
//
// ASU AI Competition
// Agent Challenge A: One-card poker
//
// Rename this file and the function below.  For example, if your agent name
// is Jones, rename this ocpAgentSmith.cpp file to ocpAgentJones.cpp and the
// ocpAgentSmith function below to ocpAgentJones.  Complete your agent
// function and turn it in on Blackboard.  Feel free to create other
// agents--each in a separate .cpp file--for yours to compete against, but
// turn in only one.  Test your agent(s) with
//
//    nice bash ocpBuild.bash
//
// and then
//
//    nice ./ocpRunSim
//
// Each submitted agent will play each other in matchups of some number of
// hands each (at least 100) to determine the standings, which will be
// posted soon after the agents are due.

#include "ocp.h"

// Rename and complete this agent function.
int ocpAgentJackie(const MatchupHistory &mh)
{
	int myCard = mh.getOwnCurrentCard();
	
	// obvious move to max/min the score
	if (myCard == 4)
		return 4;
	if (myCard == 1)
		return 1;
	
	// Your function must end up returning a bet between 1 and mh.getLimit().
	int matchSz = mh.getNumCompletedHands();
	
	// think simple for the first 49 rounds and every 10 rounds
	if (matchSz < 100)
	{
		// play only 1 or 2 (50 - 50) to minimize loss
		// when the current card is 2
		if (myCard == 2)
			return (randomInt(2) + 1);
		
		// place more high risk bets
		// when the current card is 3
		if (myCard == 3)
			return (randomInt(100) < 50) ? 3 : 4;
	}
	
	int obvious = 0;
	
	for (int i = mh.getNumCompletedHands() - 1; i >= mh.getNumCompletedHands() - 1 - 100; --i)	// learn from the pass 100 pass
		if ((mh.getOpponentPastBet(i) <= 2 && mh.getOpponentPastCard(i) <= 2) || (mh.getOpponentPastBet(i) >= 3 && mh.getOpponentPastCard(i) >= 3))
			obvious++;
	
	int maximum = INT_MIN, bestChoice = 0, minimum = INT_MAX;
	
	// try to do minimax but with only 1 level on my possible choices of 2 and 3
	for (int myChoice = 1; myChoice <= 4; ++myChoice)
	{
		for (int theirChoice = 1; theirChoice <= 4; ++theirChoice)
		{
			if (myChoice > theirChoice)
				minimum = min(minimum, theirChoice);
			else if (myChoice < theirChoice)
				minimum = min(minimum, myChoice * (-1));
			else
			{
				if (randomInt(100) < obvious)
					minimum = min(minimum, 2);
				
				else
					minimum = min(minimum, -3);
			}
			
			if (minimum > maximum)
			{
				maximum = minimum;
				bestChoice = myChoice;
			}
		}
	}
	
	return bestChoice;
}
/*
	I am just doing really simple coding
	That: the player will always play the most obvious move regarding the current hand
	
	some times, when I get 1, i will return 1 to minimize lost points
	when get 4, return 4, b/c it is sure win
	
	when i get to the other 2 cases, I will learn from the past whether the opponent is making obvious moves
	then I will try to do minimax with only 1 level, I max and they will min
	
	just looking at the past 100 rounds
	
	strength: none??? a more defensive agent
	weakness: this is totally depends on the opponent's choices of their bet and card
*/
