#include "FunctionScopeId.h"
#include "ConcreteTableColumn.h"
#include "TypesTable.h"
#include "FuncDeclaration.h"
#include "SetOperations.h"
#include "FindClassOfFunction.h"
#include "FindBaseType.h"

FunctionScopeId::FunctionScopeId(DataExtractor *next, ConcreteTableColumn *prototype, FuncDeclaration *condition, TypesTable *types):DataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn *FunctionScopeId::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	std::string class_op = "class";
	std::string value,file,line;
	VTP_TreeP tmp_tree,tmp;
	SetOperations set_operation;
	std::string identifier		= "identifier";
	std::string qualified_id	= "qualified_id";
	std::string none			= "none";
	CIO_PositionS start,stop;
	int id;
	char buff[12];

	//Find the name of the class (if exists) that includes this class definition
	//its file and start position
	tmp_tree = tree.tree;
	do {
		tmp_tree = VTP_TreeUp(tmp_tree);
	} while(tmp_tree != NULL && class_op != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)));
	if(tmp_tree != NULL) {
		//This declaration is included in a class declaration
		FindBaseType base_type;
		std::vector<std::string> usedTypes;
		tmp = VTP_TreeUp(tmp_tree);
		value = base_type.find(tmp,&usedTypes);		
		file = tree.file;
		VTP_TreeGetCoord(tmp_tree,&start,&stop);
		sprintf(buff,"%d",start.line);
		line = buff;

		//Search the ID of the class
		Table::RowSet *set1,*set2,*set3;
		std::string typeName = "TypeName";
		std::string fileName = "FileName";
		std::string startPos = "StartPosition";
		set1 = types->find_set(typeName,value);
		set2 = types->find_set(fileName,file);
		set3 = set_operation.intersection_op(set1,set2);
		delete set1;
		delete set2;
		set1 = types->find_set(startPos,line);
		set2 = set_operation.intersection_op(set1,set3);
		delete set1;
		delete set3;
		if(set2->size() == 1) {
			id = types->find_id(*set2->begin());
			sprintf(buff,"%d",id);
			value = buff;
		} else {
			value = "<ERROR>";
		}
		delete set2;
	} else {
		//This declaration is not included in a class declaration
		//Check to see if this is a definition of a function
		FindClassOfFunction myClass;
		if((value = myClass.find(tree.tree,true)) != "") {
			value = myClass.find(value,types);
		} else {
			value = "<NO_ONE>";
		}
	}

	column->init(value,true);
	return column;
}