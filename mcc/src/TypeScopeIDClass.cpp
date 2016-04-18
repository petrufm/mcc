#include "TypeScopeIDClass.h"
#include "ProxyTableColumn.h"
#include "TableRow.h"
#include "SetOperations.h"
#include "FindClassOfFunction.h"

TypeScopeIDClass::TypeScopeIDClass(DataExtractor *next, ConcreteTableColumn *prototype, ClassDeclaration *condition, TypesTable *types, BodyTable *bodies):DelayedDataExtractor(next,prototype,condition) {

	this->types = types;
	this->bodies = bodies;

}

TableColumn* TypeScopeIDClass::handleExtraction(AbstractTree &tree) {

	ProxyTableColumn* column;
	IContainer *info = new IContainer();
	CIO_PositionS start;
	CIO_PositionS stop;
	char buff[12];
	std::string value1,value2,value3,value4,value5;
	std::string class_decls		= "class_decls";
	std::string identifier		= "identifier";
	std::string qualified_id	= "qualified_id";
	std::string none			= "none";
	std::string fndef			= "fndef";
	std::string func_dcltr		= "func_dcltr";
	std::string compound		= "compound";
	std::string ctor_initializer= "ctor_initializer";
	std::string pp_else_part	= "pp_else_part";
	std::string pp_ifdef		= "pp_ifdef";
	std::string pp_ifndef		= "pp_ifndef";
	std::string pp_conditional	= "pp_conditional";
	
	VTP_TreeP tmp_tree,child;


	//Find the name of the class that includes this class definition,its file and start position
	tmp_tree = tree.tree;
	do {
		tmp_tree = VTP_TreeUp(tmp_tree);
	} while(tmp_tree != NULL && 
		   (class_decls != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)) ||
				//Patch - Fast Error
				(pp_else_part == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeUp(tmp_tree))) ||
				 pp_conditional == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeUp(tmp_tree))) ||
				 pp_ifdef == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeUp(tmp_tree))) ||
				 pp_ifndef == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeUp(tmp_tree)))
				 )
		   ) && fndef != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree)));

	if(tmp_tree != NULL) {
		
		if(class_decls == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {

			tmp_tree = VTP_TreeLeft(tmp_tree);
			//This class definition is included into another one - find its name
			if(identifier == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tmp_tree,1)))) {
				//When the definition is "class X {"
				value1 = VTP_NAME_VALUE(VTP_TreeAtomValue(VTP_TreeDown(tmp_tree,1)));
			} else if(qualified_id == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tmp_tree,1)))) {
				//When the definition is "class name_space::..::class_name::..::X {"
				tmp_tree = VTP_TreeDown(VTP_TreeDown(tmp_tree,1),1);
				value1 = VTP_NAME_VALUE(VTP_TreeAtomValue(tmp_tree));
			} else if(none == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tmp_tree,1)))) {
				//When the definition is "class {"
				value1 = "<ANONYMOUS>";
			}
			value2 = tree.file;
			VTP_TreeGetCoord(tmp_tree,&start,&stop);
			sprintf(buff,"%d",start.line);
			value3 = buff;
			value5 = "class";

		} else {

			//Search the body
			value2 = tree.file;
			tmp_tree = VTP_TreeDown(tmp_tree,3);
			if(compound != VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
				if(ctor_initializer == VTP_OP_NAME(VTP_TREE_OPERATOR(tmp_tree))) {
					tmp_tree = VTP_TreeDown(tmp_tree,1);
				}
			}
			VTP_TreeGetCoord(tmp_tree,&start,&stop);
			sprintf(buff,"%d",start.line);
			value3 = buff;
			value5 = "function";

		}

	}

	//Find the scope of this class definition
	if(qualified_id == VTP_OP_NAME(VTP_TREE_OPERATOR(VTP_TreeDown(tree.tree,1)))) {
		//When the definition is "class name_space::...class_name...::X {"
		tmp_tree = VTP_TreeDown(VTP_TreeDown(tree.tree,1),0);
	    ITERATOR_MAP(VTP_TreeChild, tmp_tree, child); {
			if(value4 == "") {
				value4 = VTP_NAME_STRING(VTP_TreeAtomValue(child));
			} else {
				value4 += "::";
				value4 += VTP_NAME_STRING(VTP_TreeAtomValue(child));
			}

		}
		ITERATOR_END_MAP(VTP_TreeChild);
	}

	info->push_back(value1);
	info->push_back(value2);
	info->push_back(value3);
	info->push_back(value4);
	info->push_back(value5);
	
	column = new ProxyTableColumn(prototype->getName(),(ConcreteTableColumn*)prototype->clone(),this,info);
	return column;
}

bool TypeScopeIDClass::finalizeExtraction(TableColumn *column, IContainer *info) {

	std::string upper_class_name	= (*info)[0];
	std::string upper_class_file	= (*info)[1];
	std::string upper_class_pos		= (*info)[2];
	std::string class_scope			= (*info)[3];
	std::string type				= (*info)[4];
	std::string value;
	SetOperations set_operation;
	FindClassOfFunction myclass;
	char buff[12];
	int id;

	if(class_scope == "") {

		//There is no scope (OK)
		if(type == "") {

			value = "<NO_ONE>";
			column->init(value,false);
			return true;

		} else if(type == "class") {

			//There is a upper class -> it is the scope (OK)
			Table::RowSet *set1,*set2,*set3;
			Table::RowSet *int1,*int2;

			std::string typeName = "TypeName";
			std::string fileName = "FileName";
			std::string startPos = "StartPosition";

			set1 = types->find_set(typeName,upper_class_name);
			set2 = types->find_set(fileName,upper_class_file);
			set3 = types->find_set(startPos,upper_class_pos);
			int1 = set_operation.intersection_op(set1,set2);
			int2 = set_operation.intersection_op(int1,set3);
		
			if(!int2->empty() &&  (id = types->find_id(*int2->begin())) > 0) {
				sprintf(buff,"%d",id);
				value = buff;
			} else {
				value = "<ERROR>";
			}

			delete set1;
			delete set2;
			delete set3;
			delete int1;
			delete int2;
			
			column->init(value,false);
			return true;

		} else {

			//It is in a body
			Table::RowSet *set1,*set2,*set3;
			SetOperations set_operation;
			std::string fileName	= "FileName";
			std::string startLine	= "StartLine";

			set1 = bodies->find_set(fileName,upper_class_file);
			set2 = bodies->find_set(startLine,upper_class_pos);
			set3 = set_operation.intersection_op(set1,set2);
			delete set1;
			delete set2;
			if(set3->size() == 1) {
				id = bodies->find_id(*set3->begin());
				sprintf(buff,"%d",id);
				value = buff;
			} else {
				value = "<ERROR>";
			}
			delete set3;

			column->init(value,false);
			return true;
		}

	} else {

		value =  myclass.find(class_scope,types);
		column->init(value,false);

	}

	return true;

}
