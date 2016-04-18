#include "FunctionParameters.h"
#include "FuncDeclaration.h"
#include "ConcreteTableColumn.h"

FunctionParameters::FunctionParameters(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition):DataExtractor(next,prototype,condition) {}

TableColumn* FunctionParameters::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string var_parmlist = "var_parmlist";
	std::string parm_decl	 = "parm_decl";
	std::string void_op		 = "void";
	std::string none		 = "none";
	std::string typespec	 = "typespec";
	std::string absdcltr	 = "absdcltr";
	std::string value;
	VTP_TreeP tmp_tree,child,tmp,child1;
	int count_all;
	int count_init;
	bool isVoid;
	char buff[12];

	tmp_tree = VTP_TreeDown(tree.tree,1);
	if(var_parmlist == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		tmp_tree = VTP_TreeDown(tmp_tree,0);
	}

	count_all = count_init = 0;

    ITERATOR_MAP(VTP_TreeChild, tmp_tree, child); {
		if(parm_decl == VTP_OP_NAME(VTP_TREE_OPERATOR(child))) {
			tmp = VTP_TreeDown(child,0);
			isVoid = false;
		    ITERATOR_MAP(VTP_TreeChild, tmp, child1); {
				if(typespec == VTP_OP_NAME(VTP_TREE_OPERATOR(child1)) &&
					void_op == VTP_NAME_STRING(VTP_TreeAtomValue(child1))) {
					isVoid = true;
				}
			}
			ITERATOR_END_MAP(VTP_TreeChild);
			tmp = VTP_TreeDown(child,1);
			if(absdcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) && isVoid) {
				isVoid = false;
			}
			tmp = VTP_TreeDown(child,2);
			if(none != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
				count_init++;
			}
		}
		if(!isVoid) {
			count_all++;
		}
	}
	ITERATOR_END_MAP(VTP_TreeChild);
	
	sprintf(buff,"%d %d",count_all - count_init, count_all);
	value = buff;

	if(count_init != 0) {
		column->init(value,false,1,TableColumn::MergeByCopy);
	} else {
		column->init(value,false);
	}
	return column;

}

