#include <iostream>
#include <climits>

unsigned int add_checksum(unsigned int n);
void add_checksum(unsigned int array[], std::size_t capacity);
bool verify_checksum(unsigned int n);
unsigned int remove_checksum(unsigned int n);
void remove_checksum(unsigned int array[], std::size_t capacity);

unsigned int add_checksum(unsigned int n)
{
	if (n > 99999999)
	{
		return UINT_MAX;
	}
	int list_of_nums[8];
	int l = n;
	int new_number{0};
	int total_sum{0};
	int checksum{0};

	for (int i = 0; i < 8; i++)
	{
		list_of_nums[i] = n % 10;
		n /= 10;
	}

	for (int k{0}; k < 8; k++)
	{
		new_number = 0;
		if ((k % 2) == 0)
		{
			if ((list_of_nums[k] * 2) >= 10)
			{
				new_number += (list_of_nums[k] * 2) % 10;
				new_number += ((list_of_nums[k] * 2) / 10) % 10;
				list_of_nums[k] = new_number;
			}
			else
			{
				list_of_nums[k] *= 2;
			}
		}
	}

	for (int i{0}; i < 8; i++)
	{
		total_sum += list_of_nums[i];
	}

	total_sum *= 9;
	total_sum %= 10;
	checksum = (l * 10) + total_sum;

	return checksum;
}
bool verify_checksum(unsigned int n)
{
	if (n > 999999999){
		return false;
	}
	int d = n % 10;
	int take_over_n = n;
	int remove_value = (n % 10);
	int compare_num = add_checksum((n - remove_value) / 10);

	if (compare_num == take_over_n)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void add_checksum(unsigned int array[], std::size_t capacity)
{
	for (int i = 0; i < capacity; i++)
	{
		array[i] = add_checksum(array[i]);
	}
}
unsigned int remove_checksum(unsigned int n)
{
	// 
	int remove_value{0};
	if (n > 999999999)
	{
		return UINT_MAX;
	}else if (verify_checksum(n) == false)
	{
		return UINT_MAX;
	}
	
	
	remove_value = (n % 10);
	n = (n - remove_value) / 10;

	return n;
}
void remove_checksum(unsigned int array[], std::size_t capacity)
{

	for (int i = 0; i < capacity; i++)
	{
		array[i] = remove_checksum(array[i]);
	}
}

#ifndef MARMOSET_TESTING
int main();
#endif

#ifndef MARMOSET_TESTING
int main()
{

	unsigned int value_to_protect{21352411};
	add_checksum(value_to_protect);

	unsigned int protected_value = add_checksum(value_to_protect);
	std::cout << "The value " << value_to_protect
		<< " with the checksum added is " << protected_value
		<< "." << std::endl;

	if (verify_checksum(protected_value))
	{
		std::cout << "The checksum is valid." << std::endl;
	}
	else   {
		std::cout << "The checksum is invalid." << std::endl;
	}
	const std::size_t QTY_VALUES {3};
	unsigned int value_series[QTY_VALUES] {20201122, 20209913, 20224012};

	add_checksum(value_series, QTY_VALUES);
	std::cout << "Series with checksums added: ";
	for (std::size_t series_index {0};
		series_index < QTY_VALUES; series_index++)
	{
		std::cout << value_series[series_index] << " ";
	}

	std::cout << std::endl;
	return 0;
}
#endif