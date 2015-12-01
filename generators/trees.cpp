#include "testlib.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

class Tree {
	int vertex_count;
	vector<pair<int, int> > edge_list;
public:
	Tree() {}
	explicit Tree(int n) : vertex_count(n) {}
	void addEdge(int a, int b) {
		edge_list.push_back(make_pair(a, b));
	}
	void shuffle() {
		vector<int> p(vertex_count);
		iota(p.begin(), p.end(), 0);
        ::shuffle(p.begin(), p.end());
		vector<pair<int, int> > ans;
		ans.reserve(edge_list.size());
		for (auto cur : edge_list) {
            if (rnd.next(0, 1))
				swap(cur.first, cur.second);
			ans.emplace_back(p[cur.first], p[cur.second]);
		}
		ans.swap(edge_list);
	}
	int getVertexCount() const {
		return vertex_count;
	}
	vector<pair<int, int> >::const_iterator begin() const {
		return edge_list.cbegin();
	}
	vector<pair<int, int> >::const_iterator end() const {
		return edge_list.cend();
	}
};

class DSU {
	mutable vector<int> p;
	vector<int> rank;
	int find(int v) const {
		return p[v] == v ? v : p[v] = find(p[v]);
	}
public:
	explicit DSU(int n) : p(n), rank(n) {
		iota(p.begin(), p.end(), 0);
	}
	bool addEdge(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b)
			return false;
		if (rank[a] < rank[b])
			swap(a, b);
		p[b] = a;
		if (rank[a] == rank[b])
			++rank[a];
		return true;
	}
	bool isConnected(int a, int b) const {
		a = find(a);
		b = find(b);
		return a == b;
	}
};

Tree genTreeWithBigDiametr(int n) {
	Tree ans(n);
	DSU joiner(n);
	for (int edges = 0; edges < n - 1;) {
		int x = rnd.next(0, n - 1);
		int y = rnd.next(0, n - 1);
		if (joiner.addEdge(x, y)) {
			++edges;
			ans.addEdge(x, y);
		}
	}
	ans.shuffle();
	return ans;
}

Tree genTreeWithManyLists(int n) {
	Tree ans(n);
	for (int i = 1; i < n; ++i)
		ans.addEdge(rnd.next(0, i - 1), i);
	ans.shuffle();
	return ans;
}

Tree genLongTree(int n, int bamboo_len) {
	Tree ans(n);
	for (int i = 0; i + 1 < bamboo_len; ++i)
		ans.addEdge(i, i + 1);
	for (int i = bamboo_len; i < n; ++i)
		ans.addEdge(rnd.next(0, i - 1), i);
	ans.shuffle();
	return ans;
}

Tree genNBranches(int n, int branches) {
	if (n - 1 < branches)
		throw logic_error("Too much branches!");
	Tree ans(n);
	int len = (n - 1) / branches;
	int v = 1;
	for (int i = 0; i < branches && v < n; ++i) {
		ans.addEdge(0, v++);
		for (int j = 1; j < len && v < n; ++j, ++v)
			ans.addEdge(v - 1, v);
	}
	if (v < n) {
		ans.addEdge(v, len);
		++v;
		while (v < n) {
			ans.addEdge(v - 1, v);
            ++v;
        }
	}
	ans.shuffle();
	return ans;
}

Tree genBinaryStructure(int n) {
	Tree ans(n);
	int i;
	for (i = 0; 2 * i + 2 < n; ++i) {
		ans.addEdge(i, 2 * i + 1);
		ans.addEdge(i, 2 * i + 2);
	}
	i = 2 * i + 1;
	for (; i < n; ++i)
		ans.addEdge(rnd.next(0, i - 1), i);
	ans.shuffle();
	return ans;
}

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    return 0;
}
