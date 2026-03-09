#include <Offsets.h>

void ofst::Init() {
    auto* assembly = UnityResolve::Get("Assembly-CSharp.dll");
    auto* startPreparePhaseMethod = assembly->Get("MCLogicBattleManager")->Get<UnityResolve::Method>("OnStartPreparePhase");
    
    inited = true;
}
