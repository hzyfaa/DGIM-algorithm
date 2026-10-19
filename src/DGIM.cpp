#include "DGIM.h"
#include <array>
#include <stdexcept>

DGIM::DGIM(std::size_t window_size) : window(window_size)
{
  if (window_size == 0)
  {
    throw std::invalid_argument(
        "Window size must be greater than 0");
  }
}

void DGIM::add(bool bit)
{
  // every bit should increment the window, including zeros
  ++current_timestamp;

  // check for existing expired buckets
  if (current_timestamp > window && !buckets.empty())
  {
    if (buckets.front().timestamp <= current_timestamp - window)
    {
      buckets.pop_front();
    }
  }

  // create bucket if bit is 1
  if (bit)
  {
    buckets.push_back(Bucket{current_timestamp, 1});
    // check for merge
    merge_buckets(1);
  }
}

/*
 * if 3 buckets with the same value exists,
 * the function will perform a merge operation
 * on the oldest matching buckets, retaining the newer timestamp
 */
void DGIM::merge_buckets(const std::size_t size_to_check)
{
  std::array<std::size_t, 3> matches{};
  std::size_t count = 0;

  // find 3 matches
  for (std::size_t i = 0; i < buckets.size(); ++i)
  {
    if (buckets[i].value == size_to_check)
    {
      matches[count] = i;
      ++count;

      if (count == 3) break;
    }
  }

  // less than 3 matches
  if (count < 3) return;

  const std::size_t older_index = matches[0];
  const std::size_t newer_index = matches[1];
  // sum values
  buckets[newer_index].value += buckets[older_index].value;
  // remove older bucket
  buckets.erase(buckets.begin() + older_index);
  // check for new merge
  merge_buckets(size_to_check * 2);
}

double DGIM::get_estimate_count() const
{
  if (buckets.empty()) return 0;

  double ones_count = buckets.front().value / 2.00;

  for (std::size_t i = 1; i < buckets.size(); ++i)
  {
    ones_count += buckets[i].value;
  }
  return ones_count;
}

