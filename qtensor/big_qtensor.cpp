/*
 * Copyright 2020 Xiongjie Yu, Ryan Levy, and Bryan K. Clark
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

#ifndef BIG_QUANTUM_NUMBERED_TENSOR_CLASS
#define BIG_QUANTUM_NUMBERED_TENSOR_CLASS

#include "big_qtensor.h"

template <typename T>
qtensor<T> big_qtensor<T>::product(qtensor<T>& v){
  // contract pattern:
  // L-v-mid-R
  // qtensor<T> res;
  // if(L!=nullptr) res = std::move((*L)*v);
  // for(auto m : mid){
  //   if(res.rank>0)
  //     res = std::move(res*(*m));
  //   else
  //     res = std::move(v*(*m));
  // }
  // if(R!=nullptr) res = std::move(res*(*R));

  qtensor<T> res = std::move(A*v);
  if(R!=nullptr) res = std::move(res*(*R));

  res.prime(-1);
  return res;
}
template qtensor<double> big_qtensor<double>::product(qtensor<double>& v);
template qtensor< std::complex<double> > big_qtensor< std::complex<double> >::product(qtensor< std::complex<double> >& v);


template <typename T>
T big_qtensor<T>::expec(qtensor<T>& v){
  // contract pattern:
  // L-v-mid-R
  // qtensor<T> res;
  // if(L!=nullptr) res = std::move((*L)*v);
  // for(auto m : mid){
  //   if(res.rank>0)
  //     res = std::move(res*(*m));
  //   else
  //     res = std::move(v*(*m));
  // }
  // if(R!=nullptr) res = std::move(res*(*R));

  qtensor<T> res = std::move(A*v);
  if(R!=nullptr) res = std::move(res*(*R));

  res.prime(-1);
  return res.contract(v);
}
template double big_qtensor<double>::expec(qtensor<double>& v);
template std::complex<double> big_qtensor< std::complex<double> >::expec(qtensor< std::complex<double> >& v);


template <typename T>
qtensor<T> big_qtensor<T>::diagonal(){
  // qtensor<T> res;
  // if(L!=nullptr) res = (*L);
  // for(auto m : mid){
  //   res = std::move(res*(*m));
  // }
  // if(R!=nullptr) res = std::move(res*(*R));
  // res = std::move(res.diagonal());

  qtensor<T> res;
  if(R==nullptr){
    res = std::move(A.diagonal());
  }else{
    res = std::move(A*(*R));
    res = std::move(res.diagonal());
  }

  // qtensor<T> res = std::move(A.diagonal());

  return res;
}
template qtensor<double> big_qtensor<double>::diagonal();
template qtensor< std::complex<double> > big_qtensor< std::complex<double> >::diagonal();

#endif
