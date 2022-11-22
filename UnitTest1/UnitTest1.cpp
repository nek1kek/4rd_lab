#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "..\\Full_porn\\ArraySequence.h"
#include "..\\Full_porn\\ISorter.h"
#include "..\\Full_porn\\Iterators.h"
#include "..\\Full_porn\\ListSequence.h"
#include "..\\Full_porn\\Sequence.h"
#include <string>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;



namespace python_tests
{
	TEST_CLASS(ShakerSortTest)
	{
	public:
		ArraySequence<int> seq = { 8,4,19,22,0,4,4,5,5,5,6,71,28 };
		ISorter<int, ArrayIterators<int>>* srt = nullptr;

		TEST_METHOD(Test_1) {
			srt = new Shaker_Sort<int, ArrayIterators<int>>;
			ArraySequence<int> test1(&seq);
			srt->sort(test1.begin(), test1.end(), cmp__up(int));
			ArraySequence<int> expected1 = { 0,4,4,4,5,5,5,6,8,19,22,28,71 };
			Assert::IsTrue(expected1 == test1, L"ShakerSort: wrong answer, test 1");
		}
		TEST_METHOD(Test_2) {
			srt = new Shaker_Sort<int, ArrayIterators<int>>;
			ArraySequence<int> test2(&seq);
			srt->sort(test2.begin(), test2.end(), cmp__down(int));
			ArraySequence<int> expected2 = { 71,28,22,19,8,6,5,5,5,4,4,4,0 };
			Assert::IsTrue(expected2 == test2, L"ShakerSort: wrong answer, test 2");
		}
		TEST_METHOD(Test_3) {
			srt = new Shaker_Sort<int, ArrayIterators<int>>;
			ArraySequence<int> test3(&seq);
			srt->sort(test3.begin(), test3.end(), cmp__odd_even_up(int));
			ArraySequence<int> expected3 = { 0,4,4,4,6,8,22,28, 5,5,5,19,71 };
			Assert::IsTrue(expected3 == test3, L"ShakerSort: wrong answer, test 3");
		}
		TEST_METHOD(Test_4) {
			srt = new Shaker_Sort<int, ArrayIterators<int>>;
			ArraySequence<int> test4(&seq);
			srt->sort(test4.begin(), test4.end(), cmp__digits_count_up(int));
			ArraySequence<int> expected4 = { 0, 8, 4, 4, 4, 5, 5, 5, 6, 19, 22, 71, 28 };
			Assert::IsTrue(expected4 == test4, L"ShakerSort: wrong answer, test 4");
		}
	};
	TEST_CLASS(QuickSortTest)
	{
		ArraySequence<int> seq = { 8,4,19,22,0,4,4,5,5,5,6,71,28 };
		ISorter<int, ArrayIterators<int>>* srt = nullptr;

		TEST_METHOD(Test_1) {
			srt = new Quick_Sort<int, ArrayIterators<int>>;
			ArraySequence<int> test1(&seq);
			srt->sort(test1.begin(), test1.end(), cmp__up(int));
			ArraySequence<int> expected1 = { 0,4,4,4,5,5,5,6,8,19,22,28,71 };
			Assert::IsTrue(expected1 == test1, L"Quick_Sort: wrong answer, test 1");
		}
		TEST_METHOD(Test_2) {
			srt = new Quick_Sort<int, ArrayIterators<int>>;
			ArraySequence<int> test2(&seq);
			srt->sort(test2.begin(), test2.end(), cmp__down(int));
			ArraySequence<int> expected2 = { 71,28,22,19,8,6,5,5,5,4,4,4,0 };
			Assert::IsTrue(expected2 == test2, L"Quick_Sort: wrong answer, test 2");
		}
		TEST_METHOD(Test_3) {
			srt = new Quick_Sort<int, ArrayIterators<int>>;
			ArraySequence<int> test3(&seq);
			srt->sort(test3.begin(), test3.end(), cmp__odd_even_up(int));
			ArraySequence<int> expected3 = { 0, 4, 4, 4, 6, 8, 22, 28, 5, 5, 5, 19, 71 };
			Assert::IsTrue(expected3 == test3, L"Quick_Sort: wrong answer, test 3");
		}
		TEST_METHOD(Test_4) {
			srt = new Quick_Sort<int, ArrayIterators<int>>;
			ArraySequence<int> test4(&seq);
			srt->sort(test4.begin(), test4.end(), cmp__digits_count_up(int));
			ArraySequence<int> expected4 = { 0, 4, 4, 8, 5, 4, 5, 5, 6, 19, 22, 71, 28 };
			Assert::IsTrue(expected4 == test4, L"Quick_Sort: wrong answer, test 4");

		}
	};
	TEST_CLASS(MergeSortTest)
	{
		ArraySequence<int> seq = { 8,4,19,22,0,4,4,5,5,5,6,71,28 };
		ISorter<int, ArrayIterators<int>>* srt = nullptr;

		TEST_METHOD(Test_1) {
			srt = new Merge_Sort<int, ArrayIterators<int>>;
			ArraySequence<int> test1(&seq);
			srt->sort(test1.begin(), test1.end(), cmp__up(int));
			ArraySequence<int> expected1 = { 0,4,4,4,5,5,5,6,8,19,22,28,71 };
			Assert::IsTrue(expected1 == test1, L"MergeSort: wrong answer, test 1");
		}
		TEST_METHOD(Test_2) {
			srt = new Merge_Sort<int, ArrayIterators<int>>;
			ArraySequence<int> test2(&seq);
			srt->sort(test2.begin(), test2.end(), cmp__down(int));
			ArraySequence<int> expected2 = { 71,28,22,19,8,6,5,5,5,4,4,4,0 };
			Assert::IsTrue(expected2 == test2, L"MergeSort: wrong answer, test 2");
		}
		TEST_METHOD(Test_3) {
			srt = new Merge_Sort<int, ArrayIterators<int>>;
			ArraySequence<int> test3(&seq);
			srt->sort(test3.begin(), test3.end(), cmp__odd_even_up(int));
			ArraySequence<int> expected3 = { 0,4,4,4,6,8,22,28, 5,5,5,19,71 };
			Assert::IsTrue(expected3 == test3, L"MergeSort: wrong answer, test 3");
		}
		TEST_METHOD(Test_4) {
			srt = new Merge_Sort<int, ArrayIterators<int>>;
			ArraySequence<int> test4(&seq);
			srt->sort(test4.begin(), test4.end(), cmp__digits_count_up(int));
			ArraySequence<int> expected4 = { 0, 8, 4, 4, 4, 5, 5, 5, 6, 19, 22, 71, 28 };
			Assert::IsTrue(expected4 == test4, L"MergeSort: wrong answer, test 4");
		}
	};
	TEST_CLASS(BinaryInsertionSortTest)
	{
		ArraySequence<int> seq = { 8,4,19,22,0,4,4,5,5,5,6,71,28 };
		ISorter<int, ArrayIterators<int>>* srt = nullptr;

		TEST_METHOD(Test_1) {
			srt = new Binary_Insertion_Sort<int, ArrayIterators<int>>;
			ArraySequence<int> test1(&seq);
			srt->sort(test1.begin(), test1.end(), cmp__up(int));
			ArraySequence<int> expected1 = { 0,4,4,4,5,5,5,6,8,19,22,28,71 };
			Assert::IsTrue(expected1 == test1, L"BinaryInsertionSort: wrong answer, test 1");
		}
		TEST_METHOD(Test_2) {
			srt = new Binary_Insertion_Sort<int, ArrayIterators<int>>;
			ArraySequence<int> test2(&seq);
			srt->sort(test2.begin(), test2.end(), cmp__down(int));
			ArraySequence<int> expected2 = { 71,28,22,19,8,6,5,5,5,4,4,4,0 };
			Assert::IsTrue(expected2 == test2, L"BinaryInsertionSort: wrong answer, test 2");
		}
		TEST_METHOD(Test_3) {
			srt = new Binary_Insertion_Sort<int, ArrayIterators<int>>;
			ArraySequence<int> test3(&seq);
			srt->sort(test3.begin(), test3.end(), cmp__odd_even_up(int));
			ArraySequence<int> expected3 = { 0,4,4,4,6,8,22,28, 5,5,5,19,71 };
			Assert::IsTrue(expected3 == test3, L"BinaryInsertionSort: wrong answer, test 3");
		}
		TEST_METHOD(Test_4) {
			srt = new Binary_Insertion_Sort<int, ArrayIterators<int>>;
			ArraySequence<int> test4(&seq);
			srt->sort(test4.begin(), test4.end(), cmp__digits_count_up(int));
			ArraySequence<int> expected4 = { 0, 8, 4, 4, 4, 5, 5, 5, 6, 19, 22, 71, 28 };
			Assert::IsTrue(expected4 == test4, L"BinaryInsertionSort: wrong answer, test 4");
		}
	};
	TEST_CLASS(BitonicSortTest)
		{
			ArraySequence<int> seq = { 8,4,19,22,0,4,4,5,5,5,6,71,28,16,32,14 };
			ISorter<int, ArrayIterators<int>>* srt = nullptr;

			TEST_METHOD(Test_1) {
				srt = new Bitonic_Sort<int, ArrayIterators<int>>;
				ArraySequence<int> test1(&seq);
				srt->sort(test1.begin(), test1.end(), cmp__up(int));
				ArraySequence<int> expected1 = { 0,4,4,4,5,5,5,6,8,14,16,19,22,28,32,71 };
				Assert::IsTrue(expected1 == test1, L"BitonicSort: wrong answer, test 1");
			}
			TEST_METHOD(Test_2) {
				srt = new Bitonic_Sort<int, ArrayIterators<int>>;
				ArraySequence<int> test2(&seq);
				srt->sort(test2.begin(), test2.end(), cmp__down(int));
				ArraySequence<int> expected2 = { 71,32,28,22,19,16,14,8,6,5,5,5,4,4,4,0 };
				Assert::IsTrue(expected2 == test2, L"BitonicSort: wrong answer, test 2");
			}
			TEST_METHOD(Test_3) {
				srt = new Bitonic_Sort<int, ArrayIterators<int>>;
				ArraySequence<int> test3(&seq);
				srt->sort(test3.begin(), test3.end(), cmp__odd_even_up(int));
				ArraySequence<int> expected3 = { 0,4,4,4,6,8,14,16,22,28,32, 5,5,5,19,71 };
				Assert::IsTrue(expected3 == test3, L"BitonicSort: wrong answer, test 3");
			}
			TEST_METHOD(Test_4) {
				srt = new Bitonic_Sort<int, ArrayIterators<int>>;
				ArraySequence<int> test4(&seq);
				srt->sort(test4.begin(), test4.end(), cmp__digits_count_up(int));
				ArraySequence<int> expected4 = { 0, 8, 4, 4, 4, 5, 5, 5, 6, 28, 14, 32, 71, 16, 22, 19 };
				Assert::IsTrue(expected4 == test4, L"BitonicSort: wrong answer, test 4");
			}
		};
	}
