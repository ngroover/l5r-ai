#include "phasemanager.h"
#include <iostream>
#include <sstream>
#include "gamestateintfc.h"
#include "tokenmanager.h"
#include "mulliganmanager.h"

using namespace l5r;

phaseManager::phaseManager(std::shared_ptr<gamestate> state,
            std::shared_ptr<dynastyCardManager> dynastyMgr,
            std::shared_ptr<conflictCardManager> conflictMgr,
            std::shared_ptr<provinceCardManager> provinceMgr,
            std::shared_ptr<turnManager> turnMgr,
            std::shared_ptr<cardDataManager> cardMgr,
            std::shared_ptr<GameStateIntfc> stateIntfc):
            state(state),dynastyMgr(dynastyMgr),
            conflictMgr(conflictMgr), provinceMgr(provinceMgr),
            turnMgr(turnMgr), cardMgr(cardMgr),
            conflictDataMgr(&state->conflict_state, cardMgr),
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
   state->currentSubPhase = subphase::choose_conflicttype;
}

void phaseManager::goToConflictPhase()
{
   state->currentPhase = phase::conflict;
   state->currentSubPhase = subphase::choose_attackers;
   for(int i=1;i<=2;i++)
   {
      playerstate &pState = state->getPlayerState(i);
      conflictDataMgr.initializeConflicts();
   }
   // first player gets to be in conflict first
   state->currentConflict = state->currentTurn;
}

void phaseManager::doAction(choice c)
{
   setupPointers();
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
   if(c.getType() == choicetype::card)
   {
      dynastyMgr->discardProvinceCard(stateIntfc->getPlayerCards(), c.getNumber());
   }
   else if((c.getType() == choicetype::pass) || 
      (c.getType() == choicetype::none))
   {
      //playerstate &pState = state->getPlayerState(relativePlayer::myself);
      std::string name = stateIntfc->getPlayerName();
      dynastyMgr->fillProvinces(stateIntfc->getPlayerCards(), name);
      std::cout << name << " ending regroup phase" << std::endl;
      if(turnMgr->ActionAndTurnDiffer())
      {
         // unclaim each ring
         conflictDataMgr.unclaimRings();

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

void phaseManager::setupPointers()
{
   conflictDataMgr.setAttacker(stateIntfc->getAttackerConflictState(), stateIntfc->getAttackerName());
   conflictDataMgr.setDefender(stateIntfc->getDefenderConflictState(), stateIntfc->getDefenderName());
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
   switch(state->currentSubPhase)
   {
      case subphase::choose_attackers:
         doChooseAttackers(c);
         break;
      case subphase::choose_conflicttype:
         doChooseConflictType(c);
         break;
      case subphase::choose_ring:
         doChooseRing(c);
         break;
      case subphase::choose_province:
         doChooseProvince(c);
         break;
      case subphase::choose_defenders:
         doChooseDefenders(c);
         break;
      case subphase::choose_favor:
         doChooseFavor(c);
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
      provinceMgr->chooseStronghold(stateIntfc->getPlayerCards(), c.getNumber());
      if(turnMgr->ActionAndTurnDiffer())
      {
            //playerstate &pState = state->getPlayerState(p);
         dynastyMgr->fillProvinces(stateIntfc->getPlayerCards(), stateIntfc->getPlayerName());
         dynastyMgr->fillProvinces(stateIntfc->getOpponentCards(), stateIntfc->getOpponentName());
         goToDynastyMulligan();
      }
      turnMgr->swapAction();
   }
   else
   {
      throw std::runtime_error("Not a card choice!");
   }
}

void phaseManager::doChooseFavor(choice c)
{
   if(c.getType() == choicetype::conflict_type)
   {
      conflictDataMgr.changeFavorType(c.getConflictType());
      state->currentPhase = phase::fate;
      state->currentSubPhase = subphase::choose_discard;
      turnMgr->setActionToCurrentTurn();
   }
   else
   {
      throw std::runtime_error("Not a conflict type choice!");
   }
}

void phaseManager::doChooseAttackers(choice c)
{
   if(c.getType() == choicetype::card)
   {
      // move character in
      playerstate &pState = state->getPlayerState(relativePlayer::myself);
      inplaycharacter ipc = dynastyMgr->removeCharacterFromHome(stateIntfc->getPlayerCards(), c.getNumber());
      conflictDataMgr.addAttackingCharacter(ipc);
   }
   else if(c.getType() == choicetype::pass)
   {
      if(conflictDataMgr.getAttackerNames().size() > 0)
      {
         goToChooseConflictType();
      }
      else
      {
         std::cout << "Pass conflict" << std::endl;
         conflictDataMgr.passConflict();

         processEndConflict(true);
      }
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
         if(tokens.getHonor() <= 0)
         {
         //   std::cout << name << " loses due to honor " << std::endl;
            turnMgr->declareLoser();
            state->currentPhase = phase::gameover;
         }
         if(opponentTokens.getHonor() >= 25)
         {
          //  std::cout << name << " wins by to honor" << std::endl;
            turnMgr->declareWinner();
            state->currentPhase = phase::gameover;
         }
         if(opponentTokens.getHonor() <= 0)
         {
         //   std::cout << oppname << " loses due to honor " << std::endl;
            turnMgr->declareWinner();
            state->currentPhase = phase::gameover;
         }
         if(tokens.getHonor() >= 25)
         {
          //  std::cout << oppname << " wins due to honor " << std::endl;
            turnMgr->declareLoser();
            state->currentPhase = phase::gameover;
         }
         if(state->currentPhase != phase::gameover)
         {
            conflictMgr->drawCards(mydial, stateIntfc->getPlayerCards(), stateIntfc->getPlayerName());
            conflictMgr->drawCards(hisdial, stateIntfc->getOpponentCards(), stateIntfc->getOpponentName());
            //TODO: draw phase action

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

   if(c.getType() == choicetype::card)
   {
      mulligan.chooseDynastyMulligan(c.getNumber());
   }
   else if(c.getType() == choicetype::pass)
   {
      mulligan.performDynastyMulligan();
      dynastyMgr->fillProvinces(stateIntfc->getPlayerCards(), stateIntfc->getPlayerName());
      if(turnMgr->ActionAndTurnDiffer())
      {
         conflictMgr->drawCards(STARTING_NUM_CONFLICT_CARDS, stateIntfc->getPlayerCards(), stateIntfc->getPlayerName());
         conflictMgr->drawCards(STARTING_NUM_CONFLICT_CARDS, stateIntfc->getOpponentCards(), stateIntfc->getOpponentName());

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

   if(c.getType() == choicetype::card)
   {
      mulligan.chooseConflictMulligan(c.getNumber());
   }
   else if(c.getType() == choicetype::pass)
   {
      mulligan.performConflictMulligan();
      conflictMgr->drawCards(STARTING_NUM_CONFLICT_CARDS-conflictMgr->getNumCards(stateIntfc->getPlayerCards()),stateIntfc->getPlayerCards(),stateIntfc->getPlayerName());
      
      if(turnMgr->ActionAndTurnDiffer())
      {
         // set starting honor
         int startingHonor = provinceMgr->getStartingHonor(stateIntfc->getPlayerCards());
         tokens.setHonor(startingHonor);
         startingHonor = provinceMgr->getStartingHonor(stateIntfc->getOpponentCards());
         opponentTokens.setHonor(startingHonor);

         // set rings unclaimed
         conflictDataMgr.initializeRings();

         //initialize favor to nobody
         conflictDataMgr.initializeFavor();

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
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   playerstate &oppState = state->getPlayerState(relativePlayer::opponent);
   tokens.gainFate(STRONGHOLD_FATE);
   dynastyMgr->flipAllDynastyFaceup(stateIntfc->getPlayerCards(), stateIntfc->getPlayerName());
   pState.passed = false;
   opponentTokens.gainFate(STRONGHOLD_FATE);
   dynastyMgr->flipAllDynastyFaceup(stateIntfc->getOpponentCards(), stateIntfc->getOpponentName());
   oppState.passed = false;

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
      dynastyMgr->chooseCharacterToPlay(stateIntfc->getPlayerCards(), c.getNumber());
      goToAdditionalFate();
   }
   else if(c.getType() == choicetype::pass)
   {
      playerstate &oppState = state->getPlayerState(relativePlayer::opponent);
      // opponent has not passed
      if(!oppState.passed)
      {
         playerstate &pState = state->getPlayerState(relativePlayer::myself);
         std::string name = stateIntfc->getPlayerName();
         std::cout << name << " passed first" << std::endl;
         tokens.gainFate(1);
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
   tokenManager tokens(stateIntfc->getPlayerTokens(), stateIntfc->getPlayerName());

   if(c.getType() == choicetype::fate)
   {
      playerstate &pState = state->getPlayerState(relativePlayer::myself);
      int extraFate = c.getNumber();
      dynastyMgr->playCharacter(stateIntfc->getPlayerCards(), stateIntfc->getPlayerName(), extraFate);
      int pendingCharacterCost = dynastyMgr->getPendingCharCost(stateIntfc->getPlayerCards());
      tokens.loseFate(pendingCharacterCost + extraFate);
      dynastyMgr->fillProvinces(stateIntfc->getPlayerCards(), stateIntfc->getPlayerName());

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
   switch(state->currentSubPhase)
   {
      case subphase::choose_attackers:
         return getAttackersDecision();
      case subphase::choose_conflicttype:
         return getConflictTypeDecision();
      case subphase::choose_ring:
         return getRingDecision();
      case subphase::choose_province:
         return getAttackProvinceDecision();
      case subphase::choose_defenders:
         return getDefendersDecision();
      case subphase::choose_favor:
         return getFavorDecision();
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

decision phaseManager::getAttackersDecision()
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   std::list<choice> list = dynastyMgr->getAttackerChoices(stateIntfc->getPlayerCards());
   list.push_back(choice("Pass", choicetype::pass));
   decision d("Choose an attacker", list);
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

   playerstate &pState = state->getPlayerState(relativePlayer::myself);
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

decision phaseManager::getConflictTypeDecision()
{
   std::list<choice> list = conflictDataMgr.getConflictChoices();
   decision d("Choose conflict type", list);
   return d;
}

void phaseManager::doChooseConflictType(choice c)
{
   if(c.getType() == choicetype::conflict_type)
   {
      conflictDataMgr.chooseConflictType(c.getConflictType());
      state->currentSubPhase = subphase::choose_ring;
   }
   else
   {
      throw std::runtime_error("Invalid choice");
   }
}

decision phaseManager::getRingDecision()
{
   std::list<choice> list = conflictDataMgr.getConflictRingChoices();
   decision d("Choose ring", list);
   return d;
}

void phaseManager::doChooseRing(choice c)
{
   if(c.getType() == choicetype::ring)
   {
      playerstate &pState = state->getPlayerState(relativePlayer::myself);
      conflictDataMgr.chooseConflictRing(c.getChosenRing());
      state->currentSubPhase = subphase::choose_province;
   }
   else
   {
      throw std::runtime_error("Invalid choice");
   }
}

decision phaseManager::getAttackProvinceDecision()
{
   std::list<choice> list = provinceMgr->getProvinceChoices(stateIntfc->getOpponentCards());
   decision d("Choose province", list);
   return d;
}

void phaseManager::doChooseProvince(choice c)
{
   if(c.getType() == choicetype::card)
   {
      std::string name = stateIntfc->getPlayerName();
      playerstate &pState = state->getPlayerState(relativePlayer::myself);
      // TODO: move to a conflict manager
      conflictDataMgr.chooseContestedProvince(c.getNumber());
      std::cout << name << " initiated a " << conflictDataMgr.getCurrentConflictTypeName()
         << " " << conflictDataMgr.getConflictRingName() << " "
         << "at " << conflictDataMgr.getContestedProvinceName() << " with" << std::endl;
      for(auto c: conflictDataMgr.getAttackerNames())
      {
         std::cout << " " << c << std::endl;
      }
      state->currentSubPhase = subphase::choose_defenders;
      turnMgr->swapAction();
   }
   else
   {
      throw std::runtime_error("Invalid choice");
   }
}

decision phaseManager::getDefendersDecision()
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   std::list<choice> list = dynastyMgr->getDefenderChoices(stateIntfc->getPlayerCards());
   list.push_back(choice("Pass", choicetype::pass));
   decision d("Choose defender", list);
   return d;
}

void phaseManager::doChooseDefenders(choice c)
{
   tokenManager tokens(stateIntfc->getPlayerTokens(), stateIntfc->getPlayerName());

   if(c.getType() == choicetype::card)
   {
      playerstate &pState = state->getPlayerState(relativePlayer::myself);
      inplaycharacter ipc = dynastyMgr->removeCharacterFromHome(stateIntfc->getPlayerCards(), c.getNumber());
      conflictDataMgr.addDefendingCharacter(ipc);
   }
   else if(c.getType() == choicetype::pass)
   {
      std::string name = stateIntfc->getPlayerName();
      std::cout << name << " Defending with" << std::endl;
      playerstate &pState = state->getPlayerState(relativePlayer::myself);
      playerstate &oppState = state->getPlayerState(relativePlayer::opponent);
      if(conflictDataMgr.getDefenderNames().size() > 0)
      {
         for(auto a:conflictDataMgr.getDefenderNames())
         {
            std::cout << " " << a << std::endl;
         }
      }
      else
      {
         std::cout << " Nobody" << std::endl;
      }

   
      conflictDataMgr.printConflictResult();
      if(conflictDataMgr.attackerWonConflict())
      {
         if(conflictDataMgr.wasUnopposed())
         {
            std::cout << "Unopposed conflict!" << std::endl;
            tokens.loseHonor(1);
            if(tokens.getHonor() <= 0)
            {
               std::cout << stateIntfc->getPlayerName() << " loses due to honor loss" << std::endl;
               turnMgr->declareLoser();
               state->currentPhase = phase::gameover;
            }
         }
         if(conflictDataMgr.provinceBroke())
         {
            int province = conflictDataMgr.getContestedProvince();
            provinceMgr->breakProvince(stateIntfc->getPlayerCards(), province);
            if(provinceMgr->getStrongholdProvince(stateIntfc->getPlayerCards()) == 
               province)
            {
               std::cout << stateIntfc->getOpponentName() << " won the game!" << std::endl;
               turnMgr->declareLoser();
               state->currentPhase = phase::gameover;
            }
         }
         conflictDataMgr.attackerClaimRing();
      }
      else if(conflictDataMgr.defenderWonConflict())
      {
         conflictDataMgr.defenderClaimRing();
      }
      else
      {
         conflictDataMgr.contestedRingUnclaimed();
      }
      if(state->currentPhase != phase::gameover)
      {
         conflictDataMgr.bowAttackers();
         std::list<inplaycharacter> attackers= conflictDataMgr.removeAllAttackingCharacters();
         dynastyMgr->sendCharactersHome(attackers, stateIntfc->getOpponentCards());


         conflictDataMgr.bowDefenders();
         std::list<inplaycharacter> defenders= conflictDataMgr.removeAllDefendingCharacters();
         dynastyMgr->sendCharactersHome(defenders, stateIntfc->getPlayerCards());

         conflictDataMgr.completeConflict();


         // process next conflict
         processEndConflict(false);
      }
   }
   else
   {
      throw std::runtime_error("Invalid choice");
   }
}

void phaseManager::processEndConflict(bool attackerActive)
{
   state->currentSubPhase = subphase::choose_attackers;
   //playerstate &pState = state->getPlayerState(relativePlayer::myself);
   if(conflictDataMgr.defenderHasConflictsLeft())
   {
      // defender gets the conflict
      if(attackerActive)
      {
         turnMgr->swapAction();
      }
      turnMgr->swapConflict();
   }
   else if(conflictDataMgr.attackerHasConflictsLeft())
   {
      // attacker gets another conflict
      // (probably won't ever happen with current card set)
      if(!attackerActive)
      {
         turnMgr->swapAction();
      }
   }
   else
   {
      // count imperial favor
      int attackerGlory,defenderGlory;
      if(attackerActive)
      {
         playerstate &pState = state->getPlayerState(relativePlayer::myself);
         playerstate &oppState = state->getPlayerState(relativePlayer::opponent);
         attackerGlory = dynastyMgr->countFavorGlory(stateIntfc->getPlayerCards());
         defenderGlory = dynastyMgr->countFavorGlory(stateIntfc->getOpponentCards());
      }
      else
      {
         playerstate &oppState = state->getPlayerState(relativePlayer::myself);
         playerstate &pState = state->getPlayerState(relativePlayer::opponent);
         attackerGlory = dynastyMgr->countFavorGlory(stateIntfc->getPlayerCards());
         defenderGlory = dynastyMgr->countFavorGlory(stateIntfc->getOpponentCards());
      }
      if(conflictDataMgr.attackerGainsFavor(attackerGlory, defenderGlory))
      {
         if(!attackerActive)
         {
            turnMgr->swapAction();
         }
         state->currentSubPhase = subphase::choose_favor;
      }
      else if(conflictDataMgr.defenderGainsFavor(attackerGlory, defenderGlory))
      {
         if(attackerActive)
         {
            turnMgr->swapAction();
         }
         state->currentSubPhase = subphase::choose_favor;
      }
      else
      {
         std::cout << "Imperial favor stays" << std::endl;
         state->currentPhase = phase::fate;
         state->currentSubPhase = subphase::choose_discard;
         turnMgr->setActionToCurrentTurn();
      }
   }
}

decision phaseManager::getFavorDecision()
{
   std::list<choice> list = conflictDataMgr.getFavorChoices();
   decision d("Choose favor type", list);
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
   if(c.getType() == choicetype::card)
   {
      dynastyMgr->discardCharacter(stateIntfc->getPlayerCards(), c.getNumber());
   }
   else if(c.getType() == choicetype::none)
   {
      if(turnMgr->ActionAndTurnDiffer())
      {
         dynastyMgr->removeFateFromCharacters(stateIntfc->getPlayerCards());
         dynastyMgr->removeFateFromCharacters(stateIntfc->getOpponentCards());
         conflictDataMgr.putFateOnRings();
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
