#pragma once

#include <boost/spirit/include/qi.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "bounded/BoundedDouble.h"
#include "bounded/BoundedInt.h"
#include "enums/SampleSet.h"
#include "../OsuException.h"
#include <boost/fusion/container/list.hpp>
#include <boost/fusion/include/list.hpp>
#include <boost/fusion/container/list/list_fwd.hpp>
#include <boost/fusion/include/list_fwd.hpp>

class OsuObject {
public:

	OsuObject();

	virtual ~OsuObject();

	virtual double offset() const;
	virtual void setOffset(const double &offset);

protected:

	BoundedDouble m_offset = BoundedDouble(0, 0);

};
