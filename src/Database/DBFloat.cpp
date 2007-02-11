#include "DBFloat.h"

DBFloat::DBFloat(const int uniqueID, const string & name, const float floatData)
: DBData(uniqueID, name), mFloatData(floatData)
{
}

DBFloat::~DBFloat()
{
}
