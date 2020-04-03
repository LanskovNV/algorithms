#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "bloom.h"

// #define BLOOM_FILTER_STANDALONE

u_int32_t MyHash(const void * key, int len, uint seed)
{
    /* 'm' and 'r' are mixing constants generated offline.
     * They're not really 'magic', they just happen to work well.
    */
    const u_int32_t m = 0x5bd1e995;
    const int r = 24;

    /* Initialize the hash to a 'random' value. */
    u_int32_t h = seed ^ len;

    /* Mix 4 bytes at a time into the hash. */
    const uchar * data = key;
    while(len >= 4)
    {
        u_int32_t k = *(u_int32_t *)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    /* Handle the last few bytes of the input array. */
    switch(len)
    {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
        h *= m;
    };

    /* Do a few final mixes of the hash to ensure the last few
     * bytes are well-incorporated.
    */
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
} // end of MyHash function

/*------------------------------------------------------------------------------
*/

bloom_filter_t *New(int filterSize, int numHashes)
{
    bloom_filter_t	*bf;
    const size_t bits_length = (filterSize + (CHAR_BIT * sizeof *bf->bits) - 1) / (CHAR_BIT * sizeof *bf->bits);
    const size_t bits_size = bits_length * sizeof *bf->bits;

    if((bf = malloc(sizeof *bf + bits_size)) != NULL)
    {
        bf->m = filterSize;
        bf->k = numHashes;
        bf->size = 0;
        bf->bits = (ulong *) (bf + 1);
        bf->bits_length = bits_length;
        memset(bf->bits, 0, bits_size);
    }
    return bf;
}

bloom_filter_t * NewWithProbability(float prob, int num_elements)
{
    /* optimal size of massive (wikipedia) */
    const float	m = -(num_elements * logf(prob)) / powf(log(2.f), 2.f);

    /* optimal num of hashes (wikipedia) */
    const float	k = logf(2.f) * m / num_elements;

#if defined BLOOM_FILTER_STANDALONE
    printf("computed bloom filter size %f -> %u bytes\n", m, (uint) (m + .5f) / 8);
    printf(" so m/n = %.1f\n", m / num_elements);
    printf(" which gives k=%f\n", k);
#endif
    return New((uint) (m + .5f), (uint) (k + 0.5f));
}

void Destroy(bloom_filter_t *bf)
{
    free(bf);
}

void Insert(bloom_filter_t *bf, const char *string, int string_length)
{
    const size_t len = string_length > 0 ? string_length : (int)strlen(string);
    size_t 	i;

    /* Repeatedly hash the string, and set bits in the Bloom filter's bit array. */
    for(i = 0; i < bf->k; i++)
    {
        const u_int	hash = MyHash(string, len, i);
        const size_t pos = hash % bf->m;
        const size_t slot = pos / (CHAR_BIT * sizeof *bf->bits);
        const size_t bit = pos % (CHAR_BIT * sizeof *bf->bits);
#if defined BLOOM_FILTER_STANDALONE
        printf("hash(%s,%zu)=%u -> pos=%zu -> slot=%zu, bit=%zu\n", string, i, hash, pos, slot, bit);
#endif
        bf->bits[slot] |= 1UL << bit;
    }
    bf->size++;
}

bool_t Contains(const bloom_filter_t *bf, const char *string, int string_length)
{
    const size_t len = string_length > 0 ? string_length : (int)strlen(string);
    size_t 	i;

    /* Check the Bloom filter, by hashing and checking bits. */
    for(i = 0; i < bf->k; i++)
    {
        const uint	hash = MyHash(string, len, i);
        const size_t pos = hash % bf->m;
        const size_t slot = pos / (CHAR_BIT * sizeof *bf->bits);
        const size_t bit = pos % (CHAR_BIT * sizeof *bf->bits);

        /* If a bit is not set, the element is not contained, for sure. */
        if((bf->bits[slot] & (1UL << bit)) == 0)
            return m_false;
    }

    return m_true;
}
