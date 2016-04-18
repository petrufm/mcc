#include "NamespaceName.h"

NamespaceName::NamespaceName(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition):DataExtractor(next,prototype,condition) {}

TableColumn* NamespaceName::handleExtraction(AbstractTree &tree) {

	TableColumn *column = prototype->clone();
	column->init(doIt(tree),true);
	return column;
}

std::string NamespaceName::doIt(AbstractTree &tree) {

	VTP_TreeP tmp_tree;
	VTP_AtomP atom;

	std::string operatorName, name, tmp;
	std::string operatorNamespace = "namespace_def";

	AbstractTree up;

	if (operatorNamespace == VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree))) {
		tmp_tree = VTP_TreeDown(tree.tree,0);
		operatorName = VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree));
		if (operatorName == "none") {
			name = "<ANONYMOUS>";
		} else {
			atom = VTP_TreeAtomValue(tmp_tree);
			name = VTP_NAME_STRING(atom);
		}
	}

	tmp_tree = tree.tree;
	do {
		tmp_tree = VTP_TreeUp(tmp_tree);
	} while ((tmp_tree != NULL) && (operatorNamespace != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))));

	if(tmp_tree != NULL) {
		up.file = tree.file;
		up.tree = tmp_tree;
		tmp = doIt(up);
		if (tmp != "") {
			if(name != "") {
				name = tmp + "::" + name;
			} else {
				name = tmp;
			}
		}
	}

	return name;
}
