/**
 * @file Treap.cpp
 *
 * This file implements a treap for project 2 of the CS 201 Data Stuctures and
 * Algorithms class.
 *
 * Written by: Andrew Hankins
 */

#include <iostream>
#include <ctime>

using namespace std;

template <typename keytype>

/**
 * @class Treap
 *
 * Class that implements a min ordered Treap data structure.
 */
class Treap
{
    private:

        /**
         * @struct Node
         *
         * @note The order of the data variables must stay the same.
         */
        typedef struct node
        {
            struct node * parent;         ///< Pointer to the nodes parent.
            struct node * left_child;     ///< Pointer to the nodes left child.
            struct node * right_child;    ///< Pointer to the nodes right child.

            keytype k;                    ///< Data to be used as the key for the binary search tree.

            float priority;               ///< The priority of the node in the range [0 ... 1].

            int left_subtree_elms;        ///< The number of elements in the nodes left subtree.
        } Node;

        Node * root = NULL; ///< The root of the Treap data structure

        int num_nodes = 0;  ///< The number of nodes in the entire tree.

        keytype ref_val;    ///< Key that will be returned when select param is invalid.

    public:

        /**
         * The default constructor, creates an empty tree.
         */
        Treap(void)
        {
            // Seed the rand() function in order to generate random priorities.
            srand((unsigned)time(0));
        }

        /**
         * Constructor that builds a Treap using value stored in an array.
         *
         * @param[in] k An array of keys to be inserted into the Treap.
         * @param[in] p An array of priorities associated with the keys.
         * @param[in] s The size of the two arrays.
         */
        Treap(keytype k[], float p[], int s)
        {
            // Seed the rand() function in order to generate random priorities.
            srand((unsigned)time(0));

            for (int i = 0; i < s; i++)
            {
                this->insert(k[i], p[i]);
            }
        }

        /**
         * Function to copy the binary tree.
         *
         * @note Inserting the different nodes and priotities will automatically update the num_nodes
         * and left_subtree_elms.
         */
        void copy_helper(Node * obj_being_copied_node)
        {
            if (NULL != obj_being_copied_node)
            {
                // Insert node
                this->insert(obj_being_copied_node->k, obj_being_copied_node->priority);

                // Go left until you hit NULL
                this->copy_helper(obj_being_copied_node->left_child);

                // Go right until you hit NULL
                this->copy_helper(obj_being_copied_node->right_child);
            }
        }

        /**
         * Copy constuctor for the Treap class.
         *
         * @param[in] obj_being_copied A reference to a Treap object the is being copied over.
         */
        Treap(const Treap &obj_being_copied)
        {
            // Copying tree and updating variables
            this->copy_helper(obj_being_copied.root);
        }

        /**
         * Copy assignment operator for the Treap class.
         *
         * @param[in] obj_being_copied A reference to a Treap object the is being copied over.
         */
        Treap& operator=(const Treap &obj_being_copied)
        {
            // If the left hand Treap already had a tree, delete it before continuing
            if (NULL != root)
            {
                this->deallocate(root);
            }

            this->root = NULL;

            // Copying tree and updating variables
            this->copy_helper(obj_being_copied.root);

            // Return a reference to the new object.
            return *this;
        }


        /**
         * Recurively frees the allocated Treap using post-order traversal.
         *
         * @param[in] current_node A pointer to the node that function is currently on.
         *
         * @return When a NULL node is reached.
         */
        void deallocate(Node * current_node)
        {
            if (NULL == current_node)
            {
                return;
            }

            // Go left
            deallocate(current_node->left_child);

            // Go right
            deallocate(current_node->right_child);

            delete current_node;
            current_node = NULL;
        }

        /**
         * Destructor for the Treap class.
         *
         * @note Needs to iterate through the tree to free allocated memory.
         */
        ~Treap()
        {
            deallocate(root);
        }

        /**
         * A traditional search function.
         *
         * @param[in] k The key to search for.
         *
         * @return The priority of the found key, or -1 if the key is not in the Treap.
         */
        float search(keytype k)
        {
            Node * current_node = root;

            while (NULL != current_node)
            {
                if (k == current_node->k)
                {
                    // Returning the keys priority
                    return current_node->priority;
                }
                else if (k < current_node->k) // Go left
                {
                    current_node = current_node->left_child;
                }
                else // Go right
                {
                    current_node = current_node->right_child;
                }
            }

            // Key was not found in the Treap
            return -1;
        }

        /**
         * Performs a standard binary search tree insert.
         *
         * @note If the keys are equal, the new node will be placed to the right in binary search tree order.
         *
         * @param[in] new_node
         */
        void bst_insert(Node * new_node)
        {
            Node * current_node = root;
            Node * parent_node  = NULL;

            if (NULL == root)
            {
                root = new_node;
                return;
            }

            while (1)
            {
                parent_node = current_node;

                if (new_node->k < parent_node->k) // Go to the left
                {
                    // New node will be inserted ot the left of this node
                    parent_node->left_subtree_elms++;

                    current_node = current_node->left_child;

                    // Insert node at the left_child of the parent
                    if (NULL == current_node)
                    {
                        parent_node->left_child = new_node;
                        new_node->parent = parent_node;
                        return;
                    }
                }
                else // Go to the right
                {
                    current_node = current_node->right_child;

                    // Insert node at the right_child of the parent
                    if (current_node == NULL)
                    {
                        parent_node->right_child = new_node;
                        new_node->parent = parent_node;
                        return;
                    }
                }
            }
        }

        /**
         * Performs a right rotation on the given node.
         *
         * @param[in] current_node The node that needs to be rotated.
         *
         * @return The new root.
         */
        Node * right_rotate(Node * y)
        {
            Node * x  = y->left_child;
            Node * x_right_subtree = NULL;
            int x_right_subtree_elms = 0;

            if (y == root)
            {
                root = x;
            }

            if (x->right_child != NULL)
            {
                x_right_subtree = x->right_child;
                x_right_subtree->parent = y;
                x_right_subtree_elms = y->left_subtree_elms - x->left_subtree_elms - 1;
            }

            x->right_child = y;
            y->left_child  = x_right_subtree;

            x->parent  = y->parent;
            y->parent  = x;

            y->left_subtree_elms = x_right_subtree_elms;

            return x;
        }

        /**
         * Performs a left rotation on the given node.
         *
         * @param[in] current_node The node that needs to be rotated.
         *
         * @return The new root.
         */
        Node * left_rotate(Node * x)
        {
            Node * y  = x->right_child;
            Node * y_left_subtree = NULL;

            // Update the root of the tree if necessary
            if (x == root)
            {
                root = y;
            }

            if (y->left_child != NULL)
            {
                y_left_subtree = y->left_child;
                y_left_subtree->parent = x;
            }

            y->left_child  = x;
            y->parent = x->parent;

            x->right_child = y_left_subtree;
            x->parent = y;

            y->left_subtree_elms = y->left_subtree_elms + x->left_subtree_elms + 1;

            return y;
        }

        /**
         * Performs the rotation necessary for a treap insert.
         *
         * @param[in] k            The key of the node that was inserted.
         * @param[in] current_node The current node that the recursive function is on.
         *
         * @return The new root of the tree.
         */
        Node * treap_insert(keytype k, Node * current_node)
        {
            if (NULL == current_node)
            {
                return NULL;
            }

            if (k < current_node->k)
            {
                current_node->left_child = treap_insert(k, current_node->left_child);

                if ((current_node->left_child != NULL) &&
                    (current_node->left_child->priority <= current_node->priority))
                {
                    current_node = this->right_rotate(current_node);
                }
            }
            else
            {
                current_node->right_child = treap_insert(k, current_node->right_child);

                if ((current_node->right_child != NULL) &&
                    (current_node->right_child->priority < current_node->priority))
                {
                    current_node = this->left_rotate(current_node);
                }
            }

            return current_node;
        }

        /**
         * Funtion to insert a new node into the Treap.
         *
         * @param[in] k The value to be used as the key.
         * @param[in] p The value to be used for priority.
         */
        void insert(keytype k, float p)
        {
            num_nodes++;

            if (p == __FLT_MAX__)
            {
                p = p - 0.001;
            }

            Node * new_node = new Node{ NULL, NULL, NULL, k, p, 0 };

            this->bst_insert(new_node);

            if (num_nodes > 1)
            {
                // cout << "Fixing tree order\n";
                root = this->treap_insert(k, root);
            }
        }

        /**
         * Function to generate a random priority and then insert a new node into the Treap.
         *
         * @note The generated priority will be a float value in the range [0, 1].
         *
         * @param[in] k The value to be used as the key.
         */
        void insert(keytype k)
        {
            // Generating the random priority
            float p = (float)rand() / (float)RAND_MAX;

            this->insert(k, p);
        }

        /**
         * Perform a delete with the assumption that the node is a leaf.
         *
         * @param[in] k
         */
        void bst_delete(keytype k)
        {
            Node * current_node = root;

            while (NULL != current_node)
            {
                if (k == current_node->k)
                {
                    if (current_node->priority == __FLT_MAX__)
                    {
                        if (k < current_node->parent->k)
                        {
                            current_node->parent->left_child = NULL;
                        }
                        else
                        {
                            current_node->parent->right_child = NULL;
                        }
                        delete current_node;
                        break;
                    }
                    else
                    {
                        current_node->left_subtree_elms--;
                        current_node = current_node->left_child;
                    }
                }
                else if (k < current_node->k)
                {
                    current_node->left_subtree_elms--;
                    current_node = current_node->left_child;
                }
                else
                {
                    current_node = current_node->right_child;
                }
            }
        }

        /**
         * Performs the rotation necessary for a treap deletion.
         *
         * @param[in] k
         * @param[in] current_node
         */
        void treap_delete(keytype k, Node * current_node)
        {
            if (NULL == current_node)
            {
                return;
            }

            while (1)
            {
                if ((current_node->left_child == NULL) && (current_node->right_child == NULL))
                {
                    break;
                }
                else if ((current_node->left_child == NULL) && (current_node->right_child != NULL))
                {
                    if (current_node->right_child->priority < current_node->priority)
                    {
                        current_node = this->left_rotate(current_node);

                        if (current_node != root)
                        {
                            if (current_node->k < current_node->parent->k)
                            {
                                current_node->parent->left_child = current_node;
                            }
                            else
                            {
                                current_node->parent->right_child = current_node;
                            }
                        }

                            current_node = current_node->left_child;
                    }
                    else
                    {
                        current_node = current_node->right_child;
                    }
                }
                else if ((current_node->left_child != NULL) && (current_node->right_child == NULL))
                {
                    if (current_node->left_child->priority < current_node->priority)
                    {
                        current_node = this->right_rotate(current_node);

                        if (current_node != root)
                        {
                            if (current_node->k < current_node->parent->k)
                            {
                                current_node->parent->left_child = current_node;
                            }
                            else
                            {
                                current_node->parent->right_child = current_node;
                            }
                        }

                        current_node = current_node->right_child;
                    }
                    else
                    {
                        current_node = current_node->left_child;
                    }
                }
                else
                {
                    if ((current_node->left_child->priority  < current_node->priority) ||
                        (current_node->right_child->priority < current_node->priority))
                    {
                        if (current_node->left_child->priority <= current_node->right_child->priority)
                        {
                            current_node = this->right_rotate(current_node);

                            if (current_node != root)
                            {
                                if (current_node->k < current_node->parent->k)
                                {
                                    current_node->parent->left_child = current_node;
                                }
                                else
                                {
                                    current_node->parent->right_child = current_node;
                                }
                            }

                            current_node = current_node->right_child;
                        }
                        else if (current_node->right_child->priority < current_node->left_child->priority)
                        {
                            current_node = this->left_rotate(current_node);

                            if (current_node != root)
                            {
                                if (current_node->k < current_node->parent->k)
                                {
                                    current_node->parent->left_child = current_node;
                                }
                                else
                                {
                                    current_node->parent->right_child = current_node;
                                }
                            }

                            current_node = current_node->left_child;
                        }
                    }
                    else
                    {
                        if (k < current_node->k)
                        {
                            current_node = current_node->left_child;
                        }
                        else
                        {
                            current_node = current_node->right_child;
                        }
                    }
                }
            }
        }

        /**
         * Removes the node with key k from the treap.
         *
         * @param[in] k
         *
         * @retval 1 The node was successfully removed.
         * @retval 0 The key was not found in the tree.
         */
        int remove(keytype k)
        {
            Node * current_node = root;

            // Finding the node to be removed and making it's priority "infinity"
            while (1)
            {
                if (NULL == current_node)
                {
                    // Reached the end of the treap without finding the key
                    return 0;
                }
                else if (k == current_node->k)
                {
                    // Setting the nodes priotiy to "infinity"
                    current_node->priority = __FLT_MAX__;
                    break;
                }
                else if (k < current_node->k) // Go left
                {
                    current_node = current_node->left_child;
                }
                else // Go right
                {
                    current_node = current_node->right_child;
                }
            }

            // Rotates the node down to a leaf
            this->treap_delete(k, root);

            // Deletes the node while updating the left_subtree_elms varaibles.
            this->bst_delete(k);

            // Decrement the number of nodes in the treap
            num_nodes--;

            // Delete was successfull
            return 1;
        }

        /**
         * Function to return the rank of the key k in the treap.
         *
         * @param[in] k The key to find the rank of.
         *
         * @return The rank of the key if found, or 0 if the key is not in the treap.
         */
        int rank(keytype k)
        {
            Node * current_node = root;
            int rank = 0;

            while (1)
            {
                if (NULL == current_node)
                {
                    // Key was not found in the tree return 0.
                    return 0;
                }
                else if (current_node->k == k)
                {
                    return rank = rank + current_node->left_subtree_elms + 1;
                }
                else if (k < current_node->k)
                {
                    current_node = current_node->left_child;
                }
                else
                {
                    rank = rank + current_node->left_subtree_elms + 1;
                    current_node = current_node->right_child;
                }
            }
        }

        /**
         * Function that returns the key of the node at position pos in the tree. Calling with pos = 1
         * should return the smallest key in the tree, pos = n should return the largest.
         *
         * @param[in] pos The position of the key in the tree that is being looked for.
         *
         * @return Key at position pos in the tree.
         */
        keytype select(int pos)
        {
            // Position not valid so returning a random reference value
            if ((pos < 1) || (pos > num_nodes))
            {
                return ref_val;
            }

            Node * current_node = root;
            int current_pos = root->left_subtree_elms + 1;

            while (1)
            {
                if (current_pos == pos)
                {
                    return current_node->k;
                }
                else if (current_pos > pos) // Go left
                {
                    current_node = current_node->left_child;
                    current_pos = current_node->left_subtree_elms + 1;
                }
                else // Go right
                {
                    pos = pos - current_node->left_subtree_elms - 1;
                    current_node = current_node->right_child;
                    current_pos = current_node->left_subtree_elms + 1;
                }
            }
        }

        /**
         * Function to find the succesor to a value in the tree.
         *
         * @param[in] k The key to find the succesor for.
         *
         * @retval The key after k in the tree.
         */
        keytype successor(keytype k)
        {
            int rank_of_key = this->rank(k);

            if (rank_of_key == num_nodes)
            {
                return k;
            }

            return this->select(++rank_of_key);
        }

        /**
         * Function to find the predecessor to a value in the tree.
         *
         * @param[in] k The key to find the succesor for.
         *
         * @retval The key before k in the tree, or k if no predescessor exists.
         */
        keytype predecessor(keytype k)
        {
            // Finding the rank of the specified key.
            int rank_of_key = this->rank(k);

            // There is no predescessor so return k
            if (rank_of_key == 1)
            {
                return k;
            }

            // Predecessor should be (rank_of_key - 1)
            return this->select(--rank_of_key);
        }

        /**
         * Function to get the number of nodes in the tree.
         *
         * @retval The number of nodes in the treap.
         */
        int size()
        {
            return num_nodes;
        }

        /**
         * Recursive implementation of preorder traversal.
         *
         * @param[in] current_node The node that will have its key printed.
         */
        void preorder_implementation(Node * current_node)
        {
            if (NULL != current_node)
            {
                cout << current_node->k << " ";
                preorder_implementation(current_node->left_child);
                preorder_implementation(current_node->right_child);
            }
        }

        /**
         * Prints the keys in a preorder traversal.
         */
        void preorder(void)
        {
            this->preorder_implementation(root);
            cout << endl;
        }

        /**
         * Recursive implementation of inorder traversal.
         *
         * @param[in] current_node The node that will have its key printed.
         */
        void inorder_implementation(Node * current_node)
        {
            if (NULL != current_node)
            {
                inorder_implementation(current_node->left_child);
                cout << current_node->k << " ";
                inorder_implementation(current_node->right_child);
            }
        }

        /**
         * Prints the keys of the tree in an inorder traversal.
         */
        void inorder()
        {
            this->inorder_implementation(root);
            cout << endl;
        }

        /**
         * Recursive implementation of postorder traversal.
         *
         * @param[in] current_node The node that will have its key printed.
         */
        void postorder_implementation(Node * current_node)
        {
            if (NULL != current_node)
            {
                postorder_implementation(current_node->left_child);
                postorder_implementation(current_node->right_child);
                cout << current_node->k << " ";
            }
        }

        /**
         * Prints the keys of the tree in a postorder traversal.
         */
        void postorder()
        {
            this->postorder_implementation(root);
            cout << endl;
        }
};
