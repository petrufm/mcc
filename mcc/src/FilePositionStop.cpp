#include "FilePositionStop.h"
#include <stdio.h>

FilePositionStop::FilePositionStop(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition, int levelUp):DataExtractor(next,prototype,condition) {
	this->levelUp = levelUp;
}

TableColumn* FilePositionStop::handleExtraction(AbstractTree &tree) {

	VTP_TreeP tmp;
	CIO_PositionS start;
	CIO_PositionS stop;
	char buff[12];
	int level = levelUp;

	tmp = tree.tree;
	while(level != 0) {
		tmp = VTP_TreeUp(tmp);
		level--;
	}
	VTP_TreeGetCoord(tmp,&start,&stop);
	sprintf(buff,"%d",stop.line);

	TableColumn *column = prototype->clone();
	column->init(std::string(buff),false);
	return column;

}
