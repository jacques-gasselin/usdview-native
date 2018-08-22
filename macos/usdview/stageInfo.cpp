#include "stageInfo.hpp"

#include "pxr/pxr.h"
#include "pxr/usd/usd/prim.h"
#include "pxr/usd/usd/stage.h"
#include "pxr/usd/usd/prim.h"
#include "pxr/usd/usd/primRange.h"
#include "pxr/usd/sdf/declareHandles.h"

#include "boost/get_pointer.hpp"

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

// Exposes a stream of prim information in the form of
// [char*] path [char*] type
const char** _getPrimInfo(void* stagePtr, int* numPrims)
{
    auto stage = (pxr::UsdStage*)stagePtr;
    const size_t numElementsPerStream = 2;
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
    
        stream[currentStreamSize++] = child.GetPath().GetText();
        stream[currentStreamSize++] = child.GetTypeName().GetText();
        
        *numPrims += 1;
    }
    return stream;
}

double _getStartTimeCode(void* stagePtr)
{
    return ((pxr::UsdStage*)stagePtr)->GetStartTimeCode();
}

double _getEndTimeCode(void* stagePtr)
{
    return ((pxr::UsdStage*)stagePtr)->GetEndTimeCode();
}

const char* _getInterpolationType(void* stagePtr)
{
    auto interp = ((pxr::UsdStage*) stagePtr)->GetInterpolationType();
    return interp == 0 ? "Held" : "Linear";
}

double _getTimeCodesPerSecond(void* stagePtr)
{
    return ((pxr::UsdStage*)stagePtr)->GetTimeCodesPerSecond();
}

void* _openStage(const char* sPath)
{
    static auto stage = pxr::UsdStage::Open(sPath);
    return boost::get_pointer(stage);
}
