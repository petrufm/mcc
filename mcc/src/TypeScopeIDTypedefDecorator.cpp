#include "TypeScopeIDTypedefDecorator.h"
#include "ConcreteTableColumn.h"
#include "TypedefDecorator.h"
#include "TypesTable.h"
#include "FindClassOfFunction.h"
#include "SetOperations.h"

TypeScopeIDTypedefDecorator::TypeScopeIDTypedefDecorator(DataExtractor *next, ConcreteTableColumn *prototype, TypedefDecorator *condition, TypesTable *types, BodyTable *bodies):DelayedDataExtractor(next,prototype,condition) {

	this->types = types;
	this->bodies = bodies;

}

TableColumn* TypeScopeIDTypedefDecorator::handleExtraction(AbstractTree &tree) {

	ProxyTableColumn* column;
	IContainer *info = new IContainer();
	VTP_TreeP tmp_tree;
	std::string class_op	= "class";
	std::string none		= "none";
	std::string qualified_id= "qualified_id";
	std::string identifier  = "identifier";
	std::string fndef		= "fndef";
	std::string compound	= "compound";
	std::string ctor_initializer = "ctor_initializer";
	std::string value1,value2,value3,value4;
	CIO_PositionS start;
	CIO_PositionS stop;
	char buff[12];

	//Search a ascendent called class
	tmp_tree = tree.tree;
	while(tmp_tree != NULL && 
		class_op != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
		fndef != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		tmp_tree = VTP_TreeUp(tmp_tree);
	}

	if(tmp_tree != NULL) {

		if(class_op == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			//Search identifier of the class
			tmp_tree = VTP_TreeDown(tmp_tree,0);
			if(identifier == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tmp_tree,1)))) {
				//When the definition is "class X {"
				value1 = VTP_NAME_VALUE(VTP_TreeAtomValue(VTP_TreeDown(tmp_tree,1)));
			} else if(qualified_id == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tmp_tree,1)))) {
				//When the definition is "class name_space::..::class_name::..::X {"
				tmp_tree = VTP_TreeDown(VTP_TreeDown(tmp_tree,1),1);
				value1 = VTP_NAME_VALUE(VTP_TreeAtomValue(tmp_tree));
			} else if(none == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tmp_tree,1)))) {
				//When the definition is "class {"
				value1 = "<ANONYMOUS>";
			}
			value2 = tree.file;
			VTP_TreeGetCoord(tmp_tree,&start,&stop);
			sprintf(buff,"%d",start.line);
			value3 = buff;
			value4 = "class";
		} else {
			//Search the body
			value2 = tree.file;
			tmp_tree = VTP_TreeDown(tmp_tree,3);
			if(compound != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
				if(ctor_initializer == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
					tmp_tree = VTP_TreeDown(tmp_tree,1);
				}
			}
			VTP_TreeGetCoord(tmp_tree,&start,&stop);
			sprintf(buff,"%d",start.line);
			value3 = buff;
			value4 = "function";
		}

	}

	info->push_back(value1);
	info->push_back(value2);
	info->push_back(value3);
	info->push_back(value4);

	column = new ProxyTableColumn(prototype->getName(),(ConcreteTableColumn*)prototype->clone(),this,info);
	return column;
}

bool TypeScopeIDTypedefDecorator::finalizeExtraction(TableColumn *column, IContainer *info) {

	std::string name		= (*info)[0];
	std::string file		= (*info)[1];
	std::string startline	= (*info)[2];
	std::string type		= (*info)[3];
	
	std::string value;
	char buff[12];
	int id;

	if(type == "") {
		
		value = "<NO_ONE>";

	} else if(type == "class") {
		
		//If it is in a class then we search by name,file,position (OK)
		Table::RowSet *set1,*set2,*set3,*set4,*set5;
		SetOperations set_operation;

		std::string typeName = "TypeName";
		std::string fileName = "FileName";
		std::string line = "StartPosition";

		set1 = types->find_set(typeName,name);	
		set2 = types->find_set(fileName,file);
		set3 = types->find_set(line,startline);
		set4 = set_operation.intersection_op(set1,set2);
		set5 = set_operation.intersection_op(set4,set3);

		delete set1;
		delete set2;
		delete set3; 
		delete set4;

		if(set5->size() == 1 &&  (id = types->find_id(*set5->begin())) > 0) {
			sprintf(buff,"%d",id);
			value = buff;
		} else {
			value = "<ERROR>";
		}
		delete set5;

	} else {

		//It is in a body
		Table::RowSet *set1,*set2,*set3;
		SetOperations set_operation;
		std::string fileName	= "FileName";
		std::string startLine	= "StartLine";

		set1 = bodies->find_set(fileName,file);
		set2 = bodies->find_set(startLine,startline);
		set3 = set_operation.intersection_op(set1,set2);
		delete set1;
		delete set2;
		if(set3->size() == 1) {
			id = bodies->find_id(*set3->begin());
			sprintf(buff,"%d",id);
			value = buff;
		} else {
			value = "<ERROR>";
		}
		delete set3;

	}

	column->init(value,false);
	return true;
}
