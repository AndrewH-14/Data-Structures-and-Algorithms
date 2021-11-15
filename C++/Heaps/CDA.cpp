/**
 * @file CDA.cpp
 *
 * This file implements a circular dynamic array for project 1 of the CS 201 Data Stuctures and
 * Algorithms class.
 *
 * Written by: Andrew Hankins
 */

// Include guard for CDA.cpp
#ifndef CDA_CPP

#include <iostream>

using namespace std;

template <typename elmtype>

class CDA
{
    private:

        int user_size    = 0;         ///< The size of the #data_array that the user has access to.
        int arr_capacity = 0;         ///< The total storage allocated for the #data_array.

        int front_idx = 0;            ///< The index of the front element of the circular array.
        int back_idx  = 0;            ///< The index of the back element of the circular array.

        bool b_init      = false;     ///< Used to signal if the array should be treated as initialized.
        elmtype init_val = 0;         ///< The value that the array should be initialzed to.
        int elms_changed = 0;         ///< The number of elements that have been changed of the init array.

        elmtype ref_val;              ///< Reference value for the operator function

        elmtype * data_array  = NULL; ///< A pointer to the array where the data will be stored.
        int     * idx_array   = NULL; ///< A pointer to the array where the indexes of the #point_array will be stored.
        int     * point_array = NULL; ///< A pointer to the array where the indexes of the #idx_array will be stored.

    public:

        /**
         * The default constructor, sets the arr_capacity to 1,
         * user_size to 0.
         */
        CDA(void)
        {
            // The array has a capacity of 1, but the user has not added any elements.
            user_size    = 0;
            arr_capacity = 1;

            // The array has not been initialized
            b_init = false;

            // No elements have been added so the front and back are both at idx 0.
            front_idx = 0;
            back_idx  = 0;

            // Allocates an array of size 1.
            data_array  = new elmtype[1];
            idx_array   = NULL;
            point_array = NULL;
        }

        /**
         * Constructor that creates an array of #user_size s and #arr_capacity s.
         *
         * @param[in] s The value used to initialize user_size and arr_capacity.
         */
        CDA(int s)
        {
            // The user_size and arr_capcity variable should match.
            user_size    = s;
            arr_capacity = s;

            // The array has not been initialized.
            b_init = false;

            // Array is full so both indexes should be set to 0.
            front_idx = 0;
            back_idx  = 0;

            // Allocates an array of size s.
            data_array  = new elmtype[s];
            idx_array   = NULL;
            point_array = NULL;
        }

        /**
         * Constructor that creates an array of #user_size s and #arr_capacity s. The array created
         * should act as though it has been initialized with the value init, but it should still be
         * in O(1) time.
         *
         * @param[in] s    The value used to initialize the #user_size and #arr_capacity.
         * @param[in] init The value that the array should act as though it has been initialized with.
         */
        CDA(int s, elmtype init)
        {
            // Variables specific to the initialized array
            b_init             = true;
            init_val           = init;
            elms_changed       = 0;

            // User size and capacity should both be equal to the size of the array.
            user_size    = s;
            arr_capacity = s;

            // Array is full so the indexes should be equal to each other.
            front_idx = 0;
            back_idx  = 0;

            // The data array as well as the two arrays needed to initialize an array in constant time.
            // All should be of size s.
            data_array  = new elmtype[s];
            idx_array   = new int[s];
            point_array = new int[s];
        }

        /**
         * Copy Assignment operator.
         *
         * @param[in] obj_being_copied A reference to a CDA object that is going to be copied over.
         *
         *@return A reference to an updated CDA object that matches #obj_being_copied.
         */
        CDA& operator=(const CDA &obj_being_copied)
        {
            // Must delete any prior data before copying new data over.
            if (NULL != data_array)
            {
                delete[] data_array;
                data_array = NULL;
            }
            if (NULL != idx_array)
            {
                delete[] idx_array;
                idx_array = NULL;
            }
            if (NULL != point_array)
            {
                delete[] point_array;
                idx_array = NULL;
            }

            user_size    = obj_being_copied.user_size;
            arr_capacity = obj_being_copied.arr_capacity;

            front_idx = obj_being_copied.front_idx;
            back_idx  = obj_being_copied.back_idx;

            b_init = obj_being_copied.b_init;
            init_val = obj_being_copied.init_val;
            elms_changed = obj_being_copied.elms_changed;

            ref_val = obj_being_copied.ref_val;

            elmtype * new_data_array  = new elmtype[arr_capacity];
            int     * new_idx_array   = new int[arr_capacity];
            int     * new_point_array = new int[arr_capacity];

            // Loop through arrays and copy the data over for the arrays.
            for (int idx = 0; idx < arr_capacity; idx++)
            {
                new_data_array[idx] = obj_being_copied.data_array[idx];

                if (b_init)
                {
                    new_idx_array[idx]   = obj_being_copied.idx_array[idx];
                    new_point_array[idx] = obj_being_copied.point_array[idx];
                }
            }

            // Set the class array variable to the copied arrays.
            data_array  = new_data_array;
            idx_array   = new_idx_array;
            point_array = new_point_array;

            return *this;
        }

        /**
         * Copy constructor.
         *
         * @param[in] obj_being_copied A reference to a CDA object that should be used to create a
         *                             new CDA object.
         */
        CDA(const CDA &obj_being_copied)
        {
            user_size    = obj_being_copied.user_size;
            arr_capacity = obj_being_copied.arr_capacity;

            front_idx = obj_being_copied.front_idx;
            back_idx  = obj_being_copied.back_idx;

            b_init = obj_being_copied.b_init;
            init_val = obj_being_copied.init_val;
            elms_changed = obj_being_copied.elms_changed;

            ref_val = obj_being_copied.ref_val;

            elmtype * new_data_array  = new elmtype[arr_capacity];
            int     * new_idx_array   = new int[arr_capacity];
            int     * new_point_array = new int[arr_capacity];

            for (int idx = 0; idx < arr_capacity; idx++)
            {
                new_data_array[idx] = obj_being_copied.data_array[idx];

                if (b_init)
                {
                    new_idx_array[idx]   = obj_being_copied.idx_array[idx];
                    new_point_array[idx] = obj_being_copied.point_array[idx];
                }
            }

            data_array  = new_data_array;
            idx_array   = new_idx_array;
            point_array = new_point_array;
        }

        /**
         * Destructor for the CDA class.
         *
         * @note Deletes any non-NULL array that may have been allocated during runtime.
         */
        ~CDA()
        {
            if (NULL != data_array)
            {
                delete[] data_array;
                data_array = NULL;
            }
            if (NULL != idx_array)
            {
                delete[] idx_array;
                idx_array = NULL;
            }
            if (NULL != point_array)
            {
                delete[] point_array;
                idx_array = NULL;
            }
        }

        /**
         * Returns the size of the array.
         *
         * @return The size of the array that the user has access to.
         */
        int Length()
        {
            return user_size;
        }

        /**
         * Returns the capacity of the array.
         *
         * @return The total capicity of the array.
         */
        int Capacity()
        {
            return arr_capacity;
        }

        /**
         * Overload versin of the [] operator for the CDA class.
         *
         * @param[in] idx The index of the array that the user wants to access.
         *
         * @return A reference to a value in the #data_array.
         */
        elmtype &operator[](int idx)
        {
            if ((idx > (user_size - 1)) || (idx < 0)) //< If the idx is out of the accesible range.
            {
                cout << "Index out of bounds!\n";
                return ref_val;
            }
            else //< Return a reference to the idx of the array.
            {
                int idx_to_access = (front_idx + idx) % arr_capacity;

                bool b_initialized = true;

                if (b_init)
                {
                    if (idx_array[idx_to_access] < elms_changed)
                    {
                        if ((idx_array[idx_to_access] >= 0) && (idx_array[idx_to_access] < arr_capacity))
                        {
                            if (point_array[idx_array[idx_to_access]] == idx_to_access)
                            {
                                // Data is valid, return the reference.
                                b_initialized = false;
                                return data_array[idx_to_access];
                            }
                        }
                    }

                    if (b_initialized)
                    {
                        // Insert the init value into the array and update the arrays.
                        idx_array[idx_to_access]  = elms_changed;
                        point_array[elms_changed] = idx_to_access;
                        data_array[idx_to_access] = init_val;
                        elms_changed++;

                        return data_array[idx_to_access];
                    }
                }

                // Array was not initialized return the reference.
                return data_array[idx_to_access];
            }
        }

        /**
         * Functions to double the size of the #data_array.
         *
         * @note If the #data_array was initialized in constant time then the #idx_array and #point_array
         *       will also be doubled.
         */
        void DoubleArray()
        {
            // Calculate the size of the new array
            int new_arr_capacity = (2 * arr_capacity);

            // Create a new array that is twice as big as the current one
            elmtype * new_data_array = new elmtype[new_arr_capacity];
            int * new_idx_array      = NULL;
            int * new_point_array    = NULL;

            if (b_init)
            {
                // Create new arrays for the init functionality
                new_idx_array   = new int[new_arr_capacity];
                new_point_array = new int[new_arr_capacity];
            }

            // Keep track of the values that have been changed and are being copied over.
            int new_elms_changed = 0;

            for (int idx = 0; idx < user_size; idx++)
            {
                int const idx_to_copy = (front_idx + idx) % arr_capacity;

                if (b_init)
                {
                    // If the value has been changed, use the #new_elms_changed variable to update
                    // the new arrays.
                    if (WasChanged(idx_to_copy))
                    {
                        new_idx_array[idx] = new_elms_changed;
                        new_point_array[new_elms_changed] = idx;
                        new_elms_changed++;
                    }
                }

                // Copy the data value over
                new_data_array[idx] = data_array[idx_to_copy];
            }

            // Set the elms_changed variable
            elms_changed = new_elms_changed;

            // Free the memory used by the old arrays
            if (NULL != data_array)
            {
                delete[] data_array;
                data_array = NULL;
            }
            if (NULL != idx_array)
            {
                delete[] idx_array;
                idx_array = NULL;
            }
            if (NULL != point_array)
            {
                delete[] point_array;
                idx_array = NULL;
            }

            // Store the new array pointer(s)
            data_array  = new_data_array;
            idx_array   = new_idx_array;
            point_array = new_point_array;

            // Reset front and back indexes
            front_idx = 0;
            back_idx  = user_size;

            // Update the capacity variable
            arr_capacity = new_arr_capacity;

        }

        /**
         * Adds an element to the back of the #data_array.
         *
         * @param[in] data_val The data element to be added to the end of the array.
         *
         * @note Will double the size of the array in O(N) time if the array is at maximum capacity.
         */
        void AddEnd(elmtype data_val)
        {
            if (user_size == arr_capacity)
            {
                DoubleArray();
            }

            if (b_init)
            {
                data_array[back_idx]      = data_val;
                idx_array[back_idx]       = elms_changed;
                point_array[elms_changed] = back_idx;
                elms_changed++;
            }
            else
            {
                data_array[back_idx] = data_val;
            }

            // Update the size of the array the user has access to as well as the back_idx.
            user_size++;
            back_idx = (back_idx + 1) % arr_capacity;
        }

        /**
         * Adds an element to the front of the circular dynamic array.
         *
         * @param[in] v The data element to be added to the front of the array.
         *
         * @note Will double the size of the array in O(N) time if the array is at maximum capacity.
         */
        void AddFront(elmtype v)
        {
            if (user_size == arr_capacity)
            {
                DoubleArray();
            }

            // Update the front_idx variable
            front_idx = (front_idx - 1 + arr_capacity) % arr_capacity;

            if (b_init)
            {
                data_array[front_idx]      = v;
                idx_array[front_idx]       = elms_changed;
                point_array[elms_changed]  = front_idx;
                elms_changed++;
            }
            else
            {
                data_array[front_idx] = v;
            }

            user_size++;
        }

        /**
         * Function that checks whether a given index in the data array has been changed or not after
         * it had been initialzed to a certain value
         *
         * @param[in] idx The index to be checked.
         *
         * @retval true  The index has been changed.
         * @retval false The index has not been changed.
         */
        bool WasChanged(int idx)
        {
            if (idx_array[idx] < elms_changed)
            {
                if ((idx_array[idx] >= 0) && (idx_array[idx] < arr_capacity))
                {
                    if (point_array[idx_array[idx]] == idx)
                    {
                        return true;
                    }
                }
            }

            return false;
        }

        /**
         * Function that halves the size of the data array.
         *
         * @note Takes O(N) time to copy the data to the new array.
         *
         * @note If the #data_array was initialized in constant time then the #idx_array and #point_array
         *       will also be doubled.
         */
        void HalfArray()
        {
            int new_arr_capacity = (arr_capacity / 2);

            // Create new arrays that is half the size of the current one
            elmtype * new_data_array = new elmtype[new_arr_capacity];
            int * new_idx_array   = NULL;
            int * new_point_array = NULL;

            if (b_init)
            {
                // Create new arrays for the init functionality
                new_idx_array   = new int[new_arr_capacity];
                new_point_array = new int[new_arr_capacity];
            }

            int new_elms_changed = 0;

            for (int idx = 0; idx < user_size; idx++)
            {
                int const idx_to_copy = (front_idx + idx) % arr_capacity;

                if (b_init)
                {
                    if (WasChanged(idx_to_copy))
                    {
                        new_idx_array[idx] = new_elms_changed;
                        new_point_array[new_elms_changed] = idx;
                        new_elms_changed++;
                    }
                }

                new_data_array[idx] = data_array[idx_to_copy];
            }

            // Set the elms_changed variable
            elms_changed = new_elms_changed;

            // Free the memory used by the old arrays
            if (NULL != data_array)
            {
                delete[] data_array;
                data_array = NULL;
            }
            if (NULL != idx_array)
            {
                delete[] idx_array;
                idx_array = NULL;
            }
            if (NULL != point_array)
            {
                delete[] point_array;
                point_array = NULL;
            }

            // Store the new array pointer
            data_array  = new_data_array;
            idx_array   = new_idx_array;
            point_array = new_point_array;

            // Reset the front and back indexes
            front_idx = 0;
            back_idx  = user_size;

            // Update the capacity variable
            arr_capacity = new_arr_capacity;
        }

        /**
         * Deletes the back element of the array.
         *
         * @note If the array is only 25% full after the delete, the array will be halved.
         */
        void DelEnd()
        {
            // If the array is empty, don't do anything
            if (user_size == 0)
            {
                return;
            }

            // Update the circular array variables
            if (back_idx == 0)
            {
                back_idx = arr_capacity - 1;
            }
            else
            {
                back_idx = (back_idx - 1) % arr_capacity;
            }

            user_size--;

            // Don't let arr_capacity go below 4
            if ((user_size == (arr_capacity / 4)) && ((arr_capacity / 2) >= 4))
            {
                HalfArray();
            }
        }

        /**
         * Function to delete the front index of the data array
         *
         * @note Will half the size of the array when 25% of #arr_capacity is being used.
         */
        void DelFront()
        {
            // If the array is empty, don't do anything
            if (user_size == 0)
            {
                return;
            }

            // Update the circular array variables
            front_idx = (front_idx + 1) % arr_capacity;
            user_size--;

            // Don't let arr_capacity go below 4
            if ((user_size == (arr_capacity / 4)) && ((arr_capacity / 2) >= 4))
            {
                HalfArray();
            }
        }

        /**
         * The implementation of the binary search algorithm.
         *
         * @param[in]  lower_bound The index of the lowest position of the section being searched.
         * @param[in]  upper_bound The index of the highest position of the section being searched.
         * @param[out] e           The element that is being searched for.
         *
         * @return The index of the item if found, otherwise a negative number that is the bitwise
         *         complement of the index of the next element that is larger than e or, if there is
         *         no larger element, the bitwise complement of size.
         */
        int BinSearchImpl(int lower_bound, int upper_bound, elmtype e)
        {
            int const mid     = (lower_bound + upper_bound) / 2;  //< The middle of the current section.
            int const mid_idx = (front_idx + mid) % arr_capacity; //< The index of the middle.

            // Recursively search until the the two bounds reach each other
            if (lower_bound <= upper_bound)
            {
                elmtype data_val;

                if (b_init) //< Check which value to used of the init array
                {
                    if (WasChanged(mid_idx))
                    {
                        data_val = data_array[mid_idx];
                    }
                    else
                    {
                        data_val = init_val;
                    }
                }
                else //< Directly access the data variable
                {
                    data_val = data_array[mid_idx];
                }

                if (e == data_val)
                {
                    // The element was found
                    return mid;
                }
                else if (e < data_val)
                {
                    // Search the lower half
                    return BinSearchImpl(lower_bound, mid - 1, e);
                }
                else // e > data_val
                {
                    // Search the upper half
                    return BinSearchImpl(mid + 1, upper_bound, e);
                }
            }

            if ((mid_idx + 1) == ((front_idx + user_size) % arr_capacity))
            {
                // Returning the bitwise complement of the size.
                return ~user_size;
            }
            else
            {
                // Returning the bitwise complement of the next element greater.
                return (~(mid + 1));
            }
        }

        /**
         * Performs a binary search on a sorted array looking for item e.
         *
         * @param[in] e The elmtype value to look for in the array.
         *
         * @return The index of the item if found, otherwise a negative number that is the bitwise
         *         complement of the index of the next element that is larger than e or, if there is
         *         no larger element, the bitwise complement of size.
         */
        int BinSearch(elmtype e)
        {
            return BinSearchImpl(0, user_size - 1, e);
        }

        /**
         * Functions that returns a value from the #data_array
         *
         * @param[in] idx The index to be used directly to access elements in the #data_array, and
         *                the #idx_array if needed.
         *
         * @return The value at the given index.
         */
        elmtype GetVal(int idx)
        {
            if (b_init)
            {
                if (WasChanged(idx))
                {
                    return data_array[idx];
                }
                else
                {
                    return init_val;
                }
            }
            else
            {
                return data_array[idx];
            }
        }

        /**
         * Function that merges two sorted arrays together.
         *
         * @param[in] lower_bound The lower index of the section being merged.
         * @param[in] mid         The middle index of the section being merged.
         * @param[in] upper_bound The upper index of the section being sorted.d
         */
        void Merge(int lower_bound, int mid, int upper_bound)
        {
            elmtype temp_data_arr[upper_bound - lower_bound + 1]; ///< Stores the data to be copied over
            int temp_idx_arr[upper_bound - lower_bound + 1];      ///< Stores the idx info if needed
            bool use_idx_arr[upper_bound - lower_bound + 1];      ///< Stores boolean value to determine if the idx value should be used.

            int i = lower_bound; ///< Start of the left section
            int j = mid + 1;     ///< Start of the right section
            int k = 0;           ///< Index for the temp array

            // While there are still values in both arrays
            while (i <= mid && j <= upper_bound)
            {
                // If the value in the left half of the array is less than or equal to the value in
                // the right add it to the temp array. Otherwise add the value in right half of the array.
                if (GetVal((front_idx + i) % arr_capacity) <= GetVal((front_idx + j) % arr_capacity))
                {
                    temp_data_arr[k] = GetVal((front_idx + i) % arr_capacity);

                    if (b_init)
                    {
                        if (WasChanged((front_idx + i) % arr_capacity))
                        {
                            temp_idx_arr[k] = idx_array[(front_idx + i) % arr_capacity];
                            use_idx_arr[k]  = true;
                        }
                        else
                        {
                            use_idx_arr[k] = false;
                        }
                    }
                    k++; //< Increment the index of the temp array
                    i++; //< Increment the index for the left side of the array
                }
                else
                {
                    temp_data_arr[k] = GetVal((front_idx + j) % arr_capacity);

                    if (b_init)
                    {
                        if (WasChanged((front_idx + j) % arr_capacity))
                        {
                            temp_idx_arr[k] = idx_array[(front_idx + j) % arr_capacity];
                            use_idx_arr[k]  = true;
                        }
                        else
                        {
                            use_idx_arr[k] = false;
                        }
                    }
                    k++; //< Increment the index of the temp array
                    j++; //< Increment the index for the right side of the array
                }
            }

            // Fill up the temp array with values from the left half of the array
            while (i <= mid)
            {
                temp_data_arr[k] = GetVal((front_idx + i) % arr_capacity);
                if (b_init)
                {
                    if (WasChanged((front_idx + i) % arr_capacity))
                    {
                        temp_idx_arr[k] = idx_array[(front_idx + i) % arr_capacity];
                        use_idx_arr[k]  = true;
                    }
                    else
                    {
                        use_idx_arr[k] = false;
                    }
                }
                k++; //< Increment the index of the temp array
                i++; //< Increment the index for the right side of the array
            }

            // Fill up the temp array with values from the right half of the array
            while (j <= upper_bound)
            {
                temp_data_arr[k] = GetVal((front_idx + j) % arr_capacity);

                if (b_init)
                {
                    if (WasChanged((front_idx + j) % arr_capacity))
                    {
                        temp_idx_arr[k] = idx_array[(front_idx + j) % arr_capacity];
                        use_idx_arr[k]  = true;
                    }
                    else
                    {
                        use_idx_arr[k] = false;
                    }
                }
                k++; //< Increment the index of the temp array
                j++; //< Increment the index for the right side of the array
            }

            // Copy the sorted data back into the data_array
            for (i = lower_bound; i <= upper_bound; i++)
            {
                data_array[(front_idx + i) % arr_capacity] = temp_data_arr[i - lower_bound];

                if (b_init)
                {
                    if (use_idx_arr[i - lower_bound])
                    {
                        idx_array[(front_idx + i) % arr_capacity]  = temp_idx_arr[i - lower_bound];
                        point_array[idx_array[(front_idx  + i) % arr_capacity]] = (front_idx + i) % arr_capacity;
                    }
                }
            }
        }

        /**
         * Merge sort implementation.
         *
         * @param[in] lower_bound The lower index of the section being sorted.
         * @param[in] upper_bound The upper index of the section being sorted.
         */
        void MergeSort(int lower_bound, int upper_bound)
        {
            // Call recursively until the sections are as small as possible
            if (lower_bound >= upper_bound)
            {
                return;
            }

            // Find the mid point of the data array
            int mid = (lower_bound + upper_bound) / 2;

            // Sort the left half of the data array
            MergeSort(lower_bound, mid);

            // Sort the right half of the data array
            MergeSort(mid + 1, upper_bound);

            // Merge the two sorted halfs together
            Merge(lower_bound, mid, upper_bound);
        }

        /**
         * Performs the merge sort algorithm on the array.
         *
         * @note After #Sort() is called, all of the init values will have been inserted into the array.
         */
        void Sort()
        {
            // Recursively sort the data array
            MergeSort(0, user_size - 1);

            // Init values have been stored in the array, so it can now function as an uninitialized
            // array.
            b_init = false;

            // Freeing unneeded memory
            if (NULL != idx_array)
            {
                delete[] idx_array;
                idx_array = NULL;
            }
            if (NULL != point_array)
            {
                delete[] point_array;
                point_array = NULL;
            }
        }

        /**
         * Function to swap two values of the #idx_array if necessary.
         *
         * @param[in] idx1 The index of the first value to potentially swap.
         * @param[in] idx2 The index of the second value to potentially swap.
         */
        void SwapInitValues(int const idx1, int const idx2)
        {
            if (WasChanged(idx1) && WasChanged(idx2))
            {
                // Do Nothing
            }
            else if (WasChanged(idx1))
            {
                swap(idx_array[idx1],
                     idx_array[idx2]);

                // Since only one of the values have been changed, the point array must be updated.
                point_array[idx_array[idx2]] = idx2;
            }
            else if (WasChanged(idx2))
            {
                swap(idx_array[idx2],
                     idx_array[idx1]);

                // Since only one of the values have been changed, the point array must be updated.
                point_array[idx_array[idx1]] = idx1;
            }
        }

        /**
         * Generates a random partition value and swaps it to the end of the array.
         *
         * @param[in] start The index to be used as the starting position.
         * @param[in] end   The index to be used as the ending position.
         *
         * @return A pivot index to be used in they quickselect algorithm.
         */
        int RandomPartition(int const start, int const end)
        {
            // Calculate a random index within the range.
            int i = (rand() % (end - start + 1)) + start;

            if (b_init)
            {
                SwapInitValues((front_idx + end) % arr_capacity,
                               (front_idx + i) % arr_capacity);
            }

            // Move the random value to the last index.
            swap(data_array[(front_idx + end) % arr_capacity],
                 data_array[(front_idx + i) % arr_capacity]);

            return Partition(start, end);
        }

        /**
         * Partitions the block of the array using the start and end points.
         *
         * @param[in] start The index to be used as the starting position.
         * @param[in] end   The index to be used as the ending position.
         *
         * @return The index of the pivot element.
         */
        int Partition(int const start, int const end)
        {
            elmtype pivot_element;

            // Get the pivot element from the end of the section.
            if (b_init)
            {
                if (WasChanged((front_idx + end) % arr_capacity))
                {
                    pivot_element = data_array[(front_idx + end) % arr_capacity];
                }
                else
                {
                    pivot_element = init_val;
                }
            }
            else
            {
                pivot_element = data_array[(front_idx + end) % arr_capacity];
            }

            int i = start - 1;

            cout << "test\n";

            // Compare each element in the section to the pivot element.
            for (int j = start; j <= (end - 1); j++)
            {
                cout << (end - 1) << endl;
                cout << j << endl;

                elmtype data_val;

                // Get the value to compare against the pivot element.
                if (b_init)
                {
                    if (WasChanged((front_idx + j) % arr_capacity))
                    {
                        data_val = data_array[(front_idx + j) % arr_capacity];
                    }
                    else
                    {
                        data_val = init_val;
                    }
                }
                else
                {
                    data_val = data_array[(front_idx + j) % arr_capacity];
                }

                // If the element is less than or equal to the pivot element
                if (data_val <= pivot_element)
                {
                    i++;

                    if (b_init)
                    {
                        SwapInitValues((front_idx + i) % arr_capacity,
                                       (front_idx + j) % arr_capacity);
                    }

                    swap(data_array[(front_idx + i) % arr_capacity],
                         data_array[(front_idx + j) % arr_capacity]);
                }
            }

            if (b_init)
            {
                SwapInitValues((front_idx + i + 1) % arr_capacity,
                               (front_idx + end) % arr_capacity);
            }

            swap(data_array[(front_idx + i + 1) % arr_capacity],
                 data_array[(front_idx + end) % arr_capacity]);

            return i + 1;
        }

        /**
         * A function that performs the quickselect algorithm with a random partition.
         *
         * @param[in] start The starting index of the section.
         * @param[in] end   The ending index of the section.
         * @param[in] k     An integer signaling which smallest element the user is looking for.
         *
         * @return The kth smallest element in the array.
         */
        elmtype QuickSelect(int start, int end, int k)
        {
            // If there is only one element in the array, return it.
            if (start == end)
            {
                if (b_init)
                {
                    if (!WasChanged((front_idx + start) % arr_capacity))
                    {
                        return init_val;
                    }
                }

                return data_array[(front_idx + start) % arr_capacity];
            }

            int pivotIndex = RandomPartition(start, end);

            //< Number of elements less than or equal to the pivot index
            int i = pivotIndex - start + 1;

            if (k == i) //< kth smallest element is the pivot
            {
                if (b_init)
                {
                    if (!WasChanged((front_idx + pivotIndex) % arr_capacity))
                    {
                        return init_val;
                    }
                }

                return data_array[(front_idx + pivotIndex) % arr_capacity];
            }
            else if (k < i) //< kth smallest element is to the left of the pivot
            {
                return QuickSelect(start, pivotIndex - 1, k);
            }
            else //kth smallest element is to the right of the pivot
            {
                return QuickSelect(pivotIndex + 1, end, k - i);
            }
        }

        /**
         * Function that selects the kth smallest element in the array.
         *
         * @note The positions of the elements in the array are likely to change.
         *
         * @param[in] k An integer signaling which smallest element the user is looking for.
         *
         * @return The kth smallest element in the array.
         */
        elmtype Select(int k)
        {
            return QuickSelect(0, user_size - 1, k);
        }

        /**
         * Performs a linear search of the data array looking for the specified item.
         *
         * @param[in] e The elmtype value to look for in the array.
         *
         * @return The index of the item if found, or -1 if the item was not in the array.
         */
        int Search(elmtype e)
        {
            // Loop through the array looking for the specified value.
            for (int i = 0; i < user_size; i++)
            {
                int idx_to_check = (front_idx + i) % arr_capacity;

                if (b_init)
                {
                    if (WasChanged(idx_to_check))
                    {
                        if (e == data_array[idx_to_check])
                        {
                            return i;
                        }
                    }
                    else if (e == init_val)
                    {
                        return i;
                    }
                }
                else if (e == data_array[(front_idx + i) % arr_capacity])
                {
                    return i;
                }
            }

            return -1;
        }

        /*********************************
         * Debug Functions
         *********************************/

        /**
         * Displays information regarding the initialized values of the array.
         */
        void InitCheck()
        {
            cout << "Elements Changed: " << elms_changed       << endl;
            cout << "Init Value:       " << init_val           << endl;
        }

        /**
         * Displays information regarding the data array.
         */
        void ArrayCheck()
        {
            cout << "Front Index: "    << front_idx    << endl;
            cout << "Back Index: "     << back_idx     << endl;
            cout << "User Size: "      << user_size    << endl;
            cout << "Array Capacity: " << arr_capacity << endl;
        }

        /**
         * Displays the contents of the data array.
         */
        void DisplayArrayContents()
        {
            for (int idx = 0; idx < user_size; idx++)
            {
                cout << data_array[(front_idx + idx) % arr_capacity] << " ";
            }

            cout << endl;
        }

        /**
         * Displays the arrays that are used to see if an initialized index has been changed or not.
         */
        void DisplayInitArrays()
        {
            for (int idx = 0; idx < arr_capacity; idx++)
            {
                cout << idx_array[idx] << " ";
            }

            cout << endl;

            for (int idx = 0; idx < elms_changed; idx++)
            {
                cout << point_array[idx] << " ";
            }

            cout << endl;
        }
};

// End of include guard for CDA_CPP
#define CDA_CPP
#endif
