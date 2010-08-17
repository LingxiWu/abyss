#ifndef ALGORITHMS_H
#define ALGORITHMS_H 1

#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>

/** Sorts the elements in the range [first,last) ordered by the value
 * returned by the unary function op, which is called once for each
 * element in the range [first,last).
 * @author Shaun Jackman <sjackman@gmail.com>
 */
template <class It, class Op>
void sort_by_transform(It first, It last, Op op)
{
	typedef typename std::iterator_traits<It>::difference_type
		size_type;
	typedef typename Op::result_type key_type;

	size_type n = last - first;
	std::vector< std::pair<key_type, size_type> > keys;
	keys.reserve(n);
	for (It it = first; it != last; ++it)
		keys.push_back(make_pair(op(*it), it - first));
	sort(keys.begin(), keys.end());

	// Initialize the matrix to the identity matrix.
	std::vector<size_type> row(n), column(n);
	for (size_type i = 0; i < n; i++)
		row[i] = column[i] = i;

	for (size_type i = 0; i < n; i++) {
		// The elements [0,i) are in their correct positions.
		size_type j = column[keys[i].second];
		swap(first[i], first[j]);
		// The elements [0,i] are in their correct positions.

		// Swap rows i and j of the matrix.
		swap(row[i], row[j]);
		swap(column[row[i]], column[row[j]]);
		//assert(column[row[i]] == row[column[i]]);
		//assert(column[row[j]] == row[column[j]]);
	}
}

#endif
