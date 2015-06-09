#ifndef __ICUSTOM_MEDIA_H__
#define __ICUSTOM_MEDIA_H__

#include "ibase_media.h"


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
    
#ifdef CUSTOM_MEDIA_EXPORTS
#ifndef ICUSTOM_MEDIA_API
#define ICUSTOM_MEDIA_API   __declspec( dllexport )
#endif
#elif defined(CUSTOM_MEDIA_IMPORTS) // xxx.dll
#ifndef ICUSTOM_MEDIA_API
#define ICUSTOM_MEDIA_API   __declspec( dllimport )
#endif
#else
// #pragma message(".lib")
// #pragma comment(lib, ".lib")
#ifndef ICUSTOM_MEDIA_API
#define ICUSTOM_MEDIA_API
#endif
#endif
    
ICUSTOM_MEDIA_API IBaseMedia *CreateICustomMedia();
ICUSTOM_MEDIA_API void DeleteICustomMedia(IBaseMedia *in);
    
#ifdef __cplusplus
}
#endif // __cplusplus

#endif	// __ICUSTOM_MEDIA_H__