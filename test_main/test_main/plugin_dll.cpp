#include "plugin_dll.h"

#include <dlfcn.h>
#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


PluginDll::PluginDll()
{}

PluginDll::~PluginDll()
{}

void PluginDll::AttachDll()
{
    boost::filesystem::path full_path(boost::filesystem::current_path());
    std::string dir_path = full_path.string();
    dir_path += "/media/";
    
    std::stringstream ss, ss1;
    boost::property_tree::ptree xml_head, xml_child;

    vm_dir_peek((vm_char *)dir_path.c_str(), NULL, dllpath_list_);
    
    for (_listPeekFile::iterator iter=dllpath_list_.begin(); iter != dllpath_list_.end(); iter++) {
        if (NULL == strstr((*iter).c_str(), ".xml"))
            continue;
        
        try {
            boost::property_tree::xml_parser::read_xml((*iter).c_str(), xml_head);
        }
        catch(boost::exception const &ex) {
            std::cout << "[" << __LINE__ << "] PluginDll:AttachDll error." << std::endl;
            return;
        }
        
        if (xml_head.empty()) {
            std::cout << "[" << __LINE__ << "] PluginDll:AttachDll error." << std::endl;
            return;
        }
        
        xml_child = xml_head.get_child("DllInfo");
        if (xml_child.empty()) {
            std::cout << "[" << __LINE__ << "] PluginDll:AttachDll error." << std::endl;
            return;
        }
        
        boost::shared_ptr<MediaIfDllInfo> media_if_dll_info = boost::shared_ptr<MediaIfDllInfo> (new MediaIfDllInfo());
        media_if_dll_info->plug_name = xml_child.get<string>("PlugName");
        media_if_dll_info->file_name = xml_child.get<string>("FileName");
        media_if_dll_info->create_if_name = xml_child.get<string>("CreateInterface");
        media_if_dll_info->delete_if_name = xml_child.get<string>("DeleteInterface");
        
#if defined(_WIN32)
        media_if_dll_info->dll_hinst = LoadLibrary(media_if_dll_info->file_name.c_str());
#else
        media_if_dll_info->dll_hinst = dlopen(media_if_dll_info->file_name.c_str(), RTLD_LAZY);
#endif // #if defined(_WIN32)
        
        if (NULL == media_if_dll_info->dll_hinst) {
            std::cout << "[" << __LINE__ << "] PluginDll:AttachDll error." << std::endl;
            continue;
        }
        
        pfCreateIBaseMediaIF create_if = NULL;
        pfDeleteIBaseMediaIF delete_if = NULL;
#if defined(_WIN32)
        create_if = (pfCreateIBaseMediaIF)(GetProcAddress((HMODULE)media_if_dll_info->dll_hinst, media_if_dll_info->create_if_name.c_str()));
        delete_if = (pfDeleteIBaseMediaIF)(GetProcAddress((HMODULE)media_if_dll_info->dll_hinst, media_if_dll_info->delete_if_name.c_str()));
#else
        create_if = (pfCreateIBaseMediaIF)dlsym(media_if_dll_info->dll_hinst, media_if_dll_info->create_if_name.c_str());
        delete_if = (pfDeleteIBaseMediaIF)dlsym(media_if_dll_info->dll_hinst, media_if_dll_info->delete_if_name.c_str());
#endif // #if defined(_WIN32)
        
        if (create_if) {
            media_if_dll_info->create_if = create_if;
        }
        else {
            std::cout << "[" << __LINE__ << "] PluginDll:AttachDll error." << std::endl;
            continue;
        }
        
        if (delete_if) {
            media_if_dll_info->delete_if = delete_if;
        }
        else {
            std::cout << "[" << __LINE__ << "] PluginDll:AttachDll error." << std::endl;
            continue;
        }
        
        media_if_dll_info_maps_[media_if_dll_info->plug_name] = media_if_dll_info;
    }
}

void PluginDll::DeattachDll()
{
    for (MediaIfDllInfoMaps::iterator iter=media_if_dll_info_maps_.begin(); iter != media_if_dll_info_maps_.end(); iter++) {
        if (iter->second->dll_hinst) {
#if defined(_WIN32)
            FreeLibrary((HMODULE)iter->second->dll_hinst);
#else
            dlclose(iter->second->dll_hinst);
#endif
            iter->second->dll_hinst = NULL;
        }
    }
    
    media_if_dll_info_maps_.clear();
}

boost::shared_ptr<IBase> PluginDll::NewIBaseMedia(const char *plugin_name)
{
    boost::shared_ptr<IBase> tmp;
    
    MediaIfDllInfoMaps::iterator get_iter;
    if ((get_iter=media_if_dll_info_maps_.find(plugin_name)) != media_if_dll_info_maps_.end()) {
        boost::shared_ptr<IBaseMedia> new_ibase = boost::shared_ptr<IBaseMedia> (get_iter->second->create_if(), get_iter->second->delete_if);
        tmp = boost::static_pointer_cast<IBase> (new_ibase);
    }
    
    return tmp;
}