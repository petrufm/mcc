#ifndef METRICSCALCULATION_H
#define METRICSCALCULATION_H

#include "Fast_Include.h"
#include <string>

class MetricCounter {

	public:
		int getValue();
		virtual void init();
		virtual void goIn(VTP_TreeP &tree);
		virtual void goOut(VTP_TreeP &tree);
		
	protected:
		int no,stop;
		virtual void visitIn(VTP_TreeP &tree) = 0;
		virtual void visitOut(VTP_TreeP &tree) = 0;
		virtual bool evaluateStopping(VTP_TreeP &tree) = 0;

};

class NoDecisions:public MetricCounter {

	protected:
		void visitIn(VTP_TreeP &tree);
		void visitOut(VTP_TreeP &tree);
		bool evaluateStopping(VTP_TreeP &tree);
};

class CountOperators:public MetricCounter {

	public:
		CountOperators(std::string op_name);

	protected:
		void visitIn(VTP_TreeP &tree);
		void visitOut(VTP_TreeP &tree);
		bool evaluateStopping(VTP_TreeP &tree);

	private:
		std::string op_name;

};

class MaxNesting:public MetricCounter {

	public:
		void init();

	protected:
		void visitIn(VTP_TreeP &tree);
		void visitOut(VTP_TreeP &tree);
		bool evaluateStopping(VTP_TreeP &tree);

	private:
		int current;
};

class CountStatement:public MetricCounter {

	protected:
		void visitIn(VTP_TreeP &tree);
		void visitOut(VTP_TreeP &tree);
		bool evaluateStopping(VTP_TreeP &tree);

};

class CountCodeLine:public MetricCounter {

	public:
		void init();

	protected:
		void visitIn(VTP_TreeP &tree);
		void visitOut(VTP_TreeP &tree);
		bool evaluateStopping(VTP_TreeP &tree);

	private:
		int last;
};

#endif //METAMODELEXTRACTOR_H