#ifndef __IBASE_MEDIA_H__
#define __IBASE_MEDIA_H__

#include "IBase.h"


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus 

static BOMID BOID_IBASE_MEDIA = {0x22c34321, 0x9898, 0xaabc, 0x80, 0x44, 0x22, 0x84, 0x23, 0x77, 0xbb, 0x51};

class IBaseMedia: public IBase
{
public:
	virtual void GetState() = 0;
};

typedef IBaseMedia *(*pfCreateIBaseMediaIF)();
typedef void (*pfDeleteIBaseMediaIF)(IBaseMedia *in);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif	// __IBASE_MEDIA_H__
