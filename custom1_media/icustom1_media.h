#ifndef __ICUSTOM1_MEDIA_H__
#define __ICUSTOM1_MEDIA_H__

#include "ibase_media.h"


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
    
#ifdef CUSTOM1_MEDIA_EXPORTS
#ifndef ICUSTOM1_MEDIA_API
#define ICUSTOM1_MEDIA_API   __declspec( dllexport )
#endif
#elif defined(CUSTOM1_MEDIA_IMPORTS) // xxx.dll
#ifndef ICUSTOM1_MEDIA_API
#define ICUSTOM1_MEDIA_API   __declspec( dllimport )
#endif
#else
// #pragma message(".lib")
// #pragma comment(lib, ".lib")
#ifndef ICUSTOM1_MEDIA_API
#define ICUSTOM1_MEDIA_API
#endif
#endif
    
ICUSTOM1_MEDIA_API IBaseMedia *CreateICustom1Media();
ICUSTOM1_MEDIA_API void DeleteICustom1Media(IBaseMedia *in);
    
#ifdef __cplusplus
}
#endif // __cplusplus

#endif	// __ICUSTOM1_MEDIA_H__