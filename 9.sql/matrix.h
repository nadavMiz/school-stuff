#ifndef MATRIX_H
#define MATRIX_H

template <class T>
class myArray
{
	public:
		myArray(T* _data);
		T& operator[](int _index);
		
	private:
		T* m_data;
};

/*--------------------------------------------------*/

template <class Row, class Col>
class Matrix
{
public:
	template <class T>
	Matrix(T* _data);

private:
	/* data */
	template <class T> myArray<T> m_data;
};

template <class Row, class Col>
template <class T>
inline Matrix::Matrix(T* _data)
{
	template<>
	m_data = _data;
}


#endif /* MATRIX_H */

