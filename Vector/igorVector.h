#pragma once

template <class T>
class Vector {
	T* startPtr;    // указывает на начало выделенной памяти
	T* frontPtr;    // указывает на первый элемент в деке
	T* backPtr;     // указывает на последний элемет в деке
	int maxSize;    // максимальный размер, указанный при создании дека

public:
	inline void setStartPtr(T*);   // сеттер
	inline void setFrontPtr(T*);   // сеттер
	inline void setBackPtr(T*);    // сеттер
	inline void setMaxSize(T*);    // сеттер

	inline T* getStartPtr();	   // геттер
	inline T* getFrontPtr();       // геттер
	inline T* getBackPtr();        // геттер
	inline T* getMaxSize();        // геттер

	Vector(int);                    // простой конструктор с указанием наксимального кол-ва элементов, которые будут добавлены в дек
	Vector(const Vector& copy);
	Vector(const Deque&);           // конструктор копирования с полным поэлементым копированием
	~Vector();                      // дестркутор с простой очиткой памяти

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

	inline void operator=(Vector&); // полное поэлементное копирование

	inline operator int();         // вернет размер
	inline operator bool();        // вернет True, если дек не пуст, и False, если дек пуст
};

// сеттеры
template <class T>
inline void Vector<T>::setStartPtr(T* newStartPtr) { startPtr = newStartPtr; };
template <class T>
inline void Vector<T>::setFrontPtr(T* newFrontPtr) { frontPtr = newFrontPtr; };
template <class T>
inline void Vector<T>::setBackPtr(T* newBackPtr) { backPtr = newBackPtr; };
template <class T>
inline void Vector<T>::setMaxSize(T* newMaxSize) { maxSize = newMaxSize; };

// геттеры
template <class T>
inline T* Vector<T>::getStartPtr() { return startPtr; };
template <class T>
inline T* Vector<T>::getFrontPtr() { return frontPtr; };
template <class T>
inline T* Vector<T>::getBackPtr() { return backPtr; };
template <class T>
inline T* Vector<T>::getMaxSize() { return maxSize; };

template <class T>  // простой конструктор с указанием наксимального кол-ва элементов, которые будут добавлены в дек
Vector<T>::Vector(int maxLen) : startPtr(new T[maxLen * 2 - 1]),
frontPtr(startPtr + maxLen - 1),
backPtr(startPtr + maxLen - 2),
maxSize(maxLen) {};

template <class T>  // конструктор копирования с полным поэлементым копированием
Vector<T>::Vector(const Vector& copy) : startPtr(new T[copy.max_size() * 2 - 1]),
frontPtr(startPtr + (copy.getFrontPtr() - copy.getStartPtr())),
backPtr(startPtr + (copy.getBackPtr() - copy.getStartPtr())),
maxSize(copy.max_size()) {
	for (int i = copy.getFrontPtr() - copy.getStartPtr(); i <= copy.getBackPtr() - copy.getStartPtr(); ++i)
		startPtr[i] = copy.getStartPtr()[i];
};

template <class T>  // дестркутор с простой очиткой памяти
Vector<T>::~Vector() { delete[] startPtr; };

template <class T>  // вернет текущий размер дека
inline int Vector<T>::size() { return backPtr - frontPtr + 1; }
template <class T>  // вернет максимальный размер дека в одну сторону (относительно начального указателя)
inline int Vector<T>::max_size() const { return maxSize; }

template <class T>  // возврашает элемент в начале дека
inline T& Vector<T>::front() { return *frontPtr; };
template <class T>  // возвращает элемент в конце дека
inline T& Vector<T>::back() { return *backPtr; }

template <class T>  // добавление элемента в начало дека
inline void Vector<T>::push_front(T newElem) { *(--frontPtr) = newElem; };
template <class T>  // добавление элемента в конец дека
inline void Vector<T>::push_back(T newElem) { *(++backPtr) = newElem; };

template <class T>  // удаление элемента из начала дека
inline T& Vector<T>::pop_front() { return *(frontPtr++); };
template <class T>  // удаление элемента из конца дека
inline T& Vector<T>::pop_back() { return *(backPtr--); };

template <class T>  // вернет True, если дек пуст, и False, если дек не пуст
inline bool Vector<T>::empty() { return backPtr < frontPtr; }

template <class T>  // очищает дек, не удаляя элементы, просто сдвигая указатели
inline void Vector<T>::clear() {
	frontPtr = startPtr + maxSize - 1;
	backPtr = startPtr + maxSize - 2;
}

template <class T>  // обращаестя к нужному элементу дека по очереди считая от начала (асимптотика O(1))
inline T& Vector<T>::operator[](int index) { return frontPtr[index]; }
template <class T>  // аналогичен operator[]
inline T& Vector<T>::at(int index) { return frontPtr[index]; }

template <class T>  // полное поэлементное копирование
inline void Vector<T>::operator=(Vector& copy) {
	startPtr = new T[copy.max_size() * 2 - 1];
	frontPtr = startPtr + (copy.getFrontPtr() - copy.getStartPtr());
	backPtr = startPtr + (copy.getBackPtr() - copy.getStartPtr());
	maxSize = copy.max_size();
	for (int i = copy.getFrontPtr() - copy.getStartPtr(); i <= copy.getBackPtr() - copy.getStartPtr(); ++i)
		startPtr[i] = copy.getStartPtr()[i];
};

template <class T>  // итератор на начало дека
inline T* Vector<T>::begin() { return frontPtr; }
template <class T>  // итератор на следующую ячейку за концом дека
inline T* Vector<T>::end() { return backPtr + 1; }

template <class T>  // вернет размер
inline Vector<T>::operator int() { return size(); }
template <class T>  // вернет True, если дек не пуст, и False, если дек пуст
inline Vector<T>::operator bool() { return backPtr >= frontPtr; }