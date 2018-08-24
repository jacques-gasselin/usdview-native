#ifndef stageInfo_h
#define stageInfo_h

#include <stdio.h>

#if __cplusplus
extern "C" {
#endif // __cplusplus
    
    const char** _getPrimInfo(void* stagePtr, int* numPrims);
    
    double _getStartTimeCode(void* stagePtr);
    
    double _getEndTimeCode(void* stagePtr);
    
    double _getTimeCodesPerSecond(void* stagePtr);
    
    const char* _getInterpolationType(void* stagePtr);
    
    void* _openStage(const char* sPath);
    
    void _reloadStage(void* stagePtr);
    
#if __cplusplus
}
#endif // __cplusplus

#endif // stageInfo_h
