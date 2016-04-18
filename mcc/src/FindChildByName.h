#ifndef FINDCHILDBYNAME_H
#define FINDCHILDBYNAME_H

#include "fast_include.h"
#include <string>

class FindChildByName {

public:

    VTP_TreeP find(VTP_TreeP &tree, std::string name);

};
#endif //FINDCHILDBYNAME_H