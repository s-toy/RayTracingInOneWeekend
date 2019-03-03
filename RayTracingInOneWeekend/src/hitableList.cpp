#include "hitableList.h"

//***************************************************************************************
//FUNCTION:
bool CHitableList::hitV(const CRay& vRay, float vMinT, float vMaxT, SHitRecord& voRec) const
{
	SHitRecord tempRec;
	bool hitAnything = false;
	double closestSoFar = vMaxT;
	for (int i = 0; i < m_ListSize; ++i)
	{
		if (m_List[i]->hitV(vRay, vMinT, closestSoFar, tempRec))
		{
			hitAnything = true;
			closestSoFar = tempRec.t;
			voRec = tempRec;
		}
	}

	return hitAnything;
}