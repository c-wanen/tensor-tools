/*
 * Copyright 2020 Ryan Levy, Xiongjie Yu, and Bryan K. Clark
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef My_OBSERVABLES
#define My_OBSERVABLES

#include "observables.h"

//-------------------------------------
// Expectation velues
template <typename T>
T psiHphi (MPS<T>& psi, MPO<T>& H, MPS<T>& phi) {
	assert(psi.tensors_allocated);
	assert(H.tensors_allocated);
	assert(phi.tensors_allocated);
	assert(psi.phy_dim==phi.phy_dim);
	assert(psi.length==phi.length);
	assert(psi.length==H.length);
	T res = T(0);
	dtensor<T> acc, t1, t4, t5; //t2,t3
	for (size_t i = 0; i < psi.length; i++) {
		t1 = psi.A[i]; t1.dag(); t1.conj(); t1.prime();
		auto& t2 = H.A[i];
		auto& t3 = phi.A[i];
		if(i==0){
			dtensor<T> left_ends({t1.idx_set[0], t2.idx_set[0], t3.idx_set[0]});
			left_ends.setOne();
			t4 = std::move(left_ends*t1);
			t5 = std::move(t4*t2);
			acc= std::move(t5*t3);
		}else if(i==psi.length-1){
			dtensor<T> right_ends({t1.idx_set.back(), t2.idx_set.back(), t3.idx_set.back()});
			right_ends.setOne();
			t4 = std::move(acc*t1);
			t5 = std::move(t4*t2);
			acc= std::move(t5*t3);
			res= acc.contract(right_ends);
		}else{
			t4 = std::move(acc*t1);
			t5 = std::move(t4*t2);
			acc= std::move(t5*t3);
		}
	}
	return res;
}
template double psiHphi (MPS<double>& psi, MPO<double>& H, MPS<double>& phi);
template std::complex<double> psiHphi (MPS< std::complex<double> >& psi, MPO< std::complex<double> >& H, MPS< std::complex<double> >& phi);


template <typename T>
T psiHphi (qMPS<T>& psi, qMPO<T>& H, qMPS<T>& phi) {
	assert(psi.tensors_allocated);
	assert(H.tensors_allocated);
	assert(phi.tensors_allocated);
	assert(psi.phy_dim==phi.phy_dim);
	assert(psi.length==phi.length);
	assert(psi.length==H.length);
	T res = T(0);
	qtensor<T> acc, t1,  t4, t5; //t2,t3
	for (size_t i = 0; i < psi.length; i++) {
		t1 = psi.A[i]; t1.dag(); t1.conj(); t1.prime();
		auto& t2 = H.A[i];
		auto& t3 = phi.A[i];
		if(i==0){
			qtensor<T> left_ends({t1.idx_set[0], t2.idx_set[0], t3.idx_set[0]});
			left_ends.initBlock();
			left_ends.setOne();
			left_ends.dag();
			t4 = std::move(left_ends*t1);
			t5 = std::move(t4*t2);
			acc= std::move(t5*t3);
		}else if(i==psi.length-1){
			qtensor<T> right_ends({t1.idx_set.back(), t2.idx_set.back(), t3.idx_set.back()});
			right_ends.initBlock();
			right_ends.setOne();
			right_ends.dag();
			t4 = std::move(acc*t1);
			t5 = std::move(t4*t2);
			acc= std::move(t5*t3);
			res= acc.contract(right_ends);
		}else{
			t4 = std::move(acc*t1);
			t5 = std::move(t4*t2);
			acc= std::move(t5*t3);
		}
	}
	return res;
}
template double psiHphi (qMPS<double>& psi, qMPO<double>& H, qMPS<double>& phi);
template std::complex<double> psiHphi (qMPS< std::complex<double> >& psi, qMPO< std::complex<double> >& H, qMPS< std::complex<double> >& phi);

template <typename T>
T psiHphi (qsMPS<T>& psi, qsMPO<T>& H, qsMPS<T>& phi) {
	assert(psi.tensors_allocated);
	assert(H.tensors_allocated);
	assert(phi.tensors_allocated);
	assert(psi.phy_dim==phi.phy_dim);
	assert(psi.length==phi.length);
	assert(psi.length==H.length);
	T res = T(0);
	qstensor<T> acc, t1,  t4, t5; //t2,t3
	for (size_t i = 0; i < psi.length; i++) {
		t1 = psi.A[i]; t1.dag(); t1.conj(); t1.prime();
		auto& t2 = H.A[i];
		auto& t3 = phi.A[i];
		if(i==0){
			qstensor<T> left_ends({t1.idx_set[0], t2.idx_set[0], t3.idx_set[0]});
			left_ends.initBlock();
			left_ends.setOne();
			left_ends.dag();
			t4 = std::move(left_ends*t1);
			t5 = std::move(t4*t2);
			acc= std::move(t5*t3);
		}else if(i==psi.length-1){
			qstensor<T> right_ends({t1.idx_set.back(), t2.idx_set.back(), t3.idx_set.back()});
			right_ends.initBlock();
			right_ends.setOne();
			right_ends.dag();
			t4 = std::move(acc*t1);
			t5 = std::move(t4*t2);
			acc= std::move(t5*t3);
			res= acc.contract(right_ends);
		}else{
			t4 = std::move(acc*t1);
			t5 = std::move(t4*t2);
			acc= std::move(t5*t3);
		}
	}
	return res;
}
template double psiHphi (qsMPS<double>& psi, qsMPO<double>& H, qsMPS<double>& phi);
template std::complex<double> psiHphi (qsMPS< std::complex<double> >& psi, qsMPO< std::complex<double> >& H, qsMPS< std::complex<double> >& phi);

template <typename T>
T psiHKphi(MPS<T>& psi, MPO<T>& H, MPO<T>& K, MPS<T>& phi){
	assert(psi.tensors_allocated);
	assert(H.tensors_allocated);
	assert(phi.tensors_allocated);
	assert(psi.phy_dim==phi.phy_dim);
	assert(psi.length==phi.length);
	assert(psi.length==H.length);
	T res = T(0);
	dtensor<T> acc, t1, t2, t5, t6, t7;//t3,t4
	for (size_t i = 0; i < psi.length; i++) {
		t1 = psi.A[i]; t1.dag(); t1.conj(); t1.prime(2);
		t2 = H.A[i]; t2.prime();
		auto& t3 = K.A[i];
		auto& t4 = phi.A[i];
		if(i==0){
			dtensor<T> left_ends({t1.idx_set[0], t2.idx_set[0], t3.idx_set[0], t4.idx_set[0]});
			left_ends.setOne();
			t5 = std::move(left_ends*t1);
			t6 = std::move(t5*t2);
			t7 = std::move(t6*t3);
			acc= std::move(t7*t4);
		}else if(i==psi.length-1){
			dtensor<T> right_ends({t1.idx_set.back(), t2.idx_set.back(), t3.idx_set.back(), t4.idx_set.back()});
			right_ends.setOne();
			t5 = std::move(acc*t1);
			t6 = std::move(t5*t2);
			t7 = std::move(t6*t3);
			acc= std::move(t7*t4);
			res= acc.contract(right_ends);
		}else{
			t5 = std::move(acc*t1);
			t6 = std::move(t5*t2);
			t7 = std::move(t6*t3);
			acc= std::move(t7*t4);
		}
	}
	return res;
}
template double psiHKphi (MPS<double>& psi, MPO<double>& H, MPO<double>& K, MPS<double>& phi);
template std::complex<double> psiHKphi (MPS< std::complex<double> >& psi, MPO< std::complex<double> >& H, MPO< std::complex<double> >& K, MPS< std::complex<double> >& phi);


template <typename T>
T psiHKphi(qMPS<T>& psi, qMPO<T>& H, qMPO<T>& K, qMPS<T>& phi){
	assert(psi.tensors_allocated);
	assert(H.tensors_allocated);
	assert(phi.tensors_allocated);
	assert(psi.phy_dim==phi.phy_dim);
	assert(psi.length==phi.length);
	assert(psi.length==H.length);
	T res = T(0);
	qtensor<T> acc, t1, t2,  t5, t6, t7; //t3,t4
	for (size_t i = 0; i < psi.length; i++) {
		t1 = psi.A[i]; t1.dag(); t1.conj(); t1.prime(2);
		t2 = H.A[i]; t2.prime();
		auto& t3 = K.A[i];
		auto& t4 = phi.A[i];
		if(i==0){
			qtensor<T> left_ends({t1.idx_set[0], t2.idx_set[0], t3.idx_set[0], t4.idx_set[0]});
			left_ends.initBlock();
			left_ends.setOne();
			left_ends.dag();
			t5 = std::move(left_ends*t1);
			t6 = std::move(t5*t2);
			t7 = std::move(t6*t3);
			acc= std::move(t7*t4);
		}else if(i==psi.length-1){
			qtensor<T> right_ends({t1.idx_set.back(), t2.idx_set.back(), t3.idx_set.back(), t4.idx_set.back()});
			right_ends.initBlock();
			right_ends.setOne();
			right_ends.dag();
			t5 = std::move(acc*t1);
			t6 = std::move(t5*t2);
			t7 = std::move(t6*t3);
			acc= std::move(t7*t4);
			res= acc.contract(right_ends);
		}else{
			t5 = std::move(acc*t1);
			t6 = std::move(t5*t2);
			t7 = std::move(t6*t3);
			acc= std::move(t7*t4);
		}
	}
	return res;
}
template double psiHKphi (qMPS<double>& psi, qMPO<double>& H, qMPO<double>& K, qMPS<double>& phi);
template std::complex<double> psiHKphi (qMPS< std::complex<double> >& psi, qMPO< std::complex<double> >& H, qMPO< std::complex<double> >& K, qMPS< std::complex<double> >& phi);

template <typename T>
T psiHKphi(qsMPS<T>& psi, qsMPO<T>& H, qsMPO<T>& K, qsMPS<T>& phi){
	assert(psi.tensors_allocated);
	assert(H.tensors_allocated);
	assert(phi.tensors_allocated);
	assert(psi.phy_dim==phi.phy_dim);
	assert(psi.length==phi.length);
	assert(psi.length==H.length);
	T res = T(0);
	qstensor<T> acc, t1, t2, t5, t6, t7;//t3,t4
	for (size_t i = 0; i < psi.length; i++) {
		t1 = psi.A[i]; t1.dag(); t1.conj(); t1.prime(2);
		t2 = H.A[i]; t2.prime();
		auto& t3 = K.A[i];
		auto& t4 = phi.A[i];
		if(i==0){
			qstensor<T> left_ends({t1.idx_set[0], t2.idx_set[0], t3.idx_set[0], t4.idx_set[0]});
			left_ends.initBlock();
			left_ends.setOne();
			left_ends.dag();
			t5 = std::move(left_ends*t1);
			t6 = std::move(t5*t2);
			t7 = std::move(t6*t3);
			acc= std::move(t7*t4);
		}else if(i==psi.length-1){
			qstensor<T> right_ends({t1.idx_set.back(), t2.idx_set.back(), t3.idx_set.back(), t4.idx_set.back()});
			right_ends.initBlock();
			right_ends.setOne();
			right_ends.dag();
			t5 = std::move(acc*t1);
			t6 = std::move(t5*t2);
			t7 = std::move(t6*t3);
			acc= std::move(t7*t4);
			res= acc.contract(right_ends);
		}else{
			t5 = std::move(acc*t1);
			t6 = std::move(t5*t2);
			t7 = std::move(t6*t3);
			acc= std::move(t7*t4);
		}
	}
	return res;
}
template double psiHKphi (qsMPS<double>& psi, qsMPO<double>& H, qsMPO<double>& K, qsMPS<double>& phi);
template std::complex<double> psiHKphi (qsMPS< std::complex<double> >& psi, qsMPO< std::complex<double> >& H, qsMPO< std::complex<double> >& K, qsMPS< std::complex<double> >& phi);

template <typename T>
T psiHKGphi(qMPS<T>& psi, qMPO<T>& H, qMPO<T>& K, qMPO<T>& G, qMPS<T>& phi){
	assert(psi.tensors_allocated);
	assert(H.tensors_allocated);
	assert(phi.tensors_allocated);
	assert(psi.phy_dim==phi.phy_dim);
	assert(psi.length==phi.length);
	assert(psi.length==H.length);
	T res = T(0);
	qtensor<T> acc, t1, t2, t3, t6, t7, t8, t9;
	for (size_t i = 0; i < psi.length; i++) {
		t1 = psi.A[i]; t1.dag(); t1.conj(); t1.prime(3);
		t2 = H.A[i]; t2.prime(2);
		t3 = K.A[i]; t3.prime();
    auto& t4 = G.A[i];
		auto& t5 = phi.A[i];
		if(i==0){
			qtensor<T> left_ends({t1.idx_set[0], t2.idx_set[0], t3.idx_set[0], t4.idx_set[0], t5.idx_set[0]});
			left_ends.initBlock();
			left_ends.setOne();
			left_ends.dag();
			t6 = std::move(left_ends*t1);
			t7 = std::move(t6*t2);
			t8 = std::move(t7*t3);
      t9 = std::move(t8*t4);
			acc= std::move(t9*t5);
		}else if(i==psi.length-1){
			qtensor<T> right_ends({t1.idx_set.back(), t2.idx_set.back(), t3.idx_set.back(), t4.idx_set.back(), t5.idx_set.back()});
			right_ends.initBlock();
			right_ends.setOne();
			right_ends.dag();
			t6 = std::move(acc*t1);
			t7 = std::move(t6*t2);
			t8 = std::move(t7*t3);
      t9 = std::move(t8*t4);
			acc= std::move(t9*t5);
			res= acc.contract(right_ends);
		}else{
			t6 = std::move(acc*t1);
			t7 = std::move(t6*t2);
			t8 = std::move(t7*t3);
      t9 = std::move(t8*t4);
			acc= std::move(t9*t5);
		}
	}
	return res;
}
template double psiHKGphi (qMPS<double>& psi, qMPO<double>& H, qMPO<double>& K, qMPO<double>& G, qMPS<double>& phi);
template std::complex<double> psiHKGphi (qMPS< std::complex<double> >& psi, qMPO< std::complex<double> >& H, qMPO< std::complex<double> >& K, qMPO< std::complex<double> >& G, qMPS< std::complex<double> >& phi);

template <typename T>
T psiHKGphi(qsMPS<T>& psi, qsMPO<T>& H, qsMPO<T>& K, qsMPO<T>& G, qsMPS<T>& phi){
	assert(psi.tensors_allocated);
	assert(H.tensors_allocated);
	assert(phi.tensors_allocated);
	assert(psi.phy_dim==phi.phy_dim);
	assert(psi.length==phi.length);
	assert(psi.length==H.length);
	T res = T(0);
	qstensor<T> acc, t1, t2, t3, t6, t7, t8, t9;
	for (size_t i = 0; i < psi.length; i++) {
		t1 = psi.A[i]; t1.dag(); t1.conj(); t1.prime(3);
		t2 = H.A[i]; t2.prime(2);
		t3 = K.A[i]; t3.prime();
    auto& t4 = G.A[i];
		auto& t5 = phi.A[i];
		if(i==0){
			qstensor<T> left_ends({t1.idx_set[0], t2.idx_set[0], t3.idx_set[0], t4.idx_set[0], t5.idx_set[0]});
			left_ends.initBlock();
			left_ends.setOne();
			left_ends.dag();
			t6 = std::move(left_ends*t1);
			t7 = std::move(t6*t2);
			t8 = std::move(t7*t3);
      t9 = std::move(t8*t4);
			acc= std::move(t9*t5);
		}else if(i==psi.length-1){
			qstensor<T> right_ends({t1.idx_set.back(), t2.idx_set.back(), t3.idx_set.back(), t4.idx_set.back(), t5.idx_set.back()});
			right_ends.initBlock();
			right_ends.setOne();
			right_ends.dag();
			t6 = std::move(acc*t1);
			t7 = std::move(t6*t2);
			t8 = std::move(t7*t3);
      t9 = std::move(t8*t4);
			acc= std::move(t9*t5);
			res= acc.contract(right_ends);
		}else{
			t6 = std::move(acc*t1);
			t7 = std::move(t6*t2);
			t8 = std::move(t7*t3);
      t9 = std::move(t8*t4);
			acc= std::move(t9*t5);
		}
	}
	return res;
}
template double psiHKGphi (qsMPS<double>& psi, qsMPO<double>& H, qsMPO<double>& K, qsMPO<double>& G, qsMPS<double>& phi);
template std::complex<double> psiHKGphi (qsMPS< std::complex<double> >& psi, qsMPO< std::complex<double> >& H, qsMPO< std::complex<double> >& K, qsMPO< std::complex<double> >& G, qsMPS< std::complex<double> >& phi);
template <typename T>
T psiphi (MPS<T>& psi, MPS<T>& phi) {
	assert(psi.tensors_allocated);
	assert(phi.tensors_allocated);
	assert(psi.phy_dim==phi.phy_dim);
	assert(psi.length==phi.length);
	T res = T(0);
	dtensor<T> acc, t1, t2, t3;
	for (size_t i = 0; i < psi.length; i++) {
		t1 = psi.A[i]; t1.dag(); t1.conj(); t1.primeLink();
		t2 = phi.A[i];
		if(i==0){
			dtensor<T> left_ends({t1.idx_set[0], t2.idx_set[0]});
			left_ends.setOne();
			t3 = std::move(left_ends*t1);
			acc=std::move(t3*t2);
		}else if(i==psi.length-1){
			dtensor<T> right_ends({t1.idx_set.back(), t2.idx_set.back()});
			right_ends.setOne();
			t3 = std::move(t1*acc);
			acc= std::move(t3*t2);
			res= acc.contract(right_ends);
		}else{
			t3 = std::move(t1*acc);
			acc = std::move(t3*t2);
		}
	}
	return res;
}
template double psiphi (MPS<double>& psi, MPS<double>& phi);
template std::complex<double> psiphi (MPS< std::complex<double> >& psi, MPS< std::complex<double> >& phi);


template <typename T>
T psiphi (qMPS<T>& psi, qMPS<T>& phi) {
	assert(psi.tensors_allocated);
	assert(phi.tensors_allocated);
	assert(psi.phy_dim==phi.phy_dim);
	assert(psi.length==phi.length);
	T res = T(0);
	qtensor<T> acc, t1, t2, t3;
	for (size_t i = 0; i < psi.length; i++) {
		t1 = psi.A[i]; t1.dag(); t1.conj(); t1.primeLink();
		t2 = phi.A[i];
		if(i==0){
			qtensor<T> left_ends({t1.idx_set[0], t2.idx_set[0]});
			left_ends.initBlock();
			left_ends.setOne();
			left_ends.dag();
			t3 = std::move(left_ends*t1);
			acc=std::move(t3*t2);
		}else if(i==psi.length-1){
			qtensor<T> right_ends({t1.idx_set.back(), t2.idx_set.back()});
			right_ends.initBlock();
			right_ends.setOne();
			right_ends.dag();
			t3 = std::move(t1*acc);
			acc= std::move(t3*t2);
			res= acc.contract(right_ends);
		}else{
			t3 = std::move(t1*acc);
			acc = std::move(t3*t2);
		}
	}
	return res;
}
template double psiphi (qMPS<double>& psi, qMPS<double>& phi);
template std::complex<double> psiphi (qMPS< std::complex<double> >& psi, qMPS< std::complex<double> >& phi);

template <typename T>
T psiphi (qsMPS<T>& psi, qsMPS<T>& phi) {
	assert(psi.tensors_allocated);
	assert(phi.tensors_allocated);
	assert(psi.phy_dim==phi.phy_dim);
	assert(psi.length==phi.length);
	T res = T(0);
	qstensor<T> acc, t1, t2, t3;
	for (size_t i = 0; i < psi.length; i++) {
		t1 = psi.A[i]; t1.dag(); t1.conj(); t1.primeLink();
		t2 = phi.A[i];
		if(i==0){
			qstensor<T> left_ends({t1.idx_set[0], t2.idx_set[0]});
			left_ends.initBlock();
			left_ends.setOne();
			left_ends.dag();
			t3 = std::move(left_ends*t1);
			acc=std::move(t3*t2);
		}else if(i==psi.length-1){
			qstensor<T> right_ends({t1.idx_set.back(), t2.idx_set.back()});
			right_ends.initBlock();
			right_ends.setOne();
			right_ends.dag();
			t3 = std::move(t1*acc);
			acc= std::move(t3*t2);
			res= acc.contract(right_ends);
		}else{
			t3 = std::move(t1*acc);
			acc = std::move(t3*t2);
		}
	}
	return res;
}
template double psiphi (qsMPS<double>& psi, qsMPS<double>& phi);
template std::complex<double> psiphi (qsMPS< std::complex<double> >& psi, qsMPS< std::complex<double> >& phi);
#endif
