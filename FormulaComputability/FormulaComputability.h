#pragma once
#ifndef _FORMULACOMPUTALILITY_H
#define _FORMULACOMPUTALILITY_H

#include "CTagContainer.h"
#include "../pugixml/pugixml.hpp"
#include "Tag.h"
#include "TagCi.h"

using namespace pugi;

//основной класс, проверяющмй вычислимость формулы
class FormulaComputability
{
public:
	FormulaComputability();
    static bool checkComputability(const CNode& rootNode);//проверяет вычислимость формулы, 
                                                        //rootNode - корневой элемент xml-документа
	~FormulaComputability();
};

#endif