

using namespace std;
long long convert(char* ex)
{
	int n = strlen(ex);
	long long num = 0;
	for (int i = 0; i < n; i++)
	{
		if (ex[i] >= '0' and ex[i] <= '9')
			num = num * 10 + (ex[i] - '0');
		else break;
	}
	return num;
}