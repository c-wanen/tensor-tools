#include <iostream>
#include <complex>
#include <Eigen/Dense>

#include "tblis.h"

int main(int argc, char const *argv[]) {
	int s1=2, s2=3, s3=4;
	Eigen::MatrixXcd mA(s1,s2);
	mA.setRandom();
	Eigen::MatrixXcd mB(s2,s3);
	mB.setRandom();
	Eigen::MatrixXcd mC(s1,s3);
	mC.setZero();
	std::cout << "/-------------------------------------------------/" << '\n';
	std::cout << "Matrix mA:" << '\n';
	std::cout << mA << '\n' << '\n';
	std::cout << "Matrix mB:" << '\n';
	std::cout << mB << '\n' << '\n';
	std::cout << "Matrix mA*mB:" << '\n';
	std::cout << mA*mB << '\n' << '\n';
	std::cout << "/-------------------------------------------------/" << '\n';

	tblis::tensor< std::complex<double> > A({s1,s2});
	std::copy(mA.data(),mA.data()+mA.size(),A.data());

	tblis::tensor< std::complex<double> > B({s2,s3});
	std::copy(mB.data(),mB.data()+mB.size(),B.data());

	tblis::tensor< std::complex<double> > C({s1,s3});

	tblis::mult(std::complex<double>(1.0),A,"ab",B,"bc",std::complex<double>(1.0),C,"ac");
	std::copy(C.data(),C.data()+mC.size(),mC.data());

	std::cout << "tblis results:" << '\n';
	std::cout << mC << '\n' << '\n';
	std::cout << "/-------------------------------------------------/" << '\n';

  return 0;
}