#pragma once
#include <vector>



template <class T>
class Stack
{
private:
	std::vector<T> stack;


public:
	T top() { if(!stack.empty() ) return stack[stack.size() - 1]; }
	void push(T item) { stack.push_back(item); }
	void pop() { if (!stack.empty()) stack.pop_back(); }

	bool empty() { return stack.empty(); }
	int size() { return stack.size(); }
	void clear() { stack.clear(); }

	void pop_inside(T item) {
		if (!stack.empty()) {
			// Utiliser std::find pour chercher l'élément et l'effacer
			auto it = std::find(stack.begin(), stack.end(), item);
			if (it != stack.end()) {
				stack.erase(it); // Efface l'élément s'il est trouvé
			}
		}
	}
};

