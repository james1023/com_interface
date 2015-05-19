#include "CBaseControl.h"

void CBaseControl::Release()
{
    delete this;
}

BASE_ERR CBaseControl::QueryInterface(REFBOMID riid, void **ppv)
{
    if (IsEqualBOMID(riid, BOID_IBASE_CONTROL)) {
        *ppv = (IBaseControl *)this;
        return BASE_OK;
    }
    else  {
        return BASE_FAILED;
    }
}

CBaseControl::CBaseControl():
state(0)
{}

CBaseControl::~CBaseControl()
{}