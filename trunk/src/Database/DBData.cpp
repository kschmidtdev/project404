#include "DBData.h"

DBData::DBData(const int uniqueID, const string & name)
: DBBase(uniqueID), mName(name)
{
}

DBData::~DBData()
{
}
