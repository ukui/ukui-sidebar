#include "clipBoardInternalSignal.h"
static ClipBoardInternalSignal* Global_internal_signal = nullptr;
void ClipBoardInternalSignal::initInternalSignal()
{
    ClipBoardInternalSignal::getGlobalInternalSignal();
    return;
}

ClipBoardInternalSignal* ClipBoardInternalSignal::getGlobalInternalSignal()
{
    if (Global_internal_signal == nullptr) {
        Global_internal_signal = new ClipBoardInternalSignal();
    }
    return Global_internal_signal;
}
