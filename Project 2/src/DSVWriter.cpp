#include "DSVWriter.h"
#include "StringUtils.h"
#include <iostream>
#include <sstream>

// Constructor for DSV writer, sink specifies the data destination, delimiter
// specifies the delimiting character, and quoteall specifies if all values
// should be quoted or only those that contain the delimiter, a double quote,
// or a newline
struct CDSVWriter::SImplementation{
    std::shared_ptr< CDataSink > sinkIn;
    char delimiterIn;
    bool quoteallIn;
    SImplementation(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall){
        sinkIn=sink;
        delimiterIn=delimiter;
        quoteallIn=quoteall;
    }//assign input value to sinkIn, delimiterIn, quoteallIn

// Returns true if the row is successfully written, one string per column
// should be put in the row vector
    bool WriteRow(const std::vector<std::string>&row){
        std::stringstream output;
        for (const auto &a:row){
            if (quoteallIn||a.find(Delimiter)!=std::string::npos||a.find('"') !=std::string::npos||a.find('\n')!=std::string::npos){
                output << '"' << StringUtils::Replace(a,"\"","\"\"") << '"';
            }//some special conditions
            else{
                output << a;
            }//if quoteallIn is false, only add string
        }
        output << '\n';
        return !output.empty();
    }
};

CDSVWriter::CDSVWriter(std::shared_ptr< CDataSink> sink, char delimiter, bool quoteall){
    DImplementation = std::make_unique<SImplementation>(sink,delimiter,quoteall);
}

// Destructor for DSV writer
CDSVWriter::~CDSVWriter(){
}

// Returns true if the row is successfully written, one string per column
// should be put in the row vector
bool CDSVWriter::WriteRow(const std::vector<std::string>&row){
    return DImplementation->WriteRow(row);
}
