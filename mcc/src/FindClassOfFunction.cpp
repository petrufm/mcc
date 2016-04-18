#include "FindClassOfFunction.h"
#include "FindChildByName.h"
#include "TypesTable.h"
#include "SetOperations.h"

std::string FindClassOfFunction::find(VTP_TreeP &tree,bool all_scope) {

	VTP_TreeP tmp_tree,tmp;
	std::string fndef					= "fndef";
	std::string parenth_dcltr			= "parenth_dcltr";
	std::string func_dcltr				= "func_dcltr";
	std::string array_dcltr				= "array_dcltr";
	std::string ptr_dcltr				= "ptr_dcltr";
	std::string ref_dcltr				= "ref_dcltr";
	std::string memptr_dcltr			= "memptr_dcltr";
	std::string qualified_id			= "qualified_id";
	std::string template_name			= "template_name";
	
	std::string value;
	FindChildByName child;

	tmp_tree = tree;
	
	while(tmp_tree != NULL && fndef != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		tmp_tree = VTP_TreeUp(tmp_tree);
	}

	if(tmp_tree != NULL) {
		while((tmp = child.find(tmp_tree,func_dcltr)) == NULL ||
			(tmp = child.find(tmp,parenth_dcltr)) != NULL) {
			
			if((tmp = child.find(tmp_tree,parenth_dcltr)) != NULL ||
			   (tmp = child.find(tmp_tree,array_dcltr)) != NULL || 
			   (tmp = child.find(tmp_tree,ptr_dcltr)) != NULL ||
			   (tmp = child.find(tmp_tree,ref_dcltr)) != NULL ||
			   (tmp = child.find(tmp_tree,memptr_dcltr)) != NULL) {
				tmp_tree = tmp;
			} else {
				break;
			}
		}
		if((tmp_tree = child.find(tmp_tree,func_dcltr)) != NULL) {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
			if(qualified_id == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
				tmp_tree = VTP_TreeDown(tmp_tree,0);
				if(template_name == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tmp_tree,0)))) {
					tmp_tree = VTP_TreeDown(VTP_TreeDown(tmp_tree,0),0);
					value = VTP_NAME_STRING(VTP_TreeAtomValue(tmp_tree));
				} else {
					ITERATOR_MAP(VTP_TreeChild, tmp_tree, tmp); {
					if(value == "") {
						value = VTP_NAME_STRING(VTP_TreeAtomValue(tmp));
					} else {
						if(all_scope) {
							value += "::";
							value += VTP_NAME_STRING(VTP_TreeAtomValue(tmp));
						} else {
							value = VTP_NAME_STRING(VTP_TreeAtomValue(tmp));
						}
					}
					}
					ITERATOR_END_MAP(VTP_TreeChild);
				}
			}
		} else {
			value = "";
		}
	} else {
		value = "";
	}
		
	return value;
}

std::string FindClassOfFunction::find(std::string class_scope,TypesTable *types) {

	std::string::size_type pos;
	std::string class_name,value;

	TypesTable::RowSet *set;
	std::string typeName	= "TypeName";
	std::string kindOf		= "KindOf";
	int id;
	char buff[12];

	//Search for a class with the last identifier of the scope
	pos = class_scope.find_last_of(":");
	if(pos < class_scope.size()) {
		class_name = class_scope.substr(pos + 1);
		class_scope = class_scope.substr(0,pos - 1);
	} else {
		class_name = class_scope;
		class_scope = "";
	}

	set = types->find_set(typeName,class_name);

	//If this is true then the last identifier from the scope
	//is not a class but a namespace so the class is not included in any class (OK)
	if(set->size() == 0) {
		value = "<NO_ONE>";
		delete set;
		return value;
	}

	if(set->size() != 1) {
		value = "<ERROR>";
	} else if((id = types->find_id(*set->begin())) > 0) {
		sprintf(buff,"%d",id);
		value = buff;
	} else {
		value = "<ERROR>";
	}
	delete set;
	return value;
}