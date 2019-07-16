#include "cardgenerator.h"

using namespace l5r;

cardgenerator::cardgenerator() : generator("./cards/data")
{
}

cardgenerator::~cardgenerator()
{
}


CardDataSharedPtr cardgenerator::generateCard(std::string c)
{
   return generator.generateCard(c);
}

CardSharedPtr cardgenerator::getCard(std::string id)
{
   return std::make_shared<Card>(generator.generateCard(id));
}
