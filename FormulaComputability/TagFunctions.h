#pragma once
#ifndef _TAGFURMULA_H
#define _TAGFURMULA_H

#include "Tag.h"

template< CType TArg,CType TRes>
class CTagFunction : public CTag
{
public:
	CNode checkArgument(const CNode& node)const;//check that node is correct argument and return node.next_sibling()
	virtual void operator ()(const CNode& node)const;
	CTagFunction() {
		type = TArg | FUNCTION | CALCULATEBLE;
	};
};

template< CType TArg,CType TRes>
CNode CTagFunction<TArg, TRes>::checkArgument(const CNode& node)const
{
	if (node.empty())
		throwException(node.name(), node.offset_debug(), INVALID_ARGUMENT);
	CType argType = CTagContainer::getTag(node.name())->type;
	if ((!(argType & TArg)) || (argType & (~TArg)))
		throwException(node.name(), node.offset_debug(), INVALID_ARGUMENT);
	return node.next_sibling();
};

template< CType TArg,CType TRes>
void CTagFunction<TArg, TRes>::operator ()(const CNode& node)const
{
	hasNoAttributes(node);
	hasNoChilds(node);
	hasNoText(node);
};

//function with various arguments
template< CType TArg,CType TRes>
class CTagVarArgFunction : public CTagFunction<TArg, TRes>
{
public:
	virtual const CNode checkSignature(const CNode& node)const;
};

//function with CountArg arguments
template< CType TArg, CType TRes, int CountArg>
class CTagNArgFunction : public CTagFunction<TArg, TRes>
{
public:
	virtual const CNode checkSignature(const CNode& node)const;
};

template< CType TArg,CType TRes>
const CNode CTagVarArgFunction<TArg, TRes>::checkSignature(const CNode& node)const
{
	auto arg = CTagFunction<TArg, TRes>::checkArgument(node.next_sibling());
	while (!arg.empty())
	{
		arg = CTagFunction<TArg, TRes>::checkArgument(arg.next_sibling());
	};
	return arg;
};

template< CType TArg, CType TRes, int CountArg>
const CNode CTagNArgFunction<TArg, TRes, CountArg>::checkSignature(const CNode& node)const
{
	auto arg = node;
	for (int i = 0; i < CountArg; ++i)
	{
		arg = CTagFunction<TArg, TRes>::checkArgument(arg.next_sibling());
	};
	return arg;
};

#endif