#ifndef LOOSEEXTRACTOR_H
#define LOOSEEXTRACTOR_H

#include "MetaModelExtractor.h"
#include "FilesParser.h"
#include "PackagesTable.h"
#include "NamespaceTable.h"
#include "TypesTable.h"
#include "TemplateInstanceChainsTable.h"
#include "TemplateParTypesRelation.h"
#include "BodyTable.h"
#include "FuncsTable.h"
#include "VariablesTable.h"
#include "InheritanceTable.h"
#include "AccessTable.h"
#include "CallTable.h"

#include <string>

class LOOSEExtractor : public MetaModelExtractor {

public:

    LOOSEExtractor(std::string*, std::string*, std::string*);
	~LOOSEExtractor();
	virtual bool extract();

protected:

	virtual void createTables();

private:    

    /** @link dependency */
    /*# FilesParser lnkFilesParser; */

	std::string *source_dir,*dest_dir,*conf_file;

    /**
     * @supplierCardinality 1 
     */
	PackagesTable *packages;

    /**
     * @supplierCardinality 1 
     */
	NamespaceTable *namespaces;

    /**
     * @supplierCardinality 1 
     */
	TypesTable *types;

    /**
     * @supplierCardinality 1 
     */
	TemplateInstanceChainsTable *chains;

    /**
     * @supplierCardinality 1 
     */
	TemplateParTypesRelation *t2t;

    /**
     * @supplierCardinality 1 
     */
	FuncsTable *funcs;

    /**
     * @supplierCardinality 1 
     */
	BodyTable *body;

    /**
     * @supplierCardinality 1 
     */
	VariablesTable *vars;

    /**
     * @supplierCardinality 1 
     */
	InheritanceTable *inh;

    /**
     * @supplierCardinality 1 
     */
	AccessTable *accesses;

    /**
     * @supplierCardinality 1 
     */
	CallTable *calls;

	void print(Table*,const char*);
};
#endif //LOOSEEXTRACTOR_H