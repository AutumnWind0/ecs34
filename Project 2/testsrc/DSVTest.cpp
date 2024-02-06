#include <gtest/gtest.h>
#include "DSVReader.h"
#include "DSVWriter.h"
#include "StringDataSource.h"
#include "StringDataSink.h"

TEST(DSVReader, Read){
    auto TestDataSource=std::make_shared<StringDataSource>("Hello!world");
    CDSVReader Reader(TestDataSource, '!');
    std::vector<std::string> Result;

    EXPECT_TRUE(Reader.Read(Result));
    ASSERT_EQ(Result.size(), 2);
    EXPECT_EQ(Result[0], "Hello");
    EXPECT_EQ(Result[1], "world");
}

TEST(DSVReader, Read){
    auto TestDataSource=std::make_shared<StringDataSource>("Good&morning");
    CDSVReader Reader(TestDataSource, '&');
    std::vector<std::string> Result;

    EXPECT_TRUE(Reader.Read(Result));
    ASSERT_EQ(Result.size(), 2);
    EXPECT_EQ(Result[0], "Good");
    EXPECT_EQ(Result[1], "morning");
}

TEST(DSVReader, Read){
    auto TestDataSource=std::make_shared<StringDataSource>("I$LIKE$APPLES");
    CDSVReader Reader(TestDataSource, '$');
    std::vector<std::string> Result;

    EXPECT_TRUE(Reader.Read(Result));
    ASSERT_EQ(Result.size(), 3);
    EXPECT_EQ(Result[0], "I");
    EXPECT_EQ(Result[1], "LIKE");
    EXPECT_EQ(Result[1], "APPLES");
}

TEST(DSVWriter, Write){
    auto TestDataSink=std::make_shared<StringDataSink>();
    CDSVWriter Writer(TestDataSink, '&');
    std::vector<std::string> Data={"Hello", "World"};

    EXPECT_TRUE(Writer.Write(Data));
    EXPECT_EQ(TestDataSink->GetData(), "Hello&World");
}

TEST(DSVWriter, Write){
    auto TestDataSink=std::make_shared<StringDataSink>();
    CDSVWriter Writer(TestDataSink, '$');
    std::vector<std::string> Data={"Good", "morning"};

    EXPECT_TRUE(Writer.Write(Data));
    EXPECT_EQ(TestDataSink->GetData(), "Good$morning");
}

TEST(DSVWriter, Write){
    auto TestDataSink=std::make_shared<StringDataSink>();
    CDSVWriter Writer(TestDataSink, '!');
    std::vector<std::string> Data={"read", "book"};

    EXPECT_TRUE(Writer.Write(Data));
    EXPECT_EQ(TestDataSink->GetData(), "read!book");
}