/*
*	User: Isanchez_Aguilar
*	Problem: SPOJ NHAY - A Needle in the Haystack
*/
#include <bits/stdc++.h>

#define MAX_POW 10000001
#define AMOUNT_PRIMES 2

using namespace std;
using Number = long long;
using HashValue = tuple<Number, Number, Number>;

const Number hashP[] = {173ll, 151ll, 137ll};
const Number hashM[] = {1000000021ll, 100000007ll, 1000000009ll};

vector<Number> powersP[AMOUNT_PRIMES];

inline void preComputeHashPowers()
{
	powersP[0] = vector<Number>(MAX_POW);
	powersP[1] = vector<Number>(MAX_POW);

	powersP[0][0] = 1;
	powersP[1][0] = 1;

	for (int i = 1; i < MAX_POW; ++i)
	{
		powersP[0][i] = powersP[0][i - 1] * hashP[0];
		powersP[1][i] = powersP[1][i - 1] * hashP[1];

		powersP[0][i] %= hashM[0];
		powersP[1][i] %= hashM[1];
	}

	return;
}

inline Number getCode(const char c)
{
	Number code = Number(c - 'A' + 1);

	if (c == tolower(c))
		code -= 6;

	return code;
}

inline Number modHash(const Number& p, const Number& m)
{
	return (p % m + m) % m;
}

class HashString {
public:
	int length;
	vector<Number> prefixXor;
	vector<Number> prefix[2];

	HashString() {}

	HashString(const string& s):length(s.length())
	{
		prefixXor.resize(length);
		prefix[0].resize(length);
		prefix[1].resize(length);

		Number charVal = getCode(s[0]);
		
		prefixXor[0] = charVal;
		prefix[0][0] = charVal;
		prefix[1][0] = charVal;


		for (int i = 1; i < length; ++i)
		{
			charVal = getCode(s[i]);

			prefixXor[i] = prefixXor[i - 1] ^ charVal;
			prefix[0][i] = prefix[0][i - 1] * hashP[0] + charVal;
			prefix[1][i] = prefix[1][i - 1] * hashP[1] + charVal;

			prefix[0][i] %= hashM[0];
			prefix[1][i] %= hashM[1];
		}
	}

	inline static HashValue getHash(const string& s)
	{
		const int length = s.length();
		Number charVal = getCode(s[0]);
		
		Number prefixXor = charVal;
		Number prefix1 = charVal;
		Number prefix2 = charVal;


		for (int i = 1; i < length; ++i)
		{
			charVal = getCode(s[i]);

			prefixXor ^= charVal;
			prefix1 = prefix1 * hashP[0] + charVal;
			prefix2 = prefix2 * hashP[1] + charVal;

			prefix1 %= hashM[0];
			prefix2 %= hashM[1];
		}

		return HashValue(prefix1, prefix2, prefixXor);
	}

	inline HashValue getHash() const
	{
		return HashValue(prefix[0][length - 1], prefix[1][length - 1], prefixXor[length - 1]);
	}

	inline HashValue getSubstringHash(const int i, const int j) const
	{
		HashValue hash;
		Number firstHash = prefix[0][j];
		Number secondHash = prefix[1][j];
		Number thirdHash = prefixXor[j];

		if (i > 0)
		{
			firstHash -= (powersP[0][j - i + 1] * prefix[0][i - 1]  % hashM[0]);
			secondHash -= (powersP[1][j - i + 1] * prefix[1][i - 1]  % hashM[1]);
			thirdHash ^= prefixXor[i - 1];

			firstHash = modHash(firstHash, hashM[0]);
			secondHash = modHash(secondHash, hashM[1]);
		}

		return HashValue(firstHash, secondHash, thirdHash);
	}

	inline bool operator==(const HashString& a)
	{
		return getHash() == a.getHash();
	}
};

int main(void)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	preComputeHashPowers();

	while (cin >> n)
	{
		string s, w;
		cin >> w >> s;
		
		const int length = s.length();

		if (n <= length)
		{
			HashString sHash(s);

			const int wLength = w.length();
			HashValue wHash = HashString::getHash(w);

			for (int i = 0; i < length - wLength + 1; ++i)
			{
				if (wHash == sHash.getSubstringHash(i, i + wLength - 1))
					cout << i << "\n";
			}
			cout << "\n";
		}

	}
	return 0;
}