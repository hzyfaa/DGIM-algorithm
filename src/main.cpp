#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>
#include <iomanip>
#include "DGIM.h"
#include "Utils.h"

// define params for simulated stream
constexpr std::size_t stream_size = 10000;
constexpr unsigned int seed = 42;

void experiment(const std::vector<std::size_t>& stream, std::size_t window);

int main()
{
  // generate simulated stream
  const std::vector<std::size_t> stream = generate_stream(stream_size, seed);

  // set up header/table for formatting output s
  std::cout << "DGIM experiments\n"
            << "Stream length: " << stream.size()
            << " | Seed: " << seed
            << " | P(1): 0.5\n"
            << "Baseline window: 1500 | Modified window: 500\n\n";

  std::cout << std::right
            << std::setw(10) << "Window"
            << std::setw(12) << "Estimate"
            << std::setw(10) << "Exact"
            << std::setw(12) << "Abs. error"
            << std::setw(16) << "Rel. error (%)"
            << std::setw(10) << "Buckets"
            << '\n';

  // run baseline experiment with window size set to 1500
  experiment(stream, 1500);
  // run modified experiment with window size divided by 3
  experiment(stream, 500);

  return 0;
}

void experiment(const std::vector<std::size_t>& stream, const std::size_t window)
{
  // initialize dgim simulation
  DGIM dgim(window);

  // iterate through data stream
  for (const auto bit : stream)
  {
    dgim.add(bit);
  }

  // get estimated count of 1s within window
  const double estimate_count = dgim.get_estimate_count();

  // get exact count of 1s
  const std::size_t start =
    stream.size() > window ? stream.size() - window : 0;

  std::size_t exact_count = 0;

  for (std::size_t i = start; i < stream.size(); ++i)
  {
    if (stream[i] == 1) ++exact_count;
  }

  // compute absolute error
  const double absolute_error = std::abs(estimate_count - static_cast<double>(exact_count));

  // show results
  std::cout << std::fixed << std::setprecision(2)
          << std::right
          << std::setw(10) << window
          << std::setw(12) << estimate_count
          << std::setw(10) << exact_count
          << std::setw(12) << absolute_error;

  if (exact_count != 0)
  {
    const double relative_error =
        100.0 * absolute_error / static_cast<double>(exact_count);

    std::cout << std::setw(16) << relative_error;
  }
  else
  {
    std::cout << std::setw(16) << "N/A";
  }

  std::cout << std::setw(10) << dgim.bucket_count() << '\n';
}
