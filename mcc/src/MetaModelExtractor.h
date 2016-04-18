#ifndef METAMODELEXTRACTOR_H
#define METAMODELEXTRACTOR_H

class Table;

class MetaModelExtractor {

protected:

    /**
     * @supplierCardinality 0..* */

    virtual void createTables() =0;

public:

    virtual bool extract() =0;

};
#endif //METAMODELEXTRACTOR_H