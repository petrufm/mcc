#include "TypeIsDecoratedPRA.h"
#include "PRADecorator.h"
#include "ConcreteTableColumn.h"

TypeIsDecoratedPRA::TypeIsDecoratedPRA(DataExtractor *next, ConcreteTableColumn *prototype, PRADecorator *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeIsDecoratedPRA::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string ptr_dcltr	= "ptr_dcltr";
	std::string ref_dcltr	= "ref_dcltr";
	std::string array_dcltr = "array_dcltr";
	std::string operator_op,value;

	operator_op = VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree));
	if(operator_op == ptr_dcltr) {
		value = "ptr-decorator";
	} else if(operator_op == ref_dcltr) {
		value = "ref-decorator";
	} else if(operator_op == array_dcltr) {
		value = "array-decorator";
	}

	column->init(value,false);

	return column;

}
