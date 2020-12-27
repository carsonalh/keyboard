#include <unity.h>
#include <unity_fixture.h>

#include <keyboard.h>
#include <keyboard_mock.h>

#include <stdlib.h>
#include <stdbool.h>

TEST_GROUP(KeyboardMock);

TEST_SETUP(KeyboardMock)
{
    KeyboardMock_Create();
}

TEST_TEAR_DOWN(KeyboardMock)
{
    KeyboardMock_Destroy();
}

TEST(KeyboardMock, CanCreate)
{
    Keyboard_Create();
}

TEST(KeyboardMock, CanVerify)
{
    Keyboard_Create();
    KeyboardMock_Verify();
}

TEST(KeyboardMock, CanVerifyCreateWasCalled)
{
    KeyboardMock_ExpectCreate();
    Keyboard_Create();
    bool result = KeyboardMock_Verify();
    TEST_ASSERT(result);
}

TEST(KeyboardMock, CanVerifyCreateWasNotCalled)
{
    KeyboardMock_ExpectCreate();
    bool result = KeyboardMock_Verify();
    TEST_ASSERT_FALSE(result);
}

TEST(KeyboardMock, GetAndSetKeyStateYieldsSameValue)
{
    srand(1);
    for (int i = 0; i < MAX_KEYS; ++i)
    {
        bool expected = rand() % 2;
        KEnum state = expected ? KEY_UP : KEY_DOWN;
        KeyboardMock_SetKey(i, state);
        bool actual = Keyboard_IsKeyDown(i);
        TEST_ASSERT(expected == actual);
    }
}

TEST(KeyboardMock, CanVerifyIsKeyDownNegative)
{
    KeyboardMock_ExpectIsKeyDown(3);
    bool result = KeyboardMock_Verify();
    TEST_ASSERT_FALSE(result);
}

TEST(KeyboardMock, CanVerifyIsKeyDownPositive)
{
    KeyboardMock_ExpectIsKeyDown(3);
    (void)Keyboard_IsKeyDown(3);
    bool result = KeyboardMock_Verify();
    TEST_ASSERT(result);
}

TEST(KeyboardMock, CanVerifyIsKeyDownDifferentKeys)
{
    KeyboardMock_ExpectIsKeyDown(3);
    (void)Keyboard_IsKeyDown(5);
    bool result = KeyboardMock_Verify();
    TEST_ASSERT_FALSE(result);
}

TEST(KeyboardMock, CanVerifyIsKeyDownMultipleTimes)
{
    KeyboardMock_ExpectIsKeyDown(3);
    KeyboardMock_ExpectIsKeyDown(12);
    KeyboardMock_ExpectIsKeyDown(1);
    (void)Keyboard_IsKeyDown(3);
    bool result = KeyboardMock_Verify();
    TEST_ASSERT(result);
}

TEST_GROUP_RUNNER(KeyboardMock)
{
    RUN_TEST_CASE(KeyboardMock, CanCreate);
    RUN_TEST_CASE(KeyboardMock, CanVerify);
    RUN_TEST_CASE(KeyboardMock, CanVerifyCreateWasCalled);
    RUN_TEST_CASE(KeyboardMock, CanVerifyCreateWasNotCalled);
    RUN_TEST_CASE(KeyboardMock, GetAndSetKeyStateYieldsSameValue);
    RUN_TEST_CASE(KeyboardMock, CanVerifyIsKeyDownPositive);
    RUN_TEST_CASE(KeyboardMock, CanVerifyIsKeyDownNegative);
    RUN_TEST_CASE(KeyboardMock, CanVerifyIsKeyDownDifferentKeys);
    RUN_TEST_CASE(KeyboardMock, CanVerifyIsKeyDownMultipleTimes);
}

void runAllTests(void)
{
    RUN_TEST_GROUP(KeyboardMock);
}

int main(int argc, char const ** argv)
{ 
    return UnityMain(argc, argv, runAllTests);
}

