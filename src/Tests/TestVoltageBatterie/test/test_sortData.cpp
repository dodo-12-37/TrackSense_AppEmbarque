#include <gtest/gtest.h>


void sortData(float data[], int size);

TEST(SortDataTest, SortsArrayInAscendingOrder)
{
    float data[] = {3.2, 1.5, 4.7, 2.1, 5.0};
    const int size = 5;
    sortData(data, size);
    EXPECT_FLOAT_EQ(data[0], 1.5);
    EXPECT_FLOAT_EQ(data[1], 2.1);
    EXPECT_FLOAT_EQ(data[2], 3.2);
    EXPECT_FLOAT_EQ(data[3], 4.7);
    EXPECT_FLOAT_EQ(data[4], 5.0);
}

// int main(int argc, char **argv)
// {
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
