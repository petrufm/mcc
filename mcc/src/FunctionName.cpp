#include "FunctionName.h"
#include "ConcreteTableColumn.h"
#include "FuncDeclaration.h"
#include "FindSignature.h"

FunctionName::FunctionName(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition):DataExtractor(next,prototype,condition) {};

TableColumn* FunctionName::handleExtraction(AbstractTree &tree) {
	
	TableColumn *column = prototype->clone();
	std::string identifier	 = "identifier";
	std::string qualified_id = "qualified_id";
	std::string destructor   = "destructor";
	std::string operator_op  = "operator";
	std::string parenth_dcltr= "parenth_dcltr";
	std::string type_id		 = "type_id";
	std::vector<std::string> usedTypes;
	std::string value;
	VTP_TreeP tmp_tree;
	FindSignature cast_type;

	tmp_tree = VTP_TreeDown(tree.tree,0);
	if(parenth_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		tmp_tree = VTP_TreeDown(tmp_tree,0);
	}

	if(identifier == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		value = VTP_NAME_STRING(VTP_TreeAtomValue(tmp_tree));
	} else if(destructor == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		value = VTP_NAME_STRING(VTP_TreeAtomValue(VTP_TreeDown(tmp_tree,0)));
		value = "~" + value;
	} else if(operator_op == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		if(type_id == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tmp_tree,0)))) {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
			value = "<";
			value+= cast_type.findElement(tmp_tree,&usedTypes);
			value+= ">";
		} else {
			value = "<";
			value+= VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tmp_tree,0)));
			value+= ">";
		}
	} else if(qualified_id == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		tmp_tree = VTP_TreeDown(tmp_tree,1);
		if(identifier == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			value = VTP_NAME_STRING(VTP_TreeAtomValue(tmp_tree));
		} else if(destructor == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			value = VTP_NAME_STRING(VTP_TreeAtomValue(VTP_TreeDown(tmp_tree,0)));
			value = "~" + value;
		} else if(operator_op == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			if(type_id == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tmp_tree,0)))) {
				tmp_tree = VTP_TreeDown(tmp_tree,0);
				value = "<";
				value+= cast_type.findElement(tmp_tree,&usedTypes);
				value+= ">";
			} else {
				value = "<";
				value+= VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tmp_tree,0)));
				value+= ">";
			}
		} else {
			value = "<ERROR>";
		}
	} else {
		value = "<ERROR>";
	}

	column->init(value,true);
	return column;
}

