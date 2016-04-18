#include "MetricsCalculation.h"

//Metric Counter definition
void MetricCounter::init() {
	no = stop = 0;
}

int MetricCounter::getValue() {
	return no;
}

void MetricCounter::goIn(VTP_TreeP &tree) {
	if(evaluateStopping(tree)) {
		stop++;
	}
	if(!stop) {
		visitIn(tree);
	}
}

void MetricCounter::goOut(VTP_TreeP &tree) {
	if(evaluateStopping(tree)) {
		stop--;
	}
	if(!stop) {
		visitOut(tree);
	}
}


//NoDecision definition
void NoDecisions::visitIn(VTP_TreeP &tree) {

	std::string op = VTP_OP_NAME(VTP_TREE_OPERATOR(tree));
	VTP_TreeP brother;
	
	if(op == "if") {
		no++;
	} else if(op == "cond") {
		no++;
	} else if(op == "case") {
		brother = VTP_TreeLeft(tree);
		if(brother != NULL) {
			op = VTP_OP_NAME(VTP_TREE_OPERATOR(brother));
			if(op != "case") {
				no++;
			} else {
				no++;
			}
		}
	}
}

void NoDecisions::visitOut(VTP_TreeP &tree) {}

bool NoDecisions::evaluateStopping(VTP_TreeP &tree) {
	
	std::string op = VTP_OP_NAME(VTP_TREE_OPERATOR(tree));
	return op == "class";
}

//CountOperators definition
CountOperators::CountOperators(std::string op_name) {
	this->op_name = op_name;
}

void CountOperators::visitIn(VTP_TreeP &tree) {

	std::string op = VTP_OP_NAME(VTP_TREE_OPERATOR(tree));
	if(op == op_name) {
		no++;
	}
}

void CountOperators::visitOut(VTP_TreeP &tree) {}

bool CountOperators::evaluateStopping(VTP_TreeP &tree) {
	
	std::string op = VTP_OP_NAME(VTP_TREE_OPERATOR(tree));
	return op == "class";
}

//MaxNesting definition
void MaxNesting::init() {
	no = stop = current = 0;
}

void MaxNesting::visitIn(VTP_TreeP &tree) {

	std::string op = VTP_OP_NAME(VTP_TREE_OPERATOR(tree));
	if(op == "compound") {
		current++;
		if(current > no) {
			no = current;
		}
	}
}

void MaxNesting::visitOut(VTP_TreeP &tree) {
	std::string op = VTP_OP_NAME(VTP_TREE_OPERATOR(tree));
	if(op == "compound") {
		current--;
	}
}

bool MaxNesting::evaluateStopping(VTP_TreeP &tree) {
	
	std::string op = VTP_OP_NAME(VTP_TREE_OPERATOR(tree));
	return op == "class";
}


//CountStatement definition
void CountStatement::visitIn(VTP_TreeP &tree) {

	std::string up_op = VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeUp(tree)));
	std::string op = VTP_OP_NAME(VTP_TREE_OPERATOR(tree));
	if(op != "compound" && up_op == "stmts") {
		no++;
	}
}

void CountStatement::visitOut(VTP_TreeP &tree) {}

bool CountStatement::evaluateStopping(VTP_TreeP &tree) {
	
	std::string op = VTP_OP_NAME(VTP_TREE_OPERATOR(tree));
	return op == "class";
}

//CountCodeLines definition
void CountCodeLine::init() {
	no = stop = 0;
	last = -1;
}

void CountCodeLine::visitIn(VTP_TreeP &tree) {

	CIO_PositionS start;
	CIO_PositionS stop;

	std::string op = VTP_OP_NAME(VTP_TREE_OPERATOR(tree));
	VTP_TreeGetCoord(tree,&start,&stop);
	if((op == "compound" || op == "stmts") && no == 0) {
		return;
	}
	if(last != start.line) {
		no++;
	}
	last = start.line;
}

void CountCodeLine::visitOut(VTP_TreeP &tree) {}

bool CountCodeLine::evaluateStopping(VTP_TreeP &tree) { return false;}
