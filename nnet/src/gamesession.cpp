#include "gamesession.h"
#include "gamegraph.h"

using namespace l5r;

GameSession::GameSession(GameGraph *g) : session(g->getGraph())
{
   this->graph = g;
}

GameSession::~GameSession()
{
}

TfSession *GameSession::getSession()
{
   return &session;
}

