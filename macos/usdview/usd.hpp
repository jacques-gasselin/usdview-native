#ifndef USD_BINDING_HEADER_HPP
#define USD_BINDING_HEADER_HPP

#include <stdio.h>

#if __cplusplus
extern "C" {
#endif // __cplusplus

const char **usdffi_getPrimInfo(void *stagePtr, int *numPrims);

double usdffi_getStartTimeCode(void *stagePtr);

double usdffi_getEndTimeCode(void *stagePtr);

double usdffi_getTimeCodesPerSecond(void *stagePtr);

const char *usdffi_getInterpolationType(void *stagePtr);

void *usdffi_openStage(const char *sPath);

void usdffi_reloadStage(void *stagePtr);

void usdffi_setDefaultPrim(void *stagePtr, const char *primPath);

const char *usdffi_getDefaultPrim(void *stagePtr);

#if __cplusplus
}
#endif // __cplusplus

#endif // USD_BINDING_HEADER_HPP
