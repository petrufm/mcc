#ifndef TYPEISLIBRARYTYPE_H
#define TYPEISLIBRARYTYPE_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class LibraryType;

class TypeIsLibraryType : public DataExtractor {

public:    

    TypeIsLibraryType(DataExtractor *next, ConcreteTableColumn *prototype, LibraryType *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //TYPEISLIBRARYTYPE_H