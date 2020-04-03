/* leins, 17.06.2018 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "bloom.h"
#include "test.h"

#define MAX_WORD_LEN 50

/*****************************
 * unit tests for bloom filter
*/

void RandStr(char *s, int strLen)
{
  for (int i = 0 ; i < strLen; i++)
  {
    *s = 'a' + rand() % 25;
    srand(time(0));
    s++;
  }
}

void ImplementString(char *s, int strLen)
{
  for (int i = 0; i < strLen; i++)
  {
    if (*s + 2 <= 'z')
      *s += 2;
    else
      *s -= 25;
    s++;
  }
}

/* 1) for two different values hashes is different
 * 2) func returns the same values for one data every time
 * (check for several times...)
*/
bool_t CompareBits(int *a, int *b, int size)
{
  for (int i = 0; i < size; i++)
    if (a[i] != b[i])
      return m_false;
  return m_true;
}

bool_t IsTheSame(int **bits, int seedS, int hashS)
{
  for (int i = 0; i < seedS - 1; i++)
  {
    for (int j = i + 1; j < seedS; j++)
    {
      if (CompareBits(bits[i], bits[j], hashS))
        return m_true;
    }
  }
  return m_false;
}

bool_t Test_MyHash()
{
  int maxSeed = 10;
  int nOfHashes = 10;
  int **b;
  bool_t ans = m_true;
  char *s = malloc(sizeof("hello") + 1);

  b = malloc(maxSeed * sizeof(int *));

  if (s != NULL)
  {
    /* generate test values  for 1) */
    strcpy(s, "hello");
    for (int i = 0 ; i < maxSeed; i++)
    {
      b[i] = malloc(nOfHashes * sizeof(int));
      for (int j = 0 ; j < nOfHashes; j++)
      {
        u_int32_t hash = MyHash(s, strlen(s), j);
        b[i][j] = hash % 2;
      }
      ImplementString(s, strlen(s)); // generate different data
    }

    /* if have same values - not good */
    if (IsTheSame(b, maxSeed, nOfHashes))
    {
      printf("TEST_MYHASH: same values for the different data\n");
      ans = m_false;
    }

    /* generate test values  for 2) */
    strcpy(s, "hello");
    for (int i = 0 ; i < maxSeed ; i++)
    {
      for (int j = 0 ; j < nOfHashes; j++)
      {
        u_int32_t hash = MyHash(s, strlen(s), i);
        b[i][j] = hash % 2;
      }
    }
    /* if haven't same values - not good */
    if (!IsTheSame(b, maxSeed, nOfHashes))
    {
      printf("TEST_MYHASH: different values for the same data\n");
      ans = m_false;
    }

  }

  free(s);
  for (int i = 0 ; i < maxSeed; i++)
    free(b[i]);
  free(b);

  return ans;
}

/* if we add new element -
 * it means that Hash should change bits in bloom filter
*/
bool_t Test_Insert()
{
  bloom_filter_t *bf;
  float probability = 10e-6;
  int numOfNodes = 30;
  uint cnt = 0;
  bool_t ans = m_true;

  /* New bloom filter
   * (Simple function, can be used without tests)
  */
  bf = NewWithProbability(probability, numOfNodes);

  /* check num of non zero values
   * after inserting one elem
  */
  Insert(bf, "hello", -1);
  for (uint i = 0; i < bf->bits_length; i++)
  {
    if (bf->bits[i] != 0)
      cnt++;
  }
  if (cnt == 0)
  {
    printf("TEST_INSERT: no non zero values\n");
    ans = m_false;
  }
  if (bf->size != 1)
  {
    printf("TEST_INSERT: size is not correct\n");
    ans = m_false;
  }

  /* just free(bf); */
  Destroy(bf);
  return ans;
}

/* if Contains return false -
 * it means that element is not in bloom filter 100%
 * truth is not so interesting
*/
bool_t Test_Contains()
{
  bloom_filter_t *bf;
  float probability = 10e-6;
  int numOfNodes = 30;
  bool_t ans = m_true;
  int len = rand() % 10;
  char *s = malloc(len + 1);

  /* New bloom filter
   * (Simple function, can be used without tests)
  */
  bf = NewWithProbability(probability, numOfNodes);

  RandStr(s,len);
  /* check false */
  if (Contains(bf, s, len)) // empty bf
  {
    printf("TEST_CONTAINS: found something in empty filter\n");
    ans = m_false;
  }

  /* just free(bf); */
  Destroy(bf);
  free(s);
  return ans;
}

void CheckZeroValues(bloom_filter_t *bf, char *fileName)
{
  FILE *f;

  if ((f = fopen(fileName, "r")) == NULL)
  {
    printf("Load: cannot open file");
    return;
  }
  else
  {
    int n;

    fscanf(f, "%i", &n);

    printf("not in filter words:\n");
    for (int i = 0 ; i < n; i++)
    {
      char *s = malloc(MAX_WORD_LEN);
      fscanf(f, "%s", s);
      if (!Contains(bf, s, -1))
        printf("\t%s\n", s);
      free(s);
    }
  }
}

/*
void Load(bloom_filter_t *bf, char *fileName)
{
  FILE *f;

  if ((f = fopen(fileName, "r")) == NULL)
  {
    printf("Load: cannot open file");
    return;
  }
  else
  {
    int n;

    fscanf(f, "%i", &n);

    for (int i = 0 ; i < n; i++)
    {
      char *s = malloc(MAX_WORD_LEN);
      fscanf(f, "%s", s);
      Insert(bf, s, -1);
      free(s);
    }
  }
}
*/
