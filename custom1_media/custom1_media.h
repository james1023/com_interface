#ifndef __CUSTOM1_MEDIA__
#define __CUSTOM1_MEDIA__

#include <stdio.h>
#include <iostream>
#include "icustom1_media.h"
#include "base_media.h"


class Custom1Media: public BaseMedia
{
protected:
    
    
public:
    explicit Custom1Media();
    virtual ~Custom1Media();
    
    virtual void Release();
    virtual BASE_ERR QueryInterface(__b_in REFBOMID riid, __b_out void **ppv);
    
    virtual void GetState() {
        std::cout << "CCustom1Media::GetState=" << state << std::endl;
    }
};

#endif /* defined(__CUSTOM1_MEDIA__) */
