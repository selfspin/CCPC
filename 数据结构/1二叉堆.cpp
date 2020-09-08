#include<algorithm>
#include<bitset>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<fstream>
#include<iostream>
#include<map>
#include<queue>
#include<random>
#include<set>
#include<string>
#include<vector>
using namespace std;
typedef long long ll;
const int maxn = 1010;
const int inf = 0x3f3f3f3f;

//4.1 二叉堆(小根堆)
const int maxsize = 100000;
struct BinaryHeap {
	int heap[maxsize], id[maxsize], pos[maxsize], n, counter;
	//heap记录元素，id记录位置为i的元素第几个插入插入，pos记录第i个插入的元素的位置
	BinaryHeap() :n(0), counter(0) {  }
	BinaryHeap(int array[],int offset):n(0), counter(offset) {  
		for (int i = 0; i < offset; ++i) {
			heap[++n] = array[i];
			id[n] = pos[n] = n;
		}
		for (int i = n / 2; i >= 1; --i) down(i);
	}

	void push(int v) { //插入键值v
		heap[++n] = v;
		id[n] = ++counter;
		pos[id[n]] = n;
		up(n);
	}

	int top() { return heap[1]; }

	int pop() {
		swap(heap[1], heap[n]);
		swap(id[1], id[n--]);
		pos[id[1]] = 1;
		down(1);
		return id[n + 1];
	}

	int get(int i) { return heap[pos[i]]; } //获得第i个插进堆中的元素值

	void change(int i, int value) { //修改第i个元素为value
		heap[pos[i]] = value;
		down(pos[i]);
		up(pos[i]);
	}

	void erase(int i) { //删除第i个元素
		heap[pos[i]] = inf;
		up(pos[i]);
		pop();
	}

	void up(int i) {
		int x = heap[i], y = id[i];
		for (int j = i / 2; j >= 1; j /= 2) {
			if (heap[j] > x) {
				heap[i] = heap[j];
				id[i] = id[j];
				pos[id[i]] = i;
				i = j;
			}
			else break;
		}
		heap[i] = x;
		id[i] = y;
		pos[y] = i;
	}

	void down(int i) {
		int x = heap[i], y = id[i];
		for (int j = i * 2; j <= n; j *= 2) {
			j += (j < n && heap[j] > heap[j + 1]);
			if (heap[j] < x) {
				heap[i] = heap[j];
				id[i] = id[j];
				pos[id[i]] = i;
				i = j;
			}
			else break;
		}
		heap[i] = x;
		id[i] = y;
		pos[y] = i;
	}

	bool empty() { return n == 0; }

	int size() { return n; }
};