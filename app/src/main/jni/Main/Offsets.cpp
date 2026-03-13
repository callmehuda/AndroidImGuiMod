#include <Offsets.h>

void ofst::Init() {

    inited = true;
}

void ofst::startPreparePhasefunc() {
    auto assembly = UnityResolve::Get("Assembly-CSharp.dll");
    auto startPreparePhaseMethod = assembly->Get("MCLogicBattleManager")->Get<UnityResolve::Method>("OnStartPreparePhase");
    startPreparePhaseMethod->Invoke<void>();
}
