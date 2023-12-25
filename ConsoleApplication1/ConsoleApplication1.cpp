#include <iostream>
#include "vector.h"
#include <string>
#include "map.h"
#include <fstream>
#include <utility>

struct edge {
    edge() : from(), to(), value(0) {}

    edge(std::string from, std::string to, int value) : from(std::move(from)), to(std::move(to)), value(value) {}

    inline bool operator>(const edge &edge2) const {
        return value > edge2.value;
    }

    inline bool operator<(const edge &edge2) const {
        return this->value < edge2.value;
    }
    std::string from;
    std::string to;
    int value;
};

struct disjointSet {
    disjointSet() {}

    std::string find(std::string x) {
        if (parent[x] == x)
            return x;
        return find(parent[x]);
    }

    void _union(std::string x, std::string y) {
        std::string rootX = find(x);
        std::string rootY = find(y);
        parent[rootX] = rootY;
        rank[rootY] += rank[rootX];
    }

    void makeSet(std::string x) {
        parent.insert(x, x);
        rank.insert(x, 1);
    }

    int rankOf(std::string x) {
        std::string rootX = find(x);
        return rank[rootX];
    }

private:
    Map<std::string, std::string> parent;
    Map<std::string, int> rank;

};

template<typename T>
int partition(my_vector<T> &a, int l, int r) {
    T v = a[(l + r) / 2];
    int i = l;
    int j = r;
    while (i <= j) {
        while (a[i] < v)
            i++;
        while (a[j] > v)
            j--;
        if (i >= j)
            break;
        std::swap(a[i++], a[j--]);
    }
    return j;
}

int partitionstring(my_vector<std::string> &a, int l, int r) {
    std::string v = a[(l + r) / 2];
    int i = l;
    int j = r;
    while (i <= j) {
        while (a[i].compare(v) < 0)
            i++;
        while (a[j].compare(v) > 0)
            j--;
        if (i >= j)
            break;
        swap(a[i++], a[j--]);
    }
    return j;
}

template<typename T>
void qsort(my_vector<T> &a, int l, int r) {
    if (l < r) {
        int q = partition(a, l, r);
        qsort(a, l, q);
        qsort(a, q + 1, r);
    }
}

void qsortstring(my_vector<std::string> &a, int l, int r) {
    if (l < r) {
        int q = partitionstring(a, l, r);
        qsort(a, l, q);
        qsort(a, q + 1, r);
    }
}

void kruskal(my_vector<edge> edges) {
    int value = 0;
    qsort(edges, 0, edges.size() - 1);
    disjointSet ds;
    my_vector<std::string> edgesNames;
    for (int i = 0; i < edges.size(); i++) { // Создаем одиночные множества
        ds.makeSet(edges[i].from);
        ds.makeSet(edges[i].to);
    }
    for (int i = 0; i < edges.size(); i++) {  // Объединяем изолированные вершины
        if (ds.rankOf(edges[i].from) == 1 or ds.rankOf(edges[i].to) == 1) {
            //cout << edges[i].from  << ' ' << ds.rankOf(edges[i].from) << ' ' << edges[i].to  << ds.rankOf(edges[i].to) << '\n';
            ds._union(edges[i].from, edges[i].to);
            value += edges[i].value;
            edgesNames.push_back(edges[i].from + " " + edges[i].to);
        }
    }
    for (int i = 0; i < edges.size(); i++) {  // Объединяем неизолированные вершины
        if (ds.find(edges[i].from) != ds.find(edges[i].to)) {
            ds._union(edges[i].from, edges[i].to);
            value += edges[i].value;
            edgesNames.push_back(edges[i].from + " " + edges[i].to);
        }
    }
    qsortstring(edgesNames, 0, edgesNames.size() - 1);
    for (int i = 0; i < edgesNames.size(); i++) {
        std::cout << edgesNames[i] << '\n';
    }
    std::cout << value << '\n';
}

my_vector<std::string> getElementsName(std::ifstream &input) {
    std::string letters;
    std::getline(input, letters);
    my_vector<std::string> elementsName;
    std::string token;
    for (const auto &letter: letters) {
        if (letter == ' ' || letter == '\t' || letter == '\n') {
            if (!token.empty()) {
                elementsName.push_back(token);
                token = "";
            }
        } else {
            token += letter;
        }
    }
    if (!token.empty()) {
        elementsName.push_back(token);
    }
    return elementsName;
}

my_vector<edge> parseMatrix(std::ifstream &input, const my_vector<std::string> &elementsName) {
    size_t n = elementsName.size();
    my_vector<edge> edges;
    size_t counter = 0;
    while (!input.eof()) {
        std::string letters;
        std::getline(input, letters);
        my_vector<int> elements;
        std::string token;
        for (const auto &letter: letters) {
            if (letter == ' ' || letter == '\t' || letter == '\n') {
                if (!token.empty()) {
                    elements.push_back(stoi(token));
                    token = "";
                }
            } else {
                token += letter;
            }
        }
        if (!token.empty()) {
            elements.push_back(stoi(token));
        }
        if (elements.size() != n) {
            throw std::runtime_error("Неверная матрица смежности!");
        }
        for (size_t i = 0; i < counter; ++i) {
            if (elements[i] != 0) edges.push_back(edge(elementsName[i], elementsName[counter], elements[i]));
        }
        ++counter;
    }
    if (counter != n) {
        throw std::runtime_error("Неверная матрица смежности!");
    }
    return edges;
}

int main() {
    // try to open file
    setlocale(0, "");
    std::string pathToFile;
    std::ifstream input;
    do {
        std::cout << "Введите верный путь к файлу: ";
        std::getline(std::cin, pathToFile);
        if (!pathToFile.ends_with(".txt")) pathToFile += ".txt";
        input.open(pathToFile, std::ios_base::in);
    } while (!input.is_open());

    // parse letters
    auto elementsName = getElementsName(input);

    // parse matrix
    auto edges = parseMatrix(input, elementsName);

    input.close();

    kruskal(edges);
    system("pause");
    return 0;
}
