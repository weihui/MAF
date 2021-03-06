/*
 *  mafVisitorFindObjectsByHashCode.h
 *  mafCore
 *
 *  Created by Daniele Giunchi on 16/09/09.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#include "mafObject.h"
#include "mafVisitorFindObjectsByHashCode.h"

using namespace mafCore;

mafVisitorFindObjectsByHashCode::mafVisitorFindObjectsByHashCode(const QString code_location) : mafVisitorFindObjects(code_location) {
}


mafVisitorFindObjectsByHashCode::mafVisitorFindObjectsByHashCode(const QString hash_code, const QString code_location) : mafVisitorFindObjects(code_location) , m_HashCode(hash_code) {
}

mafVisitorFindObjectsByHashCode::~mafVisitorFindObjectsByHashCode() {
}

void mafVisitorFindObjectsByHashCode::visit(mafObjectBase *object) {
    // Check if given object has the same hash code of that one stored into the visitor.
    if(m_HashCode == object->objectHash()) {
        // If both are equal, add the object to the result list.
        if(!m_ObjectsList->contains(object)) {
            m_ObjectsList->push_back(object);
        }
    }
}
