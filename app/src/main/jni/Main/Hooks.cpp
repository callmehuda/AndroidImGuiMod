#include <Hooks.h>
#include <Vars.h>


// <== Hooks ==>    

/*void (*Main$$_Draw)(BNM::IL2CPP::Il2CppObject *instance, void *gameTime);
void Main$$Draw(BNM::IL2CPP::Il2CppObject *instance, void *gameTime)
{
    Main$$_Draw(instance, gameTime);
    ofs::Main::spriteBatch.Get();
}*/

MYHOOK(int, get_curSnowNum, void* self) {
    if (self != nullptr && snowAurora){
            return 6;
    }
    
    return origget_curSnowNum(self);
}

// <== Initializing ==>
void Setup_Hooks() {
    auto auroraClass = BNM::Class("Battle", "MCLogicSpecialMonsterAurora", BNM::Image("Assembly-CSharp"));
    BNM::Method<int> snowAuroraMethod = auroraClass.GetMethod("get_curSnowNum", 0);
    BasicHook(
        snowAuroraMethod.GetOffset(), 
        (void *)myget_curSnowNum, 
        (void **)&origget_curSnowNum
    );
}
