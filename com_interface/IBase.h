#ifndef IBASE_H
#define IBASE_H

#include <memory.h>


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus 

#define __b_in
#define __b_in_opt
#define __b_out
#define __b_out_opt
#define __b_inout
#define __b_inout_opt
    
typedef enum _BASE_ERR
{
    BASE_OK														= 1,
    BASE_FAILED                                                 = 0,
} BASE_ERR;
    
typedef struct _BOMID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
} BOMID;

#define REFBOMID const BOMID &

inline int IsEqualBOMID(REFBOMID rguid1, REFBOMID rguid2)
{
	return !memcmp(&rguid1, &rguid2, sizeof(BOMID));
}

class IBase
{
public:
    virtual void Release() = 0;
	virtual BASE_ERR QueryInterface(__b_in REFBOMID riid, __b_out void **ppv) = 0;
};


#ifdef __cplusplus
}
#endif // __cplusplus

#endif	// IBASE_H
