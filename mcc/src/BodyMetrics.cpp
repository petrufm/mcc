#include "BodyMetrics.h"
#include "ConcreteTableColumn.h"
#include "FuncBody.h"


BodyMetrics::BodyMetrics(DataExtractor *next, ConcreteTableColumn *prototype, FuncBody *condition):DataExtractor(next,prototype,condition) {

	metricSuite.push_back(new NoDecisions());
	metricSuite.push_back(new CountOperators("and"));
	metricSuite.push_back(new CountOperators("or"));
	metricSuite.push_back(new CountOperators("return"));
	metricSuite.push_back(new CountOperators("throw"));
	metricSuite.push_back(new CountOperators("handler"));
	metricSuite.push_back(new CountOperators("for"));
	metricSuite.push_back(new CountOperators("while"));
	metricSuite.push_back(new MaxNesting());
	metricSuite.push_back(new CountStatement());
	metricSuite.push_back(new CountCodeLine());

}

TableColumn* BodyMetrics::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	char buff[1000];
	std::string value;

	std::vector<MetricCounter*>::iterator i;
	for(i = metricSuite.begin(); i != metricSuite.end(); ++i) {
		(*i)->init();
	}

	count(tree.tree);

	int no_decisions	= metricSuite[0]->getValue();
	int no_and			= metricSuite[1]->getValue();
	int no_or			= metricSuite[2]->getValue();
	int no_return		= metricSuite[3]->getValue() + metricSuite[4]->getValue();
	int no_catch		= metricSuite[5]->getValue();
	int no_loops		= metricSuite[6]->getValue() + metricSuite[7]->getValue();
	int max_nesting		= metricSuite[8]->getValue();
	int no_statements	= metricSuite[9]->getValue();
	int no_code_line	= metricSuite[10]->getValue();

	sprintf(buff,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d",
		no_decisions,
		no_loops,
		no_and,
		no_or,
		no_decisions + no_loops + no_and + no_or + 1,
		no_return,
		no_catch,
		max_nesting,
		no_statements,
		no_code_line);
	value = buff;
	column->init(value,false);
	return column;
}

void BodyMetrics::count(VTP_TreeP &tree) {

	VTP_TreeP child;
	std::string op;

	std::vector<MetricCounter*>::iterator i;
	for(i = metricSuite.begin(); i != metricSuite.end(); ++i) {
		(*i)->goIn(tree);
	}

    ITERATOR_MAP(VTP_TreeChild, tree, child);{
		count(child);
	}
	ITERATOR_END_MAP(VTP_TreeChild);

	for(i = metricSuite.begin(); i != metricSuite.end(); ++i) {
		(*i)->goOut(tree);
	}
}

std::string& BodyMetrics::handleExtractionError() {
	static std::string fatal_error = "<ERROR>\t<ERROR>\t<ERROR>\t<ERROR>\t<ERROR>\t<ERROR>\t<ERROR>\t<ERROR>\t<ERROR>\t<ERROR>";
	return fatal_error;
}
