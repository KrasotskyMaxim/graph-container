#pragma once
template <class GraphIteratorType>
class GraphIterator
{
	const GraphIteratorType* ptr;
	bool reverse;
public:
	GraphIterator() { this->reverse = false; }
	GraphIterator(const GraphIteratorType* ptr)
	{
		this->ptr = ptr;
		this->reverse = false;
	}
	GraphIterator(const GraphIteratorType* ptr, bool reverse)
	{
		this->ptr = ptr;
		this->reverse = reverse;
	}
	~GraphIterator() {}

	void operator=(GraphIteratorType* ptr) {
		this->ptr = ptr;
	}
	const GraphIteratorType* operator+(int n) {
		if (!this->reverse) {
			return this->ptr + n;
		}
		else {
			return this->ptr - n;
		}
	}
	const GraphIteratorType* operator-(int n) {
		if (!this->reverse) {
			return this->ptr - n;
		}
		else {
			return this->ptr + n;
		}
	}
	const GraphIteratorType* operator++(int) {
		if (!this->reverse) {
			return this->ptr++;
		}
		else {
			return this->ptr--;
		}
	}
	const GraphIteratorType* operator--(int) {
		if (!this->reverse) {
			return this->ptr--;
		}
		else {
			return this->ptr++;
		}
	}
	const GraphIteratorType* operator++() {
		if (!this->reverse) {
			return ++this->ptr;
		}
		else {
			return --this->ptr;
		}
	}
	const GraphIteratorType* operator--() {
		if (!this->reverse) {
			return --this->ptr;
		}
		else {
			return ++this->ptr;
		}
	}
	bool operator!=(GraphIterator& it) { return this->ptr != it.ptr; }
	bool operator==(GraphIterator& it) { return this->ptr == it.ptr; }
	const GraphIteratorType& operator*() { return *this->ptr; }
};

