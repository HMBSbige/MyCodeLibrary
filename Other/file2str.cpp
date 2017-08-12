string textfile2str(string PATH)
{
	ifstream file(PATH);
	ostringstream oss;
	oss << file.rdbuf();
	file.close();
	return oss.str();
}
void str2file(string str,string PATH)
{
	ofstream file(PATH);
	file << str;
	file.close();
}