#include <iostream> 
#include <list>
#include <queue>
#include <vector>
#include "set_class.h"
#include "interval_set_class.h"
#include "search_algorithms.h"
#include "dip.h"

template <typename T>
int barbayKenyon(Set<T> *sets[], int k, list<T> *intersection)
{
    // set eliminator element in [0,0], first element of first set
    T e = sets[0]->elements[0];
    // Set index
    int i = 1;
    // ocurrences of e
    int occr = 1;

    int n = 0; // -> Eliminar
    // Init actual elements and size of initial set
    // vector<T> actual_set=sets[i].elements;
    int size = sets[i]->size;

    while ( e != -1 ){
        // cout << "i: "<< i <<"\n";
        // position of e in i-set
        int pos = exponentialSearch(sets[i]->elements, size, e, sets[i]->pos);
        // int pos = linearSearch(actual_set, size, e);
        // cout << "pos: " << pos << "\n"; 
        // cout << "e: " << e << "\n";
        if (sets[i]->elements[pos] == e){
            occr +=1;
            sets[i]->pos = pos;
            if(occr == k){
                n+=1;
                intersection -> push_back(e);
                // cout << "elemento de la intersección: " << e << "\n";
            }
        } 
        if(occr == k || sets[i]->elements[pos] != e){
            // Position remain and size of next set
            int next_set_pos = sets[i]->pos;
            int next_set_size = sets[i]->size;

            // No elements remain in the smallest set
            if (next_set_pos == next_set_size-1){
                e = -1;
                return 0;
            }

            // e is part of sets intersection      
            if (occr == k){   
                e = sets[i]->elements[pos+1];
                // cout << "nuevo e: " << e << "\n";
                sets[i]->pos = pos+1;
            }
            // e is not found in actual set
            else{   
                // pos it's a succesor index of e
                e = sets[i]->elements[pos];
                sets[i]->pos = pos;
                // cout << "nuevo e: " << e << "\n";
                
            }
            // restart occurrences
            occr = 1;
        }
        // cout << "-------------------\n";
        // Cyclical index of sets
        i = (i+1)%k;
        // actual_set = sets[i]->elements;
        size = sets[i]->size;
    }

    return 0;
}
template int barbayKenyon<int>(Set<int> *sets[], int k, list<int> *intersection); 



template <typename T>
int forceBruteIntersection(Set<T> *sets, int k, list<T> *intersection){
    // find smallest set to intersect
    int min = sets[0].size;
    int set_index = 0;
    for(int i=0; i < k; ++i){
        if (sets[i].size < min){
            min = sets[i].size;
            set_index = i;
        }
    }
    // Search elements of smallest set in a rest of sets
    Set<T> smallest_set = sets[set_index];
    for(int i=0; i < smallest_set.size; ++i){
        T e = smallest_set.elements[i];
        int occr = 1;
        for(int j=0; j < k; ++j){
            if (j != set_index){
                Set<T> set_to_search = sets[j];
                int pos = linearSearch(set_to_search.elements, set_to_search.size, e);
                if (set_to_search.elements[pos] == e){
                    occr++;
                    if (occr == k){
                        intersection -> push_back(e);
                    }
                }
            }
        }
    }
    return 0;
}
template int forceBruteIntersection<int>(Set<int> *sets, int k, list<int> *intersection);


template <typename T>
int intervalBarbayKenyon(IntervalSet<T>* sets[] , int k, list< Interval<T> > *intersection, bool cout_) {
    
    Interval<T> e = sets[0]->elements[0]; // set eliminator element in [0,0], first element of first set
    Interval<T> original_e = sets[0]->elements[0];

    int i = 1;  // Set index
    int occr = 1;  // ocurrences of e
    int size = sets[i]->size;
    IntervalSet<T> actual_set; // Init actual elements and size of initial set

    while ( 1 ){
        // actual_set = sets[i];
        Interval<T> intersect;
        // position of e in i-th set
        int pos = intervalExponentialSearch(sets[i]->elements, size, e, &intersect, sets[i]->pos);

        Interval<T> element_intersection = sets[i] -> elements[pos];
        
        // Exist intersection
        if (intersect.low != -1){
            e.low = intersect.low;
            e.high = intersect.high;
            occr += 1;
            if(occr == k){
                intersection -> push_back(e);
            }
        }
        if(occr == k || intersect.low == -1){
            // Position remain and size of next set
            int next_set_pos = sets[i]->pos;
            int next_set_size = sets[i]->size;

            // e is part of sets intersection      
            if (occr == k){
                
                // if ( e.high < original_e.high ){
                // // if (e.high < actual_set.elements[pos].high){//sets[i].elements[pos].high){
                //     e.low = e.high ;
                //     // e.high = actual_set.elements[pos].high; //sets[i].elements[pos].high;
                //     e.high = original_e.high;
                //     if (cout_) cout << "1nuevo e: [" << e.low << "," << e.high << "]\n";
                //     sets[i].pos = pos;

                // }
                
                // if (e.high < sets[i]->elements[pos].high){//sets[i].elements[pos].high){
                if (e.high < element_intersection.high){
                    e.low = e.high ;
                    e.high = element_intersection.high; //sets[i].elements[pos].high;
                    sets[i]->pos = pos;
                    //  i = (i+1)%k};
                }
                else{
                    if ((pos+1) > next_set_size-1){
                        return 0;
                    }   
                    e = sets[i]->elements[pos+1];
                    // original_e = sets[i]->elements[pos+1];
                    sets[i]->pos = pos+1;
                    // i = (i+1)%k;
                }
            }
            
            // No elements remain in the smallest set
            else if (next_set_pos == next_set_size-1){
                return 0;
            }

            // e is not found in actual set
            else{   
                // pos it's a succesor index of e
                e = element_intersection;
                // original_e = sets[i]->elements[pos];
                sets[i]->pos = pos;
                // i = (i+1)%k;          
            }
            // restart occurrences
            occr = 1;
        }
        // Cyclical index of sets
        i = (i+1)%k;
        size = sets[i]->size;
    }
    return 0;
}
template int intervalBarbayKenyon<int>(IntervalSet<int>* sets[], int k, list< Interval<int> > *intersection, bool cout_);


template <typename T>
void classicIntersectionDIP(IntervalSet <T> *set1, IntervalSet <T> *set2, list< Interval <T> > *intersections){

    IntervalSet <T> *A, *B;
    // Small size set
    if (set1->size < set2->size){
        A = set1;
        B = set2;
    }
    else{
        B = set1;
        A = set2;
    }

    // vector < Interval <T> > intersections;
    int init_position = 0;
    for (auto x: A->elements){
        // int size_intersections = intersections->size;
        int last_comparision = 0;
        int last_visited = intervalLinearSearch(B->elements, B->size, x, intersections, init_position, &last_comparision);
        if (!last_comparision){
            init_position = last_visited;
        }
    }
}
void classicIntersectionDIP(IntervalSet <int> *set1, IntervalSet <int> *set2, list< Interval <int> > &intersections);

// method 0: Barbay and Kenyon, 1: Linear Search
template <typename T>
void intersectionDIP(heap< Partition<T>, vector< Partition<T> >, greater< Partition<T> > > &partitions1, heap< Partition<T>, vector< Partition<T> >, greater< Partition<T> > > &partitions2, list< Interval<T> > *intersection, int method){
    // Perform Barbay and Kenyon Intersection
    if ( method == 0 ){
        cout << "---------> method: " << "Barbay and Kenyon" << endl;
        for (auto i: partitions1){
            IntervalSet<T> p1 = i.set;
            for (auto j: partitions2){
                IntervalSet<T> p2 = j.set;
                IntervalSet<T>* sets_to_intersect [] = {&i.set, &j.set};
                // cout << "***Intersection Between partitions " << i.id << " and " << j.id << endl;
                // if ( i.id == 57 && j.id == 57){
                //     cout  <<"SIZE OF PARTITIONS: "<<  i.set.size << " " << j.set.size << endl;
                //      cout << "{" ;
                //     for (auto x: i.set.elements){
                //         cout << "[" << x.low << "," << x.high << ") ";
                //     }
                //     cout << "}" << endl;

                //     cout << "{" ;
                //     for (auto x: j.set.elements){
                //         cout << "[" << x.low << "," << x.high << ") ";
                //     }
                //     cout << "}" << endl; 
                //     intervalBarbayKenyon(sets_to_intersect, 2, intersection, true);
                // }
                // else{
                //     intervalBarbayKenyon(sets_to_intersect, 2, intersection, false);
                // }
                intervalBarbayKenyon(sets_to_intersect, 2, intersection, false);
                i.set.pos = 0;
                j.set.pos = 0;
                
                // cout << "pos: " << p2.pos << "\n";
            }
        }
    }
    // Perform Linear Intersection
    else if (method == 1){
        cout << "---------> method: " << "Classic Linear Intersection" << endl;
        for (auto i: partitions1){
            IntervalSet<T> p1 = i.set;
            for (auto j: partitions2){
                IntervalSet<T> p2 = j.set;
                classicIntersectionDIP(&p1, &p2, intersection);
                // cout << "***Intersection Between partitions " << i.id << " and " << j.id << endl;
            }
        }
    }
    
}
template void intersectionDIP<int>(heap< Partition<int>, vector< Partition<int> >, greater< Partition<int> > > &partitions1, heap< Partition<int>, vector< Partition<int> >, greater< Partition<int> > > &partitions2, list< Interval<int> > *intersection, int method);

template <typename T>
void reconstructIntervals(){
    
}

template <typename T>
void intersectionNumbersDIP(heap< numbersPartition<T>, vector< numbersPartition<T> >, greater< numbersPartition<T> > > &partitions1, heap< numbersPartition<T>, vector< numbersPartition<T> >, greater< numbersPartition<T> > > &partitions2, list< Interval<T> > *intersection){
    for (auto i: partitions1){
            // Set<T> p1 = i.set;
            for (auto j: partitions2){
                // Set<T> p2 = j.set;
                list<T> partialSol;
                Set<T> *sets[] = {&i.set, &j.set};
                barbayKenyon(sets, 2, &partialSol);
                cout << "partitions ids: " << i.id << ", " << j.id << endl;
                i.set.pos = 0;
                j.set.pos = 0;
                cout<< "Tamaño solución: " << partialSol.size() << endl;
            }
        }

}
template void intersectionNumbersDIP<int>(heap< numbersPartition<int>, vector< numbersPartition<int> >, greater< numbersPartition<int> > > &partitions1, heap< numbersPartition<int>, vector< numbersPartition<int> >, greater< numbersPartition<int> > > &partitions2, list< Interval<int> > *intersection);