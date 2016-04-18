#ifndef TEMPLATEPARAMETERID_H
#define TEMPLATEPARAMETERID_H

#include "DataExtractor.h"

class ConcreteTableColumn;
class TemplateArgumentAsType;
class TypesTable;

class TemplateParameterId : public DataExtractor {

public:

   TemplateParameterId(DataExtractor *next, ConcreteTableColumn *prototype, TemplateArgumentAsType *condition, TypesTable *types);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

private:

	TypesTable *types;

};
#endif //TEMPLATEPARAMETERID_H