#include "genatest_common.h"

/* a shuffled set of 116 integers, from 0 to 115 */
const int GENATEST_INT_SET[] = {
  59,88,16,29,108,12,42,63,0,35,4,111,61,113,109,50,15,30,56,107,82,2,58,
  23,80,38,7,13,76,52,100,67,21,18,9,87,66,6,70,11,60,65,72,73,48,79,57,49,
  101,51,32,8,31,40,115,99,74,17,3,53,84,41,94,20,62,85,110,47,54,96,33,25,
  69,78,77,64,98,93,86,89,39,71,103,75,102,91,105,24,10,45,44,27,68,104,5,
  19,46,43,97,36,37,55,106,90,22,92,26,114,14,112,81,34,1,95,28,83
};

const size_t GENATEST_INT_SET_LEN =
  sizeof(GENATEST_INT_SET) / sizeof(GENATEST_INT_SET[0]);

const int GENATEST_CUSTOM_INT_1 = 234;
const int GENATEST_CUSTOM_INT_2 = 749;

const genatest_str_t GENATEST_STR_SET[] = {
  "a", "ab", "abc", "abcd", "abcde", "abcdef", "abcdefg", "abcdefgh",
  "abcdefghi", "abcdefghij", "abcdefghijk", "abcdefghijkl", "abcdefghijklm",
  "abcdefghijklmn", "abcdefghijklmno",
  "b", "bc", "bcd", "bcde", "bcdef", "bcdefg", "bcdefgh", "bcdefghi",
  "bcdefghij", "bcdefghijk", "bcdefghijkl", "bcdefghijklm", "bcdefghijklmn",
  "bcdefghijklmno", "bcdefghijklmnop",
  "c", "cd", "cde", "cdef", "cdefg", "cdefgh", "cdefghi", "cdefghij",
  "cdefghijk", "cdefghijkl", "cdefghijklm", "cdefghijklmn", "cdefghijklmno",
  "cdefghijklmnop", "cdefghijklmnopa",
  "d", "de", "def", "defg", "defgh", "defghi", "defghij", "defghijk",
  "defghijkl", "defghijklm", "defghijklmn", "defghijklmno", "defghijklmnop",
  "defghijklmnopa", "defghijklmnopab",
  "e", "ef", "efg", "efgh", "efghi", "efghij", "efghijk", "efghijkl",
  "efghijklm", "efghijklmn", "efghijklmno", "efghijklmnop", "efghijklmnopa",
  "efghijklmnopab", "efghijklmnopabc",
  "f", "fg", "fgh", "fghi", "fghij", "fghijk", "fghijkl", "fghijklm",
  "fghijklmn", "fghijklmno", "fghijklmnop", "fghijklmnopa", "fghijklmnopab",
  "fghijklmnopabc", "fghijklmnopabcd",
  "g", "gh", "ghi", "ghij", "ghijk", "ghijkl", "ghijklm", "ghijklmn",
  "ghijklmno", "ghijklmnop", "ghijklmnopa", "ghijklmnopab", "ghijklmnopabc",
  "ghijklmnopabcd", "ghijklmnopabcde",
  "h", "hi", "hij", "hijk", "hijkl", "hijklm", "hijklmn", "hijklmno",
  "hijklmnop", "hijklmnopa", "hijklmnopab", "hijklmnopabc", "hijklmnopabcd",
  "hijklmnopabcde", "hijklmnopabcdef"
};

const size_t GENATEST_STR_SET_LEN =
  sizeof(GENATEST_STR_SET) / sizeof(GENATEST_STR_SET[0]);

const genatest_str_t GENATEST_CUSTOM_STR_1 = "~=str!ngVALUE-+";
const genatest_str_t GENATEST_CUSTOM_STR_2 = "[CU$TOM STRING]";

const genatest_buf_t GENATEST_BUF_SET[] = {
  {0,1,2,3}, {0,1,3,2}, {0,2,1,3}, {0,2,3,1}, {0,3,1,2}, {0,3,2,1},
  {1,0,2,3}, {1,0,3,2}, {1,2,0,3}, {1,2,3,0}, {1,3,0,2}, {1,3,2,0},
  {2,0,1,3}, {2,0,3,1}, {2,1,0,3}, {2,1,3,0}, {2,3,0,1}, {2,3,1,0},
  {3,0,1,2}, {3,0,2,1}, {3,1,0,2}, {3,1,2,0}, {3,2,0,1}, {3,2,1,0}
};

const size_t GENATEST_BUF_SET_LEN =
  sizeof(GENATEST_BUF_SET) / sizeof(GENATEST_BUF_SET[0]);

const genatest_buf_t GENATEST_CUSTOM_BUF_1 = {9,4,7,5};
const genatest_buf_t GENATEST_CUSTOM_BUF_2 =
  {1580840905,2141465707,1026411296,2013971497};
