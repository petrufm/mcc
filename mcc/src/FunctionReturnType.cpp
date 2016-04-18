#include "FunctionReturnType.h"
#include "FuncDeclaration.h"
#include "ConcreteTableColumn.h"
#include "FindClassContext.h"
#include "FindDecoratedType.h"
#include "SetOperations.h"
#include "TypesTable.h"
#include "FindSignature.h"

FunctionReturnType::FunctionReturnType(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition, TypesTable *types):DataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn *FunctionReturnType::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::vector<std::string> usedTypes;
	VTP_TreeP tmp_tree;
	FindDecoratedType ret_type;
	FindClassContext the_context;
	SetOperations set_operation;
	std::string parenth_dcltr	= "parenth_dcltr";
	std::string operator_op		= "operator";
	std::string type_id			= "type_id";
	std::string qualified_id	= "qualified_id";

	std::string name,mycontext;
	std::string typeName = "TypeName";
	std::string contextCol = "Context";
	Table::RowSet *set1,*set2,*set3;
	int id;
	char buff[12];
	FindSignature sig;

	tmp_tree = tree.tree;

	//Check to see if this is a call operator
	tmp_tree = VTP_TreeDown(tree.tree,0);
	if(parenth_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		tmp_tree = VTP_TreeDown(tmp_tree,0);
	}
	if(operator_op == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		if(type_id == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tmp_tree,0)))) {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
			name = sig.findElement(tmp_tree,&usedTypes);
		}
	} else if(qualified_id == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		tmp_tree = VTP_TreeDown(tmp_tree,1);
		if(operator_op == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			if(type_id == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tmp_tree,0)))) {
				tmp_tree = VTP_TreeDown(tmp_tree,0);
				name = sig.findElement(tmp_tree,&usedTypes);
			}
		}
	}
	
	//Check for decorated type
	tmp_tree = tree.tree;
	if(name == "") {
		name = ret_type.find(tmp_tree,&usedTypes);
	}
	
	//Check for ID
	if(name != "") {
		mycontext = the_context.find(the_context.find(tmp_tree),&usedTypes,types);
		set1 = types->find_set(typeName,name);
		if(set1->size() == 1) {
			id = types->find_id(*set1->begin());
			sprintf(buff,"%d",id);
			name = buff;
			delete set1;
		} else {
			set2 = types->find_set(contextCol,mycontext);
			set3 = set_operation.intersection_op(set1,set2);
			delete set1;
			delete set2;
			if(set3->size() == 1) {
				id = types->find_id(*set3->begin());
				sprintf(buff,"%d",id);
				name = buff;
			} else {
				name = "<ERROR>";
			}
			delete set3;
		}
	} else {
		name = "<NO_ONE>";
	}

	column->init(name,true);
	return column;
}