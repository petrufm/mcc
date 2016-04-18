#ifndef TYPEISINTERFACECLASS_H
#define TYPEISINTERFACECLASS_H

#include "DataExtractor.h"
#include "ConcreteTableColumn.h"
#include "ClassDeclaration.h"

class TypeIsInterfaceClass : public DataExtractor {

public:    

    TypeIsInterfaceClass(DataExtractor *next, ConcreteTableColumn *prototype, ClassDeclaration *condition);

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

private:

	bool methodsAreAbstract(VTP_TreeP tree);
	bool hasMethodsDeclared(VTP_TreeP tree);
};
#endif //TYPEISINTERFACECLASS_H