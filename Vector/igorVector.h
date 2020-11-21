#pragma once

template <class T>
class Deque {
	T* startPtr;    // ��������� �� ������ ���������� ������
	T* frontPtr;    // ��������� �� ������ ������� � ����
	T* backPtr;     // ��������� �� ��������� ������ � ����
	int maxSize;    // ������������ ������, ��������� ��� �������� ����

public:
	inline void setStartPtr(T*);   // ������
	inline void setFrontPtr(T*);   // ������
	inline void setBackPtr(T*);    // ������
	inline void setMaxSize(T*);    // ������

	inline T* getStartPtr() const; // ������
	inline T* getFrontPtr() const; // ������
	inline T* getBackPtr() const;  // ������
	inline T* getMaxSize() const;  // ������

	Deque(int);                    // ������� ����������� � ��������� ������������� ���-�� ���������, ������� ����� ��������� � ���
	Deque(const Deque&);           // ����������� ����������� � ������ ����������� ������������
	~Deque();                      // ���������� � ������� ������� ������

	inline T& front();             // ���������� ������� � ������ ����
	inline T& back();              // ���������� ������� � ����� ����

	inline void push_front(T);     // ���������� �������� � ������ ����
	inline void push_back(T);      // ���������� �������� � ����� ����

	inline T& pop_front();         // �������� �������� �� ������ ����
	inline T& pop_back();          // �������� �������� �� ����� ����

	inline int size();             // ������ ������� ������ ����
	inline int max_size() const;   // ������ ������������ ������ ���� � ���� ������� (������������ ���������� ���������)

	inline bool empty();           // ������ True, ���� ��� ����, � False, ���� ��� �� ����

	inline void clear();           // ������� ���, �� ������ ��������, � ������ ������� ���������

	inline T& operator[](int);     // ���������� � ������� �������� ���� �� ������� ������ �� ������ (����������� O(1))
	inline T& at(int);             // ���������� operator[]

	inline T* begin();           // �������� �� ������ ����
	inline T* end();             // �������� �� ��������� ������ �� ������ ����

	inline void operator=(Deque&); // ������ ������������ �����������

	inline operator int();         // ������ ������
	inline operator bool();        // ������ True, ���� ��� �� ����, � False, ���� ��� ����
};

// �������
template <class T>
inline void Deque<T>::setStartPtr(T* newStartPtr) { startPtr = newStartPtr; };
template <class T>
inline void Deque<T>::setFrontPtr(T* newFrontPtr) { frontPtr = newFrontPtr; };
template <class T>
inline void Deque<T>::setBackPtr(T* newBackPtr) { backPtr = newBackPtr; };
template <class T>
inline void Deque<T>::setMaxSize(T* newMaxSize) { maxSize = newMaxSize; };

// �������
template <class T>
inline T* Deque<T>::getStartPtr() const { return startPtr; };
template <class T>
inline T* Deque<T>::getFrontPtr() const { return frontPtr; };
template <class T>
inline T* Deque<T>::getBackPtr() const { return backPtr; };
template <class T>
inline T* Deque<T>::getMaxSize() const { return maxSize; };

template <class T>  // ������� ����������� � ��������� ������������� ���-�� ���������, ������� ����� ��������� � ���
Deque<T>::Deque(int maxLen) : startPtr(new T[maxLen * 2 - 1]),
frontPtr(startPtr + maxLen - 1),
backPtr(startPtr + maxLen - 2),
maxSize(maxLen) {};

template <class T>  // ����������� ����������� � ������ ����������� ������������
Deque<T>::Deque(const Deque& copy) : startPtr(new T[copy.max_size() * 2 - 1]),
frontPtr(startPtr + (copy.getFrontPtr() - copy.getStartPtr())),
backPtr(startPtr + (copy.getBackPtr() - copy.getStartPtr())),
maxSize(copy.max_size()) {
	for (int i = copy.getFrontPtr() - copy.getStartPtr(); i <= copy.getBackPtr() - copy.getStartPtr(); ++i)
		startPtr[i] = copy.getStartPtr()[i];
};

template <class T>  // ���������� � ������� ������� ������
Deque<T>::~Deque() { delete[] startPtr; };

template <class T>  // ������ ������� ������ ����
inline int Deque<T>::size() { return backPtr - frontPtr + 1; }
template <class T>  // ������ ������������ ������ ���� � ���� ������� (������������ ���������� ���������)
inline int Deque<T>::max_size() const { return maxSize; }

template <class T>  // ���������� ������� � ������ ����
inline T& Deque<T>::front() { return *frontPtr; };
template <class T>  // ���������� ������� � ����� ����
inline T& Deque<T>::back() { return *backPtr; }

template <class T>  // ���������� �������� � ������ ����
inline void Deque<T>::push_front(T newElem) { *(--frontPtr) = newElem; };
template <class T>  // ���������� �������� � ����� ����
inline void Deque<T>::push_back(T newElem) { *(++backPtr) = newElem; };

template <class T>  // �������� �������� �� ������ ����
inline T& Deque<T>::pop_front() { return *(frontPtr++); };
template <class T>  // �������� �������� �� ����� ����
inline T& Deque<T>::pop_back() { return *(backPtr--); };

template <class T>  // ������ True, ���� ��� ����, � False, ���� ��� �� ����
inline bool Deque<T>::empty() { return backPtr < frontPtr; }

template <class T>  // ������� ���, �� ������ ��������, ������ ������� ���������
inline void Deque<T>::clear() {
	frontPtr = startPtr + maxSize - 1;
	backPtr = startPtr + maxSize - 2;
}

template <class T>  // ���������� � ������� �������� ���� �� ������� ������ �� ������ (����������� O(1))
inline T& Deque<T>::operator[](int index) { return frontPtr[index]; }
template <class T>  // ���������� operator[]
inline T& Deque<T>::at(int index) { return frontPtr[index]; }

template <class T>  // ������ ������������ �����������
inline void Deque<T>::operator=(Deque& copy) {
	startPtr = new T[copy.max_size() * 2 - 1];
	frontPtr = startPtr + (copy.getFrontPtr() - copy.getStartPtr());
	backPtr = startPtr + (copy.getBackPtr() - copy.getStartPtr());
	maxSize = copy.max_size();
	for (int i = copy.getFrontPtr() - copy.getStartPtr(); i <= copy.getBackPtr() - copy.getStartPtr(); ++i)
		startPtr[i] = copy.getStartPtr()[i];
};

template <class T>  // �������� �� ������ ����
inline T* Deque<T>::begin() { return frontPtr; }
template <class T>  // �������� �� ��������� ������ �� ������ ����
inline T* Deque<T>::end() { return backPtr + 1; }

template <class T>  // ������ ������
inline Deque<T>::operator int() { return size(); }
template <class T>  // ������ True, ���� ��� �� ����, � False, ���� ��� ����
inline Deque<T>::operator bool() { return backPtr >= frontPtr; }