
#include <iostream> 
#include <list>
#include "search_algorithms.h"
#include "set_class.h"

using namespace std;


/* 
        All functions to search return the index of element 
        in array or succesor if not in array
 */


template <typename T>
int recursiveBinarySearch(vector<T> &arr, int l, int r, T x, int size){ 
    if (r >= l) 
    { 
        int mid = l + (r - l)/2; 
  
        if (arr[mid] == x) 
            return mid; 
  
        if (arr[mid] > x) 
            return recursiveBinarySearch(arr, l, mid-1, x, size); 
  
        return recursiveBinarySearch(arr, mid+1, r, x, size); 
    } 
    // if the element not in a set 
    if (l > size-1){
        return r;
    }
    if (r < 0){
        return l;
    }
    // check
    int delta_l = abs(arr[l] - x);
    int delta_r = abs(arr[r] - x);
    if (delta_l > x && delta_r > x){
        if (delta_l < delta_r){
            return l;
        }
        else 
            return r;
    }

    return arr[l]>arr[r]?l:r; 
} 
// Instantation of template function 
template int recursiveBinarySearch<int>(vector<int> &arr, int l, int r, int x, int size);


template <typename T>
int iterativeBinarySearch(vector<T> &array, int low, int high, T x, int size) {
	while (low <= high)
	{
		int mid = low + (high - low) / 2;

		if (array[mid] == x)
			return mid;

		if (array[mid] < x)
			low = mid + 1;

		else
			high = mid - 1;
	}

    if (low > size - 1){
        return high;
    }
    if (high < 0){
        return low;
    }
    
    return array[low] < array[high]?high:low;
}
//Instantation of template function
template int iterativeBinarySearch<int>(vector<int> &array, int low, int high, int x, int size);


template<typename T>
int linearSearch(vector<T> &arr, int n, T x){

    for(int i=0; i < n; i++){
        // if x in arr return index of x in arr
        if (arr[i] == x){
            return i;   
        }
        // if x not in arr return succesor index
        if (arr[i] > x){
            return i;
        }    
    }
    
    return n-1;
}
//Instantation of template function
template int linearSearch<int>(vector<int> &arr, int n, int x);


template<typename T> 
int exponentialSearch(vector<T> &arr, int n, T x, int initial_position) { 
    if (arr[initial_position] == x) 
        return 0; 
    if (arr[n-1] < x)
        return n-1;
  
    int i = initial_position + 1; 
    while (i < n && arr[i] <= x) 
        i = i*2; 
  
    return iterativeBinarySearch(arr, i/2, min(i, n-1), x, n); 
}
// Instantation of template function
template int exponentialSearch<int>(vector<int> &arr, int n, int x, int initial_position);


/* --------------------- Intervals implemetantions ---------------------*/

/* Return 1 if exist intersection and 0 if not */
template<typename T> 
int if_intersection(Interval<T> a, Interval<T> b, Interval<T>* intersection)
{
    T minLow, minHigh;
    // Not intersection case 
    if (a.high <= b.low || b.high  <= a.low){
        intersection -> low = -1;
        intersection -> high = -1;
        return 0;
    }

    // Exist intersection between a and b
    else{
        T lowRange, highRange;

        if (a.low < b.low)
            lowRange = b.low;
        else
            lowRange = a.low;

        if (a.high < b.high)
            highRange = a.high;
        else    
            highRange = b.high;
        
        intersection -> low = lowRange;
        intersection -> high = highRange;

        return 1;
    }
}
template int if_intersection<int>(Interval<int> a, Interval<int> b, Interval<int>* intersection);


template<typename T>
int intervalBinarySearch(vector< Interval<T> > &array, int low, int high, Interval<T> x, int size, Interval<T>* intersection){   
    while (low <= high)
	{
		int mid = low + (high - low) / 2;
        int if_intersect = if_intersection(array[mid], x, intersection);
		if (if_intersect){
            return mid;
        }
		
		if (array[mid].high <= x.low)
			low = mid + 1;

		else
			high = mid - 1;
	}

    if (low > size - 1){
        return high;
    }
    if (high < 0){
        return low;
    }
    return array[high].high <= x.low ? low : high;
    // return array[low].high < array[high].low ? high : low;
}
template int intervalBinarySearch<int>(vector< Interval<int> > &array, int low, int high, Interval<int> x, int size, Interval<int>* intersection);


template<typename T> 
int intervalExponentialSearch(vector< Interval<T> > &arr, int n , Interval<T> &x, Interval<T>* intersection, int initial_position, long int *n_comparisions) {   
    Interval <T> interval_intersection;
    int if_intersect = if_intersection(arr[initial_position], x, intersection); 
    
    if (if_intersect){
        return initial_position;
    }

    if (x.low < arr[initial_position].low){
        return initial_position;
    }

    if (arr[n-1].high <= x.low) {
        intersection -> low = -1;
        intersection -> high = -1;
        return n-1;
    }
    (*n_comparisions) = (*n_comparisions) + 3;
    int i = 1;
    while ((i < n-initial_position) &&  (arr[i+initial_position].low <= x.low)){
        i = i*2;
        (*n_comparisions)++;
    }

    return succesorBinarySearch(arr, i/2, min(i, n-initial_position), x, n, intersection, initial_position, n_comparisions);

}
template int intervalExponentialSearch<int>(vector< Interval<int> > &arr, int n, Interval<int> &x, Interval<int>* intersection, int initial_position, long int *n_comparisions);


template<typename T>
int succesorBinarySearch(vector< Interval <T> > &arr, int low, int high, Interval<T> x, int size, Interval<T>* intersection, int initial_position, long int *n_comparisions){

    if ( x.low <= arr[low+initial_position].low ){
        if_intersection(x, arr[low+initial_position], intersection);
        return low+initial_position;
    }
    (*n_comparisions)++;
    while( low + 1 < high ){
        int  mid = low + (high-low) / 2;
        if (arr[mid+initial_position].low < x.low){
            low = mid;
        }
        else{
            high = mid;
        }
        (*n_comparisions)++;
    }
    (*n_comparisions)++;
    if (if_intersection(x, arr[low+initial_position], intersection)){
        return low+initial_position;
    }
    else{
        if_intersection(x, arr[high+initial_position], intersection);
        return high+initial_position;
    }
}
template int succesorBinarySearch<int>(vector< Interval<int> > &arr, int low, int high, Interval<int> x, int size, Interval<int>* intersection, int intitial_position, long int *n_comparisions);


template<typename T> 
int successor(vector< Interval <T> > &arr, int low, int high, Interval<T> &x, int size, Interval<T> *intersection, int initial_position){
    int init_low = low;
    if (if_intersection(x, arr[low+initial_position], intersection))
        return low+initial_position;
    int ans = -1;
    while (low <= high) {
        int mid = low + (high - low + 1) / 2;
        Interval<T> midVal = arr[mid+initial_position];
 
        if (midVal.low < x.low) {
 
            // if mid is less than key, all elements
            // in range [low, mid - 1] are <= key
            // then we search in right side of mid
            // so we now search in [mid + 1, high]
            ans = mid;
            low = mid + 1;
        }
        else if (midVal.low > x.low) {
 
            // if mid is greater than key, all elements
            // in range [mid + 1, high] are >= key
            // we note down the last found index, then 
            // we search in left side of mid
            // so we now search in [low, mid - 1]
            high = mid - 1;
        }
        else if (midVal.low == x.low) {
 
            // if mid is equal to key, all elements in
            // range [low, mid] are <= key
            // so we now search in [mid + 1, high]
            return mid+initial_position;
            // low = mid + 1;
        }
    }
    // if (ans >= 0){
        if (if_intersection(x, arr[ans+initial_position], intersection)){
            return ans+initial_position;
        }
        else{
            if_intersection(x, arr[ans+1+initial_position], intersection);
            return ans + 1 + initial_position;
        }
    // }
    
    // else{
    //      if_intersection(x, arr[initial_position], intersection);
    //     return initial_position;
    // }

    return ans+initial_position;
}
template int successor<int>(vector< Interval<int> > &arr, int low, int high, Interval<int> &x, int size, Interval<int> *intersection, int initial_position);


template<typename T> 
int predecessorExponentialSearch(vector< Interval<T> > &arr, int n , Interval<T> &x, int initial_position, long int *n_comparisions){
    if ( x.low <= arr[initial_position].low)
        return initial_position;
    if (arr[n-1].low < x.low)
        return n-1;
    (*n_comparisions)++;
    int i = 1;
    while ((i < n-initial_position) &&  (arr[i + initial_position].low < x.low)){
        i = i*2;
        (*n_comparisions)++;
    }
        
    
    return predecessorBinarySearch(arr, i/2, min(i, n-1-(initial_position-1)), x, n, initial_position, n_comparisions);
}
template int predecessorExponentialSearch<int>(vector< Interval<int> > &arr, int n , Interval<int> &x, int initial_position, long int *n_comparisions);


template <typename T>
int predecessorBinarySearch(vector< Interval <T> > &arr, int low, int high, Interval<T> &x, int size, int initial_position, long int *n_comparisions){
    if (arr[low+initial_position].low <= x.low)
        return (low + initial_position);
    (*n_comparisions)++;
    int ans = -1;
    while (low <= high) {
        int mid = low + (high - low + 1) / 2;
        Interval<T> midVal = arr[mid+initial_position];
 
        if (midVal.low < x.low) {
            ans = mid;
            low = mid + 1;
        }
        else if (midVal.low > x.low) {
            high = mid - 1;
        }
        else if (midVal.low == x.low) {
            high = mid - 1;
        }
        (*n_comparisions)++;
        // cout << "ans: " << ans << endl;
    } 
    return (ans+initial_position);
}
template int predecessorBinarySearch<int>(vector< Interval <int> > &arr, int low, int high, Interval<int> &x, int size, int initial_position, long int *n_comparisions);


// Return all intersections of x in arr
template<typename T>
int intervalLinearSearch(vector < Interval<T> > &arr, int n, Interval<T> &x, list< Interval<T> > *intersections, int initial_position, int *last_comparision, long int *n_comparisions){
    for(int i = initial_position; i < n; ++i){
        (*n_comparisions)++;
        Interval<T> intersection;
        Interval<T> i_element = arr[i];
        int if_intersect = if_intersection(x, i_element, &intersection);
        if (if_intersect){
            intersections->push_back(intersection);
            *last_comparision = 1;
        }

        if ( x.high <= i_element.high ){
            return i; // return position of last element visited
        }
        
    }
    return n-1;
}
template int intervalLinearSearch<int>(vector < Interval<int> > &arr, int n, Interval<int> &x, list< Interval<int> > *intersections, int initial_position, int *last_comparision, long int *n_comparisions);

template<typename T>
int modifiedIntervalLinearSearch(vector< Interval <T> >& arr, int n, Interval<T> x, Interval<T>* intersection, int initial_position){
    for (int i = initial_position; i < n; ++i){
        int if_intersect = if_intersection(x, arr[i], intersection);
        if ( if_intersect ){
            return i;
        }
        if ( x.high <= arr[i].high ){
            return i;
        }
    }
    return n-1;
}
