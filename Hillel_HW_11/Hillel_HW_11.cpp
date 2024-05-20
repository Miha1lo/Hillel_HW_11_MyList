#include <iostream>

template<typename T>
struct Node
{
	T data;
	Node* prev;
	Node* next;
	Node(const T& value) : data(value), prev(nullptr), next(nullptr)
	{}
};

template<typename T>
class MyList {
private:
	Node<T>* head;
	Node<T>* tail;
	size_t size;

	void clear() {
		while (head) {
			pop_front();
		}
	}


public:
	MyList() : head(nullptr), tail(nullptr), size(0) {}

	MyList(const MyList& other) : head(nullptr), tail(nullptr), size(0) {
		Node<T>* current = other.head;
		while (current != nullptr) {
			push_back(current->data);
			current = current->next;
		}
	}

	MyList& operator=(const MyList& other) {
		if (this == &other) return *this;

		clear();
		Node<T>* current = other.head;
		while (current != nullptr) {
			push_back(current->data);
			current = current->next;
		}
		return *this;
	}

	~MyList() {
		clear();
	}

	size_t getSize() const {
		return size;
	}

	void push_back(const T& value) {
		Node<T>* newNode = new Node<T>(value);
		if (tail) {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		else {
			head = tail = newNode;
		}
		++size;
	}

	void push_front(const T& value) {
		Node<T>* newNode = new Node<T>(value);
		if (head) {
			head->prev = newNode;
			newNode->next = head;
			head = newNode;
		}
		else {
			head = tail = newNode;
		}
		++size;
	}

	void pop_back() {
		if (tail) {
			Node<T>* temp = tail;
			tail = tail->prev;
			if (tail) {
				tail->next = nullptr;
			}
			else {
				head = nullptr;
			}
			delete temp;
			--size;
		}
	}

	void pop_front() {
		if (head) {
			Node<T>* temp = head;
			head = head->next;
			if (head) {
				head->prev = nullptr;
			}
			else {
				tail = nullptr;
			}
			delete temp;
			--size;
		}
	}

	void printList() const {
		Node<T>* current = head;
		while (current != nullptr) {
			std::cout << current->data << " ";
			current = current->next;
		}
		std::cout << std::endl;
	}
};

int main() {
	MyList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_front(0);
	list.push_front(-1);
	list.printList();				// Expacted result: -1 0 1 2 3

	list.pop_back();
	list.printList();				// Expacted result: -1 0 1 2

	list.pop_front();
	list.printList();				// Expacted result: 0 1 2

	MyList<int> list2(list);
	list2.printList();			// Expacted result: 0 1 2

	MyList<int> list3;
	list3.push_back(4);
	list3.push_back(5);
	list3 = list2;
	list3.printList();			// Expacted result: 0 1 2

	return 0;
}
