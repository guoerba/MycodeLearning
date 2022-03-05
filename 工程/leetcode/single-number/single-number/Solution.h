#pragma once
#include <algorithm>
#include <stack>
#include <iostream>

template<class T>
void Swap(T &a, T &b);
template<class T>
void QuickSort(T *A, int len);
template<class T>
void QuickSort(T *A, int s, int e);
template<class T>
void QuickSortNoRecursion(T *A, int len);
template<class T>
int Partition(T *A, int s, int e);

struct QSortStack {
	int left;
	int middle;
	int right;
	int state;//堆栈状态
	QSortStack() :left(0), middle(0), right(0), state(0) {};
	QSortStack(int l, int mid, int r, int s) :left(l), middle(mid), right(r), state(s) {};
	QSortStack(const QSortStack &b)
	{
		this->left = b.left;
		this->middle = b.middle;
		this->right = b.right;
		this->state = b.state;
	}
	QSortStack & operator = (const QSortStack &b)
	{
		this->left = b.left;
		this->middle = b.middle;
		this->right = b.right;
		this->state = b.state;
		return *this;
	}
};


template<class T>
void Swap(T &a, T &b)
{
	if (a == b)
		return;
	T temp = a;
	a = b;
	b = temp;
}


template<class T>
void QuickSort(T *A, int len)
{
	QuickSort(A, 0, len - 1);
}

template<class T>
void QuickSort(T *A, int s, int e)
{
	if (s < e)
	{
		int r = Partition(A, s, e);
		QuickSort(A, s, r - 1);
		QuickSort(A, r, e);
	}
}

template<class T>
void QuickSortNoRecursion(T *A, int len)
{
	if (len <= 1)
		return;
	std::stack<QSortStack> s;
	s.push(QSortStack());
	QSortStack cur(0, 0, len - 1, 0);
	int mid = 0;
	//s.push(QSortStack(0, 0, 0, 2));
	//s.push(QSortStack(left,mid,right,0));//root state:0没遍历过；1：遍历了左子树；2：遍历了右子树
	while (!s.empty())
	{
		if (cur.left < cur.right)
		{
			switch (cur.state)
			{
			case 0:
				mid = Partition(A, cur.left, cur.right);
				s.push(QSortStack(mid + 1, 0, cur.right, 1));//记录右子树
				cur.right = mid - 1;
				break;
			case 1:
				s.push(QSortStack(cur.left, cur.middle, cur.right, 2));//更新右子树
				cur.state = 0;
				break;
			case 2:
				if (s.empty())
					break;
				cur = s.top();
				s.pop();
			}
		}
		else
		{
			if (s.empty())
				break;
			cur = s.top();
			s.pop();//删除右子树记录
		}
	}

}

template<class T>
int Partition(T *A, int s, int e)
{
	//Swap(A[r], A[e]);
	int i = s, j = s;
	while (i < e)
	{
		if (A[i] < A[e])
		{
			Swap(A[i++], A[j++]);
		}
		else
		{
			i++;
		}
	}
	Swap(A[j], A[e]);
	return j;
}


namespace SingleNumber {
	class Solution
	{
	public:
		Solution() {};
		~Solution() {};
		int singleNumber(int A[], int n) {
			QuickSortNoRecursion(A, n);
			for (int i = 0; i < n - 1; i += 2)
			{
				if (A[i] != A[i + 1])
					return A[i];
			}
			return A[n - 1];
		}
	};
};

namespace MaxDepthBinaryTree {
	struct TreeState;
	struct TreeNode;
	class Solution;

	struct TreeState {
		TreeNode *node;
		int status;
		int depth;
		TreeState() :node(0), status(0),depth(0){}
		TreeState(TreeNode *p,int s,int depth):node(p),status(s),depth(depth){}
	};

	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode() : val(0),left(NULL),right(NULL){}
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	class Solution {
	public:
		Solution():treeDepth(0){}
		int maxDepth(TreeNode *root) {
			SearchBinaryTree(root);
			return treeDepth;
		}
		void SearchBinaryTree(TreeNode *root){
			int state = 0,curDepth = 0;
			std::stack<TreeState>s;
			TreeNode *cur = root;
			bool isdone = false;
			while (!isdone)
			{
				if (!cur)//叶子节点									
				{
					state = s.top().status;//读取叶子节点父节点状态：1 则访问右子节点；2 则向上回溯	
					cur = s.top().node;
					curDepth = s.top().depth;
				}													
				switch (state)
				{
				case 0://搜寻左子树
					std::cout << "val: " << cur->val << std::endl;
					if (treeDepth < ++curDepth)
						treeDepth = curDepth;
					s.push(TreeState(cur,1,curDepth));//记录当前节点，以及下次访问时的状态，以及当前树高
					cur = cur->left;//搜寻当前节点左子树
					break;
				case 1://搜寻右子树							
					s.pop();					
					s.push(TreeState(cur, 2, curDepth));//更新当前节点状态为2
					state = 0;//下次继续搜寻当前节点右子树的左子树+
					cur = cur->right;
					break;
				case 2://向上回溯
					s.pop();//出栈
					if (s.empty())//如果栈空，则代表已经遍历完成
					{
						isdone = true;
						break;
					}						
					state = s.top().status;//读取当前节点父节点的状态
					cur = s.top().node;
					curDepth = s.top().depth;														
				}
			}
		}
		TreeNode* CreateBinaryTree()
		{
			std::cout << "请输入树根： " << std::endl;
			int val;
			std::cin >> val;
			TreeNode *root = new TreeNode(val);
			std::cout << "请输入root的左孩子：";
			std::cin >> val;
			std::cout << std::endl;
			if (val > 0)
			{
				TreeNode *left = new TreeNode(val);
				root->left = left;
				CreateBinaryTree(root->left);
			}
			std::cout << "请输入root的右孩子：";
			std::cin >> val;
			std::cout << std::endl;
			if (val > 0)
			{
				TreeNode *right = new TreeNode(val);
				root->right = right;
				CreateBinaryTree(root->right);
			}
			return root;
		}
		void CreateBinaryTree(TreeNode *node)
		{
			int val;
			std::cout << "请输入关键字为" << node->val << "的左孩子：";
			std::cin >> val;
			std::cout << std::endl;
			if (val > 0)
			{
				TreeNode *left = new TreeNode(val);
				node->left = left;
				CreateBinaryTree(node->left);
			}
			std::cout << "请输入关键字为" << node->val << "的右孩子：";
			std::cin >> val;
			std::cout << std::endl;
			if (val > 0)
			{
				TreeNode *right = new TreeNode(val);
				node->right = right;
				CreateBinaryTree(node->right);
			}

		}
		void DeleteBinaryTree(TreeNode *root)
		{
			if(root->left)
				DeleteBinaryTree(root->left);
			if(root->right)
				DeleteBinaryTree(root->right);
			delete root;
			root = NULL;
		}
	private:
		int treeDepth;
	};
}
