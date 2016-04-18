#ifndef PACKAGEID_H
#define PACKAGEID_H

#include "DataExtractor.h"
#include "PackageName.h"
#include "Always.h"
#include "PackagesTable.h"

class PackageID : public DataExtractor {

public:

	PackageID(DataExtractor *next, ConcreteTableColumn *prototype, TriggerCondition *condition, PackagesTable *packages);

	~PackageID();

protected:

    virtual TableColumn *handleExtraction(AbstractTree &tree);

private:    

    /**
     * @supplierCardinality 1 
     */
    PackageName *lnkPackageName;

	PackagesTable *packages;

	Always *tmp_condition;
};
#endif //PACKAGEID_H