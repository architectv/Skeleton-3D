#include <gtest.h>

#include "application.h"

TEST(ApplicationTest, adding)
{
    Application testApp;
    size_t oldSize = testApp.scenes.size();
    testApp.NewScene();
    size_t newSize = testApp.scenes.size();
    ASSERT_TRUE(oldSize == newSize - 1);
}