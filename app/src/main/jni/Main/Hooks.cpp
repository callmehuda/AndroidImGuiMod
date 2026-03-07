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

MYHOOK(void, set_curSnowNum, void *__this, int value, void *method) {

    if (snowAurora) {
        value = 6; // aktif saat checkbox dicentang
    }

    origset_curSnowNum(__this, value, method);
}

MYHOOK(bool, IsPreparePhase, void *method) {
    if (isprepare) return true;
    return origIsPreparePhase(method);
}

// <== Initializing ==>
void Setup_Hooks() {
    
    BNM::Class auroraClass("Battle", "MCLogicSpecialMonsterAurora");
    BNM::MethodBase snowAuroraMethod = auroraClass.GetMethod("set_curSnowNum", 1);
    BNM::MethodBase snowAuroraoverrideMethod = snowAuroraMethod.GetOverride();
    uintptr_t snowAuroraMethodaddr = snowAuroraoverrideMethod.GetInfo()
        ? snowAuroraoverrideMethod.GetOffset()
        : snowAuroraMethod.GetOffset();


    BNM::Class MCLogicUtils("Battle", "MCLogicUtils");
    BNM::MethodBase isPreparePhaseMethod = MCLogicUtils.GetMethod("IsPreparePhase", 0);
    uintptr_t prepareaddr = isPreparePhaseMethod.GetOffset();
    
    
    
    BasicHook(
        snowAuroraMethodaddr, 
        (void *)myset_curSnowNum, 
        (void **)&origset_curSnowNum
    );
    BasicHook(
        prepareaddr, 
        (void *)myIsPreparePhase, 
        (void **)&origIsPreparePhase
    );    
}
