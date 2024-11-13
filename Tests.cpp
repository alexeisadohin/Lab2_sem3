#include <cassert>
#include "ArraySequence.h"
#include "ListSequence.h"
#include "Student.h"
#include "BubbleSort.h"
#include "QuickSort.h"
#include "InsertionSort.h"
#include "ShellSort.h"
#include "SelectionSort.h"
#include "HeapSort.h"

#include "ShrdPtr.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

template <typename T, template <typename> class SequenceType, typename Comparator>
void testsSort(ISorter<T, Comparator>& sorter, Comparator comp, const std::string& sorterName, const std::string& comparatorName) {

    ShrdPtr<Sequence<T>> emptySeq = ShrdPtr<Sequence<T>>(new SequenceType<T>());
    sorter.Sort(emptySeq, comp);
    assert(emptySeq->GetLength() == 0);

    int dob1[] = {1, 1, 2000};
    int dob2[] = {2, 2, 2001};
    Student items[] = {
        Student("John", "Doe", 3, dob1, 2),
        Student("Jane", "Zoe", 1, dob2, 3),

    };
    int numItems = sizeof(items) / sizeof(items[0]);

    ShrdPtr<Sequence<T>> seq = ShrdPtr<Sequence<T>>(new SequenceType<T>(items, numItems));
    sorter.Sort(seq, comp);

    assert(seq->GetLength() == numItems);
    for (int i = 0; i < numItems - 1; ++i) {
        assert(!comp(seq->Get(i + 1), seq->Get(i)));
    }

    int dob3[] = {1, 1, 2000};
    Student itemsWithDuplicates[] = {
        Student("John", "Doe", 1, dob3, 3),
        Student("John", "Doe", 1, dob3, 3)
    };
    int numDuplicates = sizeof(itemsWithDuplicates) / sizeof(itemsWithDuplicates[0]);

    ShrdPtr<Sequence<T>> seqWithDuplicates = ShrdPtr<Sequence<T>>(new SequenceType<T>(itemsWithDuplicates, numDuplicates));
    sorter.Sort(seqWithDuplicates, comp);

    assert(seqWithDuplicates->GetLength() == numDuplicates);
    for (int i = 0; i < numDuplicates - 1; ++i) {
        assert(!comp(seqWithDuplicates->Get(i + 1), seqWithDuplicates->Get(i)));
    }

    std::cout << "Sorted sequence (" << sorterName << " with " << comparatorName << "):\n";
    for (size_t i = 0; i < seq->GetLength(); ++i) {
        std::cout << seq->Get(i) << "\n";
    }
    std::cout << "--------------------\n";



    std::cout << "Sorted sequence with duplicates (" << sorterName << " with " << comparatorName << "):\n";
    for (size_t i = 0; i < seqWithDuplicates->GetLength(); ++i) {
        std::cout << seqWithDuplicates->Get(i) << "\n";
    }
    std::cout << "--------------------\n";
}

void testAllSortersWithAllComparators() {
    using StudentComparator = std::function<bool(const Student&, const Student&)>;
    using Sorters = std::vector<std::pair<std::string, ISorter<Student, StudentComparator> *>>;
    using Comparators = std::vector<std::pair<std::string, StudentComparator>>;

    Sorters sorters = {
        {"Bubble Sort", new BubbleSort<Student, StudentComparator>()},
        {"Heap Sort", new HeapSort<Student, StudentComparator>()},
        {"Quick Sort", new QuickSort<Student, StudentComparator>()},
        {"Insertion Sort", new InsertionSort<Student, StudentComparator>()},
        {"Shell Sort", new ShellSort<Student, StudentComparator>()},
        {"Selection Sort", new SelectionSort<Student, StudentComparator>()},
    };


    Comparators comparators = {
        {"By First Name", CompareStudentsByFirstName()},
        {"By Last Name", CompareStudentsByLastName()},
        {"By ID", CompareStudentsByID()},
        {"By Year of Study", CompareStudentsByYear()}
    };

    for (const auto& sorterPair : sorters) {
        for (const auto& comparatorPair : comparators) {
            testsSort<Student, ArraySequence, StudentComparator>(*sorterPair.second, comparatorPair.second, sorterPair.first, comparatorPair.first);
            testsSort<Student, ListSequence, StudentComparator>(*sorterPair.second, comparatorPair.second, sorterPair.first, comparatorPair.first); // Test with ListSequence too
        }
    }
}

void tests() {
    testAllSortersWithAllComparators();
}
