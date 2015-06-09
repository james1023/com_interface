#include "custom_media.h"


void CustomMedia::Release()
{
    delete this;
}

IBaseMedia *CreateICustomMedia()
{
    return static_cast<IBaseMedia *> (new CustomMedia);
}

void DeleteICustomMedia(IBaseMedia *in)
{
    in->Release();
}

BASE_ERR CustomMedia::QueryInterface(REFBOMID riid, void **ppv)
{
    BASE_ERR err = BASE_OK;
    if ((err=BaseMedia::QueryInterface(riid, ppv)) == BASE_OK) {
        return err;
    }
    else  {
        return BASE_FAILED;
    }
}

CustomMedia::CustomMedia()
{}

CustomMedia::~CustomMedia()
{}
