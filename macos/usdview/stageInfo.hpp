#ifndef stageInfo_h
#define stageInfo_h

#include <stdio.h>

#if __cplusplus
extern "C" {
#endif // __cplusplus
    
    const char** _getPrimInfo(const char* sPath, int* numPrims);
    
    double _getStartTimeCode(const char* sPath);
    
    double _getEndTimeCode(const char* sPath);
    
#if __cplusplus
}
#endif // __cplusplus

#endif // stageInfo_h
