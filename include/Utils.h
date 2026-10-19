#ifndef UTILS_H
#define UTILS_H
#include <random>
#include <vector>
#include <cstddef>

// generates a random stream of N binary bits
inline std::vector<std::size_t> generate_stream(
    std::size_t stream_size,
    unsigned int seed)
{
  std::mt19937 generator(seed);
  std::bernoulli_distribution bit_dist(0.5);

  std::vector<std::size_t> stream;
  stream.reserve(stream_size);

  for (std::size_t i = 0; i < stream_size; ++i)
  {
    stream.push_back(bit_dist(generator));
  }

  return stream;
}

#endif //UTILS_H
