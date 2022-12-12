//
// Created by Anders Rydberg on 2022-12-08.
//

#include "Group.h"

Group::Group(const std::string &name) : name(name) {

}

Group::~Group() {

}

void Group::push_back(Component *comp) {
    comps.push_back(comp);
}
