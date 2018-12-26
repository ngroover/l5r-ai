#include "phasemanager.h"
#include <iostream>
#include <sstream>

using namespace l5r;


phaseManager::phaseManager(std::shared_ptr<gamestate> state,
            std::shared_ptr<dynastyCardManager> dynastyMgr,
            std::shared_ptr<conflictCardManager> conflictMgr,
            std::shared_ptr<provinceCardManager> provinceMgr,
            std::shared_ptr<turnManager> turnMgr,
            std::shared_ptr<tokenManager> tokenMgr,
            std::shared_ptr<ringManager> ringMgr,
            std::shared_ptr<agentManager> agentMgr):
            state(state),dynastyMgr(dynastyMgr),
            conflictMgr(conflictMgr), provinceMgr(provinceMgr),
            turnMgr(turnMgr), tokenMgr(tokenMgr),ringMgr(ringMgr),
            agentMgr(agentMgr)
{
}

phaseManager::~phaseManager()
{
}

void phaseManager::goToProvincePlay()
{
   state->currentSubPhase = subphase::province_play;
}
void phaseManager::goToAdditionalFate()
{
   state->currentSubPhase = subphase::additional_fate;
}

void phaseManager::goToStrongholdSelection()
{
   state->currentPhase = phase::pregame;
   state->currentSubPhase = subphase::stronghold_selection;
}

void phaseManager::goToDynastyMulligan()
{
   state->currentPhase = phase::pregame;
   state->currentSubPhase = subphase::dynasty_mulligan;
}

void phaseManager::goToConflictMulligan()
{
   state->currentPhase = phase::pregame;
   state->currentSubPhase = subphase::conflict_mulligan;
}

void phaseManager::doAction(choice c)
{
   switch(state->currentPhase)
   {
      case phase::pregame:
         pregameDoAction(c);         
         break;
      case phase::dynasty:
         dynastyDoAction(c);
         break;
      case phase::draw:
         drawDoAction(c);
         break;
      default:
         throw std::runtime_error("Invalid phase");
   }
}

void phaseManager::pregameDoAction(choice c)
{
   switch(state->currentSubPhase)
   {
      case subphase::stronghold_selection:
         doStrongholdSelection(c);
         break;
      case subphase::dynasty_mulligan:
         doDynastyMulligan(c);
         break;
      case subphase::conflict_mulligan:
         doConflictMulligan(c);
         break;
      default:
         throw std::runtime_error("Invalid substate");
   }
}

void phaseManager::drawDoAction(choice c)
{
   switch(state->currentSubPhase)
   {
      case subphase::bid:
         doBid(c);
         break;
      default:
         throw std::runtime_error("Invalid substate");
   }
}

void phaseManager::dynastyDoAction(choice c)
{
   switch(state->currentSubPhase)
   {
      case subphase::province_play:
         doProvincePlayAction(c);
         break;
      case subphase::additional_fate:
         doAdditionalFate(c);
         break;
      default:
         throw std::runtime_error("Invalid substate");
   }
}

void phaseManager::doStrongholdSelection(choice c)
{
   if(c.getType() == choicetype::card)
   {
      provinceMgr->chooseStronghold(c.getNumber());
      if(turnMgr->ActionAndTurnDiffer())
      {
         for(int p=1;p<=2;p++)
         {
            playerstate &pState = state->getPlayerState(p);
            std::string name = agentMgr->getPlayerName(p);
            dynastyMgr->fillProvinces(pState, name);
         }
         goToDynastyMulligan();
      }
      turnMgr->swapAction();
   }
   else
   {
      throw std::runtime_error("Not a card choice!");
   }
}

void phaseManager::doBid(choice c)
{
   if(c.getType() == choicetype::bid)
   {
      playerstate &pState = state->getPlayerState(relativePlayer::myself);
      std::string name = agentMgr->getPlayerName(relativePlayer::myself);
      tokenMgr->setHonorDial(c.getNumber(), pState, name);

      if(turnMgr->ActionAndTurnDiffer())
      {
         playerstate &oppState = state->getPlayerState(relativePlayer::opponent);
         std::string oppname = agentMgr->getPlayerName(relativePlayer::opponent);
         int myhonor = tokenMgr->getHonorDial(pState);
         int hishonor = tokenMgr->getHonorDial(oppState); 
         if( myhonor > hishonor)
         {
            tokenMgr->gainHonor(myhonor-hishonor, pState, name);
            tokenMgr->gainHonor(hishonor-myhonor, oppState, oppname);
         }
         else if(hishonor > myhonor)
         {
            tokenMgr->gainHonor(hishonor-myhonor, pState, name);
            tokenMgr->gainHonor(myhonor-hishonor, oppState, oppname);
         }
         conflictMgr->drawCards(myhonor, pState, name);
         conflictMgr->drawCards(hishonor, oppState, oppname);
         state->currentPhase = phase::gameover;
      }
      else
      {
         turnMgr->swapAction();
      }
   }
   else
   {
      throw std::runtime_error("Not a card choice!");
   }
}

void phaseManager::doDynastyMulligan(choice c)
{
   if(c.getType() == choicetype::card)
   {
      dynastyMgr->chooseMulliganCard(c.getNumber());
   }
   else if(c.getType() == choicetype::pass)
   {
      playerstate &pState = state->getPlayerState(relativePlayer::myself);
      std::string name = agentMgr->getPlayerName(relativePlayer::myself);
      dynastyMgr->performMulligan();
      dynastyMgr->fillProvinces(pState, name);
      if(turnMgr->ActionAndTurnDiffer())
      {
         for(int p=1;p<=2;p++)
         {
            playerstate &pState = state->getPlayerState(p);
            std::string name = agentMgr->getPlayerName(p);
            conflictMgr->drawCards(STARTING_NUM_CONFLICT_CARDS, pState, name);
         }
         goToConflictMulligan();
      }
      turnMgr->swapAction();
   }
   else
   {
      throw std::runtime_error("Not a card choice!");
   }
}

void phaseManager::doConflictMulligan(choice c)
{
   if(c.getType() == choicetype::card)
   {
      conflictMgr->chooseMulliganCard(c.getNumber());
   }
   else if(c.getType() == choicetype::pass)
   {
      conflictMgr->performMulligan();
      playerstate &pState = state->getPlayerState(relativePlayer::myself);
      std::string name = agentMgr->getPlayerName(relativePlayer::myself);
      conflictMgr->drawCards(STARTING_NUM_CONFLICT_CARDS-conflictMgr->getNumCards(),pState,name);
      
      if(turnMgr->ActionAndTurnDiffer())
      {
         // set starting honor
         for(int i=1;i<=2;i++)
         {
            std::string name = agentMgr->getPlayerName(i);
            int startingHonor = provinceMgr->getStartingHonor(i);
            tokenMgr->setHonor(startingHonor, i, name);
         }

         // set rings unclaimed
         ringMgr->setAllUnclaimed();

         // setup dynasty
         doDynastyEntry();
      }
      else
      {
         turnMgr->swapAction();
      }
   }
   else
   {
      throw std::runtime_error("Not a card choice!");
   }
}

void phaseManager::doDynastyEntry()
{
   std::cout << "Beginning Dynasty Phase" << std::endl;
   state->currentPhase = phase::dynasty;
   goToProvincePlay();

   // gain fate
   // TODO: read fate value from stronghold card
   for(int i=1;i<=2;i++)
   {
      std::string name = agentMgr->getPlayerName(i);
      playerstate &pState = state->getPlayerState(i);
      dynastyMgr->flipAllDynastyFaceup(pState, name);
      tokenMgr->gainFate(STRONGHOLD_FATE, pState, name);
   }
   turnMgr->setActionToCurrentTurn();
}

void phaseManager::doDrawPhaseEntry()
{
   std::cout << "Beginning Draw Phase" << std::endl;
   state->currentPhase = phase::draw;
   state->currentSubPhase = subphase::bid;

   turnMgr->setActionToCurrentTurn();
}

void phaseManager::doProvincePlayAction(choice c)
{
   if(c.getType() == choicetype::card)
   {
      playerstate &pState = state->getPlayerState(relativePlayer::myself);
      dynastyMgr->chooseCharacterToPlay(pState, c.getNumber());
      goToAdditionalFate();
   }
   else if(c.getType() == choicetype::pass)
   {
      playerstate &oppState = state->getPlayerState(relativePlayer::opponent);
      // opponent has not passed
      if(!oppState.passed)
      {
         playerstate &pState = state->getPlayerState(relativePlayer::myself);
         std::string name = agentMgr->getPlayerName(relativePlayer::myself);
         std::cout << name << " passed first" << std::endl;
         tokenMgr->gainFate(1, pState, name);
         pState.passed = true;
         turnMgr->swapAction();
      }
      else
      {
         doDrawPhaseEntry();
      }
   }
   else
   {
      throw std::runtime_error("Invalid choice");
   }
}

void phaseManager::doAdditionalFate(choice c)
{
   if(c.getType() == choicetype::fate)
   {
      playerstate &pState = state->getPlayerState(relativePlayer::myself);
      std::string name = agentMgr->getPlayerName(relativePlayer::myself);
      dynastyMgr->playCharacter(pState, name);
      tokenMgr->addFateToCard(pState, dynastyMgr->getPendingFateCard(pState), c.getNumber());
      dynastyMgr->fillProvinces(pState, name);

      playerstate &oppState = state->getPlayerState(relativePlayer::opponent);
      goToProvincePlay();
      if(!oppState.passed)
      {
         turnMgr->swapAction();
      }
   }
   else
   {
      throw std::runtime_error("Invalid choice");
   }
}

decision phaseManager::getDecision()
{
   switch(state->currentPhase)
   {
      case phase::pregame:
         return getPreGameDecision();
      case phase::dynasty:
         return getDynastyDecision();
      case phase::draw:
         return getDrawDecision();
   }
}

decision phaseManager::getPreGameDecision()
{
   switch(state->currentSubPhase)
   {
      case subphase::stronghold_selection:
         return getStrongholdDecision();
      case subphase::dynasty_mulligan:
         return getDynastyMulliganDecision();
      case subphase::conflict_mulligan:
         return getConflictMulliganDecision();
      default:
         throw std::runtime_error("Invalid substate");
   }
}

decision phaseManager::getDynastyDecision()
{
   switch(state->currentSubPhase)
   {
      case subphase::province_play:
         return getProvincePlayDecision();
      case subphase::additional_fate:
         return getAdditionalFateDecision();
      default:
         throw std::runtime_error("Invalid substate");
   }
}

decision phaseManager::getDrawDecision()
{
   switch(state->currentSubPhase)
   {
      case subphase::bid:
         return getBidDecision();
      default:
         throw std::runtime_error("Invalid substate");
   }
}

decision phaseManager::getStrongholdDecision()
{
   std::list<choice> list = provinceMgr->getStrongholdChoices();
   decision d("Choose a stronghold", list);
   return d;
}

decision phaseManager::getBidDecision()
{
   std::list<choice> list;
   for(int i=MIN_BID;i<=MAX_BID;i++)
   {
      std::stringstream ss;
      std::string bidStr;
      ss << i;
      ss >> bidStr;
      choice c(bidStr, choicetype::bid);
      c.setNumber(i);
      list.push_back(c);
   }
   decision d("Choose a honor bid", list);
   return d;
}

decision phaseManager::getDynastyMulliganDecision()
{
   std::list<choice> list = dynastyMgr->getProvinceDynastyChoices(dynastyCardStatus::facedown); // all should be facedown
   list.push_back(choice("Pass", choicetype::pass));
   decision d("Choose a card to mulligan", list);
   return d;
}

decision phaseManager::getConflictMulliganDecision()
{
   std::list<choice> list = conflictMgr->getConflictCardChoices();
   list.push_back(choice("Pass", choicetype::pass));
   decision d("Choose a card to mulligan", list);
   return d;
}

decision phaseManager::getProvincePlayDecision()
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   int currentFate = tokenMgr->getFate(pState);
   std::list<choice> list = dynastyMgr->getProvinceDynastyChoicesWithFate(dynastyCardStatus::faceup, currentFate); // all should be facedown
   list.push_back(choice("Pass", choicetype::pass));
   decision d("Choose a card to play", list);
   return d;
}

decision phaseManager::getAdditionalFateDecision()
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   std::list<choice> list = tokenMgr->getAdditionalFateChoices(pState, dynastyMgr->getPendingFateCard(pState));
   decision d("Choose an amount of fate to add:", list);
   return d;
}
