#include "TypeScopeIDTemplateParameter.h"
#include "SetOperations.h"

TypeScopeIDTemplateParameter::TypeScopeIDTemplateParameter(DataExtractor *next, ConcreteTableColumn *prototype, ClassTemplateParameter *condition, TypesTable *types):DelayedDataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn* TypeScopeIDTemplateParameter::handleExtraction(AbstractTree &tree) {

	ProxyTableColumn* column;
	IContainer *info = new IContainer();
	VTP_TreeP tmp_tree;
	std::string identifier = "identifier";
	std::string value1,value2,value3;
	CIO_PositionS start;
	CIO_PositionS stop;
	char buff[12];

	//It the name of the template class has scope this doesn't work
	tmp_tree = VTP_TreeDown(VTP_TreeDown(VTP_TreeDown(VTP_TreeDown(VTP_TreeRight(VTP_TreeUp(tree.tree)),0),0),0),1);

	if(identifier == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		value1 = VTP_NAME_VALUE(VTP_TreeAtomValue(tmp_tree));
	} else {
		value1 = "<ANONYMOUS>";
	}

	tmp_tree = VTP_TreeUp(tmp_tree);

	value2 = tree.file;
	VTP_TreeGetCoord(tmp_tree,&start,&stop);
	sprintf(buff,"%d",start.line);
	value3 = buff;

	info->push_back(value1);
	info->push_back(value2);
	info->push_back(value3);

	column = new ProxyTableColumn(prototype->getName(),(ConcreteTableColumn*)prototype->clone(),this,info);
	return column;
}

bool TypeScopeIDTemplateParameter::finalizeExtraction(TableColumn *column, IContainer *info) {

	std::string name	= (*info)[0];
	std::string file	= (*info)[1];
	std::string startline	= (*info)[2];
	
	std::string value;
	char buff[12];
	int id;

	Table::RowSet *set1,*set2,*set3,*set4,*set5;
	SetOperations set_operation;

	//Search for a class with known name and in a file and at an exact line (OK)
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
	column->init(value,false);
	return true;
}
