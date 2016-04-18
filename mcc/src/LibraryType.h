#ifndef LIBRARYTYPE_H
#define LIBRARYTYPE_H

#include "TriggerCondition.h"

class TypesTable;
class NamespaceTable;

class LibraryType : public TriggerCondition {

public:    

	LibraryType(TypesTable*);

    bool isTriggered(AbstractTree &tree);

private:

	TypesTable *table;

};
#endif //LIBRARYTYPE_H