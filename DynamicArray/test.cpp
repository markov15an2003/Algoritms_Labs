#include "pch.h"
#include "DynamicArray.h"

TEST(TestArray, IncreaseCap_1) {
	DynamicArray<int> arr(0);
	arr.insert(2);
	EXPECT_EQ(arr[0], 2);
	EXPECT_EQ(arr.size(), 1);
}

TEST(TestArray, IncreaseCap_2) {
	DynamicArray<string> arr(4);
	for (int i = 0; i < 1000; i++)
		arr.insert(to_string(i));
	EXPECT_EQ(arr.size(), 1000);
	for (int i = 0; i < 1000; i++)
		EXPECT_EQ(arr[i], to_string(i));
}

TEST(TestArray, Insert_1) {
	DynamicArray<string> arr;
	for (int i = 0; i < 32; i++)
		arr.insert(to_string(i));
	for (int i = 0; i < 10; i++)
		arr.insert(i * 2, to_string(i));
	for (int i = 0; i < 10; i++)
		EXPECT_EQ(arr[i * 2 + 1], to_string(i));
	for (int i = 0; i < 10; i++)
		EXPECT_EQ(arr[i * 2], to_string(i));
}

TEST(TestArray, Remove_1) {
	DynamicArray<string> arr;
	for (int i = 0; i < 100; i++)
		arr.insert(to_string(i));
	for (int i = 0; i < 15; i++)
		arr.remove(i * 3);
    EXPECT_EQ(arr.size(), 85);
    for (int i = 0; i < 85; i++)
        EXPECT_EQ(arr[i], to_string(i/3<15 ? 1+i/3+i : 15+i));
}

TEST(TestArray, Insert_2) {
    DynamicArray<int> arr;
    arr.insert(1);
    arr.insert(3);
    arr.insert(1, 2);

    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(TestArray, Remove_2) {
    DynamicArray<int> arr;
    arr.insert(1);
    arr.insert(2);
    arr.insert(3);

    arr.remove(1);

    ASSERT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(TestArray, Clear_1) {
    DynamicArray<int> arr;

    for (int i = 0; i < 10; ++i) {
        arr.insert(i);
    }

    EXPECT_EQ(arr.size(), 10);

    while (arr.size() > 0) {
        arr.remove(0);
    }

    EXPECT_EQ(arr.size(), 0);
}

TEST(TestArray, Iterator_1) {
    DynamicArray<string> arr;
    for (int i = 0; i < 5; ++i) {
        arr.insert(to_string(i + 1));
    }

    auto it = arr.iterator();
    string str = it.get();

    while (it.hasNext()) {
        it.next();
        str += it.get();
    }

    EXPECT_EQ(str, "12345");
}

TEST(TestArray, ReverseIterator_1) {
    DynamicArray<string> arr;
    for (int i = 0; i < 5; ++i) {
        arr.insert(to_string(i + 1));
    }

    auto it = arr.reverseIterator();
    string str = it.get();

    while (it.hasNext()) {
        it.next();
        str += it.get();
    }

    EXPECT_EQ(str, "54321");
}

TEST(TestArray, Move_1) {
    DynamicArray<int> base;
    base.insert(5);
    base.insert(6);

    DynamicArray<int> moved = std::move(base);

    EXPECT_EQ(base.size(), 0);
    EXPECT_EQ(moved.size(), 2);
    EXPECT_EQ(moved[0], 5);
    EXPECT_EQ(moved[1], 6);
}

TEST(TestArray, Eq_1) {
    DynamicArray <string> arr1;
    arr1.insert(to_string(1));
    arr1.insert(to_string(2));
    arr1.insert(to_string(3));
    DynamicArray <string> arr2 = arr1;
    EXPECT_EQ(arr2.size(), 3);
    EXPECT_EQ(arr2[0], "1");
    EXPECT_EQ(arr2[2], "3");
}

struct TestStr {
    int num;
    string str;
};

TEST(TestArray, Struct_1) {
    DynamicArray<TestStr> arr;

    arr.insert(TestStr{ 1, "one" });
    arr.insert(TestStr{ 2, "two" });

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0].num, 1);
    EXPECT_EQ(arr[0].str, "one");
    EXPECT_EQ(arr[1].num, 2);
    EXPECT_EQ(arr[1].str, "two");
}