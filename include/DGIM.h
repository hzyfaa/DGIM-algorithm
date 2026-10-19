#ifndef DGIM_H
#define DGIM_H
#include <cstddef>
#include <deque>
#include "Bucket.h"

class DGIM {
public:
  explicit DGIM(std::size_t window_size);
  double get_estimate_count() const;
  std::size_t bucket_count() const { return buckets.size(); }
  void add(bool bit);
private:
  std::size_t window;
  std::deque<Bucket> buckets;
  std::size_t current_timestamp = 0;
  void merge_buckets(std::size_t size_to_check);
};

#endif //DGIM_H
