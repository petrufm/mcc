#include "FindSignature.h"
#include "FindChildByName.h"
#include "FindPointerToFunctionType.h"
#include "FindBaseType.h"

//It receives a parmlist or template_arg_list operator
std::string FindSignature::find(VTP_TreeP &tree, std::vector<std::string> *types) {

	std::string name;
	VTP_TreeP tmp_tree,child;

	tmp_tree = tree;

	name = "(";
    ITERATOR_MAP(VTP_TreeChild, tmp_tree, child); {
		name+=findElement(child,types);
		name+=',';
	}
	ITERATOR_END_MAP(VTP_TreeChild);
	if(name.at(name.size() - 1) == ',') {
		name = name.substr(0,name.size() - 1);
	}
	name+= ")";
	
	if(name == "(void)") {
		name = "()";
	}
	return name;
}

std::string FindSignature::findElement(VTP_TreeP &child,std::vector<std::string> *types) {

	std::string identifier				= "identifier";
	std::string ptr_dcltr				= "ptr_dcltr";
	std::string ref_dcltr				= "ref_dcltr";
	std::string array_dcltr				= "array_dcltr";
	std::string func_dcltr				= "func_dcltr";
	std::string absdcltr				= "absdcltr";
	std::string type_id					= "type_id";
	std::string qualified_id			= "qualified_id";

	bool decorate;

	FindBaseType base_type;

	std::string name;

	VTP_TreeP tmp;

	//Something is not right with template_arg_list operator
	if(identifier == VTP_OP_NAME(VTP_TREE_OPERATOR(child))) {
		name = VTP_NAME_STRING(VTP_TreeAtomValue(child));
		types->push_back(VTP_NAME_STRING(VTP_TreeAtomValue(child)));
	} else if(qualified_id == VTP_OP_NAME(VTP_TREE_OPERATOR(child))) {
		name = base_type.find(child,types);
	} else {
		tmp = VTP_TreeDown(child,1);
		if(tmp != NULL && (ptr_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) ||
						   ref_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))	||
						   array_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) ||
						   func_dcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) ||
						   absdcltr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) ||
						   identifier == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)))) {
			decorate = true;
			name = getTypeObject(tmp,decorate,types);
		} else if(type_id == VTP_OP_NAME(VTP_TREE_OPERATOR(child))) {
			tmp = VTP_TreeDown(child,0);
			name = base_type.find(tmp,types);
		} else {
			name ="?";
		}
	}

	return name;
}

std::string FindSignature::getTypeObject(VTP_TreeP &tree, bool &decorate, std::vector<std::string> *types, int level) {

	std::string ptr_dcltr	= "ptr_dcltr";
	std::string ref_dcltr	= "ref_dcltr";
	std::string array_dcltr	= "array_dcltr";
	std::string func_dcltr	= "func_dcltr";
	std::string initdecls	= "initdecls";
	std::string res,opName;
	VTP_TreeP tmp;

	FindChildByName child_by_name;
	FindPointerToFunctionType pointer_to_function;
	FindBaseType base_type;

	opName = VTP_OP_NAME(VTP_TREE_OPERATOR(tree));

	if((tmp = child_by_name.find(tree,ptr_dcltr)) != NULL) {
		res = getTypeObject(tmp,decorate,types,0);
	} else if((tmp = child_by_name.find(tree,ref_dcltr)) != NULL) {
		res = getTypeObject(tmp,decorate,types,0);
	} else if((tmp = child_by_name.find(tree,array_dcltr)) != NULL) {
		res = getTypeObject(tmp,decorate,types,0);
	} else if((tmp = child_by_name.find(tree,func_dcltr)) != NULL) {
		res = getTypeObject(tmp,decorate,types,0);
		decorate = false;
	}

	if(opName == ptr_dcltr && decorate) {
		res ="*" + res;;
	} else if(opName == ref_dcltr && decorate) {
		res ="&" + res;;
	} else if(opName == array_dcltr && decorate) {
		res ="[]" + res;
	} else if(opName == func_dcltr) {
		tmp = child_by_name.find(tree,"parenth_dcltr");
		if(tmp != NULL) {
			res = pointer_to_function.find(tmp,types);
			VTP_TreeP tmp1;
			tmp = VTP_TreeDown(tmp,0);
			if((tmp1 = child_by_name.find(tmp,ptr_dcltr)) != NULL) {
				res+= getTypeObject(tmp1,decorate,types,0);
			} else if((tmp1 = child_by_name.find(tmp,ref_dcltr)) != NULL) {
				res+= getTypeObject(tmp1,decorate,types,0);
			} else if((tmp1 = child_by_name.find(tmp,array_dcltr)) != NULL) {
				res+= getTypeObject(tmp1,decorate,types,0);
			}	
			return res;
		} else {
			return "<ERROR>";
		}
	}

	if(level && decorate) {
		tmp = VTP_TreeUp(VTP_TreeUp(tree));
		if(initdecls != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
			tmp = tree;
		}
		tmp = VTP_TreeLeft(tmp);
		res = base_type.find(tmp,types) + res;
	}

	return res;
}

std::string FindSignature::findVariable(VTP_TreeP &tree,std::vector<std::string> *types) {

	VTP_TreeP tmp_tree;
	std::string parm_decl = "parm_decl";
	bool decorated;
	
	//Check to see if it is a parameter or variable declaration
	tmp_tree = VTP_TreeUp(tree);
	if(parm_decl == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		tmp_tree = tree;
	} else {
		tmp_tree = VTP_TreeDown(tree,0);
	}

	decorated = true;
	return getTypeObject(tmp_tree,decorated,types);
}
