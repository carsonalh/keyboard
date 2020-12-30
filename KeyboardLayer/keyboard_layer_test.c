#include <unity.h>
#include <unity_fixture.h>

#include <keyboard_layer.h>

#include <keyboard.h>
#include <keyboard_mock.h>

TEST_GROUP(KeyboardLayer);

TEST_SETUP(KeyboardLayer)
{
    KeyboardMock_Create();
}

TEST_TEAR_DOWN(KeyboardLayer)
{
    KeyboardMock_Destroy();
}

TEST(KeyboardLayer, SetsUpKeyboardOnCreate)
{
    KeyboardMock_ExpectCreate();
    KeyboardLayer_Create();
    TEST_ASSERT_TRUE(KeyboardMock_Verify());
}

TEST(KeyboardLayer, DestroysKeyboardOnDestroy)
{
    KeyboardMock_ExpectDestroy();
    KeyboardLayer_Destroy();
    TEST_ASSERT_TRUE(KeyboardMock_Verify());
}

TEST_GROUP_RUNNER(KeyboardLayer)
{
    RUN_TEST_CASE(KeyboardLayer, SetsUpKeyboardOnCreate);
    RUN_TEST_CASE(KeyboardLayer, DestroysKeyboardOnDestroy);
}

void runAllTests(void)
{
    RUN_TEST_GROUP(KeyboardLayer);
}

int main(int argc, char const ** argv)
{
    return UnityMain(argc, argv, runAllTests);
}

