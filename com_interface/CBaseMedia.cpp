#include "CBaseMedia.h"

void CBaseMedia::Release()
{
    delete this;
}

BASE_ERR CBaseMedia::QueryInterface(REFBOMID riid, void **ppv)
{
    if (IsEqualBOMID(riid, BOID_IBASE_MEDIA)) {
        *ppv = (IBaseMedia *)this;
        return BASE_OK;
    }
    else if (IsEqualBOMID(riid, BOID_IBASE_CONTROL)) {
        *ppv = (IBaseControl *)this;
        return BASE_OK;
    }
    else  {
        return BASE_FAILED;
    }
}

CBaseMedia::CBaseMedia()
{}

CBaseMedia::~CBaseMedia()
{}