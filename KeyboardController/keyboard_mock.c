#include "keyboard.h"
#include "keyboard_mock.h"

#include <string.h>

typedef struct Expectation
{
    bool create;
    int key;
    struct Expectation * next;
} expectation_t;

static expectation_t expectation;
static expectation_t actual;

void KeyboardMock_Create(void)
{
    memset(&expectation, 0, sizeof expectation);
    memset(&actual, 0, sizeof actual);
}

void KeyboardMock_Destroy(void)
{
}

void KeyboardMock_ExpectCreate(void)
{
    expectation.create = true;
}

void KeyboardMock_ExpectIsKeyDown(int key)
{
    expectation.key = key;
}

void Keyboard_Create(void)
{
    actual.create = true;
}

bool keys[MAX_KEYS];

void KeyboardMock_SetKey(int key, KEnum up_or_down)
{
    keys[key] = (up_or_down == KEY_UP) ? true : false;
}

bool Keyboard_IsKeyDown(int key)
{
    actual.key = key;
    return keys[key];
}

bool KeyboardMock_Verify(void)
{
    return 0 == memcmp(
            &expectation,
            &actual,
            sizeof expectation
    );
}

