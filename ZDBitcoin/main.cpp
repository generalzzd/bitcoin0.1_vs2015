#include "sha.h"
#include "key.h"
#include "bignum.h"
#include "ZDBitcoin.h"

#include <iostream>
#include <string>
using namespace std;
using CryptoPP::ByteReverse;


void BlockSHA256(const void* pin, unsigned int nBlocks, void* pout)
{
	unsigned int* pinput = (unsigned int*)pin;
	unsigned int* pstate = (unsigned int*)pout;

	CryptoPP::SHA256::InitState(pstate);

	for (int n = 0; n < nBlocks; n++)
	{
		unsigned int pbuf[16];
		for (int i = 0; i < 16; i++)
		{
			//pbuf[i] = ByteReverse(pinput[n * 16 + i]);
			pbuf[i] = pinput[n * 16 + i];
		}
			
		CryptoPP::SHA256::Transform(pstate, pbuf);
	}
	//for (int i = 0; i < 8; i++)
	//	pstate[i] = ByteReverse(pstate[i]);

}


unsigned int nTransactionsUpdated = 0;
//CBlockIndex* pindexBest = NULL;

//unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast)
//{
//	const unsigned int nTargetTimespan = 14 * 24 * 60 * 60; // two weeks
//	const unsigned int nTargetSpacing = 10 * 60;
//	const unsigned int nInterval = nTargetTimespan / nTargetSpacing;
//
//	// Genesis block
//	if (pindexLast == NULL)
//		return bnProofOfWorkLimit.GetCompact();
//
//	// Only change once per interval
//	if ((pindexLast->nHeight + 1) % nInterval != 0)
//		return pindexLast->nBits;
//
//	// Go back by what we want to be 14 days worth of blocks
//	const CBlockIndex* pindexFirst = pindexLast;
//	for (int i = 0; pindexFirst && i < nInterval - 1; i++)
//		pindexFirst = pindexFirst->pprev;
//	assert(pindexFirst);
//
//	// Limit adjustment step
//	unsigned int nActualTimespan = pindexLast->nTime - pindexFirst->nTime;
//	printf("  nActualTimespan = %d  before bounds\n", nActualTimespan);
//	if (nActualTimespan < nTargetTimespan / 4)
//		nActualTimespan = nTargetTimespan / 4;
//	if (nActualTimespan > nTargetTimespan * 4)
//		nActualTimespan = nTargetTimespan * 4;
//
//	// Retarget
//	CBigNum bnNew;
//	bnNew.SetCompact(pindexLast->nBits);
//	bnNew *= nActualTimespan;
//	bnNew /= nTargetTimespan;
//
//	if (bnNew > bnProofOfWorkLimit)
//		bnNew = bnProofOfWorkLimit;
//
//	/// debug print
//	printf("\n\n\nGetNextWorkRequired RETARGET *****\n");
//	printf("nTargetTimespan = %d    nActualTimespan = %d\n", nTargetTimespan, nActualTimespan);
//	printf("Before: %08x  %s\n", pindexLast->nBits, CBigNum().SetCompact(pindexLast->nBits).getuint256().ToString().c_str());
//	printf("After:  %08x  %s\n", bnNew.GetCompact(), bnNew.getuint256().ToString().c_str());
//
//	return bnNew.GetCompact();
//}
//
//
//bool BitcoinMiner()
//{
//	printf("BitcoinMiner started\n");
//
//	CKey key;
//	key.MakeNewKey();
//	CBigNum bnExtraNonce = 0;
//
//	while (1/*!vNodes.emty()*/)
//	{
//		unsigned int nTransactionsUpdatedLast = nTransactionsUpdated;
//		CBlockIndex* pindexPrev = pindexBest;
//		unsigned int nBits = GetNextWorkRequired(pindexPrev);
//
//
//		//
//		// Create coinbase tx
//		//
//		CTransaction txNew;
//		txNew.vin.resize(1);
//		txNew.vin[0].prevout.SetNull();
//		txNew.vin[0].scriptSig << nBits << ++bnExtraNonce;
//		txNew.vout.resize(1);
//		txNew.vout[0].scriptPubKey << key.GetPubKey() << OP_CHECKSIG;
//	}
//
//	return true;
//}
std::string string_to_hex(const std::string& input)
{
	static const char* const lut = "0123456789ABCDEF";
	size_t len = input.length();

	std::string output;
	output.reserve(2 * len);
	for (size_t i = 0; i < len; ++i)
	{
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	}
	return output;
}
int main()
{
	const char* str = "zzdtest";
	char res[128];
	BlockSHA256(str, 0, res);
	cout << "Result: " << string_to_hex(res) << endl;


	return 0;
}