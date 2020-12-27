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

TEST(KeyboardMock, ExpectCreateWhenCalled)
{
    KeyboardMock_ExpectCreate();
    Keyboard_Create();
    bool result = KeyboardMock_Verify();
    TEST_ASSERT_TRUE(result);
}

TEST(KeyboardMock, ExpectCreateWhenNotCalled)
{
    KeyboardMock_ExpectCreate();
    bool result = KeyboardMock_Verify();
    TEST_ASSERT_FALSE(result);
}

TEST(KeyboardMock, ExpectCreateMoreExpectationsThanCalls)
{
    KeyboardMock_ExpectCreate();
    KeyboardMock_ExpectCreate();
    Keyboard_Create();
    bool result = KeyboardMock_Verify();
    TEST_ASSERT_FALSE(result);
}

TEST(KeyboardMock, GetAndSetKeyStateYieldsSameValue)
{
    srand(1);
    for (int i = 0; i < MAX_KEYS; ++i)
    {
        bool boolean_seed = rand() % 2;
        KEnum expected = boolean_seed ? KEY_DOWN : KEY_UP;
        KeyboardMock_SetKey(i, expected);
        KEnum actual = Keyboard_GetKeyState(i);
        TEST_ASSERT_EQUAL_INT(expected, actual);
    }
}

TEST(KeyboardMock, GetKeyStateNegative)
{
    KeyboardMock_ExpectGetKeyState(3);
    bool result = KeyboardMock_Verify();
    TEST_ASSERT_FALSE(result);
}

TEST(KeyboardMock, GetKeyStatePositive)
{
    KeyboardMock_ExpectGetKeyState(3);
    (void)Keyboard_GetKeyState(3);
    bool result = KeyboardMock_Verify();
    TEST_ASSERT_TRUE(result);
}

TEST(KeyboardMock, GetKeyStateDifferentKeys)
{
    KeyboardMock_ExpectGetKeyState(3);
    (void)Keyboard_GetKeyState(5);
    bool result = KeyboardMock_Verify();
    TEST_ASSERT_FALSE(result);
}

TEST(KeyboardMock, GetKeyStateMorExpectationsThanAreMet)
{
    KeyboardMock_ExpectGetKeyState(3);
    KeyboardMock_ExpectGetKeyState(12);
    KeyboardMock_ExpectGetKeyState(1);
    (void)Keyboard_GetKeyState(3);
    bool result = KeyboardMock_Verify();
    TEST_ASSERT_FALSE(result);
}

TEST(KeyboardMock, ExpectDestroyPositive)
{
    KeyboardMock_ExpectDestroy();
    Keyboard_Destroy();
    bool result = KeyboardMock_Verify();
    TEST_ASSERT_TRUE(result);
}

TEST(KeyboardMock, ExpectDestroyNegative)
{
    KeyboardMock_ExpectDestroy();
    bool result = KeyboardMock_Verify();
    TEST_ASSERT_FALSE(result);
}

TEST(KeyboardMock, GetLastErrorCodeCanIdentifyCreate)
{
    KeyboardMock_ExpectCreate();
    (void)KeyboardMock_Verify();
    KMEnum error_code = KeyboardMock_GetLastErrorCode();
    TEST_ASSERT_EQUAL_HEX16(KM_CREATE, error_code);
}

TEST(KeyboardMock, GetLastErrorCodeCanIdentifyCreatePositiveReturnsZero)
{
    KeyboardMock_ExpectCreate();
    Keyboard_Create();
    (void)KeyboardMock_Verify();
    KMEnum error_code = KeyboardMock_GetLastErrorCode();
    TEST_ASSERT_EQUAL_HEX16(0, error_code);
}

TEST(KeyboardMock, GetLastErrorCodeCanIdentifyDestroy)
{
    KeyboardMock_ExpectDestroy();
    (void)KeyboardMock_Verify();
    KMEnum error_code = KeyboardMock_GetLastErrorCode();
    TEST_ASSERT_EQUAL_HEX16(KM_DESTROY, error_code);
}

TEST(KeyboardMock, GetLastErrorCodeCanIdentifyDestroyPositiveReturnsZero)
{
    KeyboardMock_ExpectDestroy();
    Keyboard_Destroy();
    (void)KeyboardMock_Verify();
    KMEnum error_code = KeyboardMock_GetLastErrorCode();
    TEST_ASSERT_EQUAL_HEX16(0, error_code);
}

TEST(KeyboardMock, GetLastErrorCodeCanIdentifyGetKeyState)
{
    KeyboardMock_ExpectGetKeyState(1);
    (void)KeyboardMock_Verify();
    KMEnum error_code = KeyboardMock_GetLastErrorCode();
    TEST_ASSERT_EQUAL_HEX16(KM_GET_KEY_STATE, error_code);
}

TEST(KeyboardMock, GetLastErrorCodeCanIdentifyGetKeyStatePositiveReturnsZero)
{
    KeyboardMock_ExpectGetKeyState(1);
    (void)Keyboard_GetKeyState(1);
    (void)KeyboardMock_Verify();
    KMEnum error_code = KeyboardMock_GetLastErrorCode();
    TEST_ASSERT_EQUAL_HEX16(0, error_code);
}

TEST_GROUP_RUNNER(KeyboardMock)
{
    RUN_TEST_CASE(KeyboardMock, CanCreate);
    RUN_TEST_CASE(KeyboardMock, CanVerify);
    RUN_TEST_CASE(KeyboardMock, ExpectCreateWhenCalled);
    RUN_TEST_CASE(KeyboardMock, ExpectCreateWhenNotCalled);
    RUN_TEST_CASE(KeyboardMock, ExpectCreateMoreExpectationsThanCalls);
    RUN_TEST_CASE(KeyboardMock, GetAndSetKeyStateYieldsSameValue);
    RUN_TEST_CASE(KeyboardMock, GetKeyStatePositive);
    RUN_TEST_CASE(KeyboardMock, GetKeyStateNegative);
    RUN_TEST_CASE(KeyboardMock, GetKeyStateDifferentKeys);
    RUN_TEST_CASE(KeyboardMock, GetKeyStateMorExpectationsThanAreMet);
    RUN_TEST_CASE(KeyboardMock, ExpectDestroyPositive);
    RUN_TEST_CASE(KeyboardMock, ExpectDestroyNegative);
    RUN_TEST_CASE(KeyboardMock, GetLastErrorCodeCanIdentifyCreate);
    RUN_TEST_CASE(KeyboardMock, GetLastErrorCodeCanIdentifyCreatePositiveReturnsZero);
    RUN_TEST_CASE(KeyboardMock, GetLastErrorCodeCanIdentifyDestroy);
    RUN_TEST_CASE(KeyboardMock, GetLastErrorCodeCanIdentifyGetKeyState);
    RUN_TEST_CASE(KeyboardMock, GetLastErrorCodeCanIdentifyCreatePositiveReturnsZero);
    RUN_TEST_CASE(KeyboardMock, GetLastErrorCodeCanIdentifyDestroyPositiveReturnsZero);
    RUN_TEST_CASE(KeyboardMock, GetLastErrorCodeCanIdentifyGetKeyStatePositiveReturnsZero);
}

void runAllTests(void)
{
    RUN_TEST_GROUP(KeyboardMock);
}

int main(int argc, char const ** argv)
{ 
    return UnityMain(argc, argv, runAllTests);
}

