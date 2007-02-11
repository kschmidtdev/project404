#include "DBVector2D.h"

DBVector2D::DBVector2D(const int uniqueID, const string & name, const int* vector2DData)
: DBData(uniqueID, name)
{

    for (int i=0; i<2; i++) mVector2DData[i] = vector2DData[i];

}

DBVector2D::~DBVector2D()
{
}
