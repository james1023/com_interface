#ifndef __IBASE_CONTROL_H__
#define __IBASE_CONTROL_H__

#include "ibase.h"


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus 

static BOMID BOID_IBASE_CONTROL = {0x89c91234, 0x91f6, 0x4a64, 0x82, 0x9c, 0x74, 0x73, 0x33, 0x30, 0xcb, 0x00};

class IBaseControl: public IBase
{
public:
	virtual bool Run() = 0;
	virtual bool Pause() = 0;
	virtual bool Stop() = 0;
};

#ifdef __cplusplus
}
#endif // __cplusplus

#endif	// __IBASE_CONTROL_H__
