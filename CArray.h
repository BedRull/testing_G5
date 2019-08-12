#pragma once

template <typename TData>
class CArray
{
public:

	// default cons
	CArray();

	// cons with size
	CArray(
		unsigned int _size
	);

	// copy cons
	CArray(
		const CArray& _array
	);

	// destructor
	~CArray();

	// push element at the end of array
	void push_back(
		const TData& _value
	);

	// insert at given position
	void insert(
		unsigned int _index,
		const TData& _value
	);

	void swap(
		size_t _idx1,
		size_t _idx2
	);

	// remove element by index
	void erase(
		unsigned int _index
	);

	// clear array
	void clear();

	// check if empty
	bool is_empty() const;

	// check if array sorted
	bool is_sorted() const;

	// get size of array
	unsigned int size() const;

	// get ptr to array
	TData* get_array() const;

	// get element by index
	TData& operator[] (
		unsigned int _index
	);

protected:	// attributes

	// array size
	unsigned int m_size;

	// pointer to array location
	TData* m_array;
};

template <typename TData>
CArray<TData>::~CArray()
{
  if(!is_empty())
    delete[] m_array;
}

template <typename TData>
CArray<TData>::CArray() :
  m_size(0),
  m_array(nullptr)
{
}

template <typename TData>
CArray<TData>::CArray(
	unsigned int _size
) :
  m_size(_size)
{
  // initialize every value with type default constructor
  for(size_t i = 0; i < _size; ++i)
	m_array[i] = TData();
}

template <typename TData>
CArray<TData>::CArray(
	const CArray& _array
) :
	m_size(_array.m_size),
	m_array(_array.m_array? new TData[m_size]: TData())
{
  // check if array even have elements
  if(_array.m_array)
  {
    // copy each value from given array to member of the class
    for(size_t i = 0; i < m_size; ++i)
      m_array[i] = _array.m_array[i];
  }
}

template <typename TData>
void CArray<TData>::push_back(
	const TData& _value
)
{
  // create new array with bigger size
  TData* ptr = new TData[m_size + 1];
  
  // copy each value from old to new array
  for(size_t i = 0; i < m_size; ++i)
  	ptr[i] = m_array[i];
  
  // move new value at the end
  ptr[m_size] = _value;
  
  // empty previous memory 
  if(!is_empty())
  	delete[] m_array;
  
  // assign old pointer to new array address
  m_array = ptr;
  
  // increment array size
  ++m_size;
}

template <typename TData>
void CArray<TData>::insert(
	unsigned int _index,
	const TData& _value
)
{
  // create new array
  TData* ptr = new TData[m_size + 1];
  
  // copy elements before index to new array
  for(size_t i = 0; i < _index; ++i)
  	ptr[i] = m_array[i];
  
  // insert new value
  ptr[_index] = _value;
  
  // copy remained elements
  for(size_t i = _index; i < m_size; ++i)
  	ptr[i + 1] = m_array[i];
  
  // free previous memory
  if(!is_empty())
  	delete[] m_array;
  
  // assign new address to class member
  m_array = ptr;
  
  // increment array size
  ++m_size;
}

template <typename TData>
void CArray<TData>::swap(
	size_t _idx1,
	size_t _idx2
)
{
  TData temp = m_array[_idx1];
  m_array[_idx1] = m_array[_idx2];
  m_array[_idx2] = temp;
}

template <typename TData>
void CArray<TData>::erase(
	unsigned int _index
)
{
  // check are there any elements
  if(is_empty())
  	return;
  
  --m_size;
  
  // create new array
  TData* ptr = new TData[m_size];
  
  // copy all values except value at index position
  for(size_t i = 0; i < _index; ++i)
  	ptr[i] = m_array[i];
  
  for(size_t i = _index; i < m_size; ++i)
  	ptr[i] = m_array[i + 1];
  
  delete[] m_array;
  
  m_array = ptr;
}

template <typename TData>
void CArray<TData>::clear()
{
  // check are there any elements
  if(is_empty())
  	return;
  
  delete[] m_array;
  
  m_size = 0;
}

template <typename TData>
bool CArray<TData>::is_empty() const
{
  return !m_size;
}

template <typename TData>
bool CArray<TData>::is_sorted() const
{
  for(size_t i = 0; i < m_size - 1; ++i)
  	if(m_array[i] > m_array[i + 1])
      return false;
  
  return true;
}

template <typename TData>
unsigned int CArray<TData>::size() const
{
  return m_size;
}

template <typename TData>
TData* CArray<TData>::get_array() const
{
  return m_array;
}

template <typename TData>
TData& CArray<TData>::operator[](
	unsigned int _index
)
{
  return m_array[_index];
}
