#include "keyboard.h"
#include "keyboard_mock.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Expectation
{
    KMEnum type;
    bool met;
    union
    {
        int key;
    };
    struct Expectation * next;
} Expectation;

static Expectation * expectations = NULL;
static KEnum keys[MAX_KEYS];
static KMEnum last_error_code = 0;

static Expectation * Expectation_Create(void)
{
    Expectation * created = calloc(1, sizeof *created);

    if (expectations == NULL)
        expectations = created;
    else
    {
        Expectation * node = expectations;
        while (node->next)
            node = node->next;
        node->next = created;
    }

    return created;
}

void KeyboardMock_Create(void)
{
    expectations = NULL;
}

void KeyboardMock_Destroy(void)
{
    Expectation * node = expectations;

    while (node)
    {
        Expectation * next = node->next;
        free(node);
        node = next;
    }

    expectations = NULL;

    for (int i = 0; i < MAX_KEYS; ++i)
        keys[i] = KEY_UP;

    last_error_code = 0;
}

void KeyboardMock_ExpectCreate(void)
{
    Expectation * e = Expectation_Create();
    e->type = KM_CREATE;
}

void KeyboardMock_ExpectDestroy(void)
{
    Expectation * e = Expectation_Create();
    e->type = KM_DESTROY;
}

void KeyboardMock_ExpectGetKeyState(int key)
{
    Expectation * e = Expectation_Create();
    e->type = KM_GET_KEY_STATE;
    e->key = key;
}

void Keyboard_Create(void)
{
    for (
            Expectation * node = expectations;
            node;
            node = node->next
    )
    {
        if (node->type == KM_CREATE)
        {
            node->met = true;
            return;
        }
    }
}

void Keyboard_Destroy(void)
{
    for (
            Expectation * node = expectations;
            node;
            node = node->next
    )
    {
        if (node->type == KM_DESTROY)
        {
            node->met = true;
            return;
        }
    }
}

void KeyboardMock_SetKey(int key, KEnum state)
{
    keys[key] = state;
}

KEnum Keyboard_GetKeyState(int key)
{
    Expectation * node = expectations;
    while (node)
    {
        if (node->type == KM_GET_KEY_STATE && node->key == key)
        {
            node->met = true;
            return keys[key];
        }
        node = node->next;
    }
    return keys[key];
}

bool KeyboardMock_Verify(void)
{
    Expectation * node = expectations;
    while (node)
    {
        if (!node->met)
        {
            last_error_code = node->type;
            return false;
        }
        node = node->next;
    }
    return true;
}

KMEnum KeyboardMock_GetLastErrorCode(void)
{
    /* return KM_CREATE | KM_EXPECTATION_NOT_MET; */
    return last_error_code;
}

