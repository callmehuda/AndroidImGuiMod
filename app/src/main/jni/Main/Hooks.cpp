#include <Hooks.h>
#include <Vars.h>

#include "BNM/UserSettings/GlobalSettings.hpp"
#include "BNM/Class.hpp"
#include "BNM/Image.hpp"
#include "BNM/Method.hpp"

// <== Hooks ==>    

/*void (*Main$$_Draw)(BNM::IL2CPP::Il2CppObject *instance, void *gameTime);
void Main$$Draw(BNM::IL2CPP::Il2CppObject *instance, void *gameTime)
{
    Main$$_Draw(instance, gameTime);
    ofs::Main::spriteBatch.Get();
}*/

MYHOOK(void, set_curSnowNum, void *instance, int value) {

    if (snowAurora) {
        value = 6; // aktif saat checkbox dicentang
    }

    origset_curSnowNum(instance, value);
}

MYHOOK(bool, IsPreparePhase) {
    bool result = origIsPreparePhase();

    if (forceIsPrepare) return true;

    return result; // kalau forceIsPrepare false, return nilai asli
}

// <== Initializing ==>
void Setup_Hooks() {
    
    auto auroraClass = BNM::Class("Battle", "MCLogicSpecialMonsterAurora");
    BNM::Method<void> snowAuroraMethod = auroraClass.GetMethod("set_curSnowNum", 1);

    auto MCLogicUtils = BNM::Class("Battle", "MCLogicUtils");
    BNM::Method<bool> isPreparePhaseMethod = MCLogicUtils.GetMethod("IsPreparePhase", 0);
    
    
    BNM::VirtualHook(
        auroraClass,
        snowAuroraMethod,
        myset_curSnowNum,
        origset_curSnowNum
    );
    BNM::BasicHook(
        isPreparePhaseMethod, 
        myIsPreparePhase, 
        origIsPreparePhase
    );    
}
