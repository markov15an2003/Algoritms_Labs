#include "pch.h"
#include "QuickSort.h"

using namespace std;

TEST(SortTest, Letters) {
	char arr[10] = { 'q', 'a', 'v', 'r', 'e', 's', 'n', 'j', 'o', 'j' };
	char arrr[10] = {'a', 'e', 'j', 'j', 'n', 'o', 'q', 'r', 's', 'v'};
	sort(arr, arr+10, [](char a, char b) { return a < b; });
	for (int i = 0; i < 10; i++)
		EXPECT_EQ(arr[i], arrr[i]);
}

TEST(SortTest, Reverse) {
	int arr[100];
	for (int i = 0; i < 100; i++)
		arr[i] = 100 - i;
	sort(arr, arr + 100, [](int a, int b) { return a < b; });
	for (int i = 0; i < 100; i++)
		EXPECT_EQ(arr[i], i+1);
}

TEST(SortTest, Strings) {
    string arr[100];
    for (int i = 1; i <= 100; i++)
        arr[i-1] = to_string(100 - i);
    sort(arr, arr + 100, [](string a, string b) { return a < b; });
    EXPECT_EQ(arr[0], "0");
    for (int i = 1; i < 100; i++)
        if (i % 11 == 1)
            EXPECT_EQ(arr[i], to_string(i / 11 + 1));
        else if (i % 11 == 0)
            EXPECT_EQ(arr[i], to_string((i / 11) * 10 + 9));
        else
            EXPECT_EQ(arr[i], to_string((i / 11 + 1) * 10 + i % 11 - 2));
    }

TEST(SortTest, Empty) {
    vector<int> v;
    sort(v.data(), v.data() + 1, [](int a, int b) { return a < b; });
    EXPECT_EQ(0, 0);
}

TEST(SortTest, Single) {
    int arr[1] = { 9999 };
    sort(arr, arr + 1, [](int a, int b) { return a < b; });
    EXPECT_EQ(arr[0], 9999);
}

TEST(SortTest, Sorted) {
    int arr[100];
    for (int i = 0; i < 100; i++)
        arr[i] = 100 - i;
    sort(arr, arr + 100, [](int a, int b) { return a > b; });
    for (int i = 0; i < 100; i++)
        EXPECT_EQ(arr[i], 100 - i);
}

TEST(SortTest, EqualsButOne) {
    int arr[100];
    for (int i = 0; i < 99; i++)
        arr[i] = 9999;
    arr[99] = 1;
    sort(arr, arr + 100, [](int a, int b) { return a < b; });
    for (int i = 1; i < 100; i++)
        EXPECT_EQ(arr[i], 9999);
    EXPECT_EQ(arr[0], 1);
}

TEST(SortTest, Dupes) {
    string arr[500];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 100; j++)
            arr[i * 100 + j] = to_string(100 - j);

    sort(arr, arr + 500, [](string a, string b) { return a < b; });

    for (int i = 1; i < 500; i++)
        EXPECT_TRUE(arr[i-1] <= arr[i]);
}
