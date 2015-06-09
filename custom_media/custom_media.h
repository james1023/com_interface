#ifndef __CUSTOM_MEDIA__
#define __CUSTOM_MEDIA__

#include <stdio.h>
#include <iostream>
#include "icustom_media.h"
#include "base_media.h"


class CustomMedia: public BaseMedia
{
protected:
    
    
public:
    explicit CustomMedia();
    virtual ~CustomMedia();
    
    virtual void Release();
    virtual BASE_ERR QueryInterface(__b_in REFBOMID riid, __b_out void **ppv);
    
    virtual void GetState() {
        std::cout << "CCustomMedia::GetState=" << state << std::endl;
    }
};

#endif /* defined(__CUSTOM_MEDIA__) */
