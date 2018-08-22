#include "stageInfo.hpp"

#include "pxr/pxr.h"
#include "pxr/usd/usd/prim.h"
#include "pxr/usd/usd/stage.h"
#include "pxr/usd/usd/prim.h"
#include "pxr/usd/usd/primRange.h"
#include "pxr/usd/sdf/declareHandles.h"

auto _allocStrBuffer = [](auto s) {
    return (const char**) malloc(s*sizeof(const char*));
};

auto _reallocAndCopy = [](auto& oldStream, auto size) {
    const char** newStream = _allocStrBuffer(2*size);
    const char** oldStreamHandle = oldStream;
    for (size_t i = 0; i < size; ++i) {
        newStream[i] = oldStream[i];
    }
    
    oldStream = newStream;
    return oldStreamHandle;
};

auto _getDepth = [](auto prim) {
    long depth = 0;
    
    while ((prim = prim.GetParent())) {
        depth += 1;
    }
    
    return depth;
};

// Exposes a stream of prim information in the form of
// [char*] name [char*] path [char*] type [int] depth
const char** _getPrimInfo(const char* sPath, int* numPrims)
{
    auto stage = pxr::UsdStage::Open(sPath);
    const size_t numElementsPerStream = 4;
    size_t numElementsInStreamTotal = 32;
    const char** stream = _allocStrBuffer(numElementsInStreamTotal);
    size_t currentStreamSize = 0;
    
    for (const auto& child : stage->Traverse()) {
        // We may have outgrown our original buffer estimate, if necessary
        // we will reallocate and copy our elements over, doubling the size.
        if (currentStreamSize < numElementsPerStream) {
            auto oldStream = _reallocAndCopy(stream, numElementsInStreamTotal);
            numElementsInStreamTotal *= 2;
            free(oldStream);
        }
            
        stream[currentStreamSize++] = child.GetName().GetText();
        stream[currentStreamSize++] = child.GetPath().GetText();
        stream[currentStreamSize++] = child.GetTypeName().GetText();
        stream[currentStreamSize++] = (const char*) _getDepth(child);
        
        *numPrims += 1;
    }
    return stream;
}

double _getStartTimeCode(const char* sPath)
{
    auto stage = pxr::UsdStage::Open(sPath);
    return stage->GetStartTimeCode();
}

double _getEndTimeCode(const char* sPath)
{
    auto stage = pxr::UsdStage::Open(sPath);
    return stage->GetEndTimeCode();
}
