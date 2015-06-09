#ifndef __PLUGIN_DLL__
#define __PLUGIN_DLL__

#include <string>
#include <boost/shared_ptr.hpp>
#include "vm_file.h"
#include "ibase_media.h"

typedef struct _MediaIfDllInfo
{
    std::string plug_name;
    std::string file_name;
    std::string create_if_name;
    std::string delete_if_name;
    pfCreateIBaseMediaIF create_if;
    pfDeleteIBaseMediaIF delete_if;
    void *dll_hinst;
} MediaIfDllInfo;

typedef std::map<std::string, boost::shared_ptr<MediaIfDllInfo> > MediaIfDllInfoMaps;

class PluginDll
{
protected:
    _listPeekFile dllpath_list_;
    MediaIfDllInfoMaps media_if_dll_info_maps_;
    
public:
    explicit PluginDll();
    virtual ~PluginDll();
    
    void AttachDll();
    void DeattachDll();
    
    boost::shared_ptr<IBase> NewIBaseMedia(const char *plugin_name);
};

#endif /* defined(__PLUGIN_DLL__) */
