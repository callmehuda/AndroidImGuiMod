#ifndef HORONI_OFFSETS_H
#define HORONI_OFFSETS_H

//! BNM::IL2CPP::Il2CppObject if class inherits System.Object or nothing
//! BNM::UnityEngine::Object if class inherits UnityEngine.ScriptableObject
//! BNM::UnityEngine::MonoBehaviour if class inherits UnityEngine.MonoBehaviour

/*
// BNM::Method<ret type>
// BNM::Field<type>
        BNM::Class Display_c = BNM::Class("UnityEngine", "Display");
        BNM::Method<int> Display::getWidth = Display_c.GetMethod("get_systemWidth", 0);
*/
#include "BNM/Loading.hpp"
#include "BNM/Class.hpp"
#include "BNM/MethodBase.hpp"
#include "KittyMemory/MemoryPatch.hpp"


// Offsets, Fields, Classes, Properties...
namespace ofst {
    inline bool inited = false;
    
    MemoryPatch patch_IsPreparePhase;

    BNM::Class auroraClass("Battle", "MCLogicSpecialMonsterAurora");
    BNM::MethodBase snowAuroraMethod = auroraClass.GetMethod("set_curSnowNum", 1);
    BNM::MethodBase snowAuroraoverrideMethod = snowAuroraMethod.GetOverride();
    uintptr_t snowAuroraMethodaddr = snowAuroraoverrideMethod.GetInfo()
        ? overrideMethod.GetOffset()
        : method.GetOffset();

    BNM::Class MCLogicUtils("Battle", "MCLogicUtils");
    BNM::MethodBase isPreparePhase = MCLogicUtils.GetMethod("IsPreparePhase", 0);

    
    
    void Init();

}

#endif // HORONI_OFFSETS_H