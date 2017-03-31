// the rounding follows Banker's Rule
//http://stackoverflow.com/questions/17035464
inline int32_t double2int(double d)
{
	d += 6755399441055744.0;// 1.5 * 2^52
	return reinterpret_cast<int32_t&>(d);
}
inline int64_t double2int64(double d)//d<1125899906842623
{
	d += 6755399441055744.0;// 1.5 * 2^52
	int64_t i=reinterpret_cast<int64_t&>(d);
	i <<= 13;
	i >>= 13;
	return i;
}