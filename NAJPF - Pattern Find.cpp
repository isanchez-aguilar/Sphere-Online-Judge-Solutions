/*
*	User: Isanchez_Aguilar
*	Problem: SPOJ NAJPF - Pattern Find
*/
#include <bits/stdc++.h>

using namespace std;
using Long = long long;

/*
** Complexity: O(|p| + |t|)
** Return vector of indexs where pattern
** appears in text.
*/
vector<int> rabinKarp(const string& text, const string& pattern)
{
	const int p = 173ll; 
	const int m = 1000000021ll;
	
	int tLen = text.length();
	int sLen = pattern.length();

	vector<Long> pPow(max(sLen, tLen)); 
	pPow[0] = 1; 
	
	for (int i = 1; i < pPow.size(); ++i) 
		pPow[i] = (pPow[i - 1] * p) % m;

	vector<Long> hashText(tLen + 1);

	for (int i = 0; i < tLen; ++i)
		hashText[i + 1] = (hashText[i] + (text[i] - 'a' + 1) * pPow[i]) % m; 
	
	Long hashPattern = 0; 

	for (int i = 0; i < sLen; ++i) 
		hashPattern = (hashPattern + (pattern[i] - 'a' + 1) * pPow[i]) % m; 

	vector<int> occurences;
	
	for (int i = 0; i + sLen - 1 < tLen; ++i)
	{
		Long currHash = (hashText[i + sLen] + m - hashText[i]) % m; 
		
		if (currHash == hashPattern * pPow[i] % m)
			occurences.push_back(i);
	}

	return occurences;
}
int main(void)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int testCases;
	cin >> testCases;

	while (testCases--)
	{
		string t, p;
		cin >> t >> p;

		vector<int> appearances = rabinKarp(t, p);

		if (appearances.size() == 0)
			cout << "Not Found\n";
		else
		{
			cout << appearances.size() << "\n";

			cout << appearances[0] + 1;

			for (int i = 1; i < appearances.size(); ++i)
				cout << " " << appearances[i] + 1;

			cout << "\n";
		}

		if (testCases)
			cout << "\n";
	}

	return 0;
}