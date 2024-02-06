#include <gtest/gtest.h>
#include "XMLReader.h"
#include "XMLWriter.h"
#include "StringDataSource.h"
#include "StringDataSink.h"

TEST(XMLReader, Read){
    auto InSource=std::make_shared<StringDataSource>("<eg name=\"Jack\"></eg>");
    CXMLReader Reader(InSource);
    SXMLEntity Entity;

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E.Attribute("name"), "Jack");

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);
}

TEST(XMLReader, Read){
    auto InSource=std::make_shared<StringDataSource>("<eg hobby=\"read\"></eg>");
    CXMLReader Reader(InSource);
    SXMLEntity Entity;

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E.Attribute("hobby"), "read");

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);
}

TEST(XMLReader, Read){
    auto InSource=std::make_shared<StringDataSource>("<eg book=\"notebook\"></eg>");
    CXMLReader Reader(InSource);
    SXMLEntity Entity;

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E.Attribute("book"), "notebook");

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);
}

TEST(XMLWriter, Write){
    auto OutputStream=std::make_shared<StringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity:EType:StartElement, "eg", {{"name", "Jack"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity:EType:EndElement, "eg",{}}));

    EXPECT_EQ(OutputStream->String(), "<eg name=\"Jack\"></eg>");
}

TEST(XMLWriter, Write){
    auto OutputStream=std::make_shared<StringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity:EType:StartElement, "eg", {{"hobby", "read"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity:EType:EndElement, "eg",{}}));

    EXPECT_EQ(OutputStream->String(), "<eg hobby=\"read\"></eg>");
}


TEST(XMLWriter, Write){
    auto OutputStream=std::make_shared<StringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity:EType:StartElement, "eg", {{"book", "notebook"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity:EType:EndElement, "eg",{}}));

    EXPECT_EQ(OutputStream->String(), "<eg book=\"notebook\"></eg>");
}
    