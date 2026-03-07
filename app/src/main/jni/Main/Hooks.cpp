#include <Hooks.h>
#include <Vars.h>
#include <Offset.h>

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

// <== Initializing ==>
void Setup_Hooks() {
    BasicHook(
        ofst::snowAuroraMethodaddr.GetOffset(), 
        (void *)myget_curSnowNum, 
        (void **)&origget_curSnowNum
    );
}
