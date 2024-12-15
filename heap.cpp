#include <algorithm>
#include <ios>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#define  MAX 10

using namespace std;



// heap_sort implementation 


void insert(vector<int> &heap, int key) 
{
    heap.push_back(key);

    size_t leftmost_open_place = heap.size() - 1;

    size_t parent = (leftmost_open_place - 1) / 2;

    while (leftmost_open_place > 0 && parent > 0 
	   && heap[parent] < heap[leftmost_open_place])
    {
        swap(heap[parent], heap[leftmost_open_place]);

        leftmost_open_place = parent;
        parent = (leftmost_open_place - 1) / 2;
    }
}



int extract(vector<int> &heap)
{
	int maximum_element = heap[0];
	int last_element_last_level_index = heap.size() - 1;
	int root = 0;
	int left_child = 2 * root + 1;
	int right_child = 2 * root + 2;

	heap[root] = heap[last_element_last_level_index];

	heap.pop_back();

	while (root < heap.size() && left_child < heap.size() 
	       && right_child < heap.size() 
	       && (heap[root] < heap[left_child] || heap[root] < heap[right_child]))
	{
		if (heap[left_child] > heap[right_child])
		{
			swap(heap[root], heap[left_child]);
			root = left_child;
		}
		else 
		{
			swap(heap[root], heap[right_child]);
			root = right_child;
		}

		left_child = 2 * root + 1;
		right_child = 2 * root + 2;
	}

	return maximum_element;
}

vector<int> generate_vector_with_random_numbers(void)
{
	random_device rnd_device;
	mt19937 mersenne_engine {rnd_device()};
	uniform_int_distribution<int> distribution {1, MAX};

	auto gen = [&]() {
			return distribution(mersenne_engine);
		};

	vector<int> generated_vector(MAX);
	generate(generated_vector.begin(), generated_vector.end(), gen);
	shuffle(generated_vector.begin(), generated_vector.end(), mersenne_engine);

	return generated_vector;
}

void heap_sort(vector<int> &array)
{
        vector<int> heap;

	for (auto element : array)
	{
		insert(heap, element);
	}

	for (size_t i = array.size() - 1; i > 0 ; i--)
	{
		array[i] = extract(heap);
	}

	array[0] = extract(heap);
}	


int main (int argc, char *argv[]) 
{
	vector<int> test_vector;
	vector<int> heap;

	for (int i = MAX; i > 0; i--)
	{
		test_vector.push_back(i);
	}

	std::cout << "Test vector before sorting" << endl;

	for (auto element : test_vector)
	{
		std::cout << element << " " ;
	}
	std::cout << endl;





	auto start = chrono::high_resolution_clock::now();
	heap_sort(test_vector);
	auto stop = chrono::high_resolution_clock::now();

	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

	std::cout << "time taken by inserting all elements to heap: "
	     << duration.count() << "ms" << endl;

	for (auto element : test_vector)
	{
		std::cout << element << " " ;
	}
	std::cout << endl;
	
	return 0;
}
	


	

	
	
    
