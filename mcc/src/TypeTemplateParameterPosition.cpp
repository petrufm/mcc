#include "TypeTemplateParameterPosition.h"
#include "ClassTemplateParameter.h"
#include "ConcreteTableColumn.h"

TypeTemplateParameterPosition::TypeTemplateParameterPosition(DataExtractor *next, ConcreteTableColumn *prototype, ClassTemplateParameter *condition):DataExtractor(next,prototype,condition) {}

TableColumn* TypeTemplateParameterPosition::handleExtraction(AbstractTree &tree) {

	TableColumn* column = prototype->clone();
	VTP_TreeP tmp_tree;
	int left_brothers = 0;
	char buff[12];
	std::string value;

	tmp_tree = tree.tree;
	while((tmp_tree = VTP_TreeLeft(tmp_tree)) != NULL) {
		left_brothers++;
	}
	
	sprintf(buff,"%d",left_brothers);
	value = buff;
	column->init(value,false);
	return column;
}


