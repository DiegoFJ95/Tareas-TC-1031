#ifndef LIST_H_
#define LIST_H_

#include <string>
#include <sstream>

template <class T> class List;

// Definición de la clase Link o nodo.
template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*); // Constructor con valor y hacia donde apunta.
	Link(const Link<T>&); // Constructor para copiar elementos.

	T value;
  Link<T> *next; // Apuntador al siguiente elemento.

	friend class List<T>; // Clases friend comparten sus métodos.
};

// Definición de los constructores de Link.
template <class T>
Link<T>::Link(T val) : value(val), next(0){}

template <class T>
Link<T>::Link(T val, Link* nxt) : value(val), next(nxt){}

template <class T>
Link<T>::Link(const Link<T> &source) : value(source.value), next(source.next){}

#endif

// Definición de la clase list.

template <class T>
class List {
public:
	List();
	List(const List<T>&) ;
	~List();

	std::string toString() const;
	void insertion(T) ;
  void update(T,T);
  void deleteAt(T);

	void addFirst(T) ;
  bool empty() const;
  int search(T);
	void clear();


private:
	Link<T> *head;
	int 	size;
};

// Definición de constructores.

template <class T>
List<T>::List(){
	head=0;
	size=0;
}


template <class T>
List<T>::~List(){
  clear();
}


template <class T>
List<T>::List(const List<T> &source){
  Link<T> *p,*q;

	if(source.empty()){
		size = 0;
		head = 0;
	}

	else {
		p = source.head;
		head = new Link<T>(p->value);
    q = head;
		p = p->next;

    while(p!=0){
      q->next = new Link<T>(p->value);
      p = p->next;
      q = q->next;

    }
    size = source.size;
  }
}


// Definición de métodos.

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

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
bool List<T>::empty() const {
	return (head==0);
}


template <class T>
int List<T>::search(T n){
  Link<T> *p;
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


template <class T>
void List<T>::addFirst(T n){
  Link <T> *newLink;
  newLink = new Link<T>(n);

  newLink->next = head;
  head = newLink;
  size++;
}


template <class T>
void List<T>::insertion(T n){
  Link<T> *newLink;
  Link<T> *p;
  newLink = new Link<T>(n);

  if (empty()){
    addFirst(n);
    return;
  }

  p = head;
  while(p->next != 0){
    p = p->next;
  }

  newLink->next = 0;
  p->next = newLink;
  size++;
}


template <class T>
void List<T>::update(T index, T n){
  Link<T> *p;
  p = head;

  for(int i = 0; i<index; i++){
    p = p->next;
  }

  p->value = n;
}


template <class T>
void List<T>::deleteAt(T index){
  Link<T> *p, *q;
	int cont = 0;

  if(index==0){
    p = head;
    head = p->next;
    delete p;
    size--;
    return;
  }

  p = head;
  while(cont<index){
    q = p;
    p = p->next;
		cont++;
  }
  q->next = p->next;
  delete p;
  size--;
  return;
}


template <class T>
void List<T>::clear() {
	Link<T> *p, *q;
	p = head;

	while(p != 0){
		q = p->next;
		delete p;
		p = q;
	}

	head = 0;
	size = 0;
}
