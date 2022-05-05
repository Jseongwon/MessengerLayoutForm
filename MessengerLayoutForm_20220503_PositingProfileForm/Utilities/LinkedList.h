// LinkedList.h
#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef signed long int Long;

template <typename T>
class LinkedList {
public:
	class Node {
		friend class LinkedList;

	public:
		Node() {
			this->previos = this;
			this->next = this;
		}

		Node(T object) {
			this->previous = this;
			this->object = object;
			this->next = this;
		}

		Node(Node *previous, T object) {
			this->previous = previous;
			this->object = object;
			this->next = this;
		}

		Node(T object, Node *next) {
			this->previous = this;
			this->object = object;
			this->next = next;
		}

		Node(Node *previous, T object, Node *next) {
			this->previous = previous;
			this->object = object;
			this->next = next;
		}

		Node(const Node& source) {
			this->previous = source.previous;
			this->object = source.object;
			this->next = source.next;
		}
		~Node() {
		}

		T& GetObject() const {
			return const_cast<T&>(this->object);
		}

		T* GetObjectLink() const {
			return const_cast<T*>(&this->object);
		}

		Node& operator =(const Node& source) {
			this->previous = source.previous;
			this->object = source.object;
			this->next = source.next;

			return *this;
		}

	private:
		Node *previous;
		T object;
		Node *next;
	};

public:
	LinkedList();
	LinkedList(const LinkedList& source);
	~LinkedList();
	Node* InsertBefore(Node *index, T object);
	Node* InsertAfter(Node *index, T object);
	Node* AppendFromHead(T object);
	Node* AppendFromTail(T object);
	Node* Delete(Node *index);
	Node* DeleteFromHead();
	Node* DeleteFromTail();
	void DeleteAllItems();
	Node* LinearSearchUnique(void *key, int(*compare)(void *, void *));
	void LinearSearchDuplicate(void *key, Node* *(*indexes), Long *count, int(*compare)(void *, void *));
	Node* First();
	Node* Previous();
	Node* Next();
	Node* Last();
	Node* Move(Node *index);
	T& GetAt(Node *index);
	Long GetNumber(Node* index);

	Node* GetHead() const;
	Node* GetTail() const;
	Long GetLength() const;
	Node* GetCurrent() const;
	LinkedList<T>& operator =(const LinkedList& source);
	T& operator [](Long index);
	T* operator +(Long index);

private:
	Node *head;
	Node *tail;
	Long length;
	Node *current;
};

template <typename T>
LinkedList<T>::LinkedList() {
	this->head = 0;
	this->tail = 0;
	this->length = 0;
	this->current = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& source) {
	Node *previous;
	Node *current;

	this->head = 0;
	current = source.current;
	previous = current;
	if (current != 0) {
		this->current = new Node(current->object);
		this->head = this->current;
		current = current->next;
	}
	while (previous != current) {
		this->current = new Node(this->current, current->object);
		this->current->previous->next = this->current;
		previous = current;
		current = current->next;
	}
	this->tail = this->current;
	this->length = source.length;

	this->current = this->head;
	current = source.head;
	while (current != source.current) {
		this->current = this->current->next;
		current = current->next;
	}
}

template <typename T>
LinkedList<T>::~LinkedList() {
	LinkedList<T>::Node *previous = 0;
	this->current = this->head;
	while (previous != this->current) {
		previous = this->current;
		this->head = this->current->next;
		delete this->current;
		this->current = this->head;
	}
}

/*
명칭 : InsertBefore
기능 : 연결리스트에서 위치의 앞에 삽입한다.
입력 : 위치, 오브젝트
출력 : 위치
*/
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::InsertBefore(Node *index, T object) {
	if (this->head != index) {
		this->current = new Node(index->previous, object, index);
	}
	else {
		this->current = new Node(object, index);
	}
	if (this->head != index) {
		index->previous->next = this->current;
	}
	else {
		this->head = this->current;
	}
	index->previous = this->current;
	this->length++;

	return this->current;
}

/*
명칭 : InsertAfter
기능 : 연결리스트에서 위치의 뒤에 삽입한다.
입력 : 위치, 오브젝트
출력 : 위치
*/
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::InsertAfter(Node *index, T object) {
	if (this->tail != index) {
		this->current = new Node(index, object, index->next);
	}
	else {
		this->current = new Node(index, object);
	}
	if (this->tail != index) {
		index->next->previous = this->current;
	}
	else {
		this->tail = this->current;
	}
	index->next = this->current;
	this->length++;

	return this->current;
}

/*
명칭 : AppendFromHead
기능 : 연결리스트에서 맨 앞에 끼운다.
입력 : 오브젝트
출력 : 위치
*/
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::AppendFromHead(T object) {
	if (this->head != 0) {
		this->current = new Node(object, this->head);
	}
	else {
		this->current = new Node(object);
	}
	if (this->head != 0) {
		this->head->previous = this->current;
	}
	else {
		this->tail = this->current;
	}
	this->head = this->current;
	this->length++;

	return this->current;
}

/*
명칭 : AppendFromTail
기능 : 연결리스트에서 맨 뒤에 삽입한다.
입력 : 오브젝트
출력 : 위치
*/
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::AppendFromTail(T object) {
	if (this->head != 0) {
		this->current = new Node(this->tail, object);
	}
	else {
		this->current = new Node(object);
	}
	if (this->head != 0) {
		this->tail->next = this->current;
	}
	else {
		this->head = this->current;
	}
	this->tail = this->current;
	this->length++;

	return this->current;
}

/*
명칭 : Delete
기능 : 연결리스트에서 삭제한다.
입력 : 위치
출력 : 위치(0)
*/
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Delete(Node *index) {
	if (this->head != index && this->tail != index) {
		index->previous->next = index->next;
		index->next->previous = index->previous;
		this->current = index->next;
	}
	else if (this->head == index && this->tail != index) {
		index->next->previous = index->next;
		this->head = index->next;
		this->current = index->next;
	}
	else if (this->head != index && this->tail == index) {
		index->previous->next = index->previous;
		this->tail = index->previous;
		this->current = index->previous;
	}
	else {
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}
	if (index != 0) {
		delete index;
	}
	this->length--;

	return 0;
}

/*
명칭 : DeleteFromHead
기능 : 연결리스트에서 맨 앞을 삭제한다.
입력 : X
출력 : 위치(0)
*/
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::DeleteFromHead() {
	Node *index;

	index = this->head;
	
	if (index != this->tail) {
		index->next->previous = index->next;
		this->head = index->next;
		this->current = index->next;
	}
	else {
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}
	if (index != 0) {
		delete index;
	}
	this->length--;

	return 0;
}

/*
명칭 : DeleteFromTail
기능 : 연결리스트에서 맨 뒤를 삭제한다.
입력 : X
출력 : 위치(0)
*/
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::DeleteFromTail() {
	Node *index;
	
	index = this->tail;
	if (index != this->head) {
		index->previous->next = index->previous;
		this->tail = index->previous;
		this->current = index->previous;
	}
	else {
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}
	if (index != 0) {
		delete index;
	}
	this->length--;

	return 0;
}

/*
명칭 : DeleteAllItems
기능 : 연결리스트에서 모두 삭제한다.
입력 : X
출력 : X
*/
template <typename T>
void LinkedList<T>::DeleteAllItems() {
	Node *previous = 0;

	this->current = this->head;
	while (previous != this->current) {
		this->head = this->current->next;
		previous = this->current;
		delete this->current;
		this->current = this->head;
	}
	this->head = 0;
	this->tail = 0;
	this->length = 0;
	this->current = 0;
}

/*
명칭 : LinearSearchUnique
기능 : 연결리스트에서 검색한다.
입력 : 키
출력 : 위치
*/
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::LinearSearchUnique(void *key, int(*compare)(void*, void*)) {
	Node *index;
	Node *previous = 0;
	
	index = this->head;
	while (previous != index && compare(&index->object, key) != 0) {
		previous = index;
		index = index->next;
	}
	if (previous == index) {
		index = 0;
	}

	return index;
}

/*
명칭 : LinearSearchDuplicate
기능 : 연결리스트에서 중복 검색한다.
입력 : 키
출력 : 위치들, 개수
*/
template <typename T>
void LinkedList<T>::LinearSearchDuplicate(void *key, Node* *(*indexes), Long *count, int(*compare)(void*, void*)) {
	Node *previous = 0;
	int i = 0;

	*count = 0;
	*indexes = new Node*[this->length];
	this->current = this->head;
	while (previous != this->current) {
		if (compare(&this->current->object, key) == 0) {
			(*indexes)[i] = this->current;
			(*count)++;
			i++;
		}
		previous = this->current;
		this->current = this->current->next;
	}
}

/*
명칭 : First
기능 : 연결리스트에서 처음으로 이동한다.
입력 : X
출력 : 위치
*/
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::First() {
	this->current = this->head;

	return this->current;
}

/*
명칭 : Previous
기능 : 연결리스트에서 이전으로 이동한다.
입력 : X
출력 : 위치
*/
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Previous() {
	this->current = this->current->previous;

	return this->current;
}

/*
명칭 : Next
기능 : 연결리스트에서 다음으로 이동한다.
입력 : X
출력 : 위치
*/
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Next() {
	this->current = this->current->next;

	return this->current;
}

/*
명칭 : Last
기능 : 연결리스트에서 마지막으로 이동한다.
입력 : X
출력 : 위치
*/
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Last() {
	this->current = this->tail;

	return this->current;
}

/*
명칭 : Move
기능 : 연결리스트에서 위치로 이동한다.
입력 : 위치
출력 : 위치
*/
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Move(Node *index) {
	this->current = index;

	return this->current;
}

/*
명칭 : GetAt
기능 : 연결리스트에서 읽는다.
입력 : 위치
출력 : 오브젝트
*/
template <typename T>
T& LinkedList<T>::GetAt(Node *index) {
	return index->GetObject();
}

/*
명칭 : GetNumber
기능 : 몇 번째 노드인지 센다.
입력 : X
출력 : 정수 위치
*/
template <typename T>
Long LinkedList<T>::GetNumber(Node* index) {
	Long number = 1;

	Node* previous = 0;
	Node* it = this->head;
	while (it != previous && it != index) {
		number++;
		previous = it;
		it = it->next;
	}

	return number;
}

/*
명칭 : GetHead
기능 : 연결리스트에서 처음 위치를 읽는다.
입력 : X
출력 : 사용량
*/
template <typename T>
inline typename LinkedList<T>::Node* LinkedList<T>::GetHead() const {
	return const_cast<Node*>(this->head);
}

/*
명칭 : GetHead
기능 : 연결리스트에서 마지막 위치를 읽는다.
입력 : X
출력 : 사용량
*/
template <typename T>
inline typename LinkedList<T>::Node* LinkedList<T>::GetTail() const {
	return const_cast<Node*>(this->tail);
}

/*
명칭 : GetLength
기능 : 연결리스트에서 사용량을 읽는다.
입력 : X
출력 : 사용량
*/
template <typename T>
inline Long LinkedList<T>::GetLength() const {
	return this->length;
}

/*
명칭 : GetCurrent
기능 : 연결리스트에서 현재 위치를 읽는다.
입력 : X
출력 : 위치
*/
template <typename T>
inline typename LinkedList<T>::Node* LinkedList<T>::GetCurrent() const {
	return const_cast<Node*>(this->current);
}

/*
명칭 : operator =
기능 : 연결리스트에서 =연산자를 정의한다.
입력 : source
출력 : 연결리스트
*/
template <typename T>
LinkedList<T>& LinkedList<T>::operator =(const LinkedList<T>& source) {
	Node *previous = 0;
	Node *current;
	this->current = this->head;
	while (previous != this->current) {
		previous = this->current;
		this->head = this->current->next;
		delete this->current;
		this->current = this->head;
	}

	current = source.current;
	previous = current;
	if (current != 0) {
		this->current = new Node(current->object);
		this->head = this->current;
		current = current->next;
	}
	while (previous != current) {
		this->current = new Node(this->current, current->object);
		this->current->previous->next = this->current;
		previous = current;
		current = current->next;
	}
	this->tail = this->current;
	this->length = source.length;

	this->current = this->head;
	current = source.head;
	while (current != source.current) {
		this->current = this->current->next;
		current = current->next;
	}

	return *this;
}

/*
명칭 : operator []
기능 : 연결리스트에서 []연산자를 정의한다.
입력 : 위치
출력 : 오브젝트
*/
template <typename T>
T& LinkedList<T>::operator [](Long index) {
	return this->GetAt(index);
}

/*
명칭 : operator +
기능 : 연결리스트에서 +연산자를 정의한다.
입력 : 위치
출력 : 오브젝트 주소
*/
template <typename T>
T* LinkedList<T>::operator + (Long index) {
	return &(this->GetAt(index));
}

#endif // _LINKEDLIST_H