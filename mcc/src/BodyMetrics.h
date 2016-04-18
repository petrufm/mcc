#ifndef BODYMETRICS_H
#define BODYMETRICS_H

#include "DataExtractor.h"
#include "MetricsCalculation.h"

class ConcreteTableColumn;
class FuncBody;

class BodyMetrics : public DataExtractor {

public:

    BodyMetrics(DataExtractor *next, ConcreteTableColumn *prototype, FuncBody *condition);

protected:

    virtual TableColumn* handleExtraction(AbstractTree &tree);

	virtual std::string& handleExtractionError();

private:

	void count(VTP_TreeP &tree);

	std::vector<MetricCounter*> metricSuite;
};
#endif //BODYMETRICS_H