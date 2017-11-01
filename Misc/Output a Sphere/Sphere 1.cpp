for (auto y = 1.0; y >= -1.0; y -= 0.05)
{
	for (auto x = -1.0; x <= 1.0; x += 0.025)
		if (x * x + y * y > 1.0)
			std::cout << "M";
		else
			std::cout << "@@%#*+=;:. "[static_cast<int>(((x + y + sqrt(1 - (x * x + y * y))) * sqrt(3) / 3 + 1) * 5.0f + 0.5f)];
		
	std::cout << std::endl;
}