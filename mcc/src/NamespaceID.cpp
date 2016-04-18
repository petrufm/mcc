#include "NamespaceID.h"
#include "ConcreteTableColumn.h"
#include "TriggerCondition.h"
#include "NamespaceTable.h"
#include "NamespaceName.h"
#include "Always.h"

NamespaceID::NamespaceID(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition, NamespaceTable *namespaces):DataExtractor(next,prototype,condition) {

	this->namespaces = namespaces;
	this->tmp_condition = new Always();
	this->lnkNamespaceName = new NamespaceName(NULL,prototype,tmp_condition);

}

NamespaceID::~NamespaceID() {

	delete tmp_condition;
	delete lnkNamespaceName;

}

TableColumn* NamespaceID::handleExtraction(AbstractTree &tree) {

	TableColumn *column = lnkNamespaceName->extract(tree);

	std::string name,search,value;
	int res;
	char buff[12];

	search = "NamespaceName";
	value = column->toString();
	if(value != "") {
		res = namespaces->find_id(search,value);
		if(res != -1) {
			sprintf(buff,"%d",res);
			name = buff;
		} else {
			name = "<ERROR>";
		}
	} else {
		name = "<NO_ONE>";
	}

	column->init(name,false);

	return column;
}
