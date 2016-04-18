#include "FindClassContext.h"
#include "TypesTable.h"
#include "SetOperations.h"
#include "FindClassOfFunction.h"

int FindClassContext::error_no = 0;

std::string FindClassContext::find(VTP_TreeP &tree) {

	std::string class_op		= "class";
	std::string identifier		= "identifier";
	std::string qualified_id	= "qualified_id";
	std::string none			= "none";
	std::string fndef			= "fndef";
	std::string func_dcltr		= "func_dcltr";
	std::string value;

	VTP_TreeP tmp_tree;

	//Find the class name that includes this declaration
	tmp_tree = tree;
	while(tmp_tree != NULL && class_op != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		tmp_tree = VTP_TreeUp(tmp_tree);
	}

	if(tmp_tree != NULL) {
		//Search identifier of the class
		tmp_tree = VTP_TreeDown(tmp_tree,0);
		if(identifier == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tmp_tree,1)))) {
			//When the definition is "class X {"
			value = VTP_NAME_VALUE(VTP_TreeAtomValue(VTP_TreeDown(tmp_tree,1)));
		} else if(qualified_id == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tmp_tree,1)))) {
			//When the definition is "class name_space::..::class_name::..::X {"
			tmp_tree = VTP_TreeDown(VTP_TreeDown(tmp_tree,1),1);
			value = VTP_NAME_VALUE(VTP_TreeAtomValue(tmp_tree));
		} else if(none == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tmp_tree,1)))) {
			//When the definition is "class {"
			value = "<ANONYMOUS>";
		}

	} else {

		//Find the function and then the scope
		FindClassOfFunction myclass;
		value = myclass.find(tree,false);
	}

	return value;
}

std::string FindClassContext::find(std::string class_name, std::vector<std::string> *usedTypes, TypesTable *types) {

	std::string kind7 = "template-par";

	Table::RowSet *set1,*set2,*set3,*set;
	std::string typeName	= "TypeName";
	std::string kindOf		= "KindOf";
	std::string isGeneric	= "IsGeneric";
	std::string generic		= "1";
	std::string value;
	SetOperations set_operation;
	int id;
	char buff[12];

	//Search for context generic classes(because the context class must be here)
	set1 = types->find_set(typeName,class_name);
	set2 = types->find_set(isGeneric,generic);
	set = set_operation.intersection_op(set1,set2);
	delete set1;
	delete set2;
	if(set->size() == 0) {
		value = "<NONE>";
	} else if(set->size() != 1) {
		sprintf(buff,"%d",error_no++);
		value = "<ERROR>";
		value+=buff;
	} else if((id = types->find_id(*set->begin())) > 0) {
		//We founded its id
		//Now check to see if there is a used type that is template parameter for this class
		std::string scope = "ScopeID",tmp;
		std::string not_init = "<NOT_INIT>";
		set1 = types->find_set(scope,not_init);
		set2 = types->find_set(kindOf,kind7);
		set3 = set_operation.intersection_op(set1,set2);
		if(set3->size() == 0) {
			//All template parameters are initialised
			delete set1;
			delete set3;
			sprintf(buff,"%d",id);
			tmp = buff;
			set1 = types->find_set(scope,tmp);
			set3 = set_operation.intersection_op(set1,set2);
			delete set1;
			delete set2;
			std::vector<std::string>::iterator i;
			i = usedTypes->begin();
			value = "<NONE>";
			while(i != usedTypes->end()) {
				set1 = types->find_set(typeName,(*i));
				set2 = set_operation.intersection_op(set1,set3);
				delete set1;
				if(set2->size() == 1) {
					delete set2;
					value = class_name;
					break;
				}
				delete set2;
				++i;
			}
		} else {
			delete set1;
			delete set2;
			delete set3;
			value = "<?>";
		}		
	} else {
		sprintf(buff,"%d",error_no++);
		value = "<ERROR>";
		value+=buff;
	}

	delete set;
	return value;
}
