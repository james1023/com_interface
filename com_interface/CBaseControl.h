#ifndef __CBASE_CONTROL__
#define __CBASE_CONTROL__

#include <stdio.h>
#include <iostream>

#include "IBaseControl.h"


class CBaseControl: public IBaseControl
{
protected:
    int state;
    
public:
    explicit CBaseControl();
    virtual ~CBaseControl();
    
    virtual void Release();
    virtual BASE_ERR QueryInterface(__b_in REFBOMID riid, __b_out void **ppv);
    
    virtual bool Run() {
        std::cout << "CBaseControl::Run. \n";
        state = 1;
        
        return true;
    }
    
    virtual bool Pause() {
        std::cout << "CBaseControl::Run. \n";
        state++;
        
        return true;
    }
    
    virtual bool Stop() {
        std::cout << "CBaseControl::Run. \n";
        state++;
        
        return true;
    }
};

#endif /* defined(__CBASE_CONTROL__) */
