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


#ifndef My_OBSERVABLES_H
#define My_OBSERVABLES_H

#include "tt.h"
#include "qtt.h"
#include "qstt.h"

//-------------------------------------
// Overlaps
template <typename T>
T psiHphi(MPS<T>& psi, MPO<T>& H, MPS<T>& phi);

template <typename T>
T overlap(MPS<T>& psi, MPO<T>& H, MPS<T>& phi){ return psiHphi(psi,H,phi); }

template <typename T>
T psiHphi(qMPS<T>& psi, qMPO<T>& H, qMPS<T>& phi);

template <typename T>
T overlap(qMPS<T>& psi, qMPO<T>& H, qMPS<T>& phi){ return psiHphi(psi,H,phi); }

template <typename T>
T psiHphi(qsMPS<T>& psi, qsMPO<T>& H, qsMPS<T>& phi);

template <typename T>
T overlap(qsMPS<T>& psi, qsMPO<T>& H, qsMPS<T>& phi){ return psiHphi(psi,H,phi); }

//--------------------------------------------------------------------
template <typename T>
T psiHKphi(MPS<T>& psi, MPO<T>& H, MPO<T>& K, MPS<T>& phi);

template <typename T>
T overlap(MPS<T>& psi, MPO<T>& H, MPO<T>& K, MPS<T>& phi){ return psiHKphi(psi,H,K,phi); }

template <typename T>
T psiHKphi(qMPS<T>& psi, qMPO<T>& H, qMPO<T>& K, qMPS<T>& phi);

template <typename T>
T overlap(qMPS<T>& psi, qMPO<T>& H, qMPO<T>& K, qMPS<T>& phi){ return psiHKphi(psi,H,K,phi); }

template <typename T>
T psiHKphi(qsMPS<T>& psi, qsMPO<T>& H, qsMPO<T>& K, qsMPS<T>& phi);

template <typename T>
T overlap(qsMPS<T>& psi, qsMPO<T>& H, qsMPO<T>& K, qsMPS<T>& phi){ return psiHKphi(psi,H,K,phi); }

//--------------------------------------------------------------------
template <typename T>
T psiHKGphi(qMPS<T>& psi, qMPO<T>& H, qMPO<T>& K, qMPO<T>& G, qMPS<T>& phi);

template <typename T>
T overlap(qMPS<T>& psi, qMPO<T>& H, qMPO<T>& K, qMPO<T>& G, qMPS<T>& phi){ return psiHKGphi(psi,H,K,G,phi); }

template <typename T>
T psiHKGphi(qsMPS<T>& psi, qsMPO<T>& H, qsMPO<T>& K, qsMPO<T>& G,qsMPS<T>& phi);

template <typename T>
T overlap(qsMPS<T>& psi, qsMPO<T>& H, qsMPO<T>& K, qsMPO<T>& G,qsMPS<T>& phi){ return psiHKGphi(psi,H,K,G,phi); }
//--------------------------------------------------------------------
template <typename T>
T psiphi(MPS<T>& psi, MPS<T>& phi);

template <typename T>
T overlap(MPS<T>& psi, MPS<T>& phi){ return psiphi(psi,phi); }

template <typename T>
T psiphi(qMPS<T>& psi, qMPS<T>& phi);

template <typename T>
T overlap(qMPS<T>& psi, qMPS<T>& phi){ return psiphi(psi,phi); }

template <typename T>
T psiphi(qsMPS<T>& psi, qsMPS<T>& phi);

template <typename T>
T overlap(qsMPS<T>& psi, qsMPS<T>& phi){ return psiphi(psi,phi); }

#endif
