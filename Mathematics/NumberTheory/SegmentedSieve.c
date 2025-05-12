#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAX_NUMBERS 400000
#define SIEVE_LIMIT 1300000

typedef long long int lli;
typedef long long unsigned llu;

// Pair structure
typedef struct {
	lli first;
	lli second;
} LLIPair;

// Heap sort related functions
typedef int (*Comparator)(const void*, int, int);
typedef void (*Swapper)(const void*, int, int);

void swap_long(const void* arr, int i, int j) {
	lli* array = (lli*)arr;
	lli temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

void swap_pair(const void* arr, int i, int j) {
	LLIPair* array = (LLIPair*)arr;
	LLIPair temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

int compare_long_asc(const void* arr, int i, int j) {
	const lli* array = (const lli*)arr;
	return array[i] <= array[j];
}

int compare_pair_asc(const void* arr, int i, int j) {
	const LLIPair* array = (const LLIPair*)arr;
	return array[i].first <= array[j].first;
}

void heapify(const void* arr, int root, int size, Comparator comp, Swapper swap, int offset) {
	int largest = root;
	int left = 2 * root + 1;
	int right = 2 * root + 2;

	if (left < size && comp(arr, largest + offset, left + offset)) {
		largest = left;
	}
	if (right < size && comp(arr, largest + offset, right + offset)) {
		largest = right;
	}
	if (largest != root) {
		swap(arr, largest + offset, root + offset);
		heapify(arr, largest, size, comp, swap, offset);
	}
}

void heap_sort(const void* arr, int offset, int n, Comparator comp, Swapper swap) {
	// Build heap
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(arr, i, n, comp, swap, offset);
	}
	// Extract elements
	for (int i = n - 1; i > 0; i--) {
		swap(arr, 0, i);
		heapify(arr, 0, i, comp, swap, offset);
	}
}

// Prime sieve related functions
lli primes[MAX_NUMBERS];
bool is_prime[SIEVE_LIMIT];
int prime_count = 0;

void regular_sieve(int limit) {
	memset(is_prime, true, sizeof(is_prime));
	is_prime[0] = is_prime[1] = false;

	for (int p = 2; p * p <= limit; p++) {
		if (is_prime[p]) {
			for (int multiple = p * p; multiple < limit; multiple += p) {
				is_prime[multiple] = false;
			}
		}
	}

	for (int i = 2; i < limit; i++) {
		if (is_prime[i]) {
			primes[prime_count++] = i;
		}
	}
}

void segmented_sieve(lli low, lli high) {
	memset(is_prime, true, sizeof(is_prime));
	int initial_prime_count = prime_count;

	for (int i = 0; i < initial_prime_count; i++) {
		lli p = primes[i];
		lli first_multiple = (low + p - 1) / p * p;

		for (lli multiple = first_multiple; multiple < high; multiple += p) {
			is_prime[multiple - low] = false;
		}
	}

	for (lli i = low; i < high; i++) {
		if (is_prime[i - low] && prime_count < MAX_NUMBERS) {
			primes[prime_count++] = i;
		}
	}
}

lli min(lli a, lli b) {
	return a < b ? a : b;
}
lli max(lli a, lli b) {
	return a > b ? a : b;
}
int main() {
	return 0;
}
