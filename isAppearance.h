#include <algorithm>
#include <vector>

using namespace std;

template<typename T>
bool isAppearance(T i, vector <T> X)
{
	int pos = lower_bound(X.begin(), X.end(), i) - X.begin();
	if (pos == X.size()) return false;
	if (X[pos] == i) return true;
	return false;
}
