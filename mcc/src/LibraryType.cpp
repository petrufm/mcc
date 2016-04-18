#include "LibraryType.h"
#include "TypesTable.h"
#include "NamespaceTable.h"

LibraryType::LibraryType(TypesTable *table) {
	this->table = table;
}

bool LibraryType::isTriggered(AbstractTree &tree){

	std::string identifier				= "identifier";
	std::string class_head				= "class_head";
	std::string class_op				= "class";
	std::string qualified_id			= "qualified_id";
	std::string memptr_dcltr			= "memptr_dcltr";
	std::string scope					= "scope";
	std::string template_name			= "template_name";
	std::string declaration_specifiers	= "declaration_specifiers";
	std::string type_specifiers			= "type_specifiers";
	std::string paramlist				= "paramlist";
	std::string compound				= "compound";
	std::string base_class				= "base_class";
	std::string template_arg_list		= "template_arg_list";
	std::string TypeName				= "TypeName";
	std::string NamespaceName			= "NamespaceName";
	std::string value;
	VTP_TreeP tmp;
	int level = 0;


	if(identifier != VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree))) {
		return false;
	}
	
	tmp = VTP_TreeUp(tree.tree);
	value = VTP_OP_NAME(VTP_TREE_OPERATOR(tmp));

	if(value != declaration_specifiers && value != type_specifiers && value != base_class && value != template_arg_list) {
		if(value == qualified_id) {
			tmp = VTP_TreeUp(tmp);
			if(declaration_specifiers != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) &&
				type_specifiers != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) &&
			    base_class != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
				if(class_head != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
					return false; //For protection
				}
				tmp = VTP_TreeUp(tmp);
				if(class_op != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
					return false; //For protection
				}
			}
		} else if(value == class_head) {
			tmp = VTP_TreeUp(tmp);
			if(class_op != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
				return false; // For protection
			}
		} else if(value == scope) {
			tmp = VTP_TreeUp(tmp);
			if(memptr_dcltr != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
				return false;   // We are interested in last indentifier for pointers to funcions
			} else if(VTP_TreeRight(tree.tree) != NULL) {
				return false;	// We are interested only in the last identifier
			}
		} else if(value == template_name) {
			tmp = VTP_TreeUp(tmp);
			if(declaration_specifiers != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) &&
			   qualified_id != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) &&
			   base_class != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
				return false; //For protection
			}	
		} else {
			return false;
		}
	}

	//If the type is already in TypesTable the it is considered a ProjectType
	TypesTable::RowSet *set;
	std::string library_type = "library-type";
	std::string kindOf		 = "KindOf";
	value = VTP_NAME_STRING(VTP_TreeAtomValue(tree.tree));
	set = table->find_set(TypeName,value);
	if(set->size() != 0) {
		if(set->size() == 1 && table->getColumnValue(table->find_id(*set->begin()),kindOf) == library_type) {
			delete set;
			return true;
		} else {
			delete set;
			return false;
		}
	} else {
		delete set;
		return true;
	}
}
