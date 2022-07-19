#pragma once

class CBlockIndex
{
public:
	const uint256* phashBlock;
	CBlockIndex* pprev;
	CBlockIndex* pnext;
	unsigned int nFile;
	unsigned int nBlockPos;
	int nHeight;

	// block header
	int nVersion;
	uint256 hashMerkleRoot;
	unsigned int nTime;
	unsigned int nBits;
	unsigned int nNonce;


	CBlockIndex()
	{
		phashBlock = NULL;
		pprev = NULL;
		pnext = NULL;
		nFile = 0;
		nBlockPos = 0;
		nHeight = 0;

		nVersion = 0;
		hashMerkleRoot = 0;
		nTime = 0;
		nBits = 0;
		nNonce = 0;
	}

	CBlockIndex(unsigned int nFileIn, unsigned int nBlockPosIn, CBlock& block)
	{
		phashBlock = NULL;
		pprev = NULL;
		pnext = NULL;
		nFile = nFileIn;
		nBlockPos = nBlockPosIn;
		nHeight = 0;

		nVersion = block.nVersion;
		hashMerkleRoot = block.hashMerkleRoot;
		nTime = block.nTime;
		nBits = block.nBits;
		nNonce = block.nNonce;
	}

	uint256 GetBlockHash() const
	{
		return *phashBlock;
	}

	bool IsInMainChain() const
	{
		return (pnext || this == pindexBest);
	}

	bool EraseBlockFromDisk()
	{
		// Open history file
		CAutoFile fileout = OpenBlockFile(nFile, nBlockPos, "rb+");
		if (!fileout)
			return false;

		// Overwrite with empty null block
		CBlock block;
		block.SetNull();
		fileout << block;

		return true;
	}

	enum { nMedianTimeSpan = 11 };

	int64 GetMedianTimePast() const
	{
		unsigned int pmedian[nMedianTimeSpan];
		unsigned int* pbegin = &pmedian[nMedianTimeSpan];
		unsigned int* pend = &pmedian[nMedianTimeSpan];

		const CBlockIndex* pindex = this;
		for (int i = 0; i < nMedianTimeSpan && pindex; i++, pindex = pindex->pprev)
			*(--pbegin) = pindex->nTime;

		sort(pbegin, pend);
		return pbegin[(pend - pbegin) / 2];
	}

	int64 GetMedianTime() const
	{
		const CBlockIndex* pindex = this;
		for (int i = 0; i < nMedianTimeSpan / 2; i++)
		{
			if (!pindex->pnext)
				return nTime;
			pindex = pindex->pnext;
		}
		return pindex->GetMedianTimePast();
	}



	string ToString() const
	{
		return strprintf("CBlockIndex(nprev=%08x, pnext=%08x, nFile=%d, nBlockPos=%-6d nHeight=%d, merkle=%s, hashBlock=%s)",
			pprev, pnext, nFile, nBlockPos, nHeight,
			hashMerkleRoot.ToString().substr(0, 6).c_str(),
			GetBlockHash().ToString().substr(0, 14).c_str());
	}

	void print() const
	{
		printf("%s\n", ToString().c_str());
	}
};