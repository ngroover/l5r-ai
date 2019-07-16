#include "phasemanager.h"
#include <iostream>
#include <sstream>
#include "gamestateintfc.h"
#include "tokenmanager.h"
#include "mulliganmanager.h"
#include "imperialfavormanager.h"
#include "conflictphasemanager.h"
#include "ringmanager.h"
#include "endgame.h"

using namespace l5r;

phaseManager::phaseManager(std::shared_ptr<gamestate> state,
            std::shared_ptr<dynastyCardManager> dynastyMgr,
            std::shared_ptr<provinceCardManager> provinceMgr,
            std::shared_ptr<turnManager> turnMgr,
            std::shared_ptr<cardDataManager> cardMgr,
            std::shared_ptr<GameStateIntfc> stateIntfc):
            state(state),dynastyMgr(dynastyMgr),
            provinceMgr(provinceMgr),
            turnMgr(turnMgr), cardMgr(cardMgr),
            stateIntfc(stateIntfc)
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

void phaseManager::goToChooseConflictType()
{
}

void phaseManager::goToConflictPhase()
{
   RingManager rings(stateIntfc, cardMgr);

   state->currentPhase = phase::conflict;
   state->currentSubPhase = subphase::choose_attackers;
   rings.initializeConflicts();
   // first player gets to be in conflict first
   state->currentConflict = state->currentTurn;
}

void phaseManager::doAction(choice c)
{
   try
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
         case phase::conflict:
            conflictDoAction(c);
            break;
         case phase::fate:
            fateDoAction(c);
            break;
         case phase::regroup:
            regroupDoAction(c);
            break;
         case phase::gameover:
            break;
         default:
            throw std::runtime_error("Invalid phase");
      }
   }
   catch(EndGameException &endgame)
   {
      if(stateIntfc->getPlayerTokens()->honorTokens == 0 || 
         stateIntfc->getOpponentTokens()->honorTokens == 25)
      {
         turnMgr->declareLoser();
         std::cout << stateIntfc->getPlayerName() << " losses game (honor)" << std::endl;
      }
      else if(stateIntfc->getOpponentTokens()->honorTokens == 0 || 
         stateIntfc->getPlayerTokens()->honorTokens == 25)
      {
         turnMgr->declareWinner();
         std::cout << stateIntfc->getPlayerName() << " wins game (honor)" << std::endl;
      }
      else
      {
         // assuming province broke and winner was doing the conflict
         state->winner = state->currentConflict;
         if(state->currentConflict == state->currentAction)
         {
            turnMgr->declareWinner();
            std::cout << stateIntfc->getPlayerName() << " wins game (conquest)" << std::endl;
         }
         else
         {
            turnMgr->declareLoser();
            std::cout << stateIntfc->getPlayerName() << " losses game (conquest)" << std::endl;
         }
      }
      state->currentPhase = phase::gameover;
   }
}

void phaseManager::regroupDoAction(choice c)
{
   switch(state->currentSubPhase)
   {
      case subphase::choose_discard:
         doRegroupDiscard(c);
         break;
      default:
         throw std::runtime_error("Invalid substate");
   }
}

void phaseManager::doRegroupDiscard(choice c)
{
   RingManager rings(stateIntfc, cardMgr);
   tokenManager tokens(stateIntfc->getPlayerTokens(), stateIntfc->getPlayerName());

   if(c.getType() == choicetype::card)
   {
      dynastyMgr->discardProvinceCard(stateIntfc->getPlayerCards(), c.getCard());
   }
   else if((c.getType() == choicetype::pass) || 
      (c.getType() == choicetype::none))
   {
      std::string name = stateIntfc->getPlayerName();
      dynastyMgr->fillProvinces(stateIntfc->getPlayerCards(), &tokens, name);
      std::cout << name << " ending regroup phase" << std::endl;
      if(turnMgr->ActionAndTurnDiffer())
      {
         // unclaim each ring
         rings.unclaimRings();

         // pass first player token
         turnMgr->passFirstPlayer();

         // end regroup
         doDynastyEntry();
      }
      else
      {
         turnMgr->swapAction();
      }
   }
   else
   {
      throw std::runtime_error("Not a conflict type choice!");
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

void phaseManager::conflictDoAction(choice c)
{
   ConflictPhaseManager conflictPhase(stateIntfc, cardMgr);

   switch(state->currentSubPhase)
   {
      case subphase::choose_attackers:
         conflictPhase.doChooseAttackers(c);
         break;
      case subphase::choose_conflicttype:
         conflictPhase.doChooseConflictType(c);
         break;
      case subphase::choose_ring:
         conflictPhase.doChooseRing(c);
         break;
      case subphase::choose_province:
         conflictPhase.doChooseProvince(c);
         break;
      case subphase::choose_defenders:
         conflictPhase.doChooseDefenders(c);
         break;
      case subphase::choose_favor:
         conflictPhase.doChooseFavor(c);
         break;
      default:
         throw std::runtime_error("Invalid substate");
   }
}

void phaseManager::fateDoAction(choice c)
{
   switch(state->currentSubPhase)
   {
      case subphase::choose_discard:
         doChooseFateDiscard(c);
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
      provinceMgr->chooseStronghold(stateIntfc->getPlayerCards(), c.getCard());
      std::string name = stateIntfc->getPlayerName();
      std::cout << name
         << " chose " << c.getCard()->data->name 
         << " for a stronghold" << std::endl;
      if(turnMgr->ActionAndTurnDiffer())
      {
         tokenManager tokens(stateIntfc->getPlayerTokens(), stateIntfc->getPlayerName());
         tokenManager oppTokens(stateIntfc->getOpponentTokens(), stateIntfc->getOpponentName());
         dynastyMgr->fillProvinces(stateIntfc->getPlayerCards(), &tokens, stateIntfc->getPlayerName());
         dynastyMgr->fillProvinces(stateIntfc->getOpponentCards(), &oppTokens, stateIntfc->getOpponentName());
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
   tokenManager tokens(stateIntfc->getPlayerTokens(), stateIntfc->getPlayerName());
   tokenManager opponentTokens(stateIntfc->getOpponentTokens(), stateIntfc->getOpponentName());
   conflictCardManager conflictMgr(stateIntfc, cardMgr);

   if(c.getType() == choicetype::bid)
   {
      tokens.setHonorDial(c.getNumber());

      if(turnMgr->ActionAndTurnDiffer())
      {
         int mydial = tokens.getHonorDial();
         int hisdial = opponentTokens.getHonorDial(); 
         if( mydial > hisdial)
         {
            opponentTokens.gainHonor(mydial-hisdial);
            tokens.loseHonor(mydial-hisdial);
         }
         else if(hisdial > mydial)
         {
            opponentTokens.loseHonor(hisdial-mydial);
            tokens.gainHonor(hisdial-mydial);
         }
         if(state->currentPhase != phase::gameover)
         {
            conflictMgr.drawCards(mydial, stateIntfc->getPlayerCards(), &tokens, stateIntfc->getPlayerName());
            conflictMgr.drawCards(hisdial, stateIntfc->getOpponentCards(), &opponentTokens, stateIntfc->getOpponentName());

            goToConflictPhase();

            turnMgr->setActionToCurrentTurn();
         }
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
   MulliganManager mulligan(stateIntfc->getPlayerCards(), stateIntfc->getPlayerName(), cardMgr);
   conflictCardManager conflictMgr(stateIntfc, cardMgr);

   if(c.getType() == choicetype::card)
   {
      mulligan.chooseDynastyMulligan(c.getCard());
   }
   else if(c.getType() == choicetype::pass)
   {
      mulligan.performDynastyMulligan();
      tokenManager tokens(stateIntfc->getPlayerTokens(), stateIntfc->getPlayerName());
      dynastyMgr->fillProvinces(stateIntfc->getPlayerCards(), &tokens, stateIntfc->getPlayerName());
      if(turnMgr->ActionAndTurnDiffer())
      {
         tokenManager tokens(stateIntfc->getPlayerTokens(), stateIntfc->getPlayerName());
         tokenManager opponentTokens(stateIntfc->getOpponentTokens(), stateIntfc->getOpponentName());
         conflictMgr.drawCards(STARTING_NUM_CONFLICT_CARDS, stateIntfc->getPlayerCards(), &tokens, stateIntfc->getPlayerName());
         conflictMgr.drawCards(STARTING_NUM_CONFLICT_CARDS, stateIntfc->getOpponentCards(), &opponentTokens, stateIntfc->getOpponentName());

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
   tokenManager tokens(stateIntfc->getPlayerTokens(), stateIntfc->getPlayerName());
   tokenManager opponentTokens(stateIntfc->getOpponentTokens(), stateIntfc->getOpponentName());
   MulliganManager mulligan(stateIntfc->getPlayerCards(), stateIntfc->getPlayerName(), cardMgr);
   conflictCardManager conflictMgr(stateIntfc, cardMgr);

   if(c.getType() == choicetype::card)
   {
      mulligan.chooseConflictMulligan(c.getCard());
   }
   else if(c.getType() == choicetype::pass)
   {
      mulligan.performConflictMulligan();
      conflictMgr.drawCards(STARTING_NUM_CONFLICT_CARDS-conflictMgr.getNumCards(stateIntfc->getPlayerCards()),stateIntfc->getPlayerCards(), &tokens, stateIntfc->getPlayerName());
      
      ImperialFavorManager imperialFavor(stateIntfc, cardMgr);
      RingManager rings(stateIntfc, cardMgr);
      if(turnMgr->ActionAndTurnDiffer())
      {
         // set starting honor
         int startingHonor = provinceMgr->getStartingHonor(stateIntfc->getPlayerCards());
         tokens.setHonor(startingHonor);
         startingHonor = provinceMgr->getStartingHonor(stateIntfc->getOpponentCards());
         opponentTokens.setHonor(startingHonor);

         // set rings unclaimed
         rings.initialize();

         //initialize favor to nobody
         imperialFavor.initializeFavor();

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
   tokenManager tokens(stateIntfc->getPlayerTokens(), stateIntfc->getPlayerName());
   tokenManager opponentTokens(stateIntfc->getOpponentTokens(), stateIntfc->getOpponentName());

   std::cout << "Beginning Dynasty Phase" << std::endl;
   state->currentPhase = phase::dynasty;
   goToProvincePlay();

   // gain fate
   // TODO: read fate value from stronghold card
   tokens.gainFate(STRONGHOLD_FATE);
   dynastyMgr->flipAllDynastyFaceup(stateIntfc->getPlayerCards(), stateIntfc->getPlayerName());
   opponentTokens.gainFate(STRONGHOLD_FATE);
   dynastyMgr->flipAllDynastyFaceup(stateIntfc->getOpponentCards(), stateIntfc->getOpponentName());
   turnMgr->resetPassed();

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
   tokenManager tokens(stateIntfc->getPlayerTokens(), stateIntfc->getPlayerName());

   if(c.getType() == choicetype::card)
   {
      dynastyMgr->chooseCharacterToPlay(stateIntfc->getPlayerCards(), c.getCard());
      goToAdditionalFate();
   }
   else if(c.getType() == choicetype::pass)
   {
      // opponent has not passed
      if(!turnMgr->opponentHasPassed())
      {
         std::string name = stateIntfc->getPlayerName();
         std::cout << name << " passed first" << std::endl;
         tokens.gainFate(1);
         turnMgr->passAction();
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
   tokenManager tokens(stateIntfc->getPlayerTokens(), stateIntfc->getPlayerName());

   if(c.getType() == choicetype::fate)
   {
      int extraFate = c.getNumber();
      dynastyMgr->playCharacter(stateIntfc->getPlayerCards(), stateIntfc->getPlayerName(), extraFate);
      int pendingCharacterCost = dynastyMgr->getPendingCharCost(stateIntfc->getPlayerCards());
      tokens.loseFate(pendingCharacterCost + extraFate);
      tokenManager tokens(stateIntfc->getPlayerTokens(), stateIntfc->getPlayerName());
      dynastyMgr->fillProvinces(stateIntfc->getPlayerCards(), &tokens, stateIntfc->getPlayerName());

      goToProvincePlay();
      if(!turnMgr->opponentHasPassed())
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
   decision d;
   switch(state->currentPhase)
   {
      case phase::pregame:
         return getPreGameDecision();
      case phase::dynasty:
         return getDynastyDecision();
      case phase::draw:
         return getDrawDecision();
      case phase::conflict:
         return getConflictDecision();
      case phase::fate:
         return getFateDecision();
      case phase::regroup:
         return getRegroupDecision();
      case phase::gameover:
         return d;
      default:
         throw std::runtime_error("Invalid state");
   }
}

decision phaseManager::getRegroupDecision()
{
   switch(state->currentSubPhase)
   {
      case subphase::choose_discard:
         return getRegroupDiscardDecision();
      default:
         throw std::runtime_error("Invalid substate");
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

decision phaseManager::getConflictDecision()
{
   ConflictPhaseManager conflictPhase(stateIntfc, cardMgr);
   switch(state->currentSubPhase)
   {
      case subphase::choose_attackers:
         return conflictPhase.getAttackersDecision();
      case subphase::choose_conflicttype:
         return conflictPhase.getConflictTypeDecision();
      case subphase::choose_ring:
         return conflictPhase.getRingDecision();
      case subphase::choose_province:
         return conflictPhase.getAttackProvinceDecision();
      case subphase::choose_defenders:
         return conflictPhase.getDefendersDecision();
      case subphase::choose_favor:
         return conflictPhase.getFavorDecision();
      default:
         throw std::runtime_error("Invalid substate");
   }
}

decision phaseManager::getFateDecision()
{
   switch(state->currentSubPhase)
   {
      case subphase::choose_discard:
         return getFateDiscardDecision();
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
   std::list<choice> list = provinceMgr->getStrongholdChoices(stateIntfc->getPlayerCards());
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
   MulliganManager mulligan(stateIntfc->getPlayerCards(), stateIntfc->getPlayerName(), cardMgr);
   auto list = mulligan.getDynastyMulliganChoices();
   list.push_back(choice("Pass", choicetype::pass));
   decision d("Choose a card to mulligan", list);
   return d;
}

decision phaseManager::getConflictMulliganDecision()
{
   MulliganManager mulligan(stateIntfc->getPlayerCards(), stateIntfc->getPlayerName(), cardMgr);
   auto list = mulligan.getConflictMulliganChoices();
   list.push_back(choice("Pass", choicetype::pass));
   decision d("Choose a card to mulligan", list);
   return d;
}

decision phaseManager::getProvincePlayDecision()
{
   tokenManager tokens(stateIntfc->getPlayerTokens(), stateIntfc->getPlayerName());

   int currentFate = tokens.getFate();
   std::list<choice> list = dynastyMgr->getProvinceDynastyChoicesWithFateCost(stateIntfc->getPlayerCards(), dynastyCardStatus::faceup, currentFate); // all should be facedown
   list.push_back(choice("Pass", choicetype::pass));
   decision d("Choose a card to play", list);
   return d;
}

decision phaseManager::getAdditionalFateDecision()
{
   tokenManager tokens(stateIntfc->getPlayerTokens(), stateIntfc->getPlayerName());

   std::list<choice> list;
   int pendingCharacterCost = dynastyMgr->getPendingCharCost(stateIntfc->getPlayerCards());
   int fateAvailable = tokens.getFate() - pendingCharacterCost;
   if(fateAvailable < 0)
   {
      throw std::runtime_error("Not enough fate to play card");
   }
   for(int f=0;f<=fateAvailable;f++)
   {
      std::stringstream ss;
      ss << f;
      std::string fateStr;
      ss >> fateStr;
      choice c(fateStr+" fate", choicetype::fate);
      c.setNumber(f);
      list.push_back(c);
   }
   decision d("Choose an amount of fate to add:", list);
   return d;
}


decision phaseManager::getFateDiscardDecision()
{
   std::list<choice> list = dynastyMgr->getCharactersWithNoFate(stateIntfc->getPlayerCards());
   decision d("Choose character to discard", list);
   return d;
}

void phaseManager::doChooseFateDiscard(choice c)
{
   RingManager rings(stateIntfc, cardMgr);
   if(c.getType() == choicetype::card)
   {
      dynastyMgr->discardCharacter(stateIntfc->getPlayerCards(), c.getCard());
   }
   else if(c.getType() == choicetype::none)
   {
      if(turnMgr->ActionAndTurnDiffer())
      {
         dynastyMgr->removeFateFromCharacters(stateIntfc->getPlayerCards());
         dynastyMgr->removeFateFromCharacters(stateIntfc->getOpponentCards());
         rings.putFateOnRings();
         dynastyMgr->readyAllCharacters(stateIntfc->getPlayerCards());
         dynastyMgr->readyAllCharacters(stateIntfc->getOpponentCards());
         state->currentPhase = phase::regroup;
         state->currentSubPhase = subphase::choose_discard;
         turnMgr->setActionToCurrentTurn();
      }
      else
      {
         turnMgr->swapAction();
      }
   }
   else
   {
      throw std::runtime_error("Invalid choice");
   }
}

decision phaseManager::getRegroupDiscardDecision()
{
   std::list<choice> list = dynastyMgr->getProvinceDynastyChoices(stateIntfc->getPlayerCards(), dynastyCardStatus::faceup);
   list.push_back(choice("Pass", choicetype::pass));
   decision d("Choose a province card to discard", list);
   return d;
}
