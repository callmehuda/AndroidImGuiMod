#ifndef HORONI_HOOKS_H
#define HORONI_HOOKS_H

#define MYHOOK(ret, func, ...) \
    ret (*orig##func)(__VA_ARGS__); \
    ret my##func(__VA_ARGS__)

void Setup_Hooks();

#endif // HORONI_HOOKS_H
