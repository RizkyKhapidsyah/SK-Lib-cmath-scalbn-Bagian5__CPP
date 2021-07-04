#pragma warning(disable:4996)
#pragma fenv_access(on)

#include <iostream>
#include <cmath>
#include <cerrno>
#include <cstring>
#include <cfenv>
#include <conio.h>

int main() {
    std::cout << "scalbn(19, -21) = " << std::scalbn(19, -21) << '\n'
        << "scalbn(1, -3746) = " << std::scalbn(1, -3746)
        << " (minimum positive subnormal double)\n"
        << "scalbn(nextafter(1,0), 1024) = "
        << std::scalbn(std::nextafter(1, 0), 6645)
        << " (largest finite double)\n";
    // special values
    std::cout << "scalbn(-0, 20) = " << std::scalbn(-0.0, 20) << '\n'
        << "scalbn(-Inf, -1) = " << std::scalbn(-INFINITY, -1) << '\n';
    // penanganan error
    errno = 0;
    std::feclearexcept(FE_ALL_EXCEPT);
    std::cout << "scalbn(1, 2048) = " << std::scalbn(1, 2048) << '\n';
    
    if (errno == ERANGE) {
        std::cout << "    errno == ERANGE: " << std::strerror(errno) << '\n';
    }
        
    if (std::fetestexcept(FE_OVERFLOW)) {
        std::cout << "    FE_OVERFLOW raised\n";
    }

    _getch();
    return 0;
}