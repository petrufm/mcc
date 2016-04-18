#include "TemplateParameterId.h"
#include "TemplateArgumentAsType.h"
#include "ConcreteTableColumn.h"
#include "FindBaseType.h"
#include "TypesTable.h"
#include "SetOperations.h"

TemplateParameterId::TemplateParameterId(DataExtractor *next, ConcreteTableColumn *prototype, TemplateArgumentAsType *condition, TypesTable *types):DataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn *TemplateParameterId::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string value;
	std::string template_name = "template_name";
	std::vector<std::string> usedTypes;
	FindBaseType base_type;
	VTP_TreeP tmp_tree;
	int left_brothers = 0;

	//Find the name of the template
	tmp_tree = VTP_TreeUp(VTP_TreeUp(tree.tree));
	if(template_name == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		//We are in a template instance. Find the name of the class
		tmp_tree = VTP_TreeUp(tmp_tree);
		value = base_type.find(tmp_tree,&usedTypes);
		value = value.substr(0,value.find_first_of('<'));
		tmp_tree = tree.tree;
	} else {
		//We are in a template declaration with initializers. 
		//Find the name of the class
		tmp_tree = VTP_TreeDown(VTP_TreeRight(tmp_tree),0);
		value = base_type.find(tmp_tree,&usedTypes);
		tmp_tree = VTP_TreeUp(tree.tree);
	}
	//Find the position
	while((tmp_tree = VTP_TreeLeft(tmp_tree)) != NULL) {
		left_brothers++;
	}
	//Search the ID (class/struct/union, TypeName, IsGeneric)
	std::string kind1		= "class";
	std::string kind2		= "struct";
	std::string kind3		= "union";
	std::string kind4		= "class-in-func";
	std::string kind5		= "struct-in-func";
	std::string kind6		= "union-in-func";
	std::string template_par= "template-par";
	std::string typeName	= "TypeName";
	std::string isGeneric	= "IsGeneric";
	std::string generic		= "1";
	std::string kindOf		= "KindOf";
	std::string scopeID		= "ScopeID";
	std::string position	= "Position";
	Table::RowSet *set1,*set2,*set;
	SetOperations set_operation;
	int id;
	char buff[12];

	//Search for all generic classes
	set1 = types->find_set(typeName,value);
	set2 = types->find_set(isGeneric,generic);
	set = set_operation.intersection_op(set1,set2);
	delete set1;
	delete set2;

	//Set contains our class
	if(set->size() == 1) {
		id = types->find_id(*set->begin());
		delete set;
		//Now we know the id of the class.Find it's template parameters
		set1 = types->find_set(kindOf,template_par);
		sprintf(buff,"%d",id);
		value = buff;
		set2 = types->find_set(scopeID,value);
		set = set_operation.intersection_op(set1,set2);
		delete set1;
		delete set2;
		//Set contains all the template parameters. Find the corespondent
		sprintf(buff,"%d",left_brothers);
		value = buff;
		set1 = types->find_set(position,value);
		set2 = set_operation.intersection_op(set,set1);
		delete set1;
		delete set;
		//Set2 contains our template par
		if(set2->size() == 1) {
			id = types->find_id(*set2->begin());
			sprintf(buff,"%d",id);
			value = buff;
		} else {
			value = "<ERROR>";
		}
		delete set2;
	} else if(set->size() == 0) {
		value = "<UNKNOWN>";
		delete set;
	} else {
		value = "<ERROR>";
		delete set;
	}

	column->init(value,true);
	return column;
}
