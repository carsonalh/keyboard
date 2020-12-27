#include "keyboard.h"
#include "keyboard_mock.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    EX_CREATE,
    EX_KEY_DOWN,
} ExEnum;

typedef struct Expectation
{
    ExEnum type;
    bool met;
    union
    {
        int key;
    };
    struct Expectation * next;
} Expectation;

static Expectation * expectations = NULL;

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
}

void KeyboardMock_ExpectCreate(void)
{
    if (expectations == NULL)
    {
        expectations = calloc(1, sizeof *expectations);
        expectations->type = EX_CREATE;
    }
    else
    {
        Expectation * node = expectations;
        while (node->next)
            node = node->next;
        Expectation * last = calloc(1, sizeof *node);
        node->next = last;
        last->type = EX_CREATE;
    }
}

void KeyboardMock_ExpectIsKeyDown(int key)
{
    if (expectations == NULL)
    {
        expectations = calloc(1, sizeof *expectations);
        expectations->type = EX_KEY_DOWN;
        expectations->key = key;
    }
    else
    {
        Expectation * node = expectations;
        while (node->next)
            node = node->next;
        Expectation * last = calloc(1, sizeof *node);
        node->next = last;
        last->type = EX_KEY_DOWN;
        last->key = key;
    }
}

void Keyboard_Create(void)
{
    for (
            Expectation * node = expectations;
            node;
            node = node->next
    )
    {
        if (node->type == EX_CREATE)
        {
            node->met = true;
            return;
        }
    }
}

static bool keys[MAX_KEYS];

void KeyboardMock_SetKey(int key, KEnum state)
{
    keys[key] = (state == KEY_UP) ? true : false;
}

KEnum Keyboard_GetKeyState(int key)
{
    Expectation * node = expectations;
    while (node)
    {
        if (node->type == EX_KEY_DOWN && node->key == key)
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
            return false;
        node = node->next;
    }
    return true;
}

