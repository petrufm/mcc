#include "DelayedDataExtractor.h"

DelayedDataExtractor::DelayedDataExtractor(DataExtractor *next,ConcreteTableColumn *prototype,TriggerCondition *condition):DataExtractor(next,prototype,condition) {}

DelayedDataExtractor::~DelayedDataExtractor() {}