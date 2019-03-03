#pragma once
#include "hitable.h"

class CHitableList : public CHitable
{
public:
	CHitableList() {}
	CHitableList(CHitable** vList, int vSize) : m_List(vList), m_ListSize(vSize) {}

	virtual bool hitV(const CRay& vRay, float vMinT, float vMaxT, SHitRecord& voRec) const override;

private:
	CHitable** m_List;
	int m_ListSize;
};