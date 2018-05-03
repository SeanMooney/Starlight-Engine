
namespace starlight::core{
constexpr const static int answer = 42;
unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}
}