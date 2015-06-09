#include "custom1_media.h"


IBaseMedia *CreateICustom1Media()
{
    return static_cast<IBaseMedia *> (new Custom1Media);
}

void DeleteICustom1Media(IBaseMedia *in)
{
    in->Release();
}

void Custom1Media::Release()
{
    delete this;
}

BASE_ERR Custom1Media::QueryInterface(REFBOMID riid, void **ppv)
{
    BASE_ERR err = BASE_OK;
    if ((err=BaseMedia::QueryInterface(riid, ppv)) == BASE_OK) {
        return err;
    }
    else  {
        return BASE_FAILED;
    }
}

Custom1Media::Custom1Media()
{}

Custom1Media::~Custom1Media()
{}
