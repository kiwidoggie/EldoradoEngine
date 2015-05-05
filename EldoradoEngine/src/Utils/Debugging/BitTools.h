#pragma once
// All Credits: AndrewThomas

template<typename T>
int OrBit(T& inBuf, int shiftCount, T bitState, int bitBaseBits, bool inverse = false)
{
	int bitShift = 0;
	if (inverse)
	{
		int totalSize = sizeof(T) * 8;
		bitShift = totalSize - shiftCount - bitBaseBits;
	}
	else
		bitShift = shiftCount;

	T bitWord = bitState;

	bitWord = bitWord << bitShift;

	inBuf = inBuf | bitWord;

	return 1;
}

template<typename T>
int XorBit(T& inBuf, int shiftCount, T bitState, int bitBaseBits, bool inverse = false)
{
	int bitShift = 0;
	if (inverse)
	{
		int totalSize = sizeof(T) * 8;
		bitShift = totalSize - shiftCount - bitBaseBits;
	}
	else
		bitShift = shiftCount;

	T bitBuffer = bitState;

	bitBuffer = bitWord << bitShift;

	inBuf = inBuf ^ bitBuffer;

	return 1;
}

template<typename T>
int AndBit(T& inBuf, int shiftCount, T bitState, int bitBaseBits, bool inverse = false)
{
	int bitShift = 0;
	if (inverse)
	{
		int totalSize = sizeof(T) * 8;
		bitShift = totalSize - shiftCount - bitBaseBits;
	}
	else
		bitShift = shiftCount;

	T bitBuffer = bitState;

	bitBuffer = bitBuffer << bitShift;

	inBuf = inBuf & bitBuffer;

	return 1;
}

template<typename T>
int GetSetBitCount(T inBuf)
{
	int size = sizeof(T) * 8;
	int bitCount = 0;

	T bitBuffer = inBuf;
	for (unsigned int i = 0; i < size; i++)
	{
		if ((bool)bitBuffer & 1)
			bitCount++;

		bitBuffer = inBuf << 1;
	}

	return bitCount;
}

template<typename T>
int IsBitSet(T inBuf, int bitCount)
{
	T bitBuffer = 1;
	bitBuffer = bitBuffer << bitCount;

	T ret = inBuf & bitBuffer;
	return (bool)ret;
}