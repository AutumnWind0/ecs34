#include "XMLWriter.h"
#include <iostream>
#include <expat.h>
#include <stack>

struct CXMLWriter::SImplementation{
    std::shared_ptr< CDataSink > DDataSink;
    XML_Parser DXMLParser;
    std::stack< std::string > DStack;

    SImplementation(std::shared_ptr< CDataSink > sink){
        DDataSink=sink;
        DXMLParser=XML_ParserCreate(NULL);
        XML_SetStartElementHandler(DXMLParser, StartElementHandlerCallback);
        XML_SetEndElementHandler(DXMLParser, EndElementHandlerCallback);
        XML_SetCharacterDataHandler(DXMLParser, CharacterDataHandlerCallback);
        XML_SetUserData(DXMLParser, this);
    };

    ~SImplementation(){
        XML_ParserFree(DXMLParser);
    };

// Outputs all end elements for those that have been started
    void Flush(){
        while (!DStack.empty()){
            std::string ElementName=DStack.top();
            DStack.pop();
            DDataSink->Write("</"+ElementName + ">");
        }
    };

// Writes out the entity to the output stream
    bool WriteEntity(const SXMLEntity &entity){
        switch (entity.Dtype){
            case SXMLEntity::EType::StartElement:
                Write("<"+entity.DNameData);
                for (const auto &attr:entity.DAttributes){
                    Write(" "+attr.DName+"=\""+attr.DValue+"\"");
                }
                Write(">");
                DStack.push(entity.DNameData);
                break;  
            case SXMLEntity::EType::EndElement:
                Write("</"+entity.DNameData+">");
                DElementStack.pop();
                break;
            case SXMLEntity::EType::CharacterData:
                Write(XML_EncodeString(entity.DNameData).c_str());
                break;
        }
    }
    bool Flush(){
        while (!DStack.empty()){
            Write("</"+DStack.top()+">");
            DStack.pop();
        }
        return DDataSink->Flush();
    }
    }

CXMLWriter::CXMLWriter(std::shared_ptr< CDataSink > sink){
    DImplementation=std::make_unique<SImplementation>(sink);
}

CXMLWriter::~CXMLWriter(){
}

bool CXMLWriter::WriteEntity(const SXMLEntity &entity){
    return DImplementation->WriteEntity(entity);
}

bool CXMLWriter::Flush(){
    return DImplementation->Flush();
}

