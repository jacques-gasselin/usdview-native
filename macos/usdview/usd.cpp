#include "usd.hpp"

#include "pxr/pxr.h"
#include "pxr/usd/sdf/declareHandles.h"
#include "pxr/usd/usd/prim.h"
#include "pxr/usd/usd/primRange.h"
#include "pxr/usd/usd/stage.h"

#include "boost/get_pointer.hpp"

auto allocStrBuffer = [](auto s) {
  return (const char **)malloc(s * sizeof(const char *));
};

auto reallocAndCopy = [](auto &oldStream, auto size) {
  const char **newStream = allocStrBuffer(2 * size);
  const char **oldStreamHandle = oldStream;
  for (size_t i = 0; i < size; ++i) {
    newStream[i] = oldStream[i];
  }

  oldStream = newStream;
  return oldStreamHandle;
};

// Exposes a stream of prim information in the form of
// [char*] path [char*] type
const char **usdffi_getPrimInfo(void *stagePtr, int *numPrims) {
  auto stage = (pxr::UsdStage *)stagePtr;
  const size_t numElementsPerStream = 2;
  size_t numElementsInStreamTotal = 32;
  const char **stream = allocStrBuffer(numElementsInStreamTotal);
  size_t currentStreamSize = 0;

  for (const auto &child : stage->Traverse()) {
    // We may have outgrown our original buffer estimate, if necessary
    // we will reallocate and copy our elements over, doubling the size.
    if (currentStreamSize < numElementsPerStream) {
      auto oldStream = reallocAndCopy(stream, numElementsInStreamTotal);
      numElementsInStreamTotal *= 2;
      free(oldStream);
    }

    stream[currentStreamSize++] = child.GetPath().GetText();
    stream[currentStreamSize++] = child.GetTypeName().GetText();

    *numPrims += 1;
  }
  return stream;
}

double usdffi_getStartTimeCode(void *stagePtr) {
  return ((pxr::UsdStage *)stagePtr)->GetStartTimeCode();
}

double usdffi_getEndTimeCode(void *stagePtr) {
  return ((pxr::UsdStage *)stagePtr)->GetEndTimeCode();
}

const char *usdffi_getInterpolationType(void *stagePtr) {
  auto interp = ((pxr::UsdStage *)stagePtr)->GetInterpolationType();
  return interp == 0 ? "Held" : "Linear";
}

double usdffi_getTimeCodesPerSecond(void *stagePtr) {
  return ((pxr::UsdStage *)stagePtr)->GetTimeCodesPerSecond();
}

void *usdffi_openStage(const char *sPath) {
  static auto stage = pxr::UsdStage::Open(sPath);
  return boost::get_pointer(stage);
}

void usdffi_reloadStage(void *stagePtr) {
  ((pxr::UsdStage *)stagePtr)->Reload();
}

void usdffi_setDefaultPrim(void *stagePtr, const char *primPath) {
  auto path = pxr::SdfPath(primPath);
  auto prim = ((pxr::UsdStage *)stagePtr)->GetPrimAtPath(path);
  ((pxr::UsdStage *)stagePtr)->SetDefaultPrim(prim);
}

const char *usdffi_getDefaultPrim(void *stagePtr) {
  return ((pxr::UsdStage *)stagePtr)->GetDefaultPrim().GetPath().GetText();
}
