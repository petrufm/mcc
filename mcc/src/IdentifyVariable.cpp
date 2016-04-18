#include "IdentifyVariable.h"
#include "IdentifyFunction.h"
#include "VariablesTable.h"
#include "BodyTable.h"
#include "NamespaceTable.h"
#include "FuncsTable.h"
#include "TypesTable.h"
#include "InheritanceTable.h"
#include "SetOperations.h"
#include "FindBaseType.h"
#include "TemplateParTypesRelation.h"

#include <cstdlib>

IdentifyVariable::IdentifyVariable(
		VariablesTable *vars,
		BodyTable *bodies,
		FuncsTable *funcs,
		TypesTable *types,
		InheritanceTable *inh,
		NamespaceTable *namespaces,
		TemplateParTypesRelation *tp2t) {

	this->vars			= vars;
	this->bodies		= bodies;
	this->funcs			= funcs;
	this->types			= types;
	this->inh			= inh;
	this->namespaces	= namespaces;
	this->tp2t			= tp2t;

	reset = true;
	possibleName	= new Table::RowSet;
	possibleLocal	= new Table::RowSet;
	possibleParam	= new Table::RowSet;
	possibleAttrLoc	= new Table::RowSet;

	std::string kindOfCol		= "KindOf";
	std::string kindOfAttr		= "attribute";
	std::string kindOfGlobal	= "global";
	possibleAttr	= vars->find_set(kindOfCol,kindOfAttr);
	possibleGlobal  = vars->find_set(kindOfCol,kindOfGlobal);

}

IdentifyVariable::~IdentifyVariable() {
	delete possibleName;
	delete possibleLocal;
	delete possibleParam;
	delete possibleAttrLoc;
	delete possibleAttr;
	delete possibleGlobal;
}

void IdentifyVariable::setReset() {
	reset = true;
}

std::string IdentifyVariable::findVariable(AbstractTree &tree) {

	std::string value;
	std::string qualified_id = "qualified_id";
	std::string global_scope = "global_scope";
	std::string index		 = "index";
	std::string dot			 = "dot";
	std::string arrow		 = "arrow";
	std::string call		 = "call";
	std::string this_op		 = "this";
	VTP_TreeP tmp_tree,tmp;

	//Find the bodyId,namespaceName,and classId
	if(reset) {
		fillVars(tree);
		reset = false;
	}

	//Find the possible variable by name
	delete possibleName;
	std::string nameCol		= "VariableName";
	std::string varName;
	varName = VTP_NAME_STRING(VTP_TreeAtomValue(tree.tree));
	possibleName = vars->find_set(nameCol,varName);
	if(possibleName->size() == 0) {
		return "<ERROR>";
	}

	//See if there is a qualified_id
	tmp_tree = VTP_TreeUp(tree.tree);
	if(qualified_id == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
		tmp_tree = VTP_TreeDown(tmp_tree,0);
		if(global_scope == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) && VTP_TreeDown(tmp_tree,0) == NULL) {
			//The variable has to be global
			//and outside of any namespace
			//OBS: It might be a function name (assigning functions to p2f)
			//but this will be an error
			//We search only for :: (global scope)
			value = findRelativeGlobal(tree,false);
		} else {
			//The variable has to be: 
			//class attribute
			//		 - in a class with the specified name which is in the specified
			//		 namespace or class ...
			//		 - it may be inherited
			value = findAbsoluteAttribute(tree);
			//global 
			//		 - in a namespace with the specified name
			//		 - in a namespace inside the current namespace, with this name
			//OBS:	It might be a function name (assigning function to p2f)
			if(value == "<ERROR>") {
				value = findAbsoluteGlobal(tree);
			}
		}
		return value;
	}

	//There isn't a qualifid_id, so continue the search
	//See if it is single (like a++, a + something, a[i])
	//or the first identifier in a ./-> access
	tmp_tree = VTP_TreeUp(tree.tree);
	tmp = tree.tree;
	if((dot != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) &&
	    arrow != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) || VTP_TreeRank(tmp) == 0) {
		//It is a single access:
		//Local variable
		//		- local to the current block
		value = findLocal(tree);
		//Parameter
		//		- parameter of the function
		if(value == "<ERROR>") {
			value = findParameter();
		}
		//A class attribute
		//		- in the same class as the current method (or inherited)
		if(value == "<ERROR>") {
			value = findRelativeAttribute(tree,this_classId);
		}
		//Global
		//		- a global variable, in the current namespace OR
		//		- a global variable outside of any namespace
		if(value == "<ERROR>") {
			value = findRelativeGlobal(tree,true);
		}
	} else {
		//It is a member of the class (type) of the 0 descendent
		tmp = VTP_TreeLeft(tmp);
		if(call == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
			//Check the return type of the function (is has to be a class and may be decorated)
			IdentifyFunction funcId(vars,bodies,funcs,types,inh,namespaces,tp2t);
			std::vector<std::string> calledFuncs;
			std::string ret_class;
			std::string retType = "ReturnType";
			AbstractTree aTree;
			aTree.directory = tree.directory;
			aTree.file = tree.file;
			aTree.tree = tmp;
			funcId.findFunction(aTree,calledFuncs);
			if(calledFuncs.size() == 1) {
				ret_class = funcs->getColumnValue(atoi(calledFuncs[0].c_str()),retType);
				ret_class = eliminateDecoration(ret_class);
				value = findRelativeAttribute(tree,ret_class);
			} else {
				value = "<ERROR>";
			}

		} else if(this_op == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
			//It is a this operator
			value = findRelativeAttribute(tree,this_classId);
		} else {
			//Check the type of this variable (is has to be a class, but it may be decorated)
			bool repeat;
			std::string deref				= "deref";
			std::string addr				= "addr";
			std::string parenth_expr		= "parenth_expr";
			std::string functional_cast		= "functional_cast";
			std::string static_cast_op		= "static_cast";
			std::string dynamic_cast_op		= "dynamic_cast";
			std::string reinterpret_cast_op = "reinterpret_cast";
			std::string const_cast_op		= "const_cast";
			std::string cast				= "cast";
			std::string identifier			= "identifier";
			std::string type_id				= "type_id";
			std::string type = "";
			FindBaseType base_type;
			std::vector<std::string> usedTypes;
			do {
				repeat = false;
				if(deref == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) ||
					addr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))  ||
					index == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) ||
					parenth_expr == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
						tmp = VTP_TreeDown(tmp,0);
						repeat = true;
				} else 
				if(arrow == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) ||
					dot == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) ||
					qualified_id == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
						tmp = VTP_TreeDown(tmp,1);
				} else
				if(functional_cast == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) ||
					dynamic_cast_op == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) ||
					static_cast_op == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) ||
					reinterpret_cast_op == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) ||
					const_cast_op == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp)) ||
					cast == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
						tmp = VTP_TreeDown(tmp,0);
						if(type_id == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {
							tmp = VTP_TreeDown(tmp,0);
						}
						type = base_type.find(tmp,&usedTypes);
						Table::RowSet *set1;
						std::string typeName = "TypeName";
						set1 = types->find_set(typeName,type);
						if(set1->size() == 1) {
							char buff[12];
							sprintf(buff,"%d",types->find_id(*set1->begin()));
							type = buff;
							delete set1;
						} else {
							delete set1;
							return "<ERROR>";
						}
				}
			} while(repeat);

			if(type == "") {

				if(identifier == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp))) {

					std::string var_id;
					std::string typeIdCol = "TypeID";
					AbstractTree tmp_var;

					tmp_var.directory = tree.directory;
					tmp_var.file = tree.file;
					tmp_var.tree = tmp;
						
					//It may refer an extern variable. The type may be unknown
					//at this point, so we have to go to the refered variable.
					//This is not yet implemented.
					//WARNNING. When you make a recursive call
					//you must recreate the state of the object

					Table::RowSet *last_row_set_name;
					last_row_set_name = possibleName;
					possibleName = 	new Table::RowSet;
					var_id = this->findVariable(tmp_var);
					delete possibleName;
					possibleName = last_row_set_name;
					
					if(var_id == "<ERROR>") {
						return "<ERROR>";
					}
					
					type = vars->getColumnValue(atoi(var_id.c_str()),typeIdCol);
					if(type == "<ERROR>") {
						return "<ERROR>";
					}

					//We know the type of the variable
					//But it may be decorated. This decoration have to be eliminated
					type = eliminateDecoration(type);
					if(type == "<ERROR>") {
						return "<ERROR>";
					}

				} else {

					return "<ERROR>";

				}
			}
			//Type contains the type id of the accessed class/struct/union
			//Searching an attribute in the class of the variable is correct because
			//the access to an attribute is not polimorfic

			value = findRelativeAttribute(tree,type);
		}
	}

	return value;
}

//Search the id of the body for the current point in AST
inline void IdentifyVariable::fillVars(AbstractTree &tree) {

	std::string fndef				= "fndef";
	std::string compound			= "compound";
	std::string ctor_initializer	= "ctor_initializer";
	std::string value;

	VTP_TreeP tmp_tree;

	this_bodyId = this_classId = "0";
	this_namespace = "<UNDEFINED>";

	possibleName->clear();
	possibleLocal->clear();
	possibleParam->clear();
	possibleAttrLoc->clear();

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

	//Now we can see what local variable we can have
	delete possibleLocal;
	std::string kindOfCol	= "KindOf";
	std::string kindOfLocal	= "local";
	std::string bodyId		= "BodyID";
	SetOperations set_operation;
	set1 = vars->find_set(kindOfCol,kindOfLocal);
	set2 = vars->find_set(bodyId,this_bodyId);
	possibleLocal = set_operation.intersection_op(set1,set2);
	delete set1;
	delete set2;

	//Now we can see what param variable we can have
	delete possibleParam;
	std::string kindOfParam	= "parameter";
	set1 = vars->find_set(kindOfCol,kindOfParam);
	set2 = vars->find_set(bodyId,this_bodyId);
	possibleParam = set_operation.intersection_op(set1,set2);
	delete set1;
	delete set2;

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

		//Now we can see what attr (local) we can have
		delete possibleAttrLoc;
		std::string kindOfAttr = "attribute";
		std::string classIdCol = "ClassID";
		set2 = vars->find_set(classIdCol,this_classId);
		possibleAttrLoc = set_operation.intersection_op(possibleAttr,set2);
		delete set2;
	
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

//Search for a global variable, relative to the current point in AST
inline std::string IdentifyVariable::findRelativeGlobal(AbstractTree &tree, bool checkNamespaces) {

	std::string value,tmp;
	std::string namespaceCol	= "NamespaceID";
	std::string fileNameCol		= "FileName";
	std::string refersToCol		= "RefersTo";
	std::string namespaceNameCol= "NamespaceName";
	std::string namespaceId		= "<NO_ONE>";
	std::string refTo			= "<NO_ONE>";

	Table::RowSet *set1,*set2,*set3;
	SetOperations set_operation;
	char buff[12];

	set3 = set_operation.intersection_op(possibleGlobal,possibleName);
	//Set3 contains all global variables with the searched name

	if(checkNamespaces) {

		if(this_namespace == "") {

			value = findRelativeGlobal(tree,false);

		} else {

			set1 = namespaces->find_set(namespaceNameCol,this_namespace);
			if(set1->size() == 1) {
				sprintf(buff,"%d",namespaces->find_id(*set1->begin()));
				tmp = buff;
				delete set1;
				set1 = vars->find_set(namespaceCol,tmp);
				set2 = set_operation.intersection_op(set1,set3);
				delete set1;
				if(set2->size() == 1) {
					sprintf(buff,"%d",vars->find_id(*set2->begin()));
					tmp = buff;
					value = tmp;
					delete set2;
				} else {
					delete set2;
					value = findRelativeGlobal(tree,false);
				}
			} else {
				delete set1;
				value = "<ERROR>";
			}
		}

		delete set3;

	} else {

		set1 = vars->find_set(namespaceCol,namespaceId);
		set2 = set_operation.intersection_op(set1,set3);
		delete set1;
		delete set3;
		//Set2 contains all global var. with the searched name and outside of any namespace
		if(set2->size() == 1) {
			sprintf(buff,"%d",vars->find_id(*set2->begin()));
			value = buff;
			delete set2;
		} else {
			//Try to find one in the same file
			set1 = vars->find_set(fileNameCol,tree.file);
			set3 = set_operation.intersection_op(set1,set2);
			delete set1;
			if(set3->size() == 1) {
				sprintf(buff,"%d",vars->find_id(*set3->begin()));
				value = buff;
				delete set2;
				delete set3;
			} else {
				//Try to find one which is not extern
				delete set3;
				set1 = vars->find_set(refersToCol,refTo);
				set3 = set_operation.intersection_op(set1,set2);
				delete set1;
				delete set2;
				if(set3->size() == 1) {
					sprintf(buff,"%d",vars->find_id(*set3->begin()));
					value = buff;
				} else {
					value = "<ERROR>";
				}
				delete set3;
			}
		}
	}

	return value;
}

//Search for a global variable, in an absolute manner
inline std::string IdentifyVariable::findAbsoluteGlobal(AbstractTree &tree) {

	VTP_TreeP tmp_tree = VTP_TreeLeft(tree.tree),child;
	std::string name = "";

	//Find a namespace with the specified name
    ITERATOR_MAP(VTP_TreeChild, tmp_tree, child); {
		if(name != "") {
			name+="::";
		}
		name+=VTP_NAME_STRING(VTP_TreeAtomValue(child));
	}
	ITERATOR_END_MAP(VTP_TreeChild);

	Table::RowSet *set1,*set2,*set3;
	SetOperations set_operation;
	std::string namespaceNameCol = "NamespaceName";
	std::string namespaceIdCol	 = "NamespaceID";
	std::string tmp;
	char buff[12];

	set3 = set_operation.intersection_op(possibleGlobal,possibleName);
	//Set3 contains the global variables with the specified name

	//Find the variable in the specified namespace
	set1 = namespaces->find_set(namespaceNameCol,name);
	if(set1->size() == 1) {
		sprintf(buff,"%d",namespaces->find_id(*set1->begin()));
		tmp = buff;
		delete set1;
		set1 = vars->find_set(namespaceIdCol,tmp);
		set2 = set_operation.intersection_op(set1,set3);
		delete set1;
		if(set2->size() == 1) {
			sprintf(buff,"%d",vars->find_id(*set2->begin()));
			tmp = buff;
			delete set2;
			delete set3;
			return tmp;
		}
		delete set2;
	} else {
		delete set1;
	}

	//If the control is here, then there isn't a namespace with the specified name
	//It may be a namespace inside the current namespace
	if(this_namespace != "") {		
		name = name + this_namespace;
		set1 = namespaces->find_set(namespaceNameCol,name);
		if(set1->size() == 1) {
			sprintf(buff,"%d",namespaces->find_id(*set1->begin()));
			tmp = buff;
			delete set1;
			set1 = vars->find_set(namespaceIdCol,tmp);
			set2 = set_operation.intersection_op(set1,set3);
			delete set1;
			if(set2->size() == 1) {
				sprintf(buff,"%d",vars->find_id(*set2->begin()));
				tmp = buff;
				delete set2;
				delete set3;
				return tmp;
			}
			delete set1;
			delete set2;
			delete set3;
		} else {
			delete set1;
			delete set3;
		}
		return "<ERROR>";
	} else {
		delete set3;
		return "<ERROR>";
	}
}

//Search for an attribute , in an absolute manner
inline std::string IdentifyVariable::findAbsoluteAttribute(AbstractTree &tree) {

	std::string value,tmp;
	std::string kindOfCol	= "KindOf";
	std::string typeName	= "TypeName";
	std::string classId		= "ClassID";
	std::string descendentId= "DescendentId";
	std::string parentId	= "ParentId";
	std::string kindOf		= "attribute";

	Table::RowSet *set1,*set2,*set3,*set4;
	SetOperations set_operation;
	char buff[12];

	set3 = set_operation.intersection_op(possibleAttr,possibleName);
	//Set3 contains the attribute variables with the specified name

	VTP_TreeP tmp_tree = VTP_TreeLeft(tree.tree),child;
	std::string name = "";

	//Find the name of the last right-most child
    ITERATOR_MAP(VTP_TreeChild, tmp_tree, child); {
		name = VTP_NAME_STRING(VTP_TreeAtomValue(child));
	}
	ITERATOR_END_MAP(VTP_TreeChild);

	//Search a class/union/struct with this name (but we don't search with kindOf)
	set1 = types->find_set(typeName,name);

	if(set1->size() == 1) {
		sprintf(buff,"%d",types->find_id(*set1->begin()));
		value = buff;
		delete set1;
		set2 = vars->find_set(classId,value);
		set1 = set_operation.intersection_op(set2,set3);
		delete set2;
		if(set1->size() == 1) {
			sprintf(buff,"%d",vars->find_id(*set1->begin()));
			value = buff;
			delete set1;
		} else {
			//It must be in one of its ascendents
			delete set1;
			set1 = inh->find_set(descendentId,value);
			value = "<ERROR>";
			for(Table::RowSet::iterator i = set1->begin();i!=set1->end();++i) {
				tmp = inh->getColumnValue(inh->find_id(*i),parentId);
				set2 = vars->find_set(classId,tmp);
				set4 = set_operation.intersection_op(set2,set3);
				delete set2;
				if(set4->size() == 1) {
					sprintf(buff,"%d",vars->find_id(*set4->begin()));
					value = buff;
					delete set4;
					break;
				}
				delete set4;
			}
			delete set1;
		}
	} else {
		value = "<ERROR>";
		delete set1;
	}
	delete set3;
	return value;
}

//Search for an attribute relative at the specified class
inline std::string IdentifyVariable::findRelativeAttribute(AbstractTree &tree, std::string &the_classId) {

	std::string value,tmp;
	std::string kindOfCol	= "KindOf";
	std::string classId		= "ClassID";
	std::string descendentId= "DescendentId";
	std::string parentId	= "ParentId";
	std::string kindOf		= "attribute";

	Table::RowSet *set1,*set2,*set3,*set4;
	SetOperations set_operation;
	char buff[12];

	if(the_classId == this_classId) {
		//We use the local attr cache
		set2 = set_operation.intersection_op(possibleName,possibleAttrLoc);
		set3 = set_operation.intersection_op(possibleAttr,possibleName);
	} else {
		//We have to search
		set1 = vars->find_set(classId,the_classId);
		set3 = set_operation.intersection_op(possibleAttr,possibleName);
		set2 = set_operation.intersection_op(set1,set3);
		delete set1;
	}

	//Set2 contains attibutes with the searched name and of the specified class
	if(set2->size() == 1) {
		//An access to the specified class attribute
		sprintf(buff,"%d",vars->find_id(*set2->begin()));
		value = buff;
		delete set2;
	} else {
		//It must be in an ascendents
		delete set2;
		set1 = inh->find_set(descendentId,the_classId);
		value = "<ERROR>";
		for(Table::RowSet::iterator i = set1->begin();i!=set1->end();++i) {
			tmp = inh->getColumnValue(inh->find_id(*i),parentId);
			set2 = vars->find_set(classId,tmp);
			set4 = set_operation.intersection_op(set2,set3);
			delete set2;
			if(set4->size() == 1) {
				sprintf(buff,"%d",vars->find_id(*set4->begin()));
				value = buff;
				delete set4;
				break;
			}
			delete set4;
		}
		delete set1;
	}
	delete set3;
	return value;
}

//Search for a local variable
inline std::string IdentifyVariable::findLocal(AbstractTree& tree) {

	std::string value;
	std::string visibility	= "VisibleUntilLine";

	Table::RowSet *set1;
	SetOperations set_operation;
	char buff[12];
	int decl_r,end_r,c_r,min;
	CIO_PositionS start;
	CIO_PositionS stop;

	//Set1 contains the local variable for the current body with the search name
	set1 = set_operation.intersection_op(possibleName,possibleLocal);

	VTP_TreeGetCoord(tree.tree,&start,&stop);
	c_r = start.rank;

	value = "<ERROR>";
	min = -1;
	for(Table::RowSet::iterator i = set1->begin();i!=set1->end();++i) {
		sscanf(vars->getColumnValue(vars->find_id(*i),visibility).c_str(),"%d %d",&decl_r,&end_r);
		if(decl_r < c_r && c_r < end_r) {
			if(min == -1 || min > end_r - decl_r) {
				min = end_r - decl_r;
				sprintf(buff,"%d",vars->find_id(*i));
				value = buff;
			}
		}
	}
	delete set1;
	return value;
}

//Search for a parameter variable
inline std::string IdentifyVariable::findParameter() {

	std::string value;

	Table::RowSet *set1;
	SetOperations set_operation;
	char buff[12];

	//Set1 contains the parameters for the current body with the searched name
	set1 = set_operation.intersection_op(possibleName,possibleParam);

	if(set1->size() == 1) {
		sprintf(buff,"%d",vars->find_id(*set1->begin()));
		value = buff;
	} else {
		value = "<ERROR>";
	}
		
	delete set1;
	return value;
}

//This function eliminate the decoration of a type
inline std::string IdentifyVariable::eliminateDecoration(std::string &typeId) {

	std::string decoratedType	= "DecoratedType";
	std::string kindOf			= "KindOf";
	std::string kind,value;
	
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
