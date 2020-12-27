#ifndef _KEYBOARD_MOCK_H_
#define _KEYBOARD_MOCK_H_

#include <keyboard.h>

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    KM_CREATE,
    KM_DESTROY,
    KM_GET_KEY_STATE,
} KMEnum;

void KeyboardMock_Create(void);
void KeyboardMock_Destroy(void);

void KeyboardMock_ExpectCreate(void);
void KeyboardMock_ExpectDestroy(void);
void KeyboardMock_ExpectGetKeyState(int key);
bool KeyboardMock_Verify(void);
/**
 * Check the upper byte of this value returned to see the function that has
 * caused the error, and then see the lower byte for a list of all the things
 * that went wrong by checking it with the appropriate bitmask.
 * @see KMEnum
 */
KMEnum KeyboardMock_GetLastErrorCode(void);

void KeyboardMock_SetKey(int key, KEnum up_or_down);

#ifdef __cplusplus
}
#endif

#endif // _KEYBOARD_MOCK_H_

