#include <iostream>
#include <sstream>
#include "DSVReader.h"
#include "DataSource.h"
#include "StringUtils.h"

// Constructor for DSV reader, src specifies the data source and delimiter
// specifies the delimiting character
struct CDSVReader::SImplementation{
    std::shared_ptr< CDataSource > srcIn;
    char delimiterIn;
    SImplementation(std::shared_ptr< CDataSource > src, char delimiter){
        srcIn=src;
        delimiterIn=delimiter;
}

    bool End() const{
        return srcIn->End();
    }

// Returns true if the row is successfully read, one string will be put in
// the row per column
    bool ReadRow(std::vector< std::string > &row){
        row=StringUtils::Split(row, delimiterIn);
        return !row.empty();
    }
};

CDSVReader::CDSVReader(std::shared_ptr< CDataSource > src, char delimiter){
    DImplementation=std::make_unique<SImplementation>(src,delimiter);
}

// Destructor for DSV reader
CDSVReader::~CDSVReader(){
}

//Returns true if all rows have been read from the DSV
bool CDSVReader::End() const{
    return DImplementation->End();
}

bool CDSVReader::ReadRow(std::vector< std::string > &row){
    return DImplementation->ReadRow(row);
}

