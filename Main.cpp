#include "CArray.h"
#include <time.h>
#include <iostream>
#include <cstdlib> // contains rand()
#include <string>


template <typename T>
void print_all(
	T* _ptr,
	size_t _size
)
{
  if(!_size)
  {
  	std::cout << "The array is empty." << std::endl;
  	return;
  }
  
  for(size_t i = 0; i < _size; ++i)
  	std::cout << _ptr[i] << ' ';
  
  std::cout << std::endl;
};

std::string gen_word()
{
  size_t len = 3 + rand() % 5;
  std::string word;
  
  for(size_t i = 0; i < len; ++i)
  	word += 97 + rand() % 26;			// narrow range to English alphabet letters in lowercase
  
  return word;
};

template <typename T>
void quick_sort(
	T* _ptr,
	size_t _start,
	size_t _end
)
{
  if(_start == _end)
  	return;
  
  size_t left = _start;
  size_t right = _end;
  bool left_to_right = false;
  
  while(left != right)
  {	
  	if(_ptr[left] > _ptr[right])
  	{	
	  T _temp = _ptr[left];
	  _ptr[left] = _ptr[right];
	  _ptr[right] = _temp;
	  left_to_right = !left_to_right;
  	}
  
  	if(left_to_right)
  	  ++left;
  	else
  	  --right;
  }
  
  if(right == _end)
  	return;
  
  quick_sort(_ptr, 0, right);
  quick_sort(_ptr, right + 1, _end);
}


int main()
{
  srand(time(nullptr));
  
  // int testing
  std::cout << "Int testing" << std::endl;
  
  CArray<int> int_array;
  
  // random number
  for(size_t i = 0; i < 20; ++i)
  	int_array.push_back(rand() % 201);
  
  std::cout << "(1) ";
  print_all(int_array.get_array(), int_array.size());
  
  // sort array
  quick_sort(int_array.get_array(), 0, int_array.size() - 1);
  
  std::cout << "(2) ";
  print_all(int_array.get_array(), int_array.size());
  
  // remove every 2 element
  for(size_t i = 1; i < int_array.size(); ++i)		// increment on 1 because array moves left
  	int_array.erase(i);
  
  std::cout << "(3) ";
  print_all(int_array.get_array(), int_array.size());
  
  // random value at random position
  for(size_t i = 0; i < 10; ++i)
  	int_array.insert(rand() % int_array.size(), rand() % 101);
  
  std::cout << "(4) ";
  print_all(int_array.get_array(), int_array.size());
  
  // clear the array
  int_array.clear();
  
  std::cout << "(5) ";
  print_all(int_array.get_array(), int_array.size());
  
  // string testing
  std::cout << std::endl << "String testing" << std::endl;
  
  CArray <std::string> str_array;
  
  // push back 15 random words
  for(size_t i = 0; i < 15; ++i)
  	str_array.push_back(gen_word());
  
  std::cout << "(1) ";
  print_all(str_array.get_array(), str_array.size());
  
  // sort by string length using selection sort
  for(size_t j = 0; j < str_array.size(); ++j)
  {
  	size_t max = 0;
  	size_t idx = 0;
  	size_t curr_step = str_array.size() - j;
  
  	for(size_t i = 0; i < curr_step; ++i)
  	{
  	  if(str_array[i].length() > max)
  	  {
  	  	max = str_array[i].length();
  	  	idx = i;
  	  }
  	}
  
  	str_array.swap(idx, curr_step - 1);
  }
  
  std::cout << "(2) ";
  print_all(str_array.get_array(), str_array.size());
  
  // remove all words containing any of a,b,c,d,e letters
  for(int i = str_array.size() - 1; i >= 0; --i)
  	if(str_array[i].find_first_of("abcde") != std::string::npos)
  	  str_array.erase(i);
  
  std::cout << "(3) ";
  print_all(str_array.get_array(), str_array.size());
  
  // insert 3 words at random position
  for(size_t i = 0; i < 3; ++i)
	  str_array.insert(rand() % str_array.size(), gen_word());

  std::cout << "(4) ";
  print_all(str_array.get_array(), str_array.size());
  
  return 0;
}