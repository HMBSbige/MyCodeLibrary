#include <iostream>
#include <regex>
#include <array>

uint64_t ShareLink2MatchID(std::string sharecode)
{
	sharecode = regex_replace(sharecode, std::regex("CSGO|-"), "");
	sharecode = std::string(sharecode.rbegin(), sharecode.rend());

	std::string dictionary("ABCDEFGHJKLMNOPQRSTUVWXYZabcdefhijkmnopqrstuvwxyz23456789");
	std::array<uint8_t, 18> result = {};

	for (char cur_char : sharecode)
	{
		std::array<uint8_t, 18> tmp = {};

		const int addval = static_cast<int>(dictionary.find(cur_char));
		int carry;
		int v = 0;

		for (int t = 17; t >= 0; t--) {
			carry = 0;
			for (int s = t; s >= 0; s--) {
				if (t - s == 0) {
					v = tmp[s] + result[t] * 57;
				}
				else {
					v = 0;
				}
				v = v + carry;
				carry = v >> 8;
				tmp[s] = v & 0xFF;
			}
		}

		result = tmp;
		carry = 0;

		for (int t = 17; t >= 0; t--) {
			if (t == 17) {
				v = result[t] + addval;
			}
			else {
				v = result[t];
			}
			v = v + carry;
			carry = v >> 8;
			result[t] = v & 0xFF;
		}
	}

	uint64_t matchid = *reinterpret_cast<uint64_t*>(result.data());
	//uint64_t outcomeId = *reinterpret_cast<uint64_t*>(result.data() + 8);
	//uint16_t tokenId = *reinterpret_cast<uint16_t*>(result.data() + 16);
	return matchid;
}
int main()
{
	std::cout << (ShareLink2MatchID("CSGO-PTAJb-C62Xe-ZEzAW-PXxf6-DMhWA") == 3252310514700648710?"True":"False" )<< std::endl;
	return 0;
}