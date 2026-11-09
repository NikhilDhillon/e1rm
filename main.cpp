// e1rm: estimate a one-rep max with the Epley formula.
// Taken from the scoring engine of GROWTH, a strength-tracking app.
//
//   e1rm = weight * (1 + reps / 30)

#include <charconv>
#include <cmath>
#include <format>
#include <iostream>
#include <optional>
#include <span>
#include <string_view>
#include <system_error>

namespace {

constexpr std::string_view kUsage = "Usage: e1rm <weight> <reps>";
constexpr std::string_view kInvalid = "Weight and reps must be positive numbers.";

// Parses the whole string as a finite number greater than zero.
// Rejects trailing characters ("5kg"), empty input, inf and nan.
std::optional<double> parse_positive(std::string_view text) {
    double value{};
    const char* first = text.data();
    const char* last = text.data() + text.size();
    const auto [ptr, ec] = std::from_chars(first, last, value);
    if (ec != std::errc{} || ptr != last || !std::isfinite(value) || value <= 0.0) {
        return std::nullopt;
    }
    return value;
}

constexpr double epley(double weight, double reps) {
    return weight * (1.0 + reps / 30.0);
}

}  // namespace

int main(int argc, char* argv[]) {
    const std::span args(argv, static_cast<std::size_t>(argc));

    if (args.size() != 3) {
        std::cerr << kUsage << '\n';
        return 1;
    }

    const auto weight = parse_positive(args[1]);
    const auto reps = parse_positive(args[2]);
    if (!weight || !reps) {
        std::cerr << kInvalid << '\n';
        return 1;
    }

    std::cout << std::format("Estimated 1RM: {:.1f}\n", epley(*weight, *reps));
    return 0;
}
