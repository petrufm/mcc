#include "TypeIsInterfaceClass.h"

TypeIsInterfaceClass::TypeIsInterfaceClass(DataExtractor *next, ConcreteTableColumn *prototype, ClassDeclaration *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeIsInterfaceClass::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string value;

	if(hasMethodsDeclared(VTP_TreeRight(tree.tree)) && methodsAreAbstract(VTP_TreeRight(tree.tree))) {
		value = "1";
		column->init(value,false);
	} else {
		value = "0";
		column->init(value,false);
	}

	return column;

}

bool TypeIsInterfaceClass::methodsAreAbstract(VTP_TreeP tree) {

	std::string dcltr_affinit	= "dcltr_affinit";
	std::string func_dcltr		= "func_dcltr";
	std::string ptr_dcltr		= "ptr_dcltr";
	std::string ref_dcltr		= "ref_dcltr";
	std::string memptr_dcltr	= "memptr_dcltr";
	std::string parenth_dcltr	= "parenth_dcltr";
	std::string class_op		= "class_op";


	VTP_TreeP child,parent;

	if(func_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tree)) &&
	   (parenth_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tree,0))) ||
	    ptr_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(VTP_TreeDown(tree,0),0))) ||
	    memptr_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(VTP_TreeDown(tree,0),0))) ||
		ref_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(VTP_TreeDown(tree,0),0))))) {
			parent = tree;
			do {
				parent = VTP_TreeUp(parent);
			} while(parent != NULL &&
				class_op != VTP_OP_NAME(VTP_TREE_OPERATOR(parent)) &&
				dcltr_affinit != VTP_OP_NAME(VTP_TREE_OPERATOR(parent)));
			if(parent != NULL &&
				dcltr_affinit == VTP_OP_NAME(VTP_TREE_OPERATOR(parent))) {
				return true;
			} else {
				return false;
			}
	} else {
	
		ITERATOR_MAP(VTP_TreeChild, tree, child); { 

		if(!methodsAreAbstract(child)) return false;

		} 
		ITERATOR_END_MAP(VTP_TreeChild);

		return true;
	}
}

bool TypeIsInterfaceClass::hasMethodsDeclared(VTP_TreeP tree) {

	std::string func_dcltr		= "func_dcltr";
	std::string ptr_dcltr		= "ptr_dcltr";
	std::string ref_dcltr		= "ref_dcltr";
	std::string memptr_dcltr	= "memptr_dcltr";
	std::string parenth_dcltr	= "parenth_dcltr";
	std::string class_op		= "class_op";

	VTP_TreeP child;

	if(func_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tree)) &&
	   (parenth_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tree,0))) ||
		ptr_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(VTP_TreeDown(tree,0),0))) ||
	    memptr_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(VTP_TreeDown(tree,0),0))) ||
		ref_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(VTP_TreeDown(tree,0),0))))) {
			return true;
	} else {
	
		ITERATOR_MAP(VTP_TreeChild, tree, child); { 

		//Do not seartch in inner classes
		if(class_op != VTP_OP_NAME(VTP_TREE_OPERATOR(child))) {
			if(hasMethodsDeclared(child)) return true;
		}

		}
		ITERATOR_END_MAP(VTP_TreeChild);

		return false;
	}

}