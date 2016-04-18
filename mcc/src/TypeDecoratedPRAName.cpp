#include "TypeDecoratedPRAName.h"
#include "PRADecorator.h"
#include "ConcreteTableColumn.h"
#include "FindDecoratedType.h"
#include "FindChildByName.h"
#include "FindBaseType.h"

TypeDecoratedPRAName::TypeDecoratedPRAName(DataExtractor *next, ConcreteTableColumn *prototype, PRADecorator *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeDecoratedPRAName::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string ptr_dcltr				= "ptr_dcltr";
	std::string ref_dcltr				= "ref_dcltr";
	std::string array_dcltr				= "array_dcltr";
	std::string declaration_specifiers	= "declaration_specifiers";
	std::string type_specifiers			= "type_specifiers";
	std::string type_id					= "type_id";
	std::string operator_op,value;

	FindDecoratedType algorithm;
	FindChildByName child_by_name;
	FindBaseType base_type;
	std::vector<std::string> usedTypes;

	VTP_TreeP tmp_tree,tmp;
	
	tmp_tree = VTP_TreeUp(tree.tree);

	if((tmp = child_by_name.find(tmp_tree,declaration_specifiers)) != NULL) {
		value = base_type.find(tmp,&usedTypes);	
	} else if((tmp = child_by_name.find(tmp_tree,type_specifiers)) != NULL) {
		value = base_type.find(tmp,&usedTypes);
	} else if((tmp = child_by_name.find(tmp_tree,type_id)) != NULL) {
		value = base_type.find(tmp,&usedTypes);
	} else {
		tmp_tree = VTP_TreeUp(tree.tree);
		value = algorithm.find(tmp_tree,&usedTypes);
	}

	operator_op = VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree));

	if(operator_op == ptr_dcltr) {
		value+="*";
	} else if(operator_op == ref_dcltr) {
		value+="&";
	} else if(operator_op == array_dcltr) {
		value+="[]";
	} else {
		value+="<ERROR>";
	}

	column->init(value,true);

	return column;
}
