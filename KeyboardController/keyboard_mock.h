#ifndef _KEYBOARD_MOCK_H_
#define _KEYBOARD_MOCK_H_

#include <keyboard.h>

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void KeyboardMock_Create(void);
void KeyboardMock_Destroy(void);

void KeyboardMock_ExpectCreate(void);
void KeyboardMock_ExpectIsKeyDown(int key);
bool KeyboardMock_Verify(void);

void KeyboardMock_SetKey(int key, KEnum up_or_down);

#ifdef __cplusplus
}
#endif

#endif // _KEYBOARD_MOCK_H_

