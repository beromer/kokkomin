#include <iostream>
#include "Kokkos_Core.hpp"

int main(){
  Kokkos::initialize();

  std::cout << "This is a test\n";

  Kokkos::finalize();
  return 0;
}
