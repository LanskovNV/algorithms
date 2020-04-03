#ifndef BLOOM_H
#define BLOOM_H

#include <stdlib.h> // u_int_32

typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned char uchar;

typedef enum
{
  m_false,
  m_true
} bool_t;

typedef struct{
    size_t m;           // massive size
    size_t k;           // num of hash functions
    size_t size;        // num of elements
    ulong *bits;        // bit slots
    size_t bits_length;
}bloom_filter_t;

/* source hash function */
u_int32_t MyHash(const void *key, int len, uint seed);

/* bloom filter functions */
bloom_filter_t *New(int filterSize, int numHashes);
bloom_filter_t *NewWithProbability(float prob,int num_elements);
void	Insert(bloom_filter_t *bf, const char *string, int string_length);
bool_t	Contains(const bloom_filter_t *bf, const char *string, int string_length);
void Destroy(bloom_filter_t *bf);

#endif // BLOOM_H
