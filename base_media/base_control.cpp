#include "base_control.h"

void BaseControl::Release()
{
    delete this;
}

BASE_ERR BaseControl::QueryInterface(REFBOMID riid, void **ppv)
{
    if (IsEqualBOMID(riid, BOID_IBASE_CONTROL)) {
        *ppv = (IBaseControl *)this;
        return BASE_OK;
    }
    else  {
        return BASE_FAILED;
    }
}

BaseControl::BaseControl():
state(0)
{}

BaseControl::~BaseControl()
{}