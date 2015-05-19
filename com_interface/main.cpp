#include <iostream>
#include "CBaseMedia.h"


int main(int argc, const char * argv[])
{
    CBaseMedia media;
    IBaseControl *control;
    
    media.QueryInterface(BOID_IBASE_CONTROL, (void **)&control);
    
    control->Run();
    control->Pause();
    control->Stop();
    
    media.GetState();
    
    return 0;
}
