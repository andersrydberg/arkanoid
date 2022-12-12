//
// Created by Anders Rydberg on 2022-12-08.
//

#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <string>
#include "Component.h"

class Group {
public:
    explicit Group(const std::string& name);
    virtual ~Group();

    const std::string& getName() const {return name;}
    std::vector<Component*>& getContents() {return comps;}

    void push_back(Component* comp);
private:
    std::string name;
    std::vector<Component*> comps;
};


#endif
