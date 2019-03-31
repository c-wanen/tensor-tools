#include "../util/types_and_headers.h"
#include "../linalg/lapack_wrapper.h"
#include "../dtensor/dtensor_all.h"
#include "../qtensor/qtensor_all.h"
#include "../mps/mps_all.h"

#include "../models/sites/spinhalf.h"
#include "../models/hams/Heisenberg.h"

#include "../algos/dmrg/dmrg.h"

#include "../util/timer.h"
using namespace std;

int main(int argc, char const *argv[]) {
  unsigned N = 30;
  spinhalf sites(N);
  str_vec ps;
  for (size_t i = 0; i < sites.N(); i++) {
    if(i%2==0)
      ps.push_back("Dn");
    else
      ps.push_back("Up");
  }

  std::cout.precision(8);

  {
    std::cout << "\n" << "Test MPS DMRG." << '\n';
    MPS< double > psi(&sites,1);
    psi.setRandom();
    psi.normalize();

    MPO< double > H;
    Heisenberg< double > HB(&sites);
    HB.buildHam(H);

    double Energy = psiHphi(psi, H, psi);
    std::cout<<"Initial energy of the MPS: "<<Energy<<std::endl;
    /*int nsweeps = 20;
    int maxm = 60;
    double cutoff = 1e-8;*/

    int nsweeps = 5;
    std::vector<int> maxm = {50,80,100,150,150};
    std::vector<double> cutoff = {1E-6,1E-8,1E-10,1E-12,1E-12};
    std::vector<int> max_restart = {4,3,2,2,2};
    //TODO: noise

    dmrg(psi, H, nsweeps, maxm, cutoff,max_restart);

    psi.print();

    std::cout << psiHphi(psi,H,psi) << '\n';
  }

  {
    std::cout << "\n" << "Test qMPS DMRG." << '\n';
    qMPS< double > psi(&sites,ps);
    psi.normalize();

    qMPO< double > H;
    Heisenberg< double > HB(&sites);
    HB.buildHam(H);

    int nsweeps = 20;
    int maxm = 60;
    double cutoff = 1e-8;
    dmrg(psi, H, nsweeps, maxm, cutoff);

    psi.print();

    std::cout << psiHphi(psi,H,psi) << '\n';
  }
  //------------------------------------
  return 0;
}
