#include "InheritanceTable.h"
#include "ConcreteTableColumn.h"
#include "InheritanceRelation.h"
#include "TypesTable.h"
#include "MapAll.h"
#include "InheritanceDescendent.h"
#include "InheritanceParent.h"
#include "InheritanceDepth.h"
#include "InheritanceAccess.h"
#include "Limits.h"

InheritanceTable::InheritanceTable(char *name,TypesTable *types):Table(name) {

	this->types = types;

}

InheritanceTable::~InheritanceTable() {}

void InheritanceTable::init() {

	buildColumn(std::string("DescendentId"));
	buildColumn(std::string("ParentId"));
	buildColumn(std::string("Attribute"));
	buildColumn(std::string("Depth"));

}

void InheritanceTable::extract(ATCollection &trees) {

	MapAll::VectorOfChain myVector;
	MapAll::VectorOfTrigger myTrigger;

	ConcreteTableColumn columnDescendent(std::string("DescendentId"),true);
	ConcreteTableColumn columnParent(std::string("ParentId"),true);
	ConcreteTableColumn columnAttribute(std::string("Attribute"),true);
	ConcreteTableColumn columnDit(std::string("Depth"),true);

	InheritanceRelation iCondition;
	myTrigger.push_back(&iCondition);

	InheritanceDescendent columnDescExtractor0(NULL,&columnDescendent,&iCondition,types);
	
	InheritanceParent columnParentExtractor0(NULL,&columnParent,&iCondition,types);

	InheritanceAccess columnAttributeExtractor0(NULL,&columnAttribute,&iCondition);

	InheritanceDepth columnDitExtractor0(NULL,&columnDit,&iCondition);

	myVector.push_back(&columnDescExtractor0);
	myVector.push_back(&columnParentExtractor0);
	myVector.push_back(&columnAttributeExtractor0);
	myVector.push_back(&columnDitExtractor0);

	MapAll element(trees,&myVector,&myTrigger);
	element.accept(this);

	int i,j,k;
	int **matrix;
	TableRow *row;
	TableColumn *col;
	std::string parent,child,value;
	char buff[12];

	//Matrix allocation
	matrix = new int*[vertex_index.size()];
	for(i = 0; i < vertex_index.size(); i++) {
		matrix[i] = new int[vertex_index.size()];
		for(j = 0; j < vertex_index.size(); j++) {
			matrix[i][j] =  INT_MAX / 4;
		}
	}

	//Matrix initialisation
	IdMapper::iterator it;
	std::string parentId = "ParentId";
	std::string descendentId = "DescendentId";
	for(it=iMapper.begin();it != iMapper.end(); ++it) {
		row = (*it).second;
		parent = row->getValue(col_id[parentId]);
		child  = row->getValue(col_id[descendentId]);
		if(parent == "<ERROR>" || child == "<ERROR>") continue;
		matrix[vertex_index[child]][vertex_index[parent]] = -1;
	}
	
	//Running algorithm
	for(k = 0; k < vertex_index.size(); k++)
		for(i = 0; i < vertex_index.size(); i++)
			for(j = 0; j < vertex_index.size(); j++) {
				if(i != j && 
				   matrix[i][k] != INT_MAX / 4 && matrix[k][j] != INT_MAX / 4 && 
				   matrix[i][j] > matrix[i][k] + matrix[k][j])
					matrix[i][j] = matrix[i][k] + matrix[k][j];
			}

	//Register results
	for(i = 0; i < vertex_index.size(); i++)
		for(j = 0; j < vertex_index.size(); j++)
			if(matrix[i][j] < -1 && matrix[i][j] != INT_MAX / 4) {
				row = new TableRow();
				col = new ConcreteTableColumn(std::string("DescendentId"),true);
				child = index_vertex[i];
				col->init(child,true);
				row->add(col);
				col = new ConcreteTableColumn(std::string("ParentId"),true);
				parent = index_vertex[j];
				col->init(parent,true);
				row->add(col);
				col = new ConcreteTableColumn(std::string("Attribute"),true);
				value = "NULL";
				col->init(value,false,-1 * matrix[i][j],TableColumn::MergeByCopy);
				row->add(col);
				col = new ConcreteTableColumn(std::string("Depth"),true);
				sprintf(buff,"%d",-1 * matrix[i][j]);
				value = buff;
				col->init(value,false,-1 * matrix[i][j],TableColumn::MergeByCopy);
				row->add(col);
				Table::insertRow(row);
			}

	//Deallocation
	for(i = 0; i < vertex_index.size(); i++)
		delete matrix[i];
	delete matrix;

	finalize();
}

bool InheritanceTable::insertRow(TableRow * row) {
	
	std::string parentId		= "ParentId";
	std::string descendentId	= "DescendentId";

	std::string parent = row->getValue(col_id[parentId]);
	std::string child  = row->getValue(col_id[descendentId]);
	static int index = -1;

	if(Table::insertRow(row)) {
		if(parent != "<ERROR>" && vertex_index.find(parent) == vertex_index.end()) {
			vertex_index[parent] = ++index;
			index_vertex[index] = parent;
		}
		if(child != "<ERROR>" && vertex_index.find(child) == vertex_index.end()) {
			vertex_index[child] = ++index;
			index_vertex[index] = child;
		}
		return true;
	} else {
		delete row;
		return false;
	}
}
