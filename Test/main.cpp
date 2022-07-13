#include <iostream>
#include <cstdint>

using namespace std;

static const int64_t COIN = 100000000;
int nBestHeight = 1000;

int64_t GetBlockValue(int64_t nFees)
{
	int64_t nSubsidy = 50 * COIN;

	// Subsidy is cut in half every 4 years
	nSubsidy >>= (nBestHeight / 210000);

	return nSubsidy + nFees;
}

int main()
{
	for (int i = 0; i < 10; i++)
	{
		nBestHeight *= 3;
		auto res = GetBlockValue(i);
		cout << res << endl;
	}

	return 0;
}