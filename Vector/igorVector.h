#pragma once

template <class T>
class Vector {
	T* startPtr;    // ��������� �� ������ ���������� ������
	T* frontPtr;    // ��������� �� ������ ������� � ����
	T* backPtr;     // ��������� �� ��������� ������ � ����
	int maxSize;    // ������������ ������, ��������� ��� �������� ����

public:
	inline void setStartPtr(T*);   // ������
	inline void setFrontPtr(T*);   // ������
	inline void setBackPtr(T*);    // ������
	inline void setMaxSize(T*);    // ������

	inline T* getStartPtr();	   // ������
	inline T* getFrontPtr();       // ������
	inline T* getBackPtr();        // ������
	inline T* getMaxSize();        // ������

	Vector(int);                    // ������� ����������� � ��������� ������������� ���-�� ���������, ������� ����� ��������� � ���
	Vector(const Vector& copy);
	Vector(const Deque&);           // ����������� ����������� � ������ ����������� ������������
	~Vector();                      // ���������� � ������� ������� ������

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

	inline void operator=(Vector&); // ������ ������������ �����������

	inline operator int();         // ������ ������
	inline operator bool();        // ������ True, ���� ��� �� ����, � False, ���� ��� ����
};

// �������
template <class T>
inline void Vector<T>::setStartPtr(T* newStartPtr) { startPtr = newStartPtr; };
template <class T>
inline void Vector<T>::setFrontPtr(T* newFrontPtr) { frontPtr = newFrontPtr; };
template <class T>
inline void Vector<T>::setBackPtr(T* newBackPtr) { backPtr = newBackPtr; };
template <class T>
inline void Vector<T>::setMaxSize(T* newMaxSize) { maxSize = newMaxSize; };

// �������
template <class T>
inline T* Vector<T>::getStartPtr() { return startPtr; };
template <class T>
inline T* Vector<T>::getFrontPtr() { return frontPtr; };
template <class T>
inline T* Vector<T>::getBackPtr() { return backPtr; };
template <class T>
inline T* Vector<T>::getMaxSize() { return maxSize; };

template <class T>  // ������� ����������� � ��������� ������������� ���-�� ���������, ������� ����� ��������� � ���
Vector<T>::Vector(int maxLen) : startPtr(new T[maxLen * 2 - 1]),
frontPtr(startPtr + maxLen - 1),
backPtr(startPtr + maxLen - 2),
maxSize(maxLen) {};

template <class T>  // ����������� ����������� � ������ ����������� ������������
Vector<T>::Vector(const Vector& copy) : startPtr(new T[copy.max_size() * 2 - 1]),
frontPtr(startPtr + (copy.getFrontPtr() - copy.getStartPtr())),
backPtr(startPtr + (copy.getBackPtr() - copy.getStartPtr())),
maxSize(copy.max_size()) {
	for (int i = copy.getFrontPtr() - copy.getStartPtr(); i <= copy.getBackPtr() - copy.getStartPtr(); ++i)
		startPtr[i] = copy.getStartPtr()[i];
};

template <class T>  // ���������� � ������� ������� ������
Vector<T>::~Vector() { delete[] startPtr; };

template <class T>  // ������ ������� ������ ����
inline int Vector<T>::size() { return backPtr - frontPtr + 1; }
template <class T>  // ������ ������������ ������ ���� � ���� ������� (������������ ���������� ���������)
inline int Vector<T>::max_size() const { return maxSize; }

template <class T>  // ���������� ������� � ������ ����
inline T& Vector<T>::front() { return *frontPtr; };
template <class T>  // ���������� ������� � ����� ����
inline T& Vector<T>::back() { return *backPtr; }

template <class T>  // ���������� �������� � ������ ����
inline void Vector<T>::push_front(T newElem) { *(--frontPtr) = newElem; };
template <class T>  // ���������� �������� � ����� ����
inline void Vector<T>::push_back(T newElem) { *(++backPtr) = newElem; };

template <class T>  // �������� �������� �� ������ ����
inline T& Vector<T>::pop_front() { return *(frontPtr++); };
template <class T>  // �������� �������� �� ����� ����
inline T& Vector<T>::pop_back() { return *(backPtr--); };

template <class T>  // ������ True, ���� ��� ����, � False, ���� ��� �� ����
inline bool Vector<T>::empty() { return backPtr < frontPtr; }

template <class T>  // ������� ���, �� ������ ��������, ������ ������� ���������
inline void Vector<T>::clear() {
	frontPtr = startPtr + maxSize - 1;
	backPtr = startPtr + maxSize - 2;
}

template <class T>  // ���������� � ������� �������� ���� �� ������� ������ �� ������ (����������� O(1))
inline T& Vector<T>::operator[](int index) { return frontPtr[index]; }
template <class T>  // ���������� operator[]
inline T& Vector<T>::at(int index) { return frontPtr[index]; }

template <class T>  // ������ ������������ �����������
inline void Vector<T>::operator=(Vector& copy) {
	startPtr = new T[copy.max_size() * 2 - 1];
	frontPtr = startPtr + (copy.getFrontPtr() - copy.getStartPtr());
	backPtr = startPtr + (copy.getBackPtr() - copy.getStartPtr());
	maxSize = copy.max_size();
	for (int i = copy.getFrontPtr() - copy.getStartPtr(); i <= copy.getBackPtr() - copy.getStartPtr(); ++i)
		startPtr[i] = copy.getStartPtr()[i];
};

template <class T>  // �������� �� ������ ����
inline T* Vector<T>::begin() { return frontPtr; }
template <class T>  // �������� �� ��������� ������ �� ������ ����
inline T* Vector<T>::end() { return backPtr + 1; }

template <class T>  // ������ ������
inline Vector<T>::operator int() { return size(); }
template <class T>  // ������ True, ���� ��� �� ����, � False, ���� ��� ����
inline Vector<T>::operator bool() { return backPtr >= frontPtr; }