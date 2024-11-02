#include <iostream>
#include <vector>
#include <algorithm> // для	std::random_shuffle(..., ...)
#include <string>	 // для	std::to_string(...) и stoi(...)
#include <fstream>
#include <queue>
#include <Windows.h>
#define ETERNITY 2147483647 // для обозначения отсутствия связи между вершинами

int input() {
	const int cap = 10;
	char arr[cap];
	for (int i = 0; i < cap; i++) {
		arr[i] = '\n';
	}


	char symb;
	int size = 0;
	//std::cout << "Enter your value\n>>";
	do {
		symb = std::cin.get();
		arr[size] = symb;
		size++;

	} while (symb != '\n' && size != cap);
	size--;


	for (int j = 0; j < size; j++) {
		if (j == 0 && arr[j] == '-');
		else {
			if (!(arr[j] >= 48 && arr[j] <= 57) && arr[j] != '\n') {
				std::cout << "Incorrect input (symbol: '" << arr[j] << "')!\n";
				return 0;
			}
		}
	}


	bool is_positive = arr[0] != '-';


	int number = 0;

	int j = 0;
	int k = 1;
	while (arr[j] != '\n' && j != size) {
		number += (arr[size - j - 1] - 48) * k;
		k *= 10;
		j++;
		if (j + 1 == size && !is_positive) {
			break;
		}
	}
	if (!is_positive)
		number *= -1;

	return number;
}
void fillVector(std::vector<int>& v) {
	for (int i = 0; i < 20; i++) {
		v.push_back(rand() % 10);
	}
}
void printVector(std::vector<int>& v) {
	for (auto& i : v) {
		std::cout << (i == ETERNITY ? "?" : std::to_string(i)) << " ";
	}
	std::cout << std::endl;
}
bool isSorted(std::vector<int>& v) {
	for (int i = 0; i < v.size() - 1; i++) {
		if (v.at(i) > v.at(i + 1)) return false;
	}
	return true;
}
int partition(std::vector<int>& v, int low, int high) {
	int pivot = v[(low + high) / 2];
	int i = low;
	int j = high;
	while (i <= j) {
		while (v[i] < pivot) {
			i++;
		}
		while (v[j] > pivot) {
			j--;
		}
		if (i >= j)
			break;
		int temp = v[i];
		v[i++] = v[j];
		v[j--] = temp;
	}
	return j;
}
void quickSort(std::vector<int>& v, int low, int high) {
	if (low < high) {
		int pivot = partition(v, low, high);
		quickSort(v, 0, pivot);
		quickSort(v, pivot + 1, high);
	}
}
std::vector<std::string> splitLine(std::string str) {
	// возвращает вектор подстрок, разделённых ' '
	std::vector<std::string> v;
	std::string cur = "";
	for (const auto& i : str) {
		if (i != ' ') cur += i;
		else {
			v.push_back(cur);
			cur = "";
		}
	}
	if (cur != "") v.push_back(cur);
	return v;
}
bool containsVector(std::vector<std::string>& v, std::string sub_str) {
	std::string str;
	for (auto& i : v) {
		str += i;
	}
	auto pos = str.find(sub_str);
	if (pos != std::string::npos) return true;
	else return false;
}
void printVector(std::vector<std::string>& v) {
	for (auto& i : v) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}
void printVector(std::vector<std::string>& v, std::string tab) {
	for (auto& i : v) {
		std::cout << i << tab;
	}
	std::cout << std::endl;
}
void printVector(std::vector<int>& v, std::string tab) {
	for (auto& i : v) {
		std::cout << (i == ETERNITY ? "?" : std::to_string(i)) << tab;
	}
	std::cout << std::endl;
}
int indexOfMinVector(std::vector<int>& v) {
	int m = ETERNITY;
	int ind;
	for (int i = 0; i < v.size(); i++) {
		if (v.at(i) < m) {
			m = v.at(i);
			ind = i;
		}
	}
	//v.erase(v.begin() + ind);
	return ind;
}
int sumVector(std::vector<int>& v) {
	int sum = 0;
	for (auto& i : v) {
		sum += i;
	}
	return sum;
}
class Node {
	std::string name;
	std::vector<int> links;
	bool is_visited; // для отслеживания посещения в обходе
	std::vector<std::string> set; // множество для системы непересекающихся множеств
	friend class Graph;
public:
	Node(std::string name) {
		this->name = name;
		is_visited = false;
		set.push_back(name);
	}
	Node(Node* node) {
		this->is_visited = node->is_visited;
		this->links = node->links;
		this->name = node->name;
		this->set = node->set;
	}
	void updateSet() {
		sort(set.begin(), set.end());
	}
};
class Graph {
	std::vector<Node*> graph;
	// делает связи
	void connect(std::string line) {
		std::vector<std::string> str_v = splitLine(line);
		std::vector<int> int_v;
		for (const auto& i : str_v) {
			// if (i == "?") { обработать }
			if (i == "?") int_v.push_back(ETERNITY);
			else int_v.push_back(stoi(i));
		}
		int number_of_line = -1;
		for (int i = 0; i < int_v.size(); i++) {
			if (int_v.at(i) == 0) number_of_line = i;
		}
		try {
			graph.at(number_of_line)->links = std::move(int_v);
		}
		catch (...) {
			std::cout << "Неправильнный ввод!\n";
		}
	}
	// очищает is_visited для всех узлов графа
	void updateVisitStatus() {
		for (auto& i : graph) {
			i->is_visited = false;
		}
	}
	// очищает links для узла node
	void updateLinks() {
		for (auto& i : graph) {
			for (auto& j : i->links) {
				if (j != 0) j = ETERNITY;
			}
		}
	}
	// рекурсивный обход в глубину
	void dfsRecursive(Node* node) {
		if (empty()) return;
		if (node == nullptr) return;
		if (node->is_visited) return;
		std::cout << node->name << " ";
		node->is_visited = true;
		for (int i = 0; i < node->links.size(); i++) {
			// проверяем есть ли связь
			if (node->links.at(i) != 0 && node->links.at(i) != ETERNITY) {
				if (!graph.at(i)->is_visited) {
					dfsRecursive(graph.at(i));
				}
			}
		}
	}
public:
	Graph() {};
	// конструктор копирования
	Graph(const Graph& other) {
		for (int i = 0; i < other.graph.size(); i++) {
			Node* new_node = new Node(other.graph.at(i));
			this->graph.push_back(new_node);
		}
	}
	// статус пустоты графа
	bool empty() {
		return graph.empty();
	}
	// статус ориентированности
	bool isDirected() {
		for (int i = 0; i < graph.size(); i++) {
			for (int j = 0; j < graph.size(); j++) {
				if (i != j) if (graph.at(i)->links.at(j) != graph.at(j)->links.at(i)) return true;
			}
		}
		return false;
	}
	// возвращает размер графа
	int size() {
		return graph.size();
	}
	// пушит ноду, не связывая с остальными
	void push(std::string name) {
		Node* new_node = new Node(name);
		graph.push_back(new_node);
		for (int i = 0; i < graph.size() - 1; i++) {
			graph.at(graph.size() - 1)->links.push_back(ETERNITY);
		}
		for (auto& i : graph) {
			i->links.push_back(ETERNITY);
		}
		graph.at(graph.size() - 1)->links.at(graph.size() - 1) = 0;
	}
	// выводит матрицу смежности
	void printAdjacencyMatrix() {
		std::cout << "Матрица смежности:\n";
		for (const auto& i : graph) {
			std::cout << i->name << " ";
		}
		std::cout << std::endl;
		for (const auto& i : graph) {
			printVector(i->links);
		}
		std::cout << std::endl;
	}
	// выводит список смежности
	void printAdjacencyList() {
		std::cout << "Список смежности:\n";
		for (auto& i : graph) {
			std::cout << i->name;
			for (int j = 0; j < i->links.size(); j++) {
				if (i->links.at(j) != 0 && i->links.at(j) != ETERNITY) std::cout << " -> " << graph.at(j)->name << ":" << i->links.at(j);
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	// возвращает вектор из связных узлов
	std::vector<std::string> getPairs() {
		std::vector<std::string> pairs;
		for (int i = 0; i < graph.size(); i++) {
			for (int j = 0; j < graph.at(i)->links.size(); j++) {
				if (graph.at(i)->links.at(j) != 0 && graph.at(i)->links.at(j) != ETERNITY) {
					std::string temp = graph.at(i)->name + graph.at(j)->name;
					sort(temp.begin(), temp.end());
					if (!containsVector(pairs, temp)) pairs.push_back(temp);
				}
			}
		}
		return pairs;
	}
	// выводит матрицу инцидентности
	void printIncidenceMatrix() {
		std::vector<std::string> pairs = getPairs();
		std::cout << "Матрица инцидентности:\n";
		std::cout << "\t";
		printVector(pairs, "\t");
		int links_num = pairs.size();
		int iter_num = 0;
		std::vector<std::vector<int>> matrix;
		std::vector<std::string> was;
		matrix.resize(graph.size());
		for (int i = 0; i < graph.size(); i++) {
			for (int j = 0; j < graph.at(i)->links.size(); j++) {
				if (graph.at(i)->links.at(j) != 0 && graph.at(i)->links.at(j) != ETERNITY) {

					std::string temp = graph.at(i)->name + graph.at(j)->name;
					sort(temp.begin(), temp.end());
					if (containsVector(was, temp)) continue;
					was.push_back(temp);
					if (graph.at(j)->links.at(i) != ETERNITY) {
						matrix.at(i).push_back(graph.at(i)->links.at(j));
						matrix.at(j).push_back(graph.at(i)->links.at(j));
					}
					else {
						matrix.at(i).push_back(-1 * graph.at(i)->links.at(j));
						matrix.at(j).push_back(graph.at(i)->links.at(j));
					}
					for (int k = 0; k < graph.size(); k++) {
						if (matrix.at(i).size() > matrix.at(k).size()) matrix.at(k).push_back(0);
					}
					iter_num++;
					if (iter_num == pairs.size()) {
						int p = 0;
						for (auto& k : matrix) {
							std::cout << graph.at(p)->name << "\t";
							p++;
							printVector(k, "\t");
						}
						std::cout << std::endl;
						return;
					}
				}
			}
		}
	}
	// парсит файл
	void parse(std::string path) {
		std::ifstream fin;
		try {
			fin.open(path);

			std::string first_line;
			std::getline(fin, first_line);
			std::vector<std::string> names = splitLine(first_line);
			for (const auto& i : names) {
				push(i);
			}
			for (int i = 0; i < names.size(); i++) {
				std::string line;
				std::getline(fin, line);
				connect(line);
			}
			fin.close();
		}
		catch (...) {
			std::cout << "Ошибка открытия файла!\n";
		}
	}
	// запись минимального остовного дерева в файл
	void load(std::vector<std::string>& v) {
		std::ofstream fout;
		try {
			fout.open("mst.txt");
			for (auto& i : v) {
				fout << i << std::endl;
			}
			fout.close();
		}
		catch (...) {
			std::cout << "Ошибка открытия файла!\n";
		}
	}
	// удаление графа
	void erase() {
		while (!graph.empty()) {
			delete graph.at(graph.size() - 1);
			graph.pop_back();
		}
	}
	// обход в ширину с начала
	void bfs() {
		if (empty()) return;
		std::cout << "Обход в ширину:\n";
		std::queue<Node*> q;
		q.push(graph.at(0));
		graph.at(0)->is_visited = true;
		while (!q.empty()) {
			Node* temp = q.front();
			std::cout << temp->name << " ";
			q.pop();
			for (int i = 0; i < temp->links.size(); i++) {
				if (temp->links.at(i) != 0 && temp->links.at(i) != ETERNITY) {
					if (!graph.at(i)->is_visited) {
						q.push(graph.at(i));
						graph.at(i)->is_visited = true;
					}
				}
			}
		}
		updateVisitStatus();
		std::cout << std::endl << std::endl;
	}
	// обход в глубину с начала
	void dfs() {
		if (empty()) return;
		std::cout << "Обход в глубину:\n";
		// используем цикл, чтобы не забыть про вершины, которые не связаны рёбрами
		for (int i = 0; i < graph.size(); i++) { 
			dfsRecursive(graph.at(i));
		}
		updateVisitStatus();
		std::cout << std::endl << std::endl;
	}
	// MakeSet() для union-Find data structure
	void MakeSet(std::string name) {
		// множество создано в описании узла (поле set)
	}
	// Find() для Union-Find data structure
	std::string find(std::string name) {
		int i;
		for (i = 0; i < graph.size(); i++) {
			if (graph.at(i)->name == name) break;
		}
		return graph.at(i)->set.at(0);
	}
	// Union() для Union-Find data structure
	void Union(std::string f_name, std::string s_name) {
		// находим индекс первого узла
		int f_i;
		for (f_i = 0; f_i < graph.size(); f_i++) {
			if (graph.at(f_i)->name == f_name) break;
		}
		// находим индекс второго узла
		int s_i;
		for (s_i = 0; s_i < graph.size(); s_i++) {
			if (graph.at(s_i)->name == s_name) break;
		}
		// проверяем, принадлежат ли узлы разным множествам
		if (find(graph.at(f_i)->name) != find(graph.at(s_i)->name)) {
			// дополняем множество 1 элементами множества 2
			for (auto& i : graph.at(s_i)->set) {
				graph.at(f_i)->set.push_back(i);
			}
			// дополняем множества для остальных элементов из того же множества 1
			for (auto& i : graph.at(f_i)->set) {
				int t_index;
				for (t_index = 0; t_index < graph.size(); t_index++) {
					if (graph.at(t_index)->name == i) break;
				}
				graph.at(t_index)->set = graph.at(f_i)->set;
				graph.at(t_index)->updateSet();
			}
			graph.at(f_i)->updateSet();
			// дополняем множество 2 элементами множества 1
			for (auto& i : graph.at(f_i)->set) {
				if (!containsVector(graph.at(s_i)->set, i)) graph.at(s_i)->set.push_back(i);
			}
			// дополняем множества для остальных элементов из того же множества 2
			for (auto& i : graph.at(s_i)->set) {
				int t_index;
				for (t_index = 0; t_index < graph.size(); t_index++) {
					if (graph.at(t_index)->name == i) break;
				}
				graph.at(t_index)->set = graph.at(s_i)->set;
				graph.at(t_index)->updateSet();
			}
			graph.at(s_i)->updateSet();
		}
	}
	// поиск минимального остовного дерева с помощью алгоритма Краскала
	void KruskalsAlgorithm() {
		if (empty()) return;
		if (isDirected()) return;
		std::vector<std::string> pairs = getPairs();
		std::vector<int> links;
		std::vector<std::string> final_pairs;
		std::vector<int> final_links;
		for (int i = 0; i < graph.size(); i++) {
			for (int j = i + 1; j < graph.size(); j++) {
				if (graph.at(i)->links.at(j) != ETERNITY) links.push_back(graph.at(i)->links.at(j));
			}
		}
		// здесь мы имеем вектор с парами и вектор с их расстояниями
		// очищаем связи
		updateLinks();
		// ищем n-1 нужных связей
		for (int i = 0; i < graph.size() - 1; i++) {
			for (;;) {
				int min_ind = indexOfMinVector(links);
				std::string min_pair = pairs.at(min_ind);
				std::string f_name = "";
				f_name += min_pair[0];
				std::string s_name = "";
				s_name += min_pair[1];

				if (find(f_name) == find(s_name)) {
					links.erase(links.begin() + min_ind);
					pairs.erase(pairs.begin() + min_ind);
				}
				else {
					Union(f_name, s_name);
					final_pairs.push_back(min_pair);
					final_links.push_back(links.at(min_ind));
					links.erase(links.begin() + min_ind);
					pairs.erase(pairs.begin() + min_ind);
					break;
				}
			}
		}
		std::vector<std::string> v;
		v.push_back("Минимальное остовное дерево (Алгоритм Краскала):");
		for (auto& i : final_pairs) {
			v.push_back(i);
		}
		v.push_back(std::to_string(sumVector(final_links)));
		load(v);
		std::cout << "Минимальное остовное дерево (Алгоритм Краскала):\n";
		printVector(final_pairs, "\n");
		std::cout << sumVector(final_links) << std::endl << std::endl;
	}
	// деструктор
	~Graph() {
		if (!empty()) erase();
	}
};
void showQuickSort() {
	std::vector<int> v;
	fillVector(v);
	std::cout << "Случайный массив (размер - 20):\n";
	printVector(v);
	std::cout << (isSorted(v) ? "Массив отсортирован.\n" : "Массив пока не отсортирован.\n");
	quickSort(v, 0, v.size() - 1);
	printVector(v);
	std::cout << (isSorted(v) ? "Массив отсортирован.\n" : "Массив пока не отсортирован.\n\n");
}
void chooseGraphs(std::string path) {
	Graph gr;
	gr.parse(path);
	gr.printAdjacencyMatrix();
	gr.printAdjacencyList();
	gr.printIncidenceMatrix();
	gr.bfs();
	gr.dfs();
	if (!gr.isDirected()) {
		Graph gr2 = gr;
		gr2.KruskalsAlgorithm();
	}
}
void showGraphs() {
	std::cout << "Выберите тип графа:\n1) Неориентированный граф (для алгоритма Краскала).\n2) Ориентированный граф.\n>>";
	std::string path = "UndirectedGraph.txt";
	int graph_type = input();
	std::cout << std::endl;
	switch (graph_type) {
	case 1:
		path = "UndirectedGraph.txt";
		break;
	case 2:
		path = "DirectedGraph.txt";
		break;
	default:
		break;
	}
	chooseGraphs(path);
}
void menu() {
	int number = 1;
	do {
		std::cout << "1) Сортировка Quick Sort.\n2) Графы.\n0) Закончить.\n>> ";
		number = input();
		std::cout << std::endl;
		switch (number) {
		case 1:
			showQuickSort();
			break;
		case 2:
			showGraphs();
			break;
		case 0:
			return;
		default:
			break;
		}
	} while (number);
}

int main() {
	srand(time(0));
	setlocale(0, "");
	menu();
	return 0;
}