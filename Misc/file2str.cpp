string textfile2str(const string& PATH)
{
	ifstream file(PATH);
	ostringstream oss;
	oss << file.rdbuf();
	file.close();
	return oss.str();
}
void str2file(const string& str,const string& PATH)
{
	ofstream file(PATH, std::ios::trunc);
	file << str;
	file.close();
}