#include "FilePositionStart.h"
#include <stdio.h>

FilePositionStart::FilePositionStart(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition):DataExtractor(next,prototype,condition) {}

TableColumn* FilePositionStart::handleExtraction(AbstractTree &tree) {

	CIO_PositionS start;
	CIO_PositionS stop;
	char buff[12];

	VTP_TreeGetCoord(tree.tree,&start,&stop);
	sprintf(buff,"%d",start.line);

	TableColumn *column = prototype->clone();
	column->init(std::string(buff),false);
	return column;

}
