#include "DBColour.h"

DBColour::DBColour(const int uniqueID, const string & name, const int* colourData)
: DBData(uniqueID, name)
{

    for (int i=0; i<3; i++) mColourData[i] = colourData[i];

}

DBColour::~DBColour()
{
}

