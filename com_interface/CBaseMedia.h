#ifndef __CBASE_MEDIA__
#define __CBASE_MEDIA__

#include <stdio.h>
#include <iostream>
#include "IBaseMedia.h"
#include "CBaseControl.h"


class CBaseMedia: public IBaseMedia, public CBaseControl
{
protected:
    
    
public:
    explicit CBaseMedia();
    virtual ~CBaseMedia();
    
    virtual void Release();
    virtual BASE_ERR QueryInterface(__b_in REFBOMID riid, __b_out void **ppv);
    
    virtual void GetState() {
        std::cout << "CBaseMedia::GetState=" << state << std::endl;
    }
};

#endif /* defined(__CBASE_MEDIA__) */
