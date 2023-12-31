#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>

template <class T> class DList;
template <class T>

//Definición de la clase DLink.
class DLink{
private:
	DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);
	DLink(const DLink<T>&);

	T	    value;
	DLink<T> *previous;
	DLink<T> *next;

	friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source) : value(source.value), previous(source.previous), next(source.next) {}


//Definición de la clase DList.
template <class T>
class DList {
private:
	DLink<T> *head;
	DLink<T> *tail;
	int 	 size;

public:
	DList();
	DList(const DList<T>&);
	~DList();

  std::string toStringForward() const;
  std::string toStringBackward() const;

	void insertion(T) ;
  void update(T,T);
  void deleteAt(T);

	void addFirst(T) ;
  bool empty() const;
  int search(T);
	void clear();

};

//Constructores de la clase DList.

template <class T>
DList<T>::DList() {
	head = 0;
	tail = 0;
	size = 0;
}


template <class T>
DList<T>::DList(const DList<T> &source)  {
	DLink<T> *p, *q;

	if (source.empty()) {
		size = 0;
		head = 0;
		tail = 0;
	} else {
		p = source.head;
		head = new DLink<T>(p->value);
		q = head;

		p = p->next;
		while(p != 0) {
			q->next = new DLink<T>(p->value, q, 0);
			p = p->next;
			q = q->next;
		}
		size = source.size;
	}
}


template <class T>
DList<T>::~DList() {
	clear();
}


//Métodos de la clase DList.
template <class T>
bool DList<T>::empty() const {
	return (head == 0 && tail == 0);
};


template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}


template <class T>
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}


template <class T>
void DList<T>::addFirst(T n){
  DLink <T> *newDLink;
	newDLink = new DLink<T>(n);

	if (empty()){
		head = newDLink;
		tail = newDLink;
	}
	else{
		newDLink->next = head;
		head->previous = newDLink;
		head = newDLink;
	}
	size++;
}


template <class T>
void DList<T>::insertion(T n){
  DLink<T> *newDLink;
  newDLink = new DLink<T>(n);

  if (empty()){
    addFirst(n);
  }

  else{
    newDLink->previous = tail;
    tail->next = newDLink;
    tail = newDLink;
    size++;
  }

}


template <class T>
void DList<T>::update(T index, T n){
  DLink<T> *p;;
  p = head;

  for(int i = 0; i<index; i++){
    p = p->next;
  }

  p->value = n;
}


template <class T>
void DList<T>::deleteAt(T index){
  DLink<T> *p, *q;
	int count = 0;

  if(index==0){
    p = head;
    head = p->next;

    if (head != 0) {
        head->previous = 0;
    }
    else {
        tail = 0;
    }

    delete p;

  }

  else {
    p = head;
    while (count < index) {
      q = p;
      p = p->next;
			count++;
    }
    q->next = p->next;
    if (p->next != 0) {
        p->next->previous = q;
    }
    else {
        tail = q;
    }
    delete p;
  }
	size--;
}

template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}

	head = 0;
	tail = 0;
	size = 0;
}

template <class T>
int DList<T>::search(T n){
  DLink<T> *p;
  int pos = 0;
  p = head;
  while(p!=0){
    if (p->value == n){
      return pos;
    }
    pos++;
    p = p->next;
  }
  return -1;
}


#endif
