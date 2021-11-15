/**
 * @file FibHeap.cpp
 *
 * This file implements a fibonacci heap for project 3 of the CS 201 Data Structures and
 * Algorithms class.
 *
 * Written by: Andrew Hankins
 */

#include <iostream>

using namespace std;

template<typename keytype>

class FibHeap
{
    /**
     * Private attributes for the FibHeap class.
     */
    private:

        /**
         * @struct Node
         */
        typedef struct node
        {
            /// This nodes key value
            keytype key;

            /// The rank of this node
            int rank;

            /// A pointer to this nodes parent, will be NULL if the node is in the root list.
            struct node * p_parent;

            /// A pointer to this nodes left sibling
            struct node * p_left_sibling;

            /// A pointer to this nodes right sibling
            struct node * p_right_sibling;

            /// A pointer to this nodes child
            struct node * p_left_child;
        } Node;

        /// A pointer to the head of the root list
        Node * p_head_root_list = NULL;

        /// A pointer to the tail of the root list
        Node * p_tail_root_list = NULL;

        /// The number of nodes in the root list
        int length_root_list = 0;

        /// A pointer to the minimum value in the FibHeap
        Node * p_minimum_value  = NULL;

        /// A reference key value to use
        keytype ref_val;

        /// Determines whether this object is responsible for freeing the allocated memorys
        bool b_free = true;

    /**
     * Public interface for the FibHeap class.
     */
    public:

        /**
         * Default constructor for the FibHeap class.
         */
        FibHeap() { }

        /**
         * Constructor that builds a fibonacci heap using an array of keys.
         *
         * @note Should consolidate the fibonacci heap to only have a most one of
         *       each binomial tree.
         */
        FibHeap(keytype k[], int s)
        {
            // Insert all the keys into the heap
            for (int idx = 0; idx < s; idx++)
            {
                this->insert(k[idx]);
            }

            // Consolidate the inserted keys
            this->consolidate();
        }

        /**
         * Copy Constructor for the FibHeap class.
         *
         * @param[in] obj_being_copied A reference to the FibHeap object that is being copied over.
         */
        FibHeap(const FibHeap &obj_being_copied)
        {
            this->copy_fib_heap(obj_being_copied);
        }

        /**
         * Copy assignment operator for the Treap class.
         *
         * @param[in] obj_being_copied A reference to the FibHeap object that is being copied over.
         */
        FibHeap& operator=(const FibHeap &obj_being_copied)
        {
            // If the FibHeap is not empty, delete it before continuing
            if (NULL != p_head_root_list)
            {
                this->deallocate_fib_heap();
            }

            // Copy the FibHeap
            this->copy_fib_heap(obj_being_copied);

            // Retturn a reference to the new object
            return *this;
        }

        /**
         * Destructor for the FibHeap class.
         */
        ~FibHeap()
        {
            if (b_free)
            {
                this->deallocate_fib_heap();
            }
        }

        /**
         * Returns the minimum key in the heap without modifying it.
         *
         * @return The minimum key.
         */
        keytype peekKey()
        {
            if (p_minimum_value == NULL)
            {
                return ref_val;
            }

            return p_minimum_value->key;
        }

        /**
         * Removes the minimum key in the heap and returns the key.
         *
         * @return The minimum key.
         */
        keytype extractMin()
        {
            // Get the minimum key in the Heap to return
            keytype minimum_key = p_minimum_value->key;

            // Move min's children to the root list
            if (p_minimum_value->p_left_child != NULL)
            {
                p_minimum_value->p_left_sibling->p_right_sibling = p_minimum_value->p_left_child;
                p_minimum_value->p_left_child->p_left_sibling = p_minimum_value->p_left_sibling;

                Node * p_current_node = p_minimum_value->p_left_child;

                // Loop until the last child is reached, then link it with the root list
                while (1)
                {
                    p_current_node->p_parent = NULL;

                    if (p_current_node->p_right_sibling == NULL)
                    {
                        p_current_node->p_right_sibling = p_minimum_value->p_right_sibling;
                        p_minimum_value->p_right_sibling->p_left_sibling = p_current_node;
                        break;
                    }

                    p_current_node = p_current_node->p_right_sibling;
                    length_root_list++;
                }

                // Update the head/tail of the root list if necessary
                if (p_minimum_value == p_head_root_list)
                {
                    p_head_root_list = p_minimum_value->p_left_child;
                }
                else if (p_minimum_value == p_tail_root_list)
                {
                    p_tail_root_list = p_current_node;
                }
            }
            else
            {
                // Remove the minimum value node from the root list and relink it
                p_minimum_value->p_left_sibling->p_right_sibling = p_minimum_value->p_right_sibling;
                p_minimum_value->p_right_sibling->p_left_sibling = p_minimum_value->p_left_sibling;

                // Update the head/tail of the root list if necessary
                if (p_minimum_value == p_head_root_list)
                {
                    p_head_root_list = p_minimum_value->p_right_sibling;
                }
                else if (p_minimum_value == p_tail_root_list)
                {
                    p_tail_root_list = p_minimum_value->p_left_sibling;
                }

                // One node was removed from the root list
                length_root_list--;
            }

            // Delete the minimum node
            delete p_minimum_value;
            p_minimum_value = NULL;

                // Consolidate after the min's children have been moved to the root list
            this->consolidate();

            return minimum_key;
        }

        /**
         * Inserts the key k into the heap.
         *
         * @param[in]
         */
        void insert(keytype k)
        {
            // Initialize the new nodes values
            Node * p_new_node = new Node;

            // If the first node is being inserted, set the head and tail pointers
            if (p_head_root_list == NULL && p_tail_root_list == NULL)
            {
                p_head_root_list = p_new_node;
                p_tail_root_list = p_new_node;
            }

            p_new_node->key             = k;
            p_new_node->rank            = 0;
            p_new_node->p_parent        = NULL;
            p_new_node->p_left_sibling  = p_tail_root_list;
            p_new_node->p_right_sibling = p_head_root_list;
            p_new_node->p_left_child    = NULL;

            // The previous tails right sibling is now the new node
            p_tail_root_list->p_right_sibling = p_new_node;

            // The heads left sibling is now the new node
            p_head_root_list->p_left_sibling = p_new_node;

            // The inserted node is the new tail of the root list
            p_tail_root_list = p_new_node;

            // Increment the number of nodes in the root list
            length_root_list++;

            // Update the p_minimum_key if necessary
            if (p_minimum_value == NULL)
            {
                p_minimum_value = p_new_node;
            }
            else if (k < p_minimum_value->key)
            {
                p_minimum_value = p_new_node;
            }
        }

        /**
         * Merges the heap H2 into the current heap.
         *
         * @note Consumes H2.
         */
        void merge(FibHeap<keytype> &H2)
        {
            // Update the length of the root list
            length_root_list += H2.length_root_list;

            // Connect the tail of H1 with the head of H2
            p_tail_root_list->p_right_sibling = H2.p_head_root_list;
            H2.p_head_root_list->p_left_sibling = p_tail_root_list;

            // Connect the head of H1 with the tail of H2
            p_head_root_list->p_left_sibling = H2.p_tail_root_list;
            H2.p_tail_root_list->p_right_sibling = p_head_root_list;

            // Update the tail of the root list to be the tail of H2
            p_tail_root_list = H2.p_tail_root_list;

            // Update the pointer to the minimum value if necessary
            if (H2.p_minimum_value->key < p_minimum_value->key)
            {
                p_minimum_value = H2.p_minimum_value;
            }

            // H1 will now take care of freeing the allocated memory
            H2.b_free = false;
        }

        /**
         * Writes the keys stored in the heap, starting at the head of the list. When printing
         * a binomial tree, print the size of the tree first and then use a modified preorder
         * traversal of the tree.
         */
        void printKey()
        {
            Node * current_node = p_head_root_list;

            do
            {
                cout << "B" << current_node->rank << endl;

                cout << current_node->key << " ";

                if (NULL != current_node->p_left_child)
                {
                    this->preorder_implementation(current_node->p_left_child);
                }

                cout << endl;

                current_node = current_node->p_right_sibling;

            } while (current_node != p_head_root_list);
        }

    /**
     * Private helper functions for the FibHeap class.
     */
    private:

        /**
         * Function to help copy a FibHeap object. Will create a node's sibling, then recursively
         * create it's own children/siblings.
         *
         * @param[in] p_parent       A pointer to the newly created node's parent.
         * @param[in] p_left_sibling A pointer to the newly created node's left sibling.
         * @param[in] node_to_copy   A pointer to the node that is being copied.
         *
         * @return A pointer to the newly created sibling.
         */
        Node * copy_sibling(Node * p_parent, Node * p_left_sibling, Node * node_to_copy)
        {
            // Return NULL if there is no more nodes to copy
            if (node_to_copy == NULL)
            {
                return NULL;
            }

            // Create the new sibling node
            Node * new_node = new Node;
            new_node->key            = node_to_copy->key;
            new_node->rank           = node_to_copy->rank;
            new_node->p_parent       = p_parent;
            new_node->p_left_sibling = p_left_sibling;

            // Recursively create the newly created node's children/siblings
            new_node->p_left_child    = this->copy_child(new_node, node_to_copy->p_left_child);
            new_node->p_right_sibling = this->copy_sibling(p_parent, new_node, node_to_copy->p_right_sibling);

            return new_node;
        }

        /**
         * Function to help copy a FibHeap object. Will create a node's leftmost child, then recursively
         * create the newly created node's own children/siblings.
         *
         * @param[in] p_parent     A pointer to the newly create node's parent.
         * @param[in] node_to_copy A pointer to the node that is being copied.
         *
         * @return A pointer to the newly created child.
         */
        Node * copy_child(Node * p_parent, Node * node_to_copy)
        {
            // Return NULL is there are no more nodes to copy
            if (node_to_copy == NULL)
            {
                return NULL;
            }

            // Create the new child node
            Node * new_node          = new Node;
            new_node->key            = node_to_copy->key;
            new_node->rank           = node_to_copy->rank;
            new_node->p_parent       = p_parent;
            new_node->p_left_sibling = NULL;

            // Recursively create the newly created node's children/sibling
            new_node->p_left_child    = this->copy_child(new_node, node_to_copy->p_left_child);
            new_node->p_right_sibling = this->copy_sibling(p_parent, new_node, node_to_copy->p_right_sibling);

            return new_node;
        }

        /**
         * Function to copy a FibHeap object.
         *
         * @param[in] obj_being_copied A reference to the FibHeap object that is being copied.
         */
        void copy_fib_heap(const FibHeap &obj_being_copied)
        {
            Node * node_to_copy = obj_being_copied.p_head_root_list;
            length_root_list = obj_being_copied.length_root_list;

            // Variable that will store the revious root list node in order to
            Node * previous_node = NULL;

            // Loop through each node in the root list
            for (int idx = 0; idx < obj_being_copied.length_root_list; idx++)
            {
                // Initialize the root nodes values
                Node * new_root_node    = new Node;
                new_root_node->key      = node_to_copy->key;
                new_root_node->rank     = node_to_copy->rank;
                new_root_node->p_parent = NULL;

                if (previous_node != NULL)
                {
                    // Link the two root list nodes
                    previous_node->p_right_sibling = new_root_node;
                    new_root_node->p_left_sibling  = previous_node;
                }
                else
                {
                    // The current node is the head and will be linked later
                    // once the tail has been created
                    new_root_node->p_left_sibling = NULL;
                }

                new_root_node->p_left_child = this->copy_child(new_root_node, node_to_copy->p_left_child);

                // Set the head of the root list
                if (node_to_copy == obj_being_copied.p_head_root_list)
                {
                    p_head_root_list = new_root_node;
                }

                // Set the tail of the root list
                if (node_to_copy == obj_being_copied.p_tail_root_list)
                {
                    p_tail_root_list = new_root_node;
                }

                // Set the minimum value of the root list
                if (node_to_copy == obj_being_copied.p_minimum_value)
                {
                    p_minimum_value = new_root_node;
                }

                // Store the new node as the previous node
                previous_node = new_root_node;

                // Update the node to copy to the next node in the root list
                node_to_copy = node_to_copy->p_right_sibling;
            }

            // Link the head and tail of the root list
            p_head_root_list->p_left_sibling  = p_tail_root_list;
            p_tail_root_list->p_right_sibling = p_head_root_list;
        }

        /**
         * Helper function for the destructor of the FibHeap class.
         */
        void deallocate(Node * current_node)
        {
            if ((NULL != current_node) && (current_node->p_parent != NULL))
            {
                this->deallocate(current_node->p_left_child);
                this->deallocate(current_node->p_right_sibling);

                delete current_node;
            }
        }

        /**
         * Function to delete a FibHeap object.
         */
        void deallocate_fib_heap()
        {
            // Start at the head of the root list
            Node * current_node = p_head_root_list;

            // Delete each root node's binomial tree
            do
            {
                if (NULL != current_node->p_left_child)
                {
                    // Frees the memory allocated by the root list nodes children
                    this->deallocate(current_node->p_left_child);
                }

                // Store a pointer to the current node
                Node * p_temp_node = current_node;

                // Update the current root list node
                current_node = current_node->p_right_sibling;

                // Free the memory allocated by the previous current node
                delete p_temp_node;

            } while (current_node != p_head_root_list);
        }

        /**
         * Removes y from the root and makes it the leftmost child of x
         *
         * @param[in] y
         * @param[in] x
         */
        void link_binomials(Node * y, Node * x)
        {
            // Remove y from the root list and relink it
            y->p_left_sibling->p_right_sibling = y->p_right_sibling;
            y->p_right_sibling->p_left_sibling = y->p_left_sibling;

            // Get x's current leftmost child
            Node * previous_child = x->p_left_child;

            // Make x y's parent
            y->p_parent = x;

            // If x had previous children, add y to the front of the list, else set
            // y's sibling pointers to NULL.
            if (previous_child != NULL)
            {
                x->p_left_child    = y;
                y->p_left_sibling  = previous_child->p_left_sibling;
                y->p_right_sibling = previous_child;

                // Update the previous left child's pointers
                previous_child->p_left_sibling = y;
            }
            else
            {
                x->p_left_child    = y;
                y->p_left_sibling  = NULL;
                y->p_right_sibling = NULL;
            }

            // Increment the rank of x
            x->rank++;
        }

        /**
         * Function that consolidates the root list by combining binomial tress of the same rank.
         */
        void consolidate()
        {
            // Initialize the array to contain NULL pointers
            Node * binomial_arr[50] = { 0 };

            // Start at the head of the root list
            Node * x = p_head_root_list;

            // Loop through each node in the root list
            for (int i = 0; i < length_root_list; i++)
            {
                // Save the next node to check in case the current node is removed from
                // the root list
                Node * next_node = x->p_right_sibling;

                // Get the rank of the current node
                int rank = x->rank;

                Node * y = NULL;

                // While there are duplicate binomial trees
                while (binomial_arr[rank] != NULL)
                {
                    // Get a pointer to the already stored tree
                    y = binomial_arr[rank];

                    // If y's key is greater than x's, remove y from the root list.
                    // Otherwise, remove x from the root list
                    if (y->key > x->key)
                    {
                        // Make y x's leftmost child
                        this->link_binomials(y, x);
                    }
                    else
                    {
                        // Make x y's leftmost child
                        this->link_binomials(x, y);

                        // Update the current node to be the root of the binomial tree
                        x = y;
                    }

                    // Update the array and increment the rank
                    binomial_arr[rank] = NULL;
                    rank = rank + 1;
                }

                if (y != NULL)
                {
                    if (y->key > x->key)
                    {
                        binomial_arr[rank] = x;
                    }
                    else
                    {
                        binomial_arr[rank] = y;
                    }
                }
                else
                {
                    binomial_arr[rank] = x;
                }

                x = next_node;
            }

            // Reset the minimum value and the length of the root list
            p_minimum_value = NULL;
            int temp_length_root_list = 0;

            /**
             * Loop that rebuilds the root list using the binomial tree array.
             */
            for (int idx = 0; idx < 50; idx++)
            {
                // If the index of binomial_arr is not NULL then it needs to be added to the root list
                if (binomial_arr[idx] != NULL)
                {
                    // If the root list if currently empty initialize the pointer values, else
                    // insert the binomial tree at the end of the root list.
                    if (p_minimum_value == NULL)
                    {
                        p_head_root_list = binomial_arr[idx];
                        p_tail_root_list = binomial_arr[idx];
                        p_minimum_value  = binomial_arr[idx];
                    }
                    else
                    {
                        // Insert binomial_arr[idx] into root list
                        binomial_arr[idx]->p_left_sibling  = p_tail_root_list;
                        binomial_arr[idx]->p_right_sibling = p_head_root_list;

                        // The current tails right sibling will be the new binomial tree
                        p_tail_root_list->p_right_sibling = binomial_arr[idx];

                        // The inserted binomial tree is the new tail
                        p_tail_root_list = binomial_arr[idx];

                        // Update p_minimum_value if necessary
                        if (binomial_arr[idx]->key < p_minimum_value->key)
                        {
                            p_minimum_value = binomial_arr[idx];
                        }
                    }

                    // A new binomial tree was added to the root list
                    temp_length_root_list++;
                }
            }

            length_root_list = temp_length_root_list;
        }

        /**
         * Function to recursivley traverse a binomial tree in the FibHeap.
         *
         * @param[in] current_node The current node in the preorder traversal.
         */
        void preorder_implementation(Node * current_node)
        {
            if ((NULL != current_node) && (current_node->p_parent != NULL))
            {
                cout << current_node->key << " ";
                this->preorder_implementation(current_node->p_left_child);
                this->preorder_implementation(current_node->p_right_sibling);
            }
        }
};
