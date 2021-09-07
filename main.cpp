#include <iostream>
#include "Kokkos_Core.hpp"
#include "Kokkos_DynRankView.hpp"
#include <map>
#include <string>

class variable {
  public:
    variable(std::string name, bool integrable_, bool io_, size_t N0):integrate(integrable_),io(io_){
      view = Kokkos::DynRankView<double>(name,N0);
    }
    variable(std::string name, bool integrable_, bool io_, size_t N0, size_t N1):integrate(integrable_),io(io_){
      view = Kokkos::DynRankView<double>(name,N0,N1);
    }
    Kokkos::DynRankView<double> view;
    bool integrate;
    bool io;
};

int main(){
  Kokkos::initialize();

  {
    int N0 = 16;
    int N1 = 32;
    //std::map<std::string,Kokkos::DynRankView<double>> vars;
    //vars.emplace("pressure",Kokkos::DynRankView<double>("pressure",N0,N1));
    //vars.emplace("temperature",Kokkos::DynRankView<double>("temperature",N0,N1));

    //variable test("C",true,true,15);

    std::map<std::string,variable> varws;
    varws.emplace("energy",variable("energy",true,true,N0,N1));
    varws.emplace("density",variable("density",true,true,N0,N1));
    varws.emplace("test1",variable("test1",false,true,N0));

    for (auto const& val : varws){
      std::cout << "Processing " << val.first << ".\n";

      if (val.second.integrate){
        Kokkos::parallel_for("SetVar", Kokkos::MDRangePolicy<Kokkos::Rank<2>>({0,0},{N0,N1}),
          KOKKOS_LAMBDA (const int i, const int j) {
          val.second.view(i,j) = i+j;
        });
      }
    }
  }

  std::cout << "This is a test\n";

  Kokkos::finalize();
  return 0;
}
