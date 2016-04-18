#include "IdentifyFunction.h"
#include "TypesTable.h"
#include "NamespaceTable.h"
#include "BodyTable.h"
#include "SetOperations.h"
#include "FuncsTable.h"
#include "FindBaseType.h"
#include "IdentifyVariable.h"
#include "VariablesTable.h"
#include "FindSignature.h"
#include "InheritanceTable.h"
#include "TemplateParTypesRelation.h"

#include <cstdlib>

IdentifyFunction::IdentifyFunction(
		VariablesTable *vars,
		BodyTable *bodies, 
		FuncsTable *funcs,
		TypesTable *types,
		InheritanceTable *inh,
		NamespaceTable *namespaces,
		TemplateParTypesRelation *tp2t) {

	this->vars = vars;
	this->bodies = bodies;
	this->funcs = funcs;
	this->types = types;
	this->inh = inh;
	this->namespaces = namespaces;
	this->tp2t		 = tp2t;
	this->identifVar = new IdentifyVariable(vars,bodies,funcs,types,inh,namespaces,tp2t);

	reset = true;
}

IdentifyFunction::~IdentifyFunction() {
	delete identifVar;
}

void IdentifyFunction::setReset() {
	reset = true;
	identifVar->setReset();
}

std::string IdentifyFunction::findFunction(AbstractTree &tree, std::vector<std::string> &calledFunctions) {

	std::string dot			 = "dot";
	std::string arrow		 = "arrow";
	std::string qualified_id = "qualified_id";
	std::string global_scope = "global_scope";
	std::string destructor	 = "destructor";
	std::string operator_op	 = "operator";
	std::string identifier	 = "identifier";
	std::string type_id		 = "type_id";
	std::string parenth_expr = "parenth_expr";
	std::string deref		 = "deref";
	std::string pmap		 = "pmap";
	std::string pmpp		 = "pmpp";

	std::vector<std::string> signature,usedTypes;
	FindSignature the_type;
	VTP_TreeP tmp_tree,child;

	//Fill this_bodyId,this_namespaceName,this_classId
	if(reset) {
		fillVars(tree);
		reset = false;
	}

	//Check for signature
	inferSignature(tree,signature);

	//Search the name
	tmp_tree = VTP_TreeDown(tree.tree,0);
	bool	stop,isP2F;
	std::string qualified,func_name,type,value,last_qualified;

	stop  = isP2F = false;
	qualified = type = last_qualified = "";

	do {

		if(identifier == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			func_name = VTP_NAME_STRING(VTP_TreeAtomValue(tmp_tree));
			stop = true;
		} else if(destructor == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			func_name = "~";
			func_name+= VTP_NAME_STRING(VTP_TreeAtomValue(VTP_TreeDown(tmp_tree,0)));
			stop = true;
		} else if(operator_op == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
			if(type_id != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
				func_name = "<";
				func_name+= VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree));
				func_name+= ">";
			} else {
				func_name = "<";
				func_name+= the_type.findElement(tmp_tree,&usedTypes);
				func_name+= ">";
			}
			stop = true;
		} else if(qualified_id == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
			if(global_scope == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
				VTP_TreeDown(tmp_tree,0) == NULL) {
				qualified = "::";
			} else {
				ITERATOR_MAP(VTP_TreeChild, tmp_tree, child); {
					if(qualified != "") qualified += "::";
					last_qualified = VTP_NAME_STRING(VTP_TreeAtomValue(child));
					qualified+= last_qualified;

				}
				ITERATOR_END_MAP(VTP_TreeChild);
			}
			tmp_tree = VTP_TreeDown(VTP_TreeUp(tmp_tree),1);
		} else if(parenth_expr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) ||
					deref == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			tmp_tree = VTP_TreeDown(tmp_tree,0);
		} else if(pmap == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) ||
			pmpp == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			isP2F = true;
			type = findType(tree.directory,tree.file,tmp_tree);
			stop = true;
		} else if(dot == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) || 
					arrow == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			type = findType(tree.directory,tree.file,VTP_TreeDown(tmp_tree,0));
			tmp_tree = VTP_TreeDown(tmp_tree,1);
		} else {
			func_name = "<ERROR>";
			stop = true;
		}
	
	} while(!stop);
	
	std::string typeName = "TypeName";
	std::string funcName = "FuncName";
	std::string kindOf   = "KindOf";
	Table::RowSet *set1,*set2,*set3;
	SetOperations set_operation;
	char buff[12];

	//Now search for function
	if(isP2F) {
		
		//We can be sure that the access is to a pointer to function
		//Skip decoration
		if(type == "<ERROR>") return this_bodyId;
		type = eliminateDecoration(type);
		//This must be a p2f type
		if(type == "<ERROR>") return this_bodyId;
		value = types->getColumnValue(atoi(type.c_str()),kindOf); 
		if(value != "pointer-to-function") return this_bodyId;
		//Search name
		type = types->getColumnValue(atoi(type.c_str()),typeName);
		//Search function
		if(type == "<ERROR>") return this_bodyId;
		set1 = funcs->find_set(funcName,type);
		if(set1->size() == 1) {
			sprintf(buff,"%d",funcs->find_id(*set1->begin()));
			calledFunctions.push_back(buff);
		}
		delete set1;

	} else {
		
		//Find all the possible functions
		//Name + Parameters
		std::string parameters = "Parameters";
		std::string kindOfCol  = "real-function";
		std::string func_id;
		Table::RowSet *possibleFuncs,*called;
		std::map<TableRow*,int>  scores;
		int min,max,score;
		set1 = funcs->find_set(funcName,func_name);
		set2 = funcs->find_set(kindOf,kindOfCol);
		set3 = set_operation.intersection_op(set1,set2);
		delete set1;
		delete set2;
		possibleFuncs = new Table::RowSet();
		called = new Table::RowSet();
		
		for(Table::RowSet::iterator i = set3->begin();i!=set3->end();++i) {
			sscanf(funcs->getColumnValue(funcs->find_id(*i),parameters).c_str(),"%d %d",&min,&max);
			sprintf(buff,"%d", funcs->find_id(*i));
			func_id = buff;
			if(min <= signature.size() && signature.size() <= max) {
 				score = computeScore(func_id,signature);
				possibleFuncs->insert(*i);
				scores[*i] = score;
			}
		}
		delete set3;
		
		//PossibleFuncs contains all the function with the requested name
		//and with a compatible parameter numbers		
		if(qualified != "" ) {

			if(qualified == "::") {

				//Search at global scope
				qualified = "";
				findGlobalFunc(possibleFuncs,scores,called,false,qualified);

			} else {

				//Search the last element of qualified
				std::string classId;
				set1 = types->find_set(typeName,last_qualified);
				if(set1->size() == 1) {
					sprintf(buff,"%d",types->find_id(*set1->begin()));
					classId = buff;
					findRelativeMeth(possibleFuncs,scores,called,classId);
					if(called->size() == 0 || scores[*called->begin()] != 100) {
						findGlobalFunc(possibleFuncs,scores,called,true,qualified);
					}
				} else if(set1->size() == 0) {
					findGlobalFunc(possibleFuncs,scores,called,true,qualified);
				}
				delete set1;
			}

			for(Table::RowSet::iterator i = called->begin();i!=called->end();++i) {
				sprintf(buff,"%d",funcs->find_id(*i));
				calledFunctions.push_back(buff);
			}

		
		} else if(type != "") {

			//We have an dot/arrow access
			type = eliminateDecoration(type);
			findRelativeMeth(possibleFuncs,scores,called,type);

			for(Table::RowSet::iterator i = called->begin();i!=called->end();++i) {
				sprintf(buff,"%d",funcs->find_id(*i));
				calledFunctions.push_back(buff);
			}

		} else {

			//We have a simple access
			findRelativeMeth(possibleFuncs,scores,called,this_classId);
			if(called->size() == 0 || scores[*called->begin()] != 100) {
				findGlobalFunc(possibleFuncs,scores,called,true,qualified);
			}

			for(Table::RowSet::iterator i = called->begin();i!=called->end();++i) {
				sprintf(buff,"%d",funcs->find_id(*i));
				calledFunctions.push_back(buff);
			}

		}

		if(called->size() == 0 && possibleFuncs->size() != 0) {
			//We didnt find anything but something exists
			//Check for constructors
			//Find maximum
			int max = -1;
			for(Table::RowSet::iterator i = possibleFuncs->begin();i!=possibleFuncs->end();++i) {
				if(max < scores[*i]) {
					max = scores[*i];
				}
			}

			//For this maximum
			for(Table::RowSet::iterator i = possibleFuncs->begin();i!=possibleFuncs->end();++i) {

				if(scores[*i] != max) continue;
				std::string funcName	= "FuncName";
				std::string scopeId		= "ScopeId";
				std::string func = funcs->getColumnValue(funcs->find_id(*i),funcName);
				std::string className = funcs->getColumnValue(funcs->find_id(*i),scopeId);
				className = types->getColumnValue(atoi(className.c_str()),typeName);
				if(className == func) {
					sprintf(buff,"%d",funcs->find_id(*i));
					calledFunctions.push_back(buff);
				}
			}
		}

		if(called->size() == 0 && possibleFuncs->size() == 0) {
			if(identifier == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			//It might be a pointer to function
			//Search for a variable
			AbstractTree AbTree;
			std::string typeIdCol = "TypeID";
			std::string kindOf	  = "KindOf";
			std::string variableId;
			std::string var_type;

			AbTree.directory = tree.directory;
			AbTree.file = tree.file;
			AbTree.tree = tmp_tree;
			variableId = identifVar->findVariable(AbTree);
			if(variableId != "<ERROR>") {
				//Its type must be pointer-to-function
				var_type = vars->getColumnValue(atoi(variableId.c_str()),typeIdCol);
				var_type = eliminateDecoration(var_type);
				if(types->getColumnValue(atoi(var_type.c_str()),kindOf) == "pointer-to-function") {
					//It is a pointer to function
					//Now we consider an access
					//Search name
					var_type = types->getColumnValue(atoi(var_type.c_str()),typeName);
					//Search function
					set1 = funcs->find_set(funcName,var_type);
					if(set1->size() == 1) {
						sprintf(buff,"%d",funcs->find_id(*set1->begin()));
						calledFunctions.push_back(buff);
					}
					delete set1;
				}
			}
			}
		}
		
		delete possibleFuncs;
		delete called;
	}

	return this_bodyId;
}
 

inline void IdentifyFunction::findGlobalFunc(Table::RowSet *possible, std::map<TableRow*,int> &scores, Table::RowSet *called, bool checkNamespace, std::string &known_qualified) {

	Table::RowSet *set1,*set2;
	std::string namespaceIdCol  = "NamespaceId";
	std::string namespaceId		= "<NO_ONE>";
	std::string namespaceName	= "NamespaceName";
	SetOperations set_operation;
	std::string name_id;
	std::string new_name;
	int max;
	char buff[12];

	if(called->size() == 0) {
		max = -1;
	} else {
		max = scores[*called->begin()];
	}

	if(!checkNamespace) {
		//Global namespace search
		set1 = funcs->find_set(namespaceIdCol,namespaceId);
		set2 = set_operation.intersection_op(set1,possible);
		delete set1;
		for(Table::RowSet::iterator i = set2->begin();i!=set2->end();++i) {
			if(max < scores[*i]) {
				called->clear();
				called->insert(*i);
				max = scores[*i];
			} else if(max == scores[*i]) {
				called->insert(*i);
			}
		}
		delete set2;

	} else if(known_qualified != "") {
		//There is a specified namespace name
		set1 = namespaces->find_set(namespaceName,known_qualified);
		if(set1->size() == 1) {
			sprintf(buff,"%d",namespaces->find_id(*set1->begin()));
			name_id = buff;
			delete set1;
			set1 = funcs->find_set(namespaceIdCol,name_id);
			set2 = set_operation.intersection_op(set1,possible);
			delete set1;
			for(Table::RowSet::iterator i = set2->begin();i!=set2->end();++i) {
				if(max < scores[*i]) {
					called->clear();
					called->insert(*i);
					max = scores[*i];
				} else if(max == scores[*i]) {
					called->insert(*i);
				}
			}
			delete set2;
		} else {
			delete set1;
			//The namespace may be in the current namespace
			new_name = this_namespace + known_qualified;
			set1 = namespaces->find_set(namespaceName,new_name);
			if(set1->size() == 1) {
				sprintf(buff,"%d", namespaces->find_id(*set1->begin()));
				name_id = buff;
				delete set1;
				set1 = funcs->find_set(namespaceIdCol,name_id);
				set2 = set_operation.intersection_op(set1,possible);
				delete set1;
				for(Table::RowSet::iterator i = set2->begin();i!=set2->end();++i) {
					if(max < scores[*i]) {
						called->clear();
						called->insert(*i);
						max = scores[*i];
					} else if(max == scores[*i]) {
						called->insert(*i);
					}
				}
				delete set2;
			} else {
				delete set1;
			}
		}

	} else {
		//Search in the current namespace
		if(this_namespace == "") {
			findGlobalFunc(possible,scores,called,false,known_qualified);
		} else {
			set1 = namespaces->find_set(namespaceName,this_namespace);
			if(set1->size() == 1) {
				sprintf(buff,"%d",namespaces->find_id(*set1->begin()));
				name_id = buff;
				delete set1;
				set1 = funcs->find_set(namespaceIdCol,name_id);
				set2 = set_operation.intersection_op(set1,possible);
				delete set1;
				for(Table::RowSet::iterator i = set2->begin();i!=set2->end();++i) {
					if(max < scores[*i]) {
						called->clear();
						called->insert(*i);
						max = scores[*i];
					} else if(max == scores[*i]) {
						called->insert(*i);
					}
				}
				delete set2;
				if(max != 100) {
					findGlobalFunc(possible,scores,called,false,known_qualified);
				}
			} else {
				delete set1;
			}
		}
	}
}

inline void IdentifyFunction::findRelativeMeth(Table::RowSet *possible, std::map<TableRow*,int> &scores, Table::RowSet *called, std::string &type_id) {

	Table::RowSet *set1,*set2,*set3;
	SetOperations set_operation;
	std::string scopeIdCol		= "ScopeId";
	std::string descendentId	= "DescendentId";
	std::string parentId		= "ParentId";
	std::string depth			= "Depth";
	std::string kindOf			= "KindOf";
	std::string templateParId	= "TemplateParameterId";
	std::string concreteType	= "InstantiationTypeId";
	int max		= -1;
	int min_dit;

	//Check to see if it is template parameter
	if(types->getColumnValue(atoi(type_id.c_str()),kindOf) == "template-par") {

		Table::RowSet *myFuncs = new Table::RowSet();
		set1 = tp2t->find_set(templateParId,type_id);
		for(Table::RowSet::iterator i = set1->begin();i!=set1->end();++i) {
			set2 = funcs->find_set(scopeIdCol,eliminateDecoration(tp2t->getColumnValue(tp2t->find_id(*i),concreteType)));
			set3 = set_operation.intersection_op(set2,possible);
			delete set2;
			for(Table::RowSet::iterator j = set3->begin();j!=set3->end();++j) {
				if(max < scores[*j]) {
					called->clear();
					called->insert(*j);
					max = scores[*j];
				} else if(max == scores[*j]) {
					called->insert(*j);
				}
			}
			delete set3;
		}

		delete set1;
		return;
	};

	//Search in the specified class
	set1 = funcs->find_set(scopeIdCol,type_id);
	set2 = set_operation.intersection_op(possible,set1);
	for(Table::RowSet::iterator i = set2->begin();i!=set2->end();++i) {
		if(max < scores[*i]) {
			called->clear();
			called->insert(*i);
			max = scores[*i];
			min_dit = 0;
		} else if(max == scores[*i]) {
			called->insert(*i);
		}
	}
	delete set1;
	delete set2;

	//Add from the ancestors
	//If score equality then favor the minimum DIT
	set1 = inh->find_set(descendentId,type_id);
	for(Table::RowSet::iterator i = set1->begin();i!=set1->end();++i) {
		set2 = funcs->find_set(scopeIdCol,inh->getColumnValue(inh->find_id(*i),parentId));
		set3 = set_operation.intersection_op(possible,set2);
		delete set2;
		for(Table::RowSet::iterator j = set3->begin();j != set3->end();++j) {
			if(max < scores[*j]) {
				called->clear();
				called->insert(*j);
				max = scores[*j];
				min_dit = atoi(inh->getColumnValue(inh->find_id(*i),depth).c_str());
			} else if(max == scores[*j]) {
				if(min_dit > atoi(inh->getColumnValue(inh->find_id(*i),depth).c_str())) {
					called->clear();
					called->insert(*j);
					min_dit = atoi(inh->getColumnValue(inh->find_id(*i),depth).c_str());
				} else if(min_dit == atoi(inh->getColumnValue(inh->find_id(*i),depth).c_str())) {
					called->insert(*j);
				}
			}
		}
		delete set3;
	}
	delete set1;
}

inline int IdentifyFunction::computeScore(std::string &func_id, std::vector<std::string> &signature) {

	std::string the_sig,sig_elem,call_elem;
	std::string typeName = "TypeName";
	std::string sig = "Signature";
	int val,pos;

	//There us a problem. If the infered type is usigned int, etc (when it is derived
	//from a variable) and the formal is i.e. int -> the signature has 0 compatibility
	//It might be a good ideea to analyze also 0 compatibility.
	the_sig = funcs->getColumnValue(atoi(func_id.c_str()),sig);
	the_sig = the_sig.substr(1,the_sig.size() - 2);
	
	val = pos = 0;

 	while(the_sig != "") {

		//Find the element
		sig_elem = the_sig.substr(0,the_sig.find(','));
		if(the_sig.find(',') > the_sig.size()) {
			the_sig = "";
		} else {
			the_sig = the_sig.substr(the_sig.find(',') + 1);
		}

		if(sig_elem.size() != 0 && sig_elem.at(sig_elem.size()-1) == '&') {
			sig_elem = sig_elem.substr(0,sig_elem.size()-1);
		}

		//Compare with call-signature
		if(pos < signature.size()) {
			if(signature[pos] == "<ANY_NUMERIC>" || signature[pos] == "<ZERO>") {
				if(sig_elem == "int"			|| 
					sig_elem.find("int ")		!= -1 || 
					sig_elem.find(" int")		!= -1 || 
					sig_elem == "double"		|| 
					sig_elem.find("double ")	!= -1 || 
					sig_elem.find(" double")	!= -1 || 
					sig_elem == "float" 		||
					sig_elem.find("float ")		!= -1 || 
					sig_elem.find(" float")		!= -1 || 
					sig_elem == "char"  		||
					sig_elem.find("char ")		!= -1 || 
					sig_elem.find(" char")		!= -1 || 
					sig_elem == "unsigned"  	||
					sig_elem.find("unsigned ")	!= -1 || 
					sig_elem.find(" unsigned")	!= -1 || 
					sig_elem == "short" 		||
					sig_elem.find("short ")		!= -1 || 
					sig_elem.find(" short")		!= -1 || 
					sig_elem == "long"		    ||
					sig_elem.find("long ")		!= -1 || 
					sig_elem.find(" long")		!= -1) { 
					val+=100;
				} else if(signature[pos] == "<ZERO>" && sig_elem.at(sig_elem.size() - 1) == '*') {
					val+=100;
				}
			} else if(signature[pos] == "<ERROR>") {
				val+=50;
			} else {
				call_elem = types->getColumnValue(atoi(signature[pos].c_str()),typeName);
				if(call_elem == sig_elem) {
					val+=100;
				}
			}
		} else {
			val+=100;
		}

		pos++;
	}

	if(pos == 0) {
		return 100;
	} else {
		return val / pos;
	}
}

inline std::string IdentifyFunction::findType(std::string &dir, std::string &file, VTP_TreeP tmp_tree) {

	std::string call		 = "call";
	std::string identifier	 = "identifier";
	std::string dot			 = "dot";
	std::string arrow		 = "arrow";
	std::string parenth_expr = "parenth_expr";
	std::string deref		 = "deref";
	std::string pmap		 = "pmap";
	std::string pmpp		 = "pmpp";
	std::string index		 = "index";
	std::string this_op		 = "this";
	std::string functional_cast		= "functional_cast";
	std::string static_cast_op		= "static_cast";
	std::string dynamic_cast_op		= "dynamic_cast";
	std::string reinterpret_cast_op = "reinterpret_cast";
	std::string const_cast_op		= "const_cast";
	std::string cast				= "cast";
	std::string type_id				= "type_id";


	std::string typeIdCol	 = "TypeID";
	std::string retTypeCol   = "ReturnType";
	VTP_TreeP child;

	if(call == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		IdentifyFunction funcId(vars,bodies,funcs,types,inh,namespaces,tp2t);
		std::vector<std::string> called;
		AbstractTree AbTree;
		AbTree.directory = dir;
		AbTree.file = file;
		AbTree.tree = tmp_tree;
		funcId.findFunction(AbTree,called);
		if(called.size() == 1) {
			return funcs->getColumnValue(atoi(called[0].c_str()),retTypeCol);
		} else {
			return "<ERROR>";
		}
	} else if(functional_cast == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) ||
				dynamic_cast_op == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) ||
				static_cast_op == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) ||
				reinterpret_cast_op == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) ||
				const_cast_op == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) ||
				cast == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
					VTP_TreeP tmp = VTP_TreeDown(tmp_tree,0);
					FindBaseType base_type;
					std::vector<std::string> usedTypes;
					if(type_id == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
						tmp = VTP_TreeDown(tmp,0);
					}
					std::string type;
					type = base_type.find(tmp,&usedTypes);
					Table::RowSet *set1;
					std::string typeName = "TypeName";
					set1 = types->find_set(typeName,type);
					if(set1->size() == 1) {
						char buff[12];
						sprintf(buff,"%d",types->find_id(*set1->begin()));
						type = buff;
						delete set1;
						return type;
					} else {
						delete set1;
						return "<ERROR>";
					}
	} else if(this_op == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		return this_classId;
	} else if(identifier == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		AbstractTree AbTree;
		AbTree.directory = dir;
		AbTree.file = file;
		AbTree.tree = tmp_tree;
		return vars->getColumnValue(atoi(identifVar->findVariable(AbTree).c_str()),typeIdCol);
	} else if(index == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))   ||
				deref == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) ||
				dot == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))   ||
				arrow == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) ||
				pmap == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))  ||
				pmpp == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))  ||
				parenth_expr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		ITERATOR_MAP(VTP_TreeChild, tmp_tree, child); {
			tmp_tree = child;
		}
		ITERATOR_END_MAP(VTP_TreeChild);
		return findType(dir,file,tmp_tree);
	} else {
		return "<ERROR>";
	}
}

inline std::string IdentifyFunction::eliminateDecoration(const std::string &typeId) {

	std::string kindOf = "KindOf";
	std::string kind,value;
	std::string decoratedType = "DecoratedType";

	value = typeId;
	kind = types->getColumnValue(atoi(typeId.c_str()),kindOf);
	while(kind == "ptr-decorator" ||
		  kind == "ref-decorator" ||
		  kind == "array-decorator" ||
		  kind == "typedef-decorator" || 
		  kind == "typedef-decorator-in-func" ||
		  kind == "template-instance") {
		
			value = types->getColumnValue(atoi(value.c_str()),decoratedType);
			if(value == "<ERROR>") {
				return "<ERROR>";
			}
			kind = types->getColumnValue(atoi(value.c_str()),kindOf);

	}

	return value;
}

inline void IdentifyFunction::inferSignature(AbstractTree &tree, std::vector<std::string> &signature) {

	VTP_TreeP tmp_tree,child;
	AbstractTree absTree;
	
	tmp_tree = VTP_TreeDown(tree.tree,1);
	absTree.file = tree.file;
	absTree.directory = tree.directory;
    ITERATOR_MAP(VTP_TreeChild, tmp_tree, child); {
		absTree.tree = child;
		signature.push_back(inferParameterType(absTree));
	} ITERATOR_END_MAP(VTP_TreeChild);

}

inline std::string IdentifyFunction::inferParameterType(AbstractTree &tree) {
	
	VTP_TreeP tmp_tree,tmp;
	Table::RowSet *set1,*set2,*set3;
	std::string typeName		= "TypeName";
	std::string kindOf			= "KindOf";
	std::string decoratedType	= "DecoratedType";
	std::string ptrDecorator    = "ptr-decorator";

	std::string type_id	 = "type_id";
	std::string value,tmp_value;
	std::string varType  = "TypeID";
	SetOperations set_operation;

	AbstractTree tmpTree;
	tmpTree.directory = tree.directory;
	tmpTree.file = tree.file;

	tmp_tree = tree.tree;
	std::string op = VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree));

	char buff[12];

	if(op == "integer") {

		//Any numeric character
		std::string zero = "0";
		if(zero == VTP_STRING_VALUE(VTP_TreeAtomValue(tmp_tree))) {
			return "<ZERO>";
		} else {
			return "<ANY_NUMERIC>";
		}

	} else if(op == "string") {
		
		//A pointer to character
		value = "char*";
		set1 = types->find_set(typeName,value);
		if(set1->size() == 1) {
			sprintf(buff,"%d",types->find_id(*set1->begin()));
			value = buff;
		} else {
			value = "<ERROR>";
		}
		delete set1;
		return value;

	} else if(op == "character") {

		//A character
		value = "char";
		set1 = types->find_set(typeName,value);
		if(set1->size() == 1) {
			sprintf(buff,"%d",types->find_id(*set1->begin()));
			value = buff;
		} else {
			value = "<ERROR>";
		}
		delete set1;
		return value;

	} else if(op == "true" || op == "false") {

		//A boolean
		value = "bool";
		set1 = types->find_set(typeName,value);
		if(set1->size() == 1) {
			sprintf(buff,"%d",types->find_id(*set1->begin()));
			value = buff;
		} else {
			value = "<ERROR>";
		}
		delete set1;
		return value;

	} else if(op == "this") {

		//A decoration to this class
		set1 = types->find_set(decoratedType,this_classId);
		set2 = types->find_set(kindOf,ptrDecorator);
		set3 = set_operation.intersection_op(set1,set2);
		delete set1;
		delete set2;
		if(set3->size() == 1) {
			sprintf(buff,"%d",types->find_id(*set3->begin()));
			value = buff;
		} else {
			value = "<ERROR>";
		}
		delete set3;
		return value;

	} else if(op == "functional_cast" ||
			  op == "dynamic_cast" ||
			  op == "static_cast" ||
			  op == "reinterpret_cast" ||
			  op ==	"const_cast" ||
			  op == "cast") {

		//A cast
		FindBaseType base_type;
		std::vector<std::string> usedTypes;

		//Here it will be OK to seartch for template parameters as well
		tmp = VTP_TreeDown(tmp_tree,0);
		if(type_id == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
			tmp = VTP_TreeDown(tmp,0);
		}
		value = base_type.find(tmp,&usedTypes);
		set1 = types->find_set(typeName,value);
		if(set1->size() == 1) {
			char buff[12];
			sprintf(buff,"%d",types->find_id(*set1->begin()));
			value = buff;
		} else {
			value = "<ERROR>";
		}
		delete set1;
		return value;

	} else if(op == "index") {

		tmp_tree = VTP_TreeDown(tmp_tree,0);
		tmpTree.tree = tmp_tree;
		value = inferParameterType(tmpTree);
		tmp_value = types->getColumnValue(atoi(value.c_str()),kindOf);
		if(tmp_value == "array-decorator") {
			value = types->getColumnValue(atoi(value.c_str()),decoratedType);
		} else {
			value = "<ERROR>";
		}
		return value;

	} else if(op == "deref") {

		tmp_tree = VTP_TreeDown(tmp_tree,0);
		tmpTree.tree = tmp_tree;
		value = inferParameterType(tmpTree);
		tmp_value = types->getColumnValue(atoi(value.c_str()),kindOf);
		if(tmp_value == "ptr-decorator") {
			value = types->getColumnValue(atoi(value.c_str()),decoratedType);
		} else {
			value = "<ERROR>";
		}
		return value;

	} else if(op == "addr") {

		tmp_tree = VTP_TreeDown(tmp_tree,0);
		tmpTree.tree = tmp_tree;
		value = inferParameterType(tmpTree);
		if(value == "<ERROR>") return value;
		set1 = types->find_set(decoratedType,value);
		set2 = types->find_set(kindOf,ptrDecorator);
		set3 = set_operation.intersection_op(set1,set2);
		delete set1;
		delete set2;
		if(set3->size() == 1) {
			sprintf(buff,"%d",types->find_id(*set3->begin()));
			value = buff;
		} else {
			value = "<ERROR>";
		}
		delete set3;
		return value;

	} else if(op == "dot" || op == "arrow") {

		tmp_tree = VTP_TreeDown(tmp_tree,1);
		tmpTree.tree = tmp_tree;
		value = identifVar->findVariable(tmpTree);
		value = vars->getColumnValue(atoi(value.c_str()),varType);
		return value;

	} else if(op == "call") {

		IdentifyFunction funcId(vars,bodies,funcs,types,inh,namespaces,tp2t);
		std::vector<std::string> called;
		std::string returnType = "ReturnType";

		tmpTree.tree = tmp_tree;
		funcId.findFunction(tmpTree,called);
		if(called.size() == 1) {
			value = funcs->getColumnValue(atoi(called[0].c_str()),returnType);
		} else {
			value = "<ERROR>";
		}
		return value;

	} else if(op == "identifier") {

		std::string null_op = "NULL";
		if(null_op == VTP_NAME_STRING(VTP_TreeAtomValue(tmp_tree))) {
			return "<ZERO>";
		}
		tmpTree.tree = tmp_tree;
		value = identifVar->findVariable(tmpTree);
		value = vars->getColumnValue(atoi(value.c_str()),varType);
		if(types->getColumnValue(atoi(value.c_str()),kindOf) == "ref-decorator") {
			value = types->getColumnValue(atoi(value.c_str()),decoratedType);
		};
		return value;

	} else if(op == "parenth_expr") {

		tmpTree.tree = VTP_TreeDown(tmp_tree,0);
		return inferParameterType(tmpTree);

	} else {

		return "<ERROR>";

	}

}

//Search the id of the body for the current point in AST
inline void IdentifyFunction::fillVars(AbstractTree &tree) {

	std::string fndef				= "fndef";
	std::string compound			= "compound";
	std::string ctor_initializer	= "ctor_initializer";
	std::string value;

	VTP_TreeP tmp_tree;

	this_bodyId = this_classId = "0";
	this_namespace = "<UNDEFINED>";

	//Now search the current bodyId
	tmp_tree = tree.tree;
	while(fndef != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		tmp_tree = VTP_TreeUp(tmp_tree);
	}
	tmp_tree = VTP_TreeDown(tmp_tree,3);
	if(compound != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		if(ctor_initializer == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
			tmp_tree = VTP_TreeDown(tmp_tree,1);
		} else {
			return;
		}
	}

	Table::RowSet *set1,*set2,*set3;
	std::string fileName	= "FileName";
	std::string startLine	= "StartLine";
	SetOperations set_operator;
	int id;
	char buff[12];
	CIO_PositionS start;
	CIO_PositionS stop;

	VTP_TreeGetCoord(tmp_tree,&start,&stop);
	set1 = bodies->find_set(fileName,tree.file);
	sprintf(buff,"%d",start.line);
	value = buff;
	set2 = bodies->find_set(startLine,value);
	set3 = set_operator.intersection_op(set1,set2);
	delete set1;
	delete set2;
	if(set3->size() == 1) {
		id = bodies->find_id(*set3->begin());
		sprintf(buff,"%d",id);
		this_bodyId = buff;
		delete set3;
	} else {
		delete set3;
		return;
	}

	//Now search the current namespace (its name) and classId
	std::string bodyIdCol		= "BodyId";
	std::string namespaceIdCol  = "NamespaceId";
	std::string namespaceIDCol  = "NamespaceID";
	std::string namespaceName	= "NamespaceName";
	std::string scopeId			= "ScopeId";
	std::string tmp;
	set1 = funcs->find_set(bodyIdCol,this_bodyId);
	if(set1->size() == 1) {
	
		//See the function class
		tmp = funcs->getColumnValue(funcs->find_id(*set1->begin()),scopeId);
		if(tmp != "<NO_ONE>" && tmp != "<ERROR>" && tmp != "NULL") {
			this_classId = tmp;
		}

		//See the function namespace
		tmp = funcs->getColumnValue(funcs->find_id(*set1->begin()),namespaceIdCol);
		if(tmp == "<NO_ONE>") {
			this_namespace = "";
			delete set1;
		} else if(tmp == "<ERROR>") {
			delete set1;
		} else if(tmp == "NULL") {
			tmp = funcs->getColumnValue(funcs->find_id(*set1->begin()),scopeId);
			tmp = types->getColumnValue(atoi(tmp.c_str()),namespaceIDCol);
			delete set1;
			if(tmp == "<NO_ONE>") {
				this_namespace = "";
			} else if(tmp != "<ERROR>" && tmp != "NULL") {
				this_namespace = namespaces->getColumnValue(atoi(tmp.c_str()),namespaceName);
			}
		} else {
			delete set1;
			this_namespace = namespaces->getColumnValue(atoi(tmp.c_str()),namespaceName);
		}
	} else {
		delete set1;
	}
}
