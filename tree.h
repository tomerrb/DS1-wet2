#include <stdlib.h>
#ifndef TREE_H
#define TREE_H


template<typename K, typename V>
class Tree {
public:
	
	typedef int Compare(K key1, K key2);

	Compare* compare;

	struct Node {
		K key;
		V value;
		Node* smallest;
		Node* biggest;
		Node* left;
		Node* right;
		Node* parent;
		int height;
		int left_num;
		int right_num;

		Node(const K& key, const V& value)
			: key(key)
			, value(value)
			, smallest(nullptr)
			, biggest(nullptr)
			, left(nullptr)
			, right(nullptr)
			, parent(nullptr)
			, height(1)
			, left_num(0)
			, right_num(0)
		{
		}

		Node(const K& key, const V& value, Node* smallest, Node* biggest, Node* left, Node* right, Node* parent, int height, int left_num, int right_num)
			: key(key)
			, value(value)
			, smallest(smallest)
			, biggest(biggest)
			, left(left)
			, right(right)
			, parent(parent)
			, height(height)
			, left_num(left_num)
			, right_num(right_num)
		{
		}


		int balance() {
			return (left != nullptr ? left->height : 0) - (right != nullptr ? right->height : 0);
		}

		void set_height() {
			int left_h = left != nullptr ? left->height : 0;
			int right_h = right != nullptr ? right->height : 0;
			
			height = (left_h > right_h ? left_h : right_h) + 1;
		}

	} *root;
private:
	static int height(Node* node)
	{
		return node != nullptr ? node->height : 0;
	}

	Node* rot_left(Node* node)
	{
		Node* rotation = node->right;
		Node* rotation1 = rotation->left;

		int copy1 = node->left_num;
		int copy2 = rotation->left_num;

		rotation->left = node;
		node->right = rotation1;

		node->right_num = copy2;
		rotation->left_num = copy1 + copy2 + 1;

		if (rotation1) {
			rotation1->parent = node;
		}
		rotation->parent = node->parent;
		node->parent = rotation;
		


		node->set_height();
		rotation->set_height();
		return rotation;
	}

	Node* rot_right(Node* node)
	{
		Node* rotation = node->left;
		Node* rotation1 = rotation->right;

		int copy1 = node->right_num;
		int copy2 = rotation->right_num;
		
		rotation->right = node;
		node->left = rotation1;

		node->left_num = copy2;
		rotation->right_num = copy1 + copy2 + 1;

		if (rotation1) {
			rotation1->parent = node;
		}
		rotation->parent = node->parent;
		node->parent = rotation;

		node->set_height();
		rotation->set_height();

		return rotation;
	}

	Node* get_right_new(Node* node) {
		return node->right;
	}

	Node* get_left_new(Node* node) {
		return node->left;
	}

	Node* get_parent_new(Node* node) {
		return node->parent;
	}

	V& get_value_new(Node* node, const K& key) const{

		if (compare(node->key, key) == 0)
			return node->value;

		return compare(node->key, key) > 0 ? get_value_new(node->left, key) : get_value_new(node->right, key);
	}

	void insert_fix(Node* node, Node* son, Node* grandson)
	{
		if (node == nullptr) {
			return;
		}
		node->set_height();
		int balance = node->balance();
		Node* pre_parent = node->parent;
		
		Node* new_node = node;
		if (balance == -2) {

			if (node->right->balance() < 0) {
				new_node = rot_left(node);
			}
			else {
				node->right = rot_right(node->right);
				new_node = rot_left(node);

			}
			if (pre_parent != nullptr && pre_parent->right == node) {
				pre_parent->right = new_node;
			}
			if (pre_parent != nullptr && pre_parent->left == node) {
				pre_parent->left = new_node;
			}
			if (new_node != root && node == root)
				root = new_node;
		}
		if (balance == 2) {
			if (node->left->balance() >= 0) {
				new_node = rot_right(node);
			}
			else {
				node->left = rot_left(node->left);
				new_node = rot_right(node);
			}

			if (pre_parent != nullptr && pre_parent->right == node) {
				pre_parent->right = new_node;
			}
			if (pre_parent != nullptr && pre_parent->left == node) {
				pre_parent->left = new_node;
			}
			if (new_node != root && node == root)
				root = new_node;
		}
		

		insert_fix(node->parent, node, son);
	}

	Node* insert_new(Node* parent, Node* node, const K& key, const V& value)
	{
		if (node == nullptr) {
			Node* new_node = new Node(key, value);
			new_node->parent = parent;
			if (compare(parent->key, key) <= 0) {
				parent->right = new_node;
			}
			else {
				parent->left = new_node;
			}
			insert_fix(parent, new_node, nullptr);
			Node* copy = root;
			while (copy->left) {
				copy = copy->left;
			}
			root->smallest = copy;
			copy = root;
			while (copy->right) {
				copy = copy->right;
			}
			root->biggest = copy;
			return new_node;
		}

		if (compare(node->key, key) <= 0) {
			node->right_num++;
			return insert_new(node, node->right, key, value);
		}
		else {
			node->left_num++;
			return insert_new(node, node->left, key, value);
		}
	}

	




	bool contains_r(Node* node, const K& key) const
	{
		if (node == nullptr)
			return false;

		if (compare(node->key, key) == 0)
			return true;

		return compare(node->key, key) > 0 ? contains_r(node->left, key) : contains_r(node->right, key);
	}

	Node* first_element(Node* node) {
		if (node->left == nullptr)
			return node;
		return first_element(node->left);
	}

	K& get_ith_value_new(Node* node, int i)
	{
		if (node->left_num > i)
			return get_ith_value_new(node->left, i);
		if (i == node->left_num)
			return node->key;
		return get_ith_value_new(node->right, i - 1 - node->left_num);
	}

	Node* get_new(Node* node, const K& key) const
	{
		if (compare(node->key, key) == 0) {
			return node;
		}

		return compare(node->key, key) > 0 ? get_new(node->left, key) : get_new(node->right, key);
	}

	bool smallest_new(const Node* node, const K& key) const
	{
		if (node == nullptr)
			return true;

		if (compare(node->key, key) <= 0)
			return false;

		return smallest_new(node->left, key);
	}

	K& nearest_new(Node* node, Node* nearest, int min_diff, const K& key) const
	{
		if (node == nullptr)
			return nearest->key;

		int diff = compare(node->key, key);


		if (diff == 0 || diff == -1)
			return node->key;


		if (diff < 0 && diff > min_diff || min_diff == 1) {
			nearest = node;
			min_diff = diff;
		}

		return diff > 0 ? nearest_new(node->left, nearest, min_diff, key) : nearest_new(node->right, nearest, min_diff, key);
	}

	void remove_node(Node* parent, Node* node, const K& key) {
		if (node == nullptr)
			return;

		if (node->left == nullptr && node->right == nullptr) {
			if (parent->key == node->key) {
				if (parent->right == node)
					parent->right = nullptr;
				else
					parent->left = nullptr;
				delete node;
				node = nullptr;
			}


			else {
				if (parent->right == node) {
					parent->right = nullptr;
					delete node;
					node = nullptr;
				}
				else {
					parent->left = nullptr;
					delete node;
					node = nullptr;
				}
			}
			insert_fix(parent, node, nullptr);
			Node* copy = root;
			while (copy->left) {
				copy = copy->left;
			}
			root->smallest = copy;
			copy = root;
			while (copy->right) {
				copy = copy->right;
			}
			root->biggest = copy;
		}
		else if (node->left != nullptr && node->right == nullptr) {
			K& copy_key = node->key;
			V& copy_value = node->value;
			node->key = node->left->key;
			node->value = node->left->value;
			node->left->key = copy_key;
			node->left->value = copy_value;
			node->left_num = node->left_num - 1;
			remove_node(node, node->left, key);
		}
		else if (node->left == nullptr && node->right != nullptr) {
			K& copy_key = node->key;
			V& copy_value = node->value;
			node->key = node->right->key;
			node->value = node->right->value;
			node->right->key = copy_key;
			node->right->value = copy_value;
			node->right_num = node->right_num - 1;
			remove_node(node, node->right, key);
		}
		else {
			Node* copy = node->right;
			node->right_num = node->right_num - 1;
			int check = 0;
			while (copy->left) {
				copy->left_num = copy->left_num - 1;
				check = 1;
				parent = copy;
				copy = copy->left;
			}
			if (!check) {
				parent = node;
			}
			K& copy_key = node->key;
			V& copy_value = node->value;
			node->key = copy->key;
			node->value = copy->value;
			copy->key = copy_key;
			copy->value = copy_value;
			remove_node(parent, copy, copy->key);
		}

	}

	void destroy_new(const Node* node)
	{
		if (node == nullptr) {
			return;
		}

		Node* left = node->left;
		Node* right = node->right;
		delete node;
		destroy_new(left);
		destroy_new(right);
	}


	


public:
	
Tree(Compare* cmp)
		: compare(cmp)
		, root(nullptr)
	{
	}
Tree():
	compare(nullptr),
	root(nullptr)
{
}

	
	~Tree()
	{
		destroy_new(root);
	}

	void insert_cmp(Compare* cmp)
	{
		compare = cmp;
	}

	Node* insert(const K& key, const V& value)
	{
		if (root == nullptr) {
			root = new Node(key, value);
			root->smallest= root;
			root->biggest= root;
			return root;
		}

		return insert_new(nullptr, root, key, value);
	}

	


	bool remove(const K& key)
	{
		Node* node = root;
		Node* parent = node;
		bool isHere = false;

		if (node == nullptr) {
			remove_node(nullptr, nullptr, key);
		}

		while (node) {
			if (root->right == nullptr && root->left == nullptr)
			{
				root = nullptr;
				break;
			}
			if (node->key == key) {
				isHere = true;
				remove_node(parent, node, key);
				break;
			}
			else if (compare(node->key,key) > 0) {
				node->left_num = node->left_num - 1;
				parent = node;
				node = node->left;
			}
			else {
				node->right_num = node->right_num - 1;
				parent = node;
				node = node->right;
			}
		}
		return isHere;
	}


	bool contains(const K& key) const
	{
		return contains_r(root, key);
	}




	Node* get(const K& key) 
	{
		return get_new(root, key);
	}

	Node* get_root() {
		return root;
	}

	Node* get_right() 
	{
		return get_right_new(root);
	}
	Node* get_left() 
	{
		return get_left_new(root);
	}
	Node* get_parent() 
	{
		return get_parent_new(root);
	}
	V& get_value(const K& key) const
	{
		return get_value_new(root, key);
	}

	bool get_ith_value(int i, K* res) {
		if (root == nullptr)
			return false;
		if (i > root->left_num + root->right_num)
			return false;
		res[0] = get_ith_value_new(root, i);
		return true;
	}

	bool smallest(const K& key) const
	{
		return smallest_new(root, key);
	}



	K& nearest(const K& key) const
	{
		return nearest_new(root, root, 1, key);
	}

	

	void set_parent(Node* parent, Node* child) {
		child->parent = parent;
		if (child->left != nullptr) {
			set_parent(child, child->left);
		}
		if (child->right != nullptr) {
			set_parent(child, child->right);
		}
	}

	static Node* copyNodes(Node* t)
	{
		if (t != nullptr)
		{
			Node* left = copyNodes(t->left);
			Node* right = copyNodes(t->right);
			return new Node(t->key, t->value, nullptr, nullptr, left, right, nullptr, t->height, t->left_num, t->right_num);
		}
		else
		{
			return nullptr;
		}
	}

	Tree(const Tree& rhs)
	{
		root = copyNodes(rhs.root);
		compare = rhs.compare;
		if (root != nullptr)
			set_parent(nullptr, root);
	}

	void operator=(const Tree& rhs) {
		root = copyNodes(rhs.root);
		compare = rhs.compare;
		if (root != nullptr)
			set_parent(nullptr, root);
	}
};


template<typename K, typename V>
void treeToArr (const Tree<K,V>& tree, int* counter, typename Tree<K,V>::Node** arr, typename Tree<K,V>::Node* current)
{
	if (!current)
	{
		return;
	}
	if (current->left!=nullptr)
	{
		treeToArr(tree, counter, arr, current->left);
	}
	arr[*counter]= current;
	(*counter)++;
	if (current->right!=nullptr)
	{
		treeToArr(tree, counter, arr, current->right);
	}
	return;
}

template<typename K, typename V>
void mergeArrs (const Tree<K,V>& tree, typename Tree<K,V>::Node** merged, typename Tree<K,V>::Node** arr1, typename Tree<K,V>::Node** arr2, int size1, int size2)
{
	int counter1=0;
	int counter2=0;
	int counter=0;
	for (int i=0; i<(size1 + size2); i++)
	{
		if (counter1==size1 || counter2==size2)
		{
			counter=i;
			break;
		}
		if (tree.compare(arr1[counter1]->key, arr2[counter2]->key) < 0)
		{
			merged[i]=arr1[counter1];
			counter1++;
			counter=i;
			continue;
		}
		if (tree.compare(arr1[counter1]->key, arr2[counter2]->key) > 0)
		{
			merged[i]=arr2[counter2];
			counter2++;
			counter=i;
			continue;
		}
		counter=i;
	}
	if (counter1==(size1))
	{
		for (int i=counter; i<=(size1 + size2 - 1); i++)
		{
			merged[i]= arr2[counter2];
			counter2++;
		}
	}
	if (counter2==(size2))
	{
		if (counter1==(size1))
		{
			return;
		}
		for (int i=counter; i<=(size1 + size2 - 1); i++)
		{
			merged[i]= arr1[counter1];
			counter1++;
		}
	}
	return;
}

template<typename K, typename V>
void arrToTree(typename Tree<K,V>::Node** arr, int start, int end, Tree<K,V>& tree)
{
	if (start>end)
	{
		return;
	}
	int mid= (end+start)/2;
	if ((start+end)%2 == 0 && (start+end)!=2 && start != end)
    {
        mid++;
    }
	arrToTree(arr, start, mid-1, tree);
	tree.insert(arr[mid]->key, arr[mid]->value);
	arrToTree(arr, mid+1, end, tree);
	return;
}

template<typename K, typename V>
Tree<K, V> unite(Tree<K, V> tree1, Tree<K, V> tree2) {
	Tree<K, V> new_tree = Tree<K, V>(tree1.compare);
	typename Tree<K,V>::Node* root1=tree1.get_root();
	typename Tree<K,V>::Node* root2=tree2.get_root();
	typename Tree<K,V>::Node** arr1= new typename Tree<K,V>::Node*[root1->left_num + root1->right_num + 1];
	typename Tree<K,V>::Node** arr2= new typename Tree<K,V>::Node*[root2->left_num + root2->right_num + 1];
	int counter=0;
	treeToArr(tree1, &counter, arr1, root1);
	counter=0;
	treeToArr(tree2, &counter, arr2, root2);
	typename Tree<K,V>::Node** mergedArr= new typename Tree<K,V>::Node*[root1->left_num + root1->right_num + root2->left_num + root2->right_num + 2];
	mergeArrs(new_tree, mergedArr, arr1, arr2, root1->left_num + root1->right_num + 1, root2->left_num + root2->right_num + 1);
	arrToTree(mergedArr, 0, root1->left_num + root1->right_num + root2->left_num + root2->right_num + 1, new_tree);
	delete[] arr1;
	delete[] arr2;
	delete[] mergedArr;
	return new_tree;
}




#endif

