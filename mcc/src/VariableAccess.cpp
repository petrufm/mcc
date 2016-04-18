#include "VariableAccess.h"

VariableAccess::VariableAccess() {

	//Simple expresion
	op_table.insert("pmap");
	op_table.insert("pmpp");
	op_table.insert("throw");
	op_table.insert("plus");
	op_table.insert("minus");
	op_table.insert("mul");
	op_table.insert("div");
	op_table.insert("rem");
	op_table.insert("lsh");
	op_table.insert("rsh");
	op_table.insert("lt");
	op_table.insert("gt");
	op_table.insert("ge");
	op_table.insert("le");
	op_table.insert("eq");
	op_table.insert("neq");
	op_table.insert("bwand");
	op_table.insert("bwor");
	op_table.insert("bwxor");
	op_table.insert("and");
	op_table.insert("or");
	op_table.insert("cond");
	op_table.insert("ass");
	op_table.insert("plus_ass");
	op_table.insert("minus_ass");
	op_table.insert("mul_ass");
	op_table.insert("div_ass");
	op_table.insert("rem_ass");
	op_table.insert("bwand_ass");
	op_table.insert("bwxor_ass");
	op_table.insert("bwor_ass");
	op_table.insert("lsh_ass");
	op_table.insert("rsh_ass");

	//Unary
	op_table.insert("cast");
	op_table.insert("deref");
	op_table.insert("addr");
	op_table.insert("uminus");
	op_table.insert("uplus");
	op_table.insert("pre_incr");
	op_table.insert("pre_decr");
	op_table.insert("bwnot");
	op_table.insert("not");
	op_table.insert("size_of");
	op_table.insert("delete");
	op_table.insert("global_scope_delete");
	op_table.insert("array_delete");
	op_table.insert("global_scope_array_delete");

	//Primary
	op_table.insert("parenth_expr");
	op_table.insert("index");
	op_table.insert("dot");
	op_table.insert("arrow");
	op_table.insert("post_incr");
	op_table.insert("post_decr");
	op_table.insert("dynamic_cast");
	op_table.insert("static_cast");
	op_table.insert("reinterpret_cast");
	op_table.insert("const_cast");
	op_table.insert("typeid");

	//Stm
	op_table.insert("if");
	op_table.insert("while");
	op_table.insert("do");
	op_table.insert("for");
	op_table.insert("switch");
	op_table.insert("return");
	op_table.insert("case");
	op_table.insert("expr_stmt");

	//Others
	op_table.insert("exprlist");
	op_table.insert("expr");
	op_table.insert("dcltr_affinit");
	op_table.insert("initializer_list");
	op_table.insert("bit_field");
	op_table.insert("parm_decl");
	op_table.insert("typeof");
	op_table.insert("enumerator");
	op_table.insert("array_dcltr");
	op_table.insert("new_gnu_type");
}

bool VariableAccess::isTriggered(AbstractTree &tree){

	std::string identifier   = "identifier";
	std::string scope	     = "scope";
	std::string qualified_id = "qualified_id";
	std::string call		 = "call";
	std::string value;

	VTP_TreeP tmp_tree,the_id;

	//It has to be an identifier
	if(identifier != VTP_OP_NAME(VTP_TREE_OPERATOR(tree.tree))) {
		return false;
	}

	//NOW IT HAS TO REPRESENT A VARIABLE
	//Fist it must not have a scope parent
	tmp_tree = VTP_TreeUp(tree.tree);
	the_id = tree.tree;
	if(scope == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		return false;
	}

	//If its parent is qualified_id go one step up
	if(qualified_id == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		the_id = tmp_tree;
		tmp_tree = VTP_TreeUp(tmp_tree);
	}
	
	//This operator must be in op_table
	value = VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree));
	if(op_table.find(value) != op_table.end()) {

		//But for some operators there are other conditions
		if(value == "dcltr_affinit" && VTP_TreeRank(the_id) == 0) {
			return false;
		}
		if(value == "bit_field" && VTP_TreeRank(the_id) == 0) {
			return false;
		}
		if(value == "parm_decl" && VTP_TreeRank(the_id) != 2) {
			return false;
		}
		if(value == "enumerator" && VTP_TreeRank(the_id) != 1) {
			return false;
		}
		if(value == "array_dcltr" && VTP_TreeRank(the_id) != 1) {
			return false;
		}

		//It shouldn't be a function call
		if((value == "dot" || value == "arrow") && VTP_TreeRank(the_id) == 1 &&
			call == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeUp(tmp_tree)))) {
			return false;
		}

		//It has to be in an function body
		if(!isInBody(tree.tree)) {
			return false;
		}

		//For the moment macros are difficult to handle
		//All variable with an identifier made only with caps are eliminated
		bool all_caps = true;
		value = VTP_NAME_STRING(VTP_TreeAtomValue(tree.tree));
		if(value.size() > 1) {
			for(int i = 0; i < strlen(value.c_str()); i++) {
				if(isalpha(value.at(i)) && islower(value.at(i))) {
					all_caps = false;
					break;
				}
			}
			if(all_caps) {
				return false;
			}
		}

		return true;

	} else {
		
		return false;
	
	}
}
