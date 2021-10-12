// YOUR NAME: Nam Bui
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

namespace
{
}

// Rename and complete this agent function.

int ocpAgentNam(const MatchupHistory &mh)
{
    if (mh.getOwnCurrentCard() == 4) // if card is 4 bet 4
		return 4;
	
	if (mh.getOwnCurrentCard() == 1) // if card is 1 bet 1
		return 1;
	
	int overBet = 0;
	int underBet = 0;
	
	for (uint i = mh.getNumCompletedHands(); i > 0; i--) // check to see the amount of time opponent bet more/less than their cards
	{
		if (mh.getOpponentPastBet(i - 1) >= mh.getOpponentPastCard(i - 1))
			overBet++;
		
		if (mh.getOpponentPastBet(i - 1) < mh.getOpponentPastCard(i - 1))
			underBet++;
	}
	
	//int r = randomInt(mh.getNumCompletedHands());
	
	if (underBet >= overBet) // if they are under betting make use of it
		return mh.getOwnCurrentCard();
	
    return 1;
}
