#ifndef TYPELIBRARYISGENERIC_H
#define TYPELIBRARYISGENERIC_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class LibraryType;

class TypeLibraryIsGeneric : public DataExtractor {

public:    

	TypeLibraryIsGeneric(DataExtractor *next, ConcreteTableColumn *prototype, LibraryType *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

};
#endif //TPELIBRARYISGENERIC_H