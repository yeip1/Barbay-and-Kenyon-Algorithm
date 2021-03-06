#ifndef BARBAY_AND_KENYON_H_
#define BARBAY_AND_KENYON_H_

#include <iostream>
#include <list>
#include <queue>
#include "dip.h"

template <typename T>
int barbayKenyon(Set<T> *sets[], int k, list<T> *intersection);

template <typename T>
int forceBruteIntersection(Set<T> *sets, int k, list<T> *intersection);

template <typename T>
int intervalBarbayKenyon(IntervalSet<T> *sets [], int k, list< Interval<T> > *intersection, bool cout_, long int *n_comparisions);

template <typename T>
void intersectionDIP(heap< Partition<T>*, vector< Partition<T>* >, orderIntervalsHeap<T> > &partitions1, heap< Partition<T>*, vector< Partition<T>* >, orderIntervalsHeap<T> > &partitions2, list< Interval<T> > *intersection, int method, long int *n_comparisions);

template <typename T>
void classicIntersectionDIP(IntervalSet <T> *set1, IntervalSet <T> *set2, list< Interval <T> > &intersections, int method, long int *n_comparisions);

template <typename T>
void intersectionNumbersDIP(heap< numbersPartition<T>*, vector< numbersPartition<T>* >, orderNumbersHeap<T> > &partitions1, heap< numbersPartition<T>*, vector< numbersPartition<T>* >, orderNumbersHeap<T> > &partitions2, list< Interval<T> > *intersection);
#endif