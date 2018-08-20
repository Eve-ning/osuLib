#pragma once
#include "osuobject.h"

template <class ObjType>
class OsuObjectList {
public:

	OsuObjectList() : m_value() {}
	OsuObjectList(const OsuObjectList&) = default;
	OsuObjectList(OsuObjectList&&) = default;
	OsuObjectList& operator=(const OsuObjectList&) & = default;
	OsuObjectList& operator=(OsuObjectList&&) & = default;

	OsuObjectList(std::vector<std::shared_ptr<ObjType>> value) : m_value(value) {}

	virtual ~OsuObjectList() {}

	std::shared_ptr<OsuObjectList> clone() const { return doClone(); }
	virtual void append(std::shared_ptr<ObjType> value) {
		m_value.push_back(value);
	}

	virtual std::vector<double> offsetList() const {
		std::vector<double> output = {};
			for (std::shared_ptr<ObjType> TP : m_value) { output.push_back(TP->offset()); }
		return output;
	}
	virtual void setOffsetList(const std::vector<double> &value) {
		if (!sameSize(value)) {
			return;
		}
		for (int i = 0; i < size(); ++i) {
			m_value[i]->setOffset(value[i]);
		}
	}

	virtual typename std::shared_ptr<ObjType> operator [](int i) { return at(i); }
	virtual typename std::shared_ptr<ObjType> at(int i) {
		if (i < size() && i >= 0) {
			return m_value.at(i);
		}
		else {
			std::cout << "Index on OOL out of range.";
			return m_value.at(0);
		}
	}

	virtual double min() const {
		auto offset_list = offsetList();
		return *std::min_element(offset_list.begin(), offset_list.end());
	}
	virtual double max() const {
		auto offset_list = offsetList();
		return *std::max_element(offset_list.begin(), offset_list.end());
	}

	virtual size_t size() const {
		return m_value.size();
	}
	virtual void sort(bool isAscending = true) {
		std::sort(m_value.begin(), m_value.end(),
			[isAscending](std::shared_ptr<ObjType> a,
				std::shared_ptr<ObjType> b) {
			if (isAscending) {
				return a->offset() < b->offset();
			}
			else {
				return a->offset() > b->offset();
			}
		});
	}
	virtual double length() const {
		return max() - min();
	}

	virtual std::vector<std::shared_ptr<ObjType>> value() const { return m_value; }
	virtual void setValue(const std::vector<std::shared_ptr<ObjType>> &value) { m_value = value; }

	virtual typename std::vector<std::shared_ptr<ObjType>>::const_iterator begin() const { return m_value.begin(); }
	virtual typename std::vector<std::shared_ptr<ObjType>>::const_iterator end() const { return m_value.end(); }

	std::vector<double> unqOffsetList() const {
		std::vector<double> v_offsetList = offsetList();
		std::vector<double> unq_offsetList = {};

		std::for_each(v_offsetList.begin(), v_offsetList.end(), [&](double &offset) {
			if (std::find(unq_offsetList.begin(), unq_offsetList.end(), offset) == unq_offsetList.end()) {
				unq_offsetList.push_back(offset);
			}
		});

		return unq_offsetList;
	}

protected:

	std::vector<std::shared_ptr<ObjType>> m_value = {};

	template <typename T>
	bool sameSize(std::vector<T> compare) {
		if (this->size() == compare.size()) {
			return true;
		}

		throw OsuException(OsuException::ID::MISMATCH_SET_LENGTH);
	}

	virtual std::shared_ptr<OsuObjectList> doClone() const {
		std::vector<std::shared_ptr<ObjType>> output;
		output = std::move(m_value);
		return std::make_shared<OsuObjectList>(m_value);
	}
};
