#include "DecoratedTypeTypedefDecorator.h"
#include "TypedefDecorator.h"
#include "ConcreteTableColumn.h"
#include "TypesTable.h"
#include "FindDecoratedType.h"
#include "FindClassContext.h"
#include "SetOperations.h"
#include "FindChildByName.h"

DecoratedTypeTypedefDecorator::DecoratedTypeTypedefDecorator(DataExtractor *next, ConcreteTableColumn *prototype, TypedefDecorator *condition, TypesTable *types):DelayedDataExtractor(next,prototype,condition) {

	this->types = types;

}

TableColumn* DecoratedTypeTypedefDecorator::handleExtraction(AbstractTree &tree) {

	ProxyTableColumn* column;
	IContainer *info = new IContainer();
	std::string value,value1,value2;
	FindDecoratedType decorated_type;
	FindClassContext context;
	std::vector<std::string> usedTypes;
	std::string declaration_specifiers = "declaration_specifiers";

	value  = decorated_type.find(tree.tree,&usedTypes);
	value1 = context.find(tree.tree);
	value2 = "";

	if(value == "<ANONYMOUS>") {
		//Memorize the position
		VTP_TreeP tmp_tree,tmp;
		FindChildByName childName;

		tmp_tree = VTP_TreeUp(tree.tree);
		do {
			tmp = tmp_tree;
			do {
				tmp = VTP_TreeLeft(tmp);
			} while(tmp != NULL && declaration_specifiers != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)));
			if(tmp != NULL) {
				tmp = childName.find(tmp,"class");
				if(tmp != NULL) {
					tmp = VTP_TreeDown(tmp,0);
					CIO_PositionS start;
					CIO_PositionS stop;
					char buff[12];

					VTP_TreeGetCoord(tmp,&start,&stop);
					sprintf(buff,"%d",start.line);
					value2 = buff;
				}
				break;
			}
			tmp_tree = VTP_TreeUp(tmp_tree);
		} while(tmp_tree != NULL);
	}

	info->push_back(value);
	info->push_back(value1);
	info->push_back(value2);
	info->push_back(tree.file);

	for(std::vector<std::string>::iterator i = usedTypes.begin(); i != usedTypes.end(); ++i) {
		info->push_back(*i);
	}

	column = new ProxyTableColumn(prototype->getName(),(ConcreteTableColumn*)prototype->clone(),this,info);
	return column;
}

bool DecoratedTypeTypedefDecorator::finalizeExtraction(TableColumn *column, IContainer *info) {

	std::string type_name	= (*info)[0];
	std::string value;
	std::string value1		= (*info)[1];
	std::string value2		= (*info)[2];
	std::string value3		= (*info)[3];
	std::vector<std::string> usedTypes;
	FindClassContext context;
	SetOperations set_operations;
	char buff[12];
	int id;

	Table::RowSet *set,*set1,*set2,*set3;

	//Continue with searching
	for(IContainer::iterator i = info->begin() + 4; i!=info->end(); ++i) {
		usedTypes.push_back(*i);
	}

	value = context.find(value1,&usedTypes,types);

	if(value == "<?>") {
		return false;
	}

	std::string typeName = "TypeName";
	set = types->find_set(typeName,type_name);
	
	//If the name is anonymous then is has to be defined after typedef (we know where)
	if(type_name == "<ANONYMOUS>" && value2 != "") {
		std::string fileName = "FileName";
		std::string filePos  = "StartPosition";
		set1 = types->find_set(fileName,value3);
		set2 = types->find_set(filePos,value2);
		set3 = set_operations.intersection_op(set1,set2);
		delete set1;
		delete set2;
		set1 = set_operations.intersection_op(set,set3);
		delete set;
		delete set3;
		set = set1;
	}

	//We have to eliminate this row from the search
	TableRow *the_row = column->getRow();
	set1 = set_operations.difference_op(set,the_row);
	delete set;
	set = set1;
	
	//Search the typeId
	if(set->size() == 1 &&  (id = types->find_id(*set->begin())) > 0) {
		delete set;
		sprintf(buff,"%d",id);
		value = buff;
	} else if(set->size() == 0) {
		delete set;
		return false;
	} else {
		std::string con = "Context";
		set1 = types->find_set(con,value);
		set2 = set_operations.intersection_op(set,set1);
		delete set;
		delete set1;
		if(set2->size() == 1 &&  (id = types->find_id(*set2->begin())) > 0) {
			delete set2;
			sprintf(buff,"%d",id);
			value = buff;
		} else if(set2->size() == 0) {
			delete set2;
			return false;
		} else {
			delete set2;
			value = "<ERROR>";
		}
	}

	column->init(value,false);

	return true;
}