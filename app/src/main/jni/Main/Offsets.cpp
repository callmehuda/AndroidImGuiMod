#include <Offsets.h>

void ofst::Init() {

    uintptr_t prepareaddr = isPreparePhase.GetOffset();

    patch_IsPreparePhase = MemoryPatch::createWithHex(
        prepareaddr,
        "20 00 80 52"   // MOV W0, #1
        " C0 03 5F D6"  // RET
    );


  inited = true;
}
