#include "BloomFilter.h"
#include <stdio.h>
#include <ctype.h>

BloomFilter::BloomFilter()
{
	randNum[0] = 50161;
	randNum[1] = 22696;
	randNum[2] = 273;
	randNum[3] = 19159;
	randNum[4] = 14692;
	randNum[5] = 8255;
	randNum[6] = 20154;
	randNum[7] = 13109;
	randNum[8] = 11098;
	randNum[9] = 866;
	randNum[10] = 15643;
	randNum[11] = 11554;
	randNum[12] = 38297;
	randNum[13] = 42447;
	randNum[14] = 9827;
	randNum[15] = 9648;
	randNum[16] = 45568;
	randNum[17] = 47227;
	randNum[18] = 48459;
	randNum[19] = 30713;
	randNum[20] = 9110;
	size = 11;
	hashtable = new bool[size];
	for(int i = 0; i < (int)size; i++)
		hashtable[i] = false;
}

BloomFilter::BloomFilter (int s)
{
	randNum[0] = 50161;
	randNum[1] = 22696;
	randNum[2] = 273;
	randNum[3] = 19159;
	randNum[4] = 14692;
	randNum[5] = 8255;
	randNum[6] = 20154;
	randNum[7] = 13109;
	randNum[8] = 11098;
	randNum[9] = 866;
	randNum[10] = 15643;
	randNum[11] = 11554;
	randNum[12] = 38297;
	randNum[13] = 42447;
	randNum[14] = 9827;
	randNum[15] = 9648;
	randNum[16] = 45568;
	randNum[17] = 47227;
	randNum[18] = 48459;
	randNum[19] = 30713;
	randNum[20] = 9110;

	if(s <= 11) size = 11;
	else if(s <= 23) size = 23;
	else if(s <= 47) size = 47;
	else if(s <= 97) size = 97;
	else if(s <= 197) size = 197;
	else if(s <= 397) size = 397;
	else if(s <= 797) size = 797;
	else if(s <= 1597) size = 1597;
	else if(s <= 3203) size = 3203;
	else if(s <= 6421) size = 6421;
	else if(s <= 12853) size = 12853;
	else if(s <= 25717) size = 25717;
	else size = 51437;

	hashtable = new bool[size];
	for(int i = 0; i < (int)size; i++)
		hashtable[i] = false;
}

BloomFilter::~BloomFilter()
{
	delete [] hashtable;
}

void BloomFilter::insert(std::string input)
{
	if(contains(input)) return;
	if(isValid(input) == false) return;
	int h1 = hash1(input);
	int h2 = hash2(input);
	int h3 = hash3(input);

	hashtable[h1] = true;
	hashtable[h2] = true;
	hashtable[h3] = true;
}

bool BloomFilter::contains(std::string input)
{
	if(isValid(input) == false) return false;
	int h1 = hash1(input);
	int h2 = hash2(input);
	int h3 = hash3(input);

	if(hashtable[h1] == false) return false;
	if(hashtable[h2] == false) return false;
	if(hashtable[h3] == false) return false;

	return true;
}

int BloomFilter::hash1(std::string input) const
{
	std::vector<int> seq = getSequence(input);
	long product[21];
	for(int i = 0; i < 21; i++)
		product[i] = randNum[i] * seq[i];
	int h1 = ((unsigned long)(product[0] + product[1] + product[2] + product[3] + product[4] + 
				product[5] + product[6] + product[7] + product[8] + product[9] + 
				product[10] + product[11] + product[12] + product[13] + product[14] + 
				product[15] + product[16] + product[17] + product[18] + product[19] + product[20]) % size);
	return h1;
}

int BloomFilter::hash2(std::string input) const
{
	std::vector<int> seq = getSequence(input);
	long product[21];
	for(int i = 0; i < 21; i++)
		product[i] = randNum[i] * seq[i];
	int p;
	if(size == 11) p = 7;
	else if(size == 23) p = 19;
	else if(size == 47) p = 43;
	else if(size == 97) p = 89;
	else if(size == 197) p = 193;
	else if(size == 397) p = 389;
	else if(size == 797) p = 787;
	else if(size == 1597) p = 1583;
	else if(size == 3203) p = 3191;
	else if(size == 6421) p = 6397;
	else if(size == 12853) p = 12841;
	else if(size == 25717) p = 25703;
	else p = 51431;

	int h2 = p - ((unsigned long)(product[0] + product[1] + product[2] + product[3] + product[4] + 
				product[5] + product[6] + product[7] + product[8] + product[9] + 
				product[10] + product[11] + product[12] + product[13] + product[14] + 
				product[15] + product[16] + product[17] + product[18] + product[19] + product[20]) % p);
	return h2;
}

int BloomFilter::hash3(std::string input) const
{
	std::vector<int> seq = getSequence(input);
	int h3 = ((unsigned long)(seq[0] + seq[1] + seq[2] + seq[3] + seq[4] + 
			seq[5] +	seq[6] +	seq[7] +	seq[8] +	seq[9] + 
			seq[10] +	seq[11] +	seq[12] +	seq[13] +	seq[14] + 
			seq[15] +	seq[16] +	seq[17] +	seq[18] +	seq[19] +	seq[20]) % size);
	return h3;
}

int BloomFilter::getCharVal(const char k) const
{
	int val = 0;
	if(k == '.') val = 1;
	if(k == '/') val = 2;
	if(k == ':') val = 3;
	if(k == '_') val = 4;
	if(islower(k)) val = (k - 'a') + 5;
	return val;
}

std::vector<int> BloomFilter::getSequence(std::string input) const
{
	std::vector<int> seq;
	int a1 = 0;
	int a2 = 0;
	int a3 = 0;
	int sequence[21];
	int readAmt = input.length() / 3;
	if(input.length() % 3 > 0) readAmt++;
	int start = 21 - readAmt;
	for(int i = 0; i < start; i++) sequence[i] = 0;


	int pos = 0;
	if(input.length() % 3 > 0)
	{
		if(input.length() % 3 == 1)
		{
			sequence[start] = getCharVal(input[pos]);
			start++;
			pos++;
		}
		else if(input.length() % 3 == 2)
		{
			int w = 31*getCharVal(input[pos]);
			pos++;
			w += (getCharVal(input[pos]));
			sequence[start] = w;
			start++;
			pos++;
		}
	}


	for(int i = start; i < 21; i++)
	{
		for(int x = 0; x < 3; x++)
		{
			if(x == 0) a1 = (31 * 31) * getCharVal(input[pos]);
			else if(x == 1) a2 = 31 * getCharVal(input[pos]);
			else if(x == 2) 
			{
				a3 = getCharVal(input[pos]);
				sequence[i] = a1 + a2 + a3;
			}
			pos++;
		}
	}

	for(int i = 0; i < 21; i++)
		seq.push_back(sequence[i]);
	return seq;
}

bool BloomFilter::isValid(std::string web)
{
	if(web.length() > 63) return false;
	for(int i = 0; i < (int)web.length(); i++)
	{
		if(!islower(web[i]) && web[i] != '/' && web[i] != ':' && web[i] != '_' && web[i] != '.')
			return false;
	}
	return true;
}
