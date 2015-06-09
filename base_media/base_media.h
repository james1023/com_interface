#ifndef __BASE_MEDIA__
#define __BASE_MEDIA__

#include <stdio.h>
#include <iostream>
#include "ibase_media.h"
#include "base_control.h"


class BaseMedia: public IBaseMedia, public BaseControl
{
protected:
    
    
public:
    explicit BaseMedia();
    virtual ~BaseMedia();
    
    virtual void Release();
    virtual BASE_ERR QueryInterface(__b_in REFBOMID riid, __b_out void **ppv);
    
    virtual void GetState() {
        std::cout << "CBaseMedia::GetState=" << state << std::endl;
    }
};

#endif /* defined(__BASE_MEDIA__) */
