#ifndef __BASE_CONTROL__
#define __BASE_CONTROL__

#include <stdio.h>
#include <iostream>

#include "ibase_control.h"


class BaseControl: public IBaseControl
{
protected:
    int state;
    
public:
    explicit BaseControl();
    virtual ~BaseControl();
    
    virtual void Release();
    virtual BASE_ERR QueryInterface(__b_in REFBOMID riid, __b_out void **ppv);
    
    virtual bool Run() {
        std::cout << "CBaseControl::Run. \n";
        state = 1;
        
        return true;
    }
    
    virtual bool Pause() {
        std::cout << "CBaseControl::Pause. \n";
        state++;
        
        return true;
    }
    
    virtual bool Stop() {
        std::cout << "CBaseControl::Stop. \n";
        state++;
        
        return true;
    }
};

#endif /* defined(__BASE_CONTROL__) */
