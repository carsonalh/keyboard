#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    MAX_KEYS = 256,
    KEY_UP = 0, KEY_DOWN = 1,
} KEnum;

void Keyboard_Create(void);
bool Keyboard_IsKeyDown(int key);

#ifdef __cplusplus
}
#endif

#endif // _KEYBOARD_H_

