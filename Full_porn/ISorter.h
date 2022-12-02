#pragma once
#include "Sequence.h"
#include <math.h>
#include <algorithm>
#include <iterator>
#define cmp__up(T) [](T a, T b)->bool { return a <= b; }
#define cmp__down(T) [](T a, T b)->bool { return a >= b; }
#define cmp__odd_even_up(T) [](T a, T b)->bool { return Auxillary::odd<T>::_odd(a) == Auxillary::odd<T>::_odd(b) ? a <= b : Auxillary::odd<T>::_odd(a) <= Auxillary::odd<T>::_odd(b); }
#define cmp__odd_even_down(T) [](T a, T b)->bool { return Auxillary::odd<T>::_odd(a) == Auxillary::odd<T>::_odd(b) ? a >= b : Auxillary::odd<T>::_odd(a) <= Auxillary::odd<T>::_odd(b); }
#define cmp__even_odd_up(T) [](T a, T b)->bool { return Auxillary::odd<T>::_odd(a) == Auxillary::odd<T>::_odd(b) ? a <= b : Auxillary::odd<T>::_odd(a) >= Auxillary::odd<T>::_odd(b); }
#define cmp__even_odd_down(T) [](T a, T b)->bool { return Auxillary::odd<T>::_odd(a) == Auxillary::odd<T>::_odd(b) ? a >= b : Auxillary::odd<T>::_odd(a) >= Auxillary::odd<T>::_odd(b);}
#define cmp__digits_count_up(T) [](T a, T b)->bool { return Auxillary::count<T>::cnt(a) <= Auxillary::count<T>::cnt(b);}
#define cmp__digits_count_down(T) [](T a, T b)->bool { return Auxillary::count<T>::cnt(a) >= Auxillary::count<T>::cnt(b); }
#define cmp__digits_sum_up(T) [](T a, T b)->bool { return Auxillary::sum<T>::sum_d(a) <= Auxillary::sum<T>::sum_d(b); }
#define cmp__digits_sum_down(T) [](T a, T b)->bool { return Auxillary::sum<T>::sum_d(a) >= Auxillary::sum<T>::sum_d(b); }

#define it(T, _It) typename Sequence<T, _It>::iterator

namespace Auxillary {//спецификация  функций(вспомогательных)
	template<typename T>
	struct sum {
		static int sum_d(T a) {
			throw SetException(IncorrectComparator);
		}
	};
	template<>
	struct sum<int> {
		static int sum_d(int a) {
			int res = 0;
			while (a > 0) {
				res += a % 10;
				a /= 10;
			}
			return res;
		}
	};

	template<typename T>
	struct count {
		static int cnt(T a) {
			throw SetException(IncorrectComparator);
		}
	};
	template<>
	struct count<int> {
		static int cnt(int a) {
			int res = 0;
			while (a > 0) {
				res += 1;
				a /= 10;
			}
			return res;
		}
	};

	template<typename T>
	struct odd {
		static int _odd(T a) {
			throw SetException(IncorrectComparator);
		}
	};
	template<>
	struct odd<int> {
		static int _odd(int a) {
			return a % 2;
		}
	};

	template<typename T>
	void swap(T& first, T& second) {
		T cur = first;
		first = second;
		second = cur;
	}
}

enum SortType { ShakerSort, BinaryInsertionSort, MergeSort, QuickSort, BitonicSort };


template<typename T, class _Iterators>
class ISorter {//абстрактный класс сортировок
public:
	virtual void sort(typename Sequence<T, _Iterators>::iterator, typename Sequence<T, _Iterators>::iterator, bool (T, T) = cmp__up(T)) = 0;//ФУНКЦИЯ НИХУЯ НЕ ДЕЛАЕТ ТИПО PASS БЛЯТЬ 
	virtual SortType GetType() = 0;
};


template<class T, class _Iterators>//ТУТ КЛАСС НАСЛЕДУЕТСЯ ОТ ВЕРХНЕГО, НО САМ НАПИСАН БУДЕТ ПОЗЖЕ   
class Shaker_Sort : public ISorter<T, _Iterators> {
public:
	void sort(typename Sequence<T, _Iterators>::iterator, typename Sequence<T, _Iterators>::iterator, bool (T, T) = cmp__up(T)) override;
	SortType GetType() override;
};

template<class T, class _Iterators>
class Binary_Insertion_Sort : public ISorter<T, _Iterators> {
public:
	void sort(typename Sequence<T, _Iterators>::iterator, typename Sequence<T, _Iterators>::iterator, bool (T, T) = cmp__up(T)) override;
	SortType GetType() override;
};

template<class T, bool X>
class BidirectionalIterator;

template<class T, class _Iterators>
class Merge_Sort : public ISorter<T, _Iterators> {
private:
	template<typename V, bool X> friend class BidirectionalIterator;
	typename Sequence<T, _Iterators>::iterator& sort1(typename Sequence<T, _Iterators>::iterator, typename Sequence<T, _Iterators>::iterator, size_t, bool(T, T) = cmp__up(T));
public:
	void sort(typename Sequence<T, _Iterators>::iterator, typename Sequence<T, _Iterators>::iterator, bool(T, T) = cmp__up(T)) override;
	SortType GetType() override;
};

template<class T>
class Merge_Sort<T, ArrayIterators<T>> : public ISorter<T, ArrayIterators<T>> {
	void sort2(typename Sequence<T, ArrayIterators<T>>::iterator, typename Sequence<T, ArrayIterators<T>>::iterator, size_t, bool(T, T) = cmp__up(T));

public:
	void sort(typename Sequence<T, ArrayIterators<T>>::iterator, typename Sequence<T, ArrayIterators<T>>::iterator, bool(T, T) = cmp__up(T)) override;
	SortType GetType() override;
};

template<class T, class _Iterators>
class Quick_Sort : public ISorter<T, _Iterators> {
private:
	size_t partition(typename Sequence<T, _Iterators>::iterator, typename Sequence<T, _Iterators>::iterator, size_t, bool (T, T));
	void sort(typename Sequence<T, _Iterators>::iterator, typename Sequence<T, _Iterators>::iterator, size_t, bool(T, T));
public:
	void sort(typename Sequence<T, _Iterators>::iterator, typename Sequence<T, _Iterators>::iterator, bool(T, T) = cmp__up(T)) override;
	SortType GetType() override;
};

template<class T, class _Iterators>
class Bitonic_Sort : public ISorter<T, _Iterators> {
private:
	void bitonic_merge(typename Sequence<T, _Iterators>::iterator, typename Sequence<T, _Iterators>::iterator, size_t, bool (T, T), bool);
	void sort(typename Sequence<T, _Iterators>::iterator, typename Sequence<T, _Iterators>::iterator, size_t, bool (T, T), bool);
	void sort(typename Sequence<T, _Iterators>::iterator, typename Sequence<T, _Iterators>::iterator, size_t, bool(T, T));

public:
	void sort(typename Sequence<T, _Iterators>::iterator, typename Sequence<T, _Iterators>::iterator, bool(T, T) = cmp__up(T)) override;

	SortType GetType() override;
};



//туда сюда гоняет, меня с признаком cmp друг за другом, и ставя спереди наибольший элемент, и назад, ставя на первое наименьший и т.п.
//shakersort
/*
http://algolab.valemak.com/cocktail
Худшая	O(n2)
Средняя	O(n2)
Лучшая	O(n)
Общая	O(n)
Сложность по памяти:
Дополнительная	O(1)
Средняя	O(n2)
*/
template<typename T, class _Iterators>//ДВОЕТОЧИЕ ТИПО ТУТ ФУНКЦИИ ОПИСЫВАЕМ У ЭТИХ 5 НАСЛЕДОВАННЫХ КЛАССОВ
void Shaker_Sort<T, _Iterators>::sort(typename Sequence<T, _Iterators>::iterator begin, typename Sequence<T, _Iterators>::iterator end, bool cmp(T, T)) {
	while (begin != end) {//то есть могут
		bool flag = false;
		for (typename Sequence<T, _Iterators>::iterator i = begin; (i+1) != end; i++) {
			if (!cmp(*i, *(i + 1))) {
				Auxillary::swap(*i, *(i + 1));
				flag = true;
			}
		}
		if (!flag) {
			return;
		}
		for (typename Sequence<T, _Iterators>::iterator i = end - 1; i != begin; i--) {
			if (!cmp(*(i - 1), *(i))) {
				Auxillary::swap(*i, *(i - 1));
			}
		}
		begin++;
		end--;
	}
	return;
}

template<typename T, class _Iterators>
SortType Shaker_Sort<T, _Iterators>::GetType() {
	return ShakerSort;
}


//сортировка подмассивом с бинарным поиском для вставки
//binary insertion sort 
/*
http://www.algolab.valemak.com/insertion-binary-search

Сложность по времени:
Худшая	O(n2 / 2)
Средняя	O(n2 / 4)
Лучшая	O(n)

Сложность по памяти:
Общая	O(n)
Дополнительная	O(1)
*/

template<typename T, class _Iterators>
void Binary_Insertion_Sort<T, _Iterators>::sort(typename Sequence<T, _Iterators>::iterator begin, typename Sequence<T, _Iterators>::iterator end, bool cmp(T, T)) {
	size_t sorted = 0;
	size_t low = 0;
	size_t high = distance<T>(begin, end);
	for (int i = low + 1; i < high; i++) {
		int left = low - 1;
		int right = i;
		T key = *(begin + i);
		int pos = 0;
		while (left < right - 1) {
			int mid = (left + right) / 2;
			bool leftcheck = cmp(*(begin + mid), key);
			bool rightcheck = mid + 1 >= i || cmp(key, *(begin + mid + 1));
			if (leftcheck && rightcheck) {//вот и бинарный поиск
				pos = mid + 1;
			}
			if (leftcheck) {
				left = mid;
			}
			else if (rightcheck) {
				right = mid;
			}
			else {
				throw SetException(IncorrectComparator);
			}
		}
		for (int j = i; j > pos; j--) {//двигаем все направо
			*(begin + j) = *(begin + j - 1);
		}
		*(begin + pos) = key;//ебать вставляем
	}
	return;
}
template<typename T, class _Iterators>
SortType Binary_Insertion_Sort<T, _Iterators>::GetType() {
	return BinaryInsertionSort;
}


//массив разбиваем на подмассивы по 2, потом сортируем, потом хуячим массивы из 4, и т.д.
//Merge_Sort
/*
http://algolab.valemak.com/merge-simple

Сложность по времени:
Худшая	O(n log n)
Средняя	O(n log n)
Лучшая	O(n log n)

сделано две, потому что на списке быстрее работы, так как вставка сделана быстрее

Сложность по памяти:
Общая	O(n)
Дополнительная	O(n)
*/

template<typename T, class _Iterators>
typename Sequence<T, _Iterators>::iterator& Merge_Sort<T, _Iterators>::sort1(typename Sequence<T, _Iterators>::iterator begin, typename Sequence<T, _Iterators>::iterator end, size_t length, bool cmp(T, T)) {
	if (begin == (end - 1)) {//для списков
		return begin;
	}
	size_t right_i = length;
	size_t mid_i = right_i / 2;
	typename Sequence<T, _Iterators>::iterator mid = begin + mid_i;
	begin = sort1(begin, mid, (mid_i), cmp);
	mid = sort1(mid, end, length - (mid_i), cmp);
	typename Sequence<T, _Iterators>::iterator leftindex = begin;
	typename Sequence<T, _Iterators>::iterator rightindex = mid;
	size_t leftindex_i = 0;
	size_t rightindex_i = mid_i;
	while (leftindex_i < mid_i && rightindex_i < right_i) {
		if (cmp(*(leftindex), *(rightindex))) {
			leftindex++;
			leftindex_i++;
		}
		else {
			leftindex.arr->InsertAt(*rightindex, leftindex);
			if (leftindex == begin) begin--;
			leftindex.arr->del_item(rightindex);
			rightindex_i++;
		}
	}

	return begin;
}
template<typename T, class _Iterators>
void Merge_Sort<T, _Iterators>::sort(typename Sequence<T, _Iterators>::iterator begin, typename Sequence<T, _Iterators>::iterator end, bool cmp(T, T)) {
	size_t length = distance<T>(begin, end);
	this->sort1(begin, end, length, cmp);
}
template<typename T>
void Merge_Sort<T, ArrayIterators<T>>::sort(typename Sequence<T, ArrayIterators<T>>::iterator begin, typename Sequence<T, ArrayIterators<T>>::iterator end, bool cmp(T, T)) {
	size_t length = distance<T>(begin, end);
	this->sort2(begin, end, length, cmp);
}
template<typename T>
void Merge_Sort<T, ArrayIterators<T>>::sort2(typename Sequence<T, ArrayIterators<T>>::iterator begin, typename Sequence<T, ArrayIterators<T>>::iterator end, size_t length, bool cmp(T, T)) {
	if (begin == (end - 1)) {
		return;
	}
	size_t mid = (length - 1) / 2;
	size_t left_length = mid + 1;
	sort2(begin, begin + mid + 1, left_length, cmp);
	sort2(begin + mid + 1, end, length - left_length, cmp);
	size_t leftindex = 0;
	size_t rightindex = mid + 1;
	size_t resindex = 0;
	size_t right = length - 1;
	ArraySequence<T> tmp_seq;
	while (leftindex <= mid && rightindex <= right) {
		if (cmp(*(begin + leftindex), *(begin + rightindex)) && (resindex == 0 ||
			cmp(tmp_seq[resindex - 1], *(begin + leftindex)))) {
			tmp_seq.Append(*(begin + leftindex));
			leftindex++;
		}
		else {
			tmp_seq.Append(*(begin + rightindex));
			rightindex++;
		}
		resindex++;
	}
	while (leftindex <= mid) {
		tmp_seq.Append(*(begin + leftindex));
		leftindex++;
		resindex++;
	}
	while (rightindex <= right) {
		tmp_seq.Append(*(begin + rightindex));
		rightindex++;
		resindex++;
	}
	for (int i = 0; i <= right; i++) {
		*(begin + i) = tmp_seq[i];
	}
	return;
}




template<typename T, class _Iterators>
SortType Merge_Sort<T, _Iterators>::GetType() {
	return MergeSort;
}
template<typename T>
SortType Merge_Sort<T, ArrayIterators<T>>::GetType() {
	return MergeSort;
}



//quicksort

template<typename T, class _Iterators>
size_t Quick_Sort<T, _Iterators>::partition(typename Sequence<T, _Iterators>::iterator begin, typename Sequence<T, _Iterators>::iterator end, size_t length, bool cmp(T, T)) {
	size_t mid = (length - 1) / 2;
	//возьмем медианный из 1, среднего и последнего и поставим его в середину, слева маленький и справа наибольший
	if (!cmp(*begin, *(begin + mid))) Auxillary::swap<T>(*begin, *(begin + mid));
	if (!cmp(*begin, *(end - 1))) Auxillary::swap<T>(*begin, *(end-1));
	if (!cmp(*(begin + mid), *(end-1))) Auxillary::swap<T>(*(end-1), *(begin + mid));
	T pivot = *(begin + mid);// серединный элемент
	size_t i = 0;
	size_t high = length - 1;
	size_t j = high;
	//поставим слева все элементы меньше, справа те что больше
	while (true) {
		while (i <= high && cmp(*(begin + i), pivot) && *(begin + i) != pivot) i++;
		while (j >= 0 && cmp(pivot, *(begin + j)) && *(begin + j) != pivot) j--;
		if (i >= j) return j;
		Auxillary::swap<T>(*(begin + i), *(begin + j));
		i++;
		j--;
	}
}

template<typename T, class _Iterators>
void Quick_Sort<T, _Iterators>::sort(typename Sequence<T, _Iterators>::iterator begin, typename Sequence<T, _Iterators>::iterator end, size_t length, bool cmp(T, T)) {
	if (begin == end) return;
	if (begin == (end - 1)) return;
	size_t newpivot = partition(begin, end, length, cmp);
	size_t leftindex = newpivot;
	size_t rightindex = newpivot + 1;
	// рекурсивно пройдемся
	sort(begin, begin + leftindex + 1, leftindex, cmp);
	sort(begin + rightindex, end, length - (leftindex + 1), cmp);

}

template<typename T, class _Iterators>
void Quick_Sort<T, _Iterators>::sort(typename Sequence<T, _Iterators>::iterator begin, typename Sequence<T, _Iterators>::iterator end, bool cmp(T, T)) {
	size_t length = distance<T>(begin, end);
	this->sort(begin, end, length, cmp);
}

template<typename T, class _Iterators>
SortType Quick_Sort<T, _Iterators>::GetType() {
	return QuickSort;
}


//bitonicsort
/*https://pythobyte.com/bitonic-sort-python-28918/ жесть сортирует конечно,так как реализация странная
https://www.youtube.com/watch?v=32NLIL_6WJg битоническая последовательность и берем 1ый элемент и средний элмент + 1
*/

template<typename T, class _Iterators>
void Bitonic_Sort<T, _Iterators>::bitonic_merge(typename Sequence<T, _Iterators>::iterator begin, typename Sequence<T, _Iterators>::iterator end, size_t length, bool cmp(T, T), bool reversed) {
	if (begin == end) return;
	if (begin == (end - 1)) return;
	size_t right = length - 1;
	size_t half = (right + 1) / 2;
	for (size_t i = 0; i < half; i++) {
		if ((i + half <= right) && !(cmp(*(begin + i), *(begin + i + half)) ^ reversed)) {
			Auxillary::swap(*(begin + i), *(begin + i + half));
		}
	}
	bitonic_merge(begin, begin + half, half, cmp, reversed);
	bitonic_merge(begin + half, end, length - (half), cmp, reversed);
}
template<typename T, class _Iterators>
void Bitonic_Sort<T, _Iterators>::sort(typename Sequence<T, _Iterators>::iterator begin, typename Sequence<T, _Iterators>::iterator end, size_t length, bool cmp(T, T), bool reversed) {
	if (begin == end) return;
	if (begin == (end - 1)) return;
	size_t half = (length) / 2;
	typename Sequence<T, _Iterators>::iterator half_it = begin + half;
	sort(begin, half_it, half, cmp, false);//тут чтобы возрастала
	sort(half_it, end, length - (half), cmp, true);//тут чтобы убывала
	bitonic_merge(begin, end, length, cmp, reversed);
}
template<typename T, class _Iterators>
void Bitonic_Sort<T, _Iterators>::sort(typename Sequence<T, _Iterators>::iterator begin, typename Sequence<T, _Iterators>::iterator end, size_t length, bool cmp(T, T)) {
	if (log2(length) != ((double)(int)(log2(length)))) {
		throw SetException(IncorrectRange);
	}
	this->sort(begin, end, length, cmp, false);
}
template<typename T, class _Iterators>
void Bitonic_Sort<T, _Iterators>::sort(typename Sequence<T, _Iterators>::iterator begin, typename Sequence<T, _Iterators>::iterator end, bool cmp(T, T)) {
	size_t length = distance<T>(begin, end);
	this->sort(begin, end, length, cmp);
}

template<typename T, class _Iterators>
SortType Bitonic_Sort<T, _Iterators>::GetType() {
	return BitonicSort;
}
