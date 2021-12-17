/**
 * @file CDA.cpp
 *
 * This file implements a heap for project 3 of the CS 201 Data Stuctures and
 * Algorithms class.
 *
 * Written by: Andrew Hankins
 */

#include <iostream>

#include "CDA.cpp"

using namespace std;

template<typename keytype>

class Heap
{
    private:

        /// Dynamic array that will store the heap data structure.
        CDA<keytype> heap_arr;

        /// The index of the #heap_arr where a new key should be inserted.
        int insert_index;

        /// A keytype value to use when an invalid key is requested.
        keytype ref_val;

        /**
         * Helper funtion to perform "bottom-up" heap building.
         *
         * @param[in] index The index of the heap to evaluate.
         */
        void minHeapify(int index)
        {
            int left_index;
            int right_index;
            int smallest_key_index;
            bool b_continue = true;

            // Loop until the subtree contians no heap violations
            while (b_continue)
            {
                left_index  = (2 * index) + 1;
                right_index = (2 * index) + 2;
                smallest_key_index = index;

                /**
                 * If index has a left child and it's key is less than the key at index, the smallest key in
                 * the 3 node subtree is the key at the left child index.
                 */
                if ((left_index < insert_index) && (heap_arr[left_index] < heap_arr[index]))
                {
                    smallest_key_index = left_index;
                }

                /**
                 * If index has a right child and it's key is less that the current smallest key, the
                 * smallest key in the 3 node subtree is the key at the right child index.
                 */
                if ((right_index < insert_index) && (heap_arr[right_index] < heap_arr[smallest_key_index]))
                {
                    smallest_key_index = right_index;
                }

                /**
                 * If the smallest key's index is not equal to the starting index, there is a heap
                 * order violation. Fix the violation, and then follow the key down the subtree.
                 */
                if (smallest_key_index != index)
                {
                    swap(heap_arr[index], heap_arr[smallest_key_index]);
                    index = smallest_key_index;
                }
                else
                {
                    // There are no more heap order violations in this subtree
                    b_continue = false;
                }
            }
        }

    public:

        /**
         * Default constructor for the Heap class.
         */
        Heap()
        {
            insert_index = 0;
        }

        /**
         * Constructor for the Heap class that creates a heap data structure from
         * a given array.
         *
         * @param[in] k A pointer to the array that contains the keys to be added.
         * @param[in] s The number of keys in the array.
         */
        Heap(keytype k[], int s)
        {
            insert_index = s;

            // Add the keys to the heap in the order given
            for (int idx = 0; idx < s; idx++)
            {
                heap_arr.AddEnd(k[idx]);
            }

            // Loop through the heap fixing any violations using the "bottom-up" method
            for (int idx = insert_index - 1; idx >= 0; idx--)
            {
                this->minHeapify(idx);
            }
        }

        /**
         * Destructor for the Heap class.
         */
        ~Heap()
        {

        }

        /**
         * Copy constructor.
         *
         * @param[in] obj_being_copied A reference to a Heap object that should be used ot create a
         *                             new Heap object.
         */
        Heap(const Heap &obj_being_copied)
        {
            // Uses the CDA's copy assignment operator, which performs a deep copy
            heap_arr     = obj_being_copied.heap_arr;

            insert_index = obj_being_copied.insert_index;
            ref_val      = ref_val;
        }

        /**
         * Copy Assignment operator.
         *
         * @param[in] obj_being_copied A reference to a Heap object that is going to be copied over.
         *
         * @return A reference to an updated Heap object that matches #obj_being_copied.
         */
        Heap& operator=(const Heap &obj_being_copied)
        {
            // Uses the CDA's copy assignment operator, which performs a deep copy
            heap_arr     = obj_being_copied.heap_arr;

            insert_index = obj_being_copied.insert_index;
            ref_val      = ref_val;
        }

        /**
         * Returns the minumum key in the heap without modifying it.
         *
         * @return The minimum key in the heap.
         */
        keytype peekKey()
        {
            // Return random value if the Heap is empty
            if (insert_index == 0)
            {
                return ref_val;
            }
            else
            {
                // Minimum value should be at index 0
                return heap_arr[0];
            }
        }

        /**
         * Removes the minimum key in the heap and returns the key.
         *
         * @return The minimum key in the heap.
         */
        keytype extractMin()
        {
            keytype min_key;

            if (insert_index > 0)
            {

                // Replace the key at index zero with the last key in the heap
                min_key = heap_arr[0];
                insert_index--;
                heap_arr[0] = heap_arr[insert_index];
                bool b_continue = true;
                int current_index = 0;
                heap_arr.DelEnd();

                /**
                 * Loop through the heap until no more order violations are found
                 */
                while (b_continue)
                {
                    int left_child_idx  = (2 * current_index) + 1;
                    int right_child_idx = (2 * current_index) + 2;

                    if ((left_child_idx < insert_index) && (right_child_idx < insert_index))
                    {
                        // key has two children, therefore all the options need to be checked

                        if ((heap_arr[left_child_idx] < heap_arr[current_index]) &&
                            (heap_arr[left_child_idx] < heap_arr[right_child_idx]))
                        {
                            // The left child's priority is less than the right's, therefore swap it with the parent
                            swap(heap_arr[left_child_idx], heap_arr[current_index]);
                            current_index = left_child_idx;
                        }
                        else if ((heap_arr[right_child_idx] < heap_arr[current_index]) &&
                                 (heap_arr[right_child_idx] < heap_arr[left_child_idx]))
                        {
                            // The right child's priority is less than the left's, therfore swap it with the parent
                            swap(heap_arr[right_child_idx], heap_arr[current_index]);
                            current_index = right_child_idx;
                        }
                        else
                        {
                            // No more heap order violations exist
                            b_continue = false;
                        }
                    }
                    else if (left_child_idx < insert_index)
                    {
                        // key only has a left child, therefore just check the left child's priority

                        if (heap_arr[left_child_idx] < heap_arr[current_index])
                        {
                            swap(heap_arr[left_child_idx], heap_arr[current_index]);
                            current_index = left_child_idx;
                        }
                        else
                        {
                            // No more heap order violations exist
                            b_continue = false;
                        }
                    }
                    else
                    {
                        // Reached the lowest level of the heap
                        b_continue = false;
                    }
                }
            }
            else
            {
                cout << "Heap is empty!\n";
            }

            return min_key;
        }

        /**
         * Inserts the key k into the heap.
         *
         * @param[in] k The key to be inserted into the heap.
         */
        void insert(keytype k)
        {
            // Insert the new k at the end of the array
            heap_arr.AddEnd(k);

            bool b_continue = true;
            int inserted_key_index = insert_index;

            /**
             * Loop through the heap, fixing any violations caused by the insert
             */
            while (b_continue)
            {
                if (inserted_key_index == 0)
                {
                    // Inserted key is at the top of the heap
                    b_continue = false;
                }
                else if (heap_arr[inserted_key_index] < heap_arr[(inserted_key_index - 1) / 2])
                {
                    // Inserted key's priority is less than it's parent, therefore swap them and continue
                    // up the heap
                    swap(heap_arr[inserted_key_index], heap_arr[(inserted_key_index - 1) / 2]);
                    inserted_key_index = (inserted_key_index - 1) / 2;
                }
                else
                {
                    // No heap order violations remain
                    b_continue = false;
                }
            }

            insert_index++;
        }

        /**
         * Writes the keys stored in the array, starting at the root.
         */
        void printKey()
        {
            for (int idx = 0; idx < insert_index; idx++)
            {
                cout << heap_arr[idx] << " ";
            }
            cout << endl;
        }
};
