void print(const std::vector<double>& v)
{
	std::cout << "{ ";
	for (size_t i(0); i < v.size(); ++i)
	{
		std::cout << v[i];
		if (i != v.size() - 1)
		{
			std::cout << ", ";
		}
	}

	std::cout << " }\n";
}
