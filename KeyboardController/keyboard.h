#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    MAX_KEYS = 256,

    /**
     * In this context, "up" means that the switch is not turned off, and
     * therefore false. The analogy to be used here is that of a physical
     * keyboard, where its "up" state is not being pressed, and the opposite
     * for the "down" state.
    */
    KEY_UP = 0, KEY_DOWN = 1,
} KEnum;

void Keyboard_Create(void);
void Keyboard_Destroy(void);
KEnum Keyboard_GetKeyState(int key);

#ifdef __cplusplus
}
#endif

#endif // _KEYBOARD_H_

