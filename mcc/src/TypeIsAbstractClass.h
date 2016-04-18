#ifndef TYPEISABSTRACTCLASS_H
#define TYPEISABSTRACTCLASS_H

#include "DataExtractor.h"
#include "ConcreteTableColumn.h"
#include "ClassDeclaration.h"

class TypeIsAbstractClass : public DataExtractor {

    


public:

    TypeIsAbstractClass(DataExtractor *next, ConcreteTableColumn *prototype, ClassDeclaration *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

private:

	bool isClassAbstract(VTP_TreeP tree);

};
#endif //TYPEISABSTRACTCLASS_H