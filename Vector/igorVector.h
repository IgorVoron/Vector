#pragma once

template <class T>
class Deque {
	T* startPtr;    // указывает на начало выделенной памяти
	T* frontPtr;    // указывает на первый элемент в деке
	T* backPtr;     // указывает на последний элемет в деке
	int maxSize;    // максимальный размер, указанный при создании дека

public:
	inline void setStartPtr(T*);   // сеттер
	inline void setFrontPtr(T*);   // сеттер
	inline void setBackPtr(T*);    // сеттер
	inline void setMaxSize(T*);    // сеттер

	inline T* getStartPtr() const; // геттер
	inline T* getFrontPtr() const; // геттер
	inline T* getBackPtr() const;  // геттер
	inline T* getMaxSize() const;  // геттер

	Deque(int);                    // простой конструктор с указанием наксимального кол-ва элементов, которые будут добавлены в дек
	Deque(const Deque&);           // конструктор копирования с полным поэлементым копированием
	~Deque();                      // дестркутор с простой очиткой памяти

	inline T& front();             // возврашает элемент в начале дека
	inline T& back();              // возвращает элемент в конце дека

	inline void push_front(T);     // добавление элемента в начало дека
	inline void push_back(T);      // добавление элемента в конец дека

	inline T& pop_front();         // удаление элемента из начала дека
	inline T& pop_back();          // удаление элемента из конца дека

	inline int size();             // вернет текущий размер дека
	inline int max_size() const;   // вернет максимальный размер дека в одну сторону (относительно начального указателя)

	inline bool empty();           // вернет True, если дек пуст, и False, если дек не пуст

	inline void clear();           // очищает дек, не удаляя элементы, а просто сдвигая указатели

	inline T& operator[](int);     // обращаестя к нужному элементу дека по очереди считая от начала (асимптотика O(1))
	inline T& at(int);             // аналогичен operator[]

	inline T* begin();           // итератор на начало дека
	inline T* end();             // итератор на следующую ячейку за концом дека

	inline void operator=(Deque&); // полное поэлементное копирование

	inline operator int();         // вернет размер
	inline operator bool();        // вернет True, если дек не пуст, и False, если дек пуст
};

// сеттеры
template <class T>
inline void Deque<T>::setStartPtr(T* newStartPtr) { startPtr = newStartPtr; };
template <class T>
inline void Deque<T>::setFrontPtr(T* newFrontPtr) { frontPtr = newFrontPtr; };
template <class T>
inline void Deque<T>::setBackPtr(T* newBackPtr) { backPtr = newBackPtr; };
template <class T>
inline void Deque<T>::setMaxSize(T* newMaxSize) { maxSize = newMaxSize; };

// геттеры
template <class T>
inline T* Deque<T>::getStartPtr() const { return startPtr; };
template <class T>
inline T* Deque<T>::getFrontPtr() const { return frontPtr; };
template <class T>
inline T* Deque<T>::getBackPtr() const { return backPtr; };
template <class T>
inline T* Deque<T>::getMaxSize() const { return maxSize; };

template <class T>  // простой конструктор с указанием наксимального кол-ва элементов, которые будут добавлены в дек
Deque<T>::Deque(int maxLen) : startPtr(new T[maxLen * 2 - 1]),
frontPtr(startPtr + maxLen - 1),
backPtr(startPtr + maxLen - 2),
maxSize(maxLen) {};

template <class T>  // конструктор копирования с полным поэлементым копированием
Deque<T>::Deque(const Deque& copy) : startPtr(new T[copy.max_size() * 2 - 1]),
frontPtr(startPtr + (copy.getFrontPtr() - copy.getStartPtr())),
backPtr(startPtr + (copy.getBackPtr() - copy.getStartPtr())),
maxSize(copy.max_size()) {
	for (int i = copy.getFrontPtr() - copy.getStartPtr(); i <= copy.getBackPtr() - copy.getStartPtr(); ++i)
		startPtr[i] = copy.getStartPtr()[i];
};

template <class T>  // дестркутор с простой очиткой памяти
Deque<T>::~Deque() { delete[] startPtr; };

template <class T>  // вернет текущий размер дека
inline int Deque<T>::size() { return backPtr - frontPtr + 1; }
template <class T>  // вернет максимальный размер дека в одну сторону (относительно начального указателя)
inline int Deque<T>::max_size() const { return maxSize; }

template <class T>  // возврашает элемент в начале дека
inline T& Deque<T>::front() { return *frontPtr; };
template <class T>  // возвращает элемент в конце дека
inline T& Deque<T>::back() { return *backPtr; }

template <class T>  // добавление элемента в начало дека
inline void Deque<T>::push_front(T newElem) { *(--frontPtr) = newElem; };
template <class T>  // добавление элемента в конец дека
inline void Deque<T>::push_back(T newElem) { *(++backPtr) = newElem; };

template <class T>  // удаление элемента из начала дека
inline T& Deque<T>::pop_front() { return *(frontPtr++); };
template <class T>  // удаление элемента из конца дека
inline T& Deque<T>::pop_back() { return *(backPtr--); };

template <class T>  // вернет True, если дек пуст, и False, если дек не пуст
inline bool Deque<T>::empty() { return backPtr < frontPtr; }

template <class T>  // очищает дек, не удаляя элементы, просто сдвигая указатели
inline void Deque<T>::clear() {
	frontPtr = startPtr + maxSize - 1;
	backPtr = startPtr + maxSize - 2;
}

template <class T>  // обращаестя к нужному элементу дека по очереди считая от начала (асимптотика O(1))
inline T& Deque<T>::operator[](int index) { return frontPtr[index]; }
template <class T>  // аналогичен operator[]
inline T& Deque<T>::at(int index) { return frontPtr[index]; }

template <class T>  // полное поэлементное копирование
inline void Deque<T>::operator=(Deque& copy) {
	startPtr = new T[copy.max_size() * 2 - 1];
	frontPtr = startPtr + (copy.getFrontPtr() - copy.getStartPtr());
	backPtr = startPtr + (copy.getBackPtr() - copy.getStartPtr());
	maxSize = copy.max_size();
	for (int i = copy.getFrontPtr() - copy.getStartPtr(); i <= copy.getBackPtr() - copy.getStartPtr(); ++i)
		startPtr[i] = copy.getStartPtr()[i];
};

template <class T>  // итератор на начало дека
inline T* Deque<T>::begin() { return frontPtr; }
template <class T>  // итератор на следующую ячейку за концом дека
inline T* Deque<T>::end() { return backPtr + 1; }

template <class T>  // вернет размер
inline Deque<T>::operator int() { return size(); }
template <class T>  // вернет True, если дек не пуст, и False, если дек пуст
inline Deque<T>::operator bool() { return backPtr >= frontPtr; }