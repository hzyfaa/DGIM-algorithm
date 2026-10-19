#ifndef BUCKET_H
#define BUCKET_H
#include <cstddef>

struct Bucket
{
  std::size_t timestamp; // position of the newest 1
  std::size_t value; // number of 1s represented
};

#endif //BUCKET_H
