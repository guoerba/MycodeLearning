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
	int state;//��ջ״̬
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
	//s.push(QSortStack(left,mid,right,0));//root state:0û��������1����������������2��������������
	while (!s.empty())
	{
		if (cur.left < cur.right)
		{
			switch (cur.state)
			{
			case 0:
				mid = Partition(A, cur.left, cur.right);
				s.push(QSortStack(mid + 1, 0, cur.right, 1));//��¼������
				cur.right = mid - 1;
				break;
			case 1:
				s.push(QSortStack(cur.left, cur.middle, cur.right, 2));//����������
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
			s.pop();//ɾ����������¼
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
				if (!cur)//Ҷ�ӽڵ�									
				{
					state = s.top().status;//��ȡҶ�ӽڵ㸸�ڵ�״̬��1 ��������ӽڵ㣻2 �����ϻ���	
					cur = s.top().node;
					curDepth = s.top().depth;
				}													
				switch (state)
				{
				case 0://��Ѱ������
					std::cout << "val: " << cur->val << std::endl;
					if (treeDepth < ++curDepth)
						treeDepth = curDepth;
					s.push(TreeState(cur,1,curDepth));//��¼��ǰ�ڵ㣬�Լ��´η���ʱ��״̬���Լ���ǰ����
					cur = cur->left;//��Ѱ��ǰ�ڵ�������
					break;
				case 1://��Ѱ������							
					s.pop();					
					s.push(TreeState(cur, 2, curDepth));//���µ�ǰ�ڵ�״̬Ϊ2
					state = 0;//�´μ�����Ѱ��ǰ�ڵ���������������+
					cur = cur->right;
					break;
				case 2://���ϻ���
					s.pop();//��ջ
					if (s.empty())//���ջ�գ�������Ѿ��������
					{
						isdone = true;
						break;
					}						
					state = s.top().status;//��ȡ��ǰ�ڵ㸸�ڵ��״̬
					cur = s.top().node;
					curDepth = s.top().depth;														
				}
			}
		}
		TreeNode* CreateBinaryTree()
		{
			std::cout << "������������ " << std::endl;
			int val;
			std::cin >> val;
			TreeNode *root = new TreeNode(val);
			std::cout << "������root�����ӣ�";
			std::cin >> val;
			std::cout << std::endl;
			if (val > 0)
			{
				TreeNode *left = new TreeNode(val);
				root->left = left;
				CreateBinaryTree(root->left);
			}
			std::cout << "������root���Һ��ӣ�";
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
			std::cout << "������ؼ���Ϊ" << node->val << "�����ӣ�";
			std::cin >> val;
			std::cout << std::endl;
			if (val > 0)
			{
				TreeNode *left = new TreeNode(val);
				node->left = left;
				CreateBinaryTree(node->left);
			}
			std::cout << "������ؼ���Ϊ" << node->val << "���Һ��ӣ�";
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
