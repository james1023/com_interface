
#include <iostream>
#include "ibase_media.h"
#include "ibase_control.h"
#include "plugin_dll.h"


int main(int argc, const char * argv[])
{
    std::cout << "[" << __LINE__ << "] test plugin com dll." << std::endl;
    
    boost::shared_ptr<IBaseMedia> imedia;
    IBaseControl *icontrol = NULL;
    
    PluginDll plugin;
    plugin.AttachDll();
    
    imedia = boost::dynamic_pointer_cast<IBaseMedia> (plugin.NewIBaseMedia("custom"));
    imedia->GetState();
    
    imedia->QueryInterface(BOID_IBASE_CONTROL, (void **)&icontrol);
    if (icontrol) {
        icontrol->Run();
        icontrol->Pause();
        icontrol->Stop();
    }
                                                           
    plugin.DeattachDll();
    
    return 0;
}
