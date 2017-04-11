typedef int64_t ll;
ll binary_search(std::vector<ll> array,ll value)
{
	ll left = 0;
	ll right = array.size() - 1;//ll right = array.size();

	while (left <= right)//while(left < right) 
	{
		ll middle = left + ((right - left) >> 1);  

		if (array[middle]>value)
		{
			right = middle - 1;//right = mid  
		}
		else if (array[middle]<value)
		{
			left = middle + 1;
		}
		else
			return middle;
	}
	return -1;
}