#include "base_media.h"


void BaseMedia::Release()
{
    delete this;
}

BASE_ERR BaseMedia::QueryInterface(REFBOMID riid, void **ppv)
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

BaseMedia::BaseMedia()
{}

BaseMedia::~BaseMedia()
{}