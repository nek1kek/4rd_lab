#pragma once
#include "exception.h"
#include "Sequence.h"
#include "Iterators.h"

template<typename T, bool IsConst>
class RandomAccessIterator;

template<typename T>
class DynamicArray;//������� ������� �����,����� �� �������� ������


template<typename V>
struct ArrayIterators;//� ������� �����������

template<typename T>//����������  ����� ������������
size_t distance(typename DynamicArray<T>::iterator begin, typename DynamicArray<T>::iterator end) {
	size_t res = 0;
	while (begin != end) {
		begin++;
		res++;
	}
	return res;
}

template<typename T, bool IsConst>
class RandomAccessIterator {
	template<typename T> friend class DynamicArray; 
private:
	size_t cur_pos = 0;
	using type = std::conditional_t<IsConst, const T, T>;
	DynamicArray<T>* arr = nullptr;
public:
	RandomAccessIterator(size_t pos, DynamicArray<T>* arr) : arr(arr) {
		cur_pos = pos;
	}
	RandomAccessIterator(const RandomAccessIterator<T, IsConst>& other) : arr(other.arr) {
		cur_pos = other.cur_pos;
	}
	type& operator *() {
		return arr->Get(cur_pos);
	}
	RandomAccessIterator<T, IsConst> operator ->() const {
		return *this;
	}
	RandomAccessIterator<T, IsConst>& operator++() {
		cur_pos++;
		return *this;
	}
	RandomAccessIterator<T, IsConst>& operator--() {
		cur_pos--;
		return *this;
	}
	RandomAccessIterator<T, IsConst>& operator++(int) {
		cur_pos++;
		return *this;
	}
	RandomAccessIterator<T, IsConst>& operator--(int) {
		cur_pos--;
		return *this;
	}
	RandomAccessIterator<T, IsConst>& operator+=(int t) {
		cur_pos += t;
		return *this;
	}
	RandomAccessIterator<T, IsConst>& operator-=(int t) {
		cur_pos -= t;
		return *this;
	}
	RandomAccessIterator<T, IsConst> operator+(int t) {
		RandomAccessIterator<T, IsConst> newIterator(cur_pos + t, this->arr);
		return newIterator;
	}

	RandomAccessIterator<T, IsConst> operator-(int t) {
		RandomAccessIterator<T, IsConst> newIterator(cur_pos - t, this->arr);
		return newIterator;
	}
	bool operator != (const RandomAccessIterator<T, IsConst>& other) {
		if (other.cur_pos != this->cur_pos) return true;
		if (other.arr != this->arr) return true;
		return false;
	}
	bool operator == (const RandomAccessIterator<T, IsConst>& other) {
		if (other.cur_pos != this->cur_pos) return false;
		if (other.arr != this->arr) return false;
		return true;
	}
};


template <class T>
class DynamicArray
{
	template<typename T, bool V>
	friend class RandomAccessIterator;//� ���� ���� ������ � �������� ���������� ������ DynamicArray
private:
	T* items = nullptr;//��������� �� 1�������
	int size = 0;//������� ����� ����
	size_t used_items = 0;//������� ��� ������� �����
public:
	//��������
	using iterator = RandomAccessIterator<T, false>;//�������������� � ���� ������ �����
	using const_iterator = RandomAccessIterator<T, true>;
	iterator begin() {
		iterator iter(0, this);
		return iter;
	}
	const_iterator cbegin() {
		const_iterator iter(0, this);
		return iter;
	}
	iterator end() {
		iterator iter(used_items, this);
		return iter;
	}
	const_iterator cend() {
		const_iterator iter(used_items, this);
		return iter;
	}
	//������������
	DynamicArray();
	DynamicArray(size_t, T);
	DynamicArray(T*, int);
	DynamicArray(DynamicArray<T>*);
	DynamicArray(std::initializer_list<T>);

	//�������������
	~DynamicArray();

	//�������
	T& Get(int);
	int GetSize();

	//��������
	void Set(int, T);
	void Resize(int);
	void Append(T);
	void Prepend(T);
	void InsertAt(T, iterator);
	DynamicArray<T>* GetSubArray(iterator, iterator);
	DynamicArray<T>* Concat(DynamicArray<T>*);
	void del_item(iterator);
	iterator find(iterator, iterator, T);
	bool Equals(DynamicArray<T>*);
	bool IsSubArr(DynamicArray<T>*);

	//���������
	T& operator[] (int index);
	bool operator==(DynamicArray<T>& seq);
	bool operator!=(DynamicArray<T>& seq);
};


//������������
template <class T>
DynamicArray<T>::DynamicArray() {
	items = nullptr;
}

template <class T>
DynamicArray<T>::DynamicArray(size_t count, T fill) {
	if (count < 0) throw SetException(SizeBelowZero);
	items = new T[(count + 1) * 2];//������ �������� �������, ���������� ����� + � ��� ���� ������ �� ������ ������
	size = count * 2;
	used_items = count;
	for (int i = 0; i < count; i++) {
		items[i] = fill;
	}
}
template <class T>
DynamicArray<T>::DynamicArray(T* items, int count) {
	if (count < 0) throw SetException(SizeBelowZero);
	this->items = new T[(count + 1) * 2];
	size = count * 2;
	used_items = count;
	for (int i = 0; i < count; i++) {
		this->items[i] = items[i];
	}
}
template <class T>
DynamicArray<T>::DynamicArray(DynamicArray<T>* dynamic_array) {
	items = new T[dynamic_array->size];
	size = dynamic_array->size;
	used_items = dynamic_array->used_items;
	for (int i = 0; i < size; i++) {
		items[i] = dynamic_array->items[i];
	}
}

template<class T>
DynamicArray<T>::DynamicArray(std::initializer_list<T> list) : DynamicArray(list.size(), T()) {
	int j = 0;
	for (auto i : list) {
		this->items[j] = i;
		j++;
	}
}


//����������
template <class T>
DynamicArray<T>::~DynamicArray() {
	delete[] this->items;
}


//�������
template <class T>
T& DynamicArray<T>::Get(int index) {
	if (index >= used_items || index < 0) {
		throw SetException(IndexOutOfRange);
	}
	return items[index];
}


//��������


template <class T>
void DynamicArray<T>::Resize(int NewSize) {
	if (NewSize < 0) {
		throw SetException(SizeBelowZero);
	}
	try {
		T* items_cur = new T[NewSize];
		int cpy_num = (NewSize > size ? size : NewSize);//����� ����������� 
		memcpy(items_cur, items, cpy_num * sizeof(T));//cpy_num = copy_num
		delete[] items;
		items = items_cur;
		size = NewSize;
	}
	catch (std::bad_alloc) {
		throw SetException(MemoryAllocateError);
	}
}

template <class T>
void DynamicArray<T>::Append(T item) {
	if (used_items >= size) {
		this->Resize((size + 1) * 2);
	}
	used_items++;
	this->Set(used_items - 1, item);
	
}

template <class T>
void DynamicArray<T>::Prepend(T item) {
	if (used_items >= size) {
		this->Resize((size + 1) * 2);
	}
	memmove(this->items + 1, this->items, (used_items) * sizeof(T));
	this->Set(0, item);
	used_items++;
}

template <class T>
void DynamicArray<T>::InsertAt(T item, iterator it) {
	if (it == end()) {
		throw SetException(IndexOutOfRange);
	}
	if (used_items >= size) {
		this->Resize((size + 1) * 2);
	}

	memmove(this->items + distance<T>(begin(), it) + 1, this->items + distance<T>(begin(), it), (used_items - distance<T>(begin(), it)) * sizeof(T));
	*it = item;
	it++;
	used_items++;
}

template <class T>
DynamicArray<T>* DynamicArray<T>::GetSubArray(iterator start, iterator end) {
	if (start == this->end() || end == this->end() || distance<T>(begin(), start) > distance<T>(begin(), end)) {
		throw SetException(IndexOutOfRange);
	}
	DynamicArray<T>* res = new DynamicArray<T>;
	for (iterator i = start; i != end; i++) {
		res->Append(*i);
	}
	return res;
}

template <class T>
DynamicArray<T>* DynamicArray<T>::Concat(DynamicArray<T>* arr) {
	DynamicArray<T>* res = new DynamicArray<T>;
	for (int i = 0; i < used_items; i++) {
		res->Append(this->Get(i));
	}
	for (int i = 0; i < arr->GetSize(); i++) {
		res->Append(arr->Get(i));
	}
	return res;
}

template <class T>
void DynamicArray<T>::del_item(iterator it) {
	if (it == end()) {
		throw SetException(IndexOutOfRange);
	}
	memmove(items + distance<T>(begin(), it), items + distance<T>(begin(), it) + 1, (used_items - 1 - distance<T>(begin(), it)) * sizeof(T));//��������� ����, ��������� ������, � �������
	used_items--;
	if (used_items <= (size / 2)) {
		this->Resize(this->size / 2);
	}
}


template <class T>
typename DynamicArray<T>::iterator DynamicArray<T>::find(iterator start, iterator end, T item) {
	if (used_items == 0) return this->end();
	if (distance<T>(begin(), start) > distance<T>(begin(), end)) {
		throw SetException(IndexOutOfRange);
	}
	for (iterator i = start; i != end; i++) {
		if ((*i) == item) return i;
	}
	return this->end();
}

template <typename T>
void DynamicArray<T>::Set(int index, T value) {
	if (index > this->used_items || index < 0) {
		throw SetException(IndexOutOfRange);
	}
	items[index] = value;
}



template <class T>
bool DynamicArray<T>::Equals(DynamicArray<T>* seq) {
	if (this->GetSize() != seq->GetSize()) return false;
	for (int i = 0; i < seq->GetSize(); i++) {
		if (this->Get(i) != seq->Get(i)) return false;
	}
	return true;
}

template <class T>
bool DynamicArray<T>::IsSubArr(DynamicArray<T>* seq) {
	iterator pos = begin();
	for (int i = 0; i < seq->GetSize() && (pos != end()); i++) {
		pos = this->find(pos, end() - 1, seq->Get(i));
	}
	return pos != end();
}

//���������
template <class T>
T& DynamicArray<T>:: operator[] (int index) {
	return this->Get(index);
}

template <class T>
bool DynamicArray<T>:: operator==(DynamicArray<T>& seq) {
	return this->Equals(&seq);
}

template <class T>
bool DynamicArray<T>::operator!=(DynamicArray<T>& seq) {
	return !this->Equals(&seq);
}

template<class T>
int DynamicArray<T>::GetSize() {
	return used_items;
}

