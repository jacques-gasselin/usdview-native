#ifndef USD_BINDING_HEADER_HPP
#define USD_BINDING_HEADER_HPP

#include <stdio.h>

#if __cplusplus
extern "C" {
#endif // __cplusplus

const char **_getPrimInfo(void *stagePtr, int *numPrims);

double _getStartTimeCode(void *stagePtr);

double _getEndTimeCode(void *stagePtr);

double _getTimeCodesPerSecond(void *stagePtr);

const char *_getInterpolationType(void *stagePtr);

void *_openStage(const char *sPath);

void _reloadStage(void *stagePtr);

void _setDefaultPrim(void *stagePtr, const char *primPath);

const char *_getDefaultPrim(void *stagePtr);

#if __cplusplus
}
#endif // __cplusplus

#endif // USD_BINDING_HEADER_HPP
