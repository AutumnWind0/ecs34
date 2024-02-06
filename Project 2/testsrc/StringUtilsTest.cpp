#include <gtest/gtest.h>
#include "StringUtils.h"

TEST(StringUtilsTest, SliceTest){
    EXPECT_EQ(StringUtils::Slice("Hello, world!", 0, 5), "Hello");
    EXPECT_EQ(StringUtils::Slice("Hello, world!", -6, -1), "world");
    EXPECT_EQ(StringUtils::Slice("Hello, world!", 7, 0), "world!");
}

TEST(StringUtilsTest, Capitalize){
    EXPECT_EQ(StringUtils::Capitalize("hello"), "Hello");
    EXPECT_EQ(StringUtils::Capitalize("world"), "World");
    EXPECT_EQ(StringUtils::Capitalize("apple"), "Apple");
}

TEST(StringUtilsTest, Upper){
    EXPECT_EQ(StringUtils::Upper("apple"), "APPLE");
    EXPECT_EQ(StringUtils::Upper("HellO"), "HELLO");
    EXPECT_EQ(StringUtils::Upper("World"), "WORLD");
}

TEST(StringUtilsTest, Lower){
    EXPECT_EQ(StringUtils::Lower("APPle"), "apple");
    EXPECT_EQ(StringUtils::Lower("heLLO"), "hello");
    EXPECT_EQ(StringUtils::Lower("WORLD"), "world");
}

TEST(StringUtilsTest, LStrip){
    EXPECT_EQ(StringUtils::LStrip("   Hello"), "Hello");
    EXPECT_EQ(StringUtils::LStrip("   wd"), "wd");
  
}

TEST(StringUtilsTest, RStrip){
    EXPECT_EQ(StringUtils::RStrip("wd     "), "wd");
    EXPECT_EQ(StringUtils::RStrip("Hello          "), "Hello");
}

TEST(StringUtilsTest, Strip){
    EXPECT_EQ(StringUtils::Strip("   Hello  "), "Hello");
    EXPECT_EQ(StringUtils::Strip("   wd"), "wd");
}

TEST(StringUtilsTest, Center){
    EXPECT_EQ(StringUtils::Center("Hello", 7, ' '), " Hello ");
    EXPECT_EQ(StringUtils::Center("Hello", 9, 'A'), "AAHelloAA");
}

TEST(StringUtilsTest, LJust){
    EXPECT_EQ(StringUtils::LJust("Hello", 7), "Hello  ");
    EXPECT_EQ(StringUtils::LJust("wd", 1), "wd");
}

TEST(StringUtilsTest, RJust){
    EXPECT_EQ(StringUtils::RJust("Hello", 7), "  Hello");
    EXPECT_EQ(StringUtils::RJust("wd", 6), "    wd");
}

TEST(StringUtilsTest, Replace){
    EXPECT_EQ(StringUtils::Replace("Hello", "e", "a"), "Hallo");
    EXPECT_EQ(StringUtils::Replace("Hello", "l", "e"), "Heeeo");
}

TEST(StringUtilsTest, Split){
    EXOECT_EQ(StringUtils::Split("Hello,world", ","), "Hello", "world");
    EXOECT_EQ(StringUtils::Split("world", "o"), "w", "rld");
}

TEST(StringUtilsTest, Join){
    EXPECT_EQ(StringUtils::Join(" ", std::vector<std::string>{"Hello", "world"}), "Hello world");
    EXPECT_EQ(StringUtils::Join(",", std::vector<std::string>{"a", "b", "c"}), "a,b,c");
    EXPECT_EQ(StringUtils::Join(" ", std::vector<std::string>{"eat", "apple"}), "eat apple");
}

TEST(StringUtilsTest, ExpandTabs){
    EXPECT_EQ(StringUtils::ExpandTabs("Hello\tworld"), "Hello    world");
    EXPECT_EQ(StringUtils::ExpandTabs("\tHello\tworld\t"), "    Hello    world    ");
    EXPECT_EQ(StringUtils::ExpandTabs("eat\tapple"), "eat    apple");
}

TEST(StringUtilsTest, EditDistance){
    EXPECT_EQ(StringUtils::EditDistance("HELLO", "hello", true), 0);
    EXPECT_EQ(StringUtils::EditDistance("HELLO", "hello", false), 5);
    EXPECT_EQ(StringUtils::EditDistance("worLD", "apple", false), 5);
}
