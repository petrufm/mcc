#ifndef TYPELIBRARYNAME_H
#define TYPELIBRARYNAME_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class LibraryType;

class TypeLibraryName : public DataExtractor {

public:    

    TypeLibraryName(DataExtractor *next, ConcreteTableColumn *prototype, LibraryType *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

};
#endif //TYPELIBRARYNAME_H