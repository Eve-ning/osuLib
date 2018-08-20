#include "stdafx.h"
#include "OsuObject.h"

OsuObject::OsuObject() : m_offset(0) {}
OsuObject::~OsuObject() {}

double OsuObject::offset() const
{
	return m_offset.value();
}

void OsuObject::setOffset(const double & offset)
{
	m_offset.setValue(offset);
}
