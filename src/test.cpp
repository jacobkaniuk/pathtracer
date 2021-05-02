#include <iostream>
#include <gtest/gtest.h>

TEST(MyTest, MyTestCase){
    bool t1 = true;
    bool t2 = true;
    EXPECT_EQ(t1, t2);
}

int main(){
    MyTest_MyTestCase_Test();
    return 0;
}