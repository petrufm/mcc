#include "DataExtractor.h"
#include "Always.h"
#include <iostream>

DataExtractor::DataExtractor(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition) {

	this->next = next;
	this->prototype = prototype;
	this->condition = condition;
	if(this->condition == NULL) {
		this->condition = new Always();
	}

}

DataExtractor::~DataExtractor() {}

std::string& DataExtractor::handleExtractionError() {
	static std::string fatal_error = "<ERROR>";
	return fatal_error;
}

TableColumn* DataExtractor::protectedExecution(DataExtractor *t, AbstractTree &tree, ConcreteTableColumn *prot) {
	TableColumn *cell;
	//TODO:Can this be made compiler independent?
	//__try {
		cell = t->handleExtraction(tree);
	//} __except(EXCEPTION_EXECUTE_HANDLER) {
	//	cell = prot->clone();
	//	cell->init(t->handleExtractionError(),false);
	//	CIO_PositionS start;
	//	CIO_PositionS stop;
	//	char buff[12];
	//	VTP_TreeGetCoord(tree.tree,&start,&stop);
	//	sprintf(buff,"%d",start.line);
	//	cout << endl << " - unpredicted error caught in extractor: " << tree.file.c_str() << '@' << start.line << flush << endl;
	//}
	return cell;
}

TableColumn* DataExtractor::extract(AbstractTree &tree){

	if(canHandle(tree)) {

		#ifdef _DEBUG
			CIO_PositionS start;
			CIO_PositionS stop;
			char buff[12];
			VTP_TreeGetCoord(tree.tree,&start,&stop);
			sprintf(buff,"%d",start.line);
			cout << "Triggered:" << tree.file.c_str() << '@' << start.line << endl;
		#endif

		return protectedExecution(this,tree,prototype);

	} else if(next == NULL) {

		std::string value;
		value = "NULL";

		TableColumn *column = prototype->clone();

		column->init(value,false);

		return column;

	} else {
		
		return next->extract(tree);

	}

}

bool DataExtractor::canHandle(AbstractTree &tree) {

	return condition->isTriggered(tree);

}
