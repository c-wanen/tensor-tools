/*
 * Originally copyright 2018 The Simons Foundation, Inc., 
 * with modifications by Ryan Levy
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


#ifndef AUTOMPO_H
#define AUTOMPO_H

#include <set>
#include "../sites/sites.h"


class AutoMPO;

using Cplx = std::complex<double>;
using Real = double;

//
// Given an AutoMPO representing a Hamiltonian H,
// returns an IQMPO which approximates exp(-tau*H)
//
// Although the tau argument is of Complex type, passing a Real
// tau (Real is auto convertible to Complex) will 
// result in a real-valued MPO.

struct SiteTerm
    {
    std::string op;
    int i;

    SiteTerm();

    SiteTerm(std::string const& op,
             int i);

    bool
    operator==(SiteTerm const& o) const { return (op == o.op && i == o.i); }

    bool
    operator!=(SiteTerm const& other) const { return !operator==(other); }

    bool
    operator<(SiteTerm const& o) const
        {
        if(i != o.i) return i < o.i;
        return op < o.op;
        }

    bool
    operator>(SiteTerm const& o) const
        {
        if(i != o.i) return i > o.i;
        return op > o.op;
        }
    };

using SiteTermProd = std::vector<SiteTerm>;

bool
isFermionic(SiteTerm const& st);

struct HTerm
    {
    Cplx coef = 0.;
    SiteTermProd ops;

    HTerm() : coef(1.) { }

    HTerm(Cplx z, SiteTermProd const& prod) : coef(z), ops(prod) { }

    HTerm(Cplx z, SiteTermProd && prod) : coef(z), ops(std::move(prod)) { }

    void
    add(std::string const& op,
        int i,
        Real x = 1);

    explicit
    operator bool() const { return !ops.empty(); }

    int
    Nops() const { return ops.size(); }

    SiteTerm const&
    first() const { return ops.front(); }

    SiteTerm const&
    last() const { return ops.back(); }

    HTerm&
    operator*=(Real x);

    HTerm&
    operator*=(Cplx x);

    bool
    operator==(HTerm const& other) const;

    bool
    operator!=(HTerm const& other) const { return !operator==(other); }

    bool
    operator<(HTerm const& other) const;
    };

struct LessNoCoef
    {
    bool
    operator()(HTerm const& t1, HTerm const& t2) const;
    };

class AutoMPO
    {
    public:
    using storage = std::set<HTerm,LessNoCoef>;
    private:
    //abstract_sites sites_;
    storage terms_;

    enum State { New, Op };

    class Accumulator
        {
        AutoMPO* pa;
        State state;
        Cplx coef;
        std::string op;
        public:
        HTerm term;

        Accumulator(AutoMPO* pa, 
                    Real x);

        Accumulator(AutoMPO* pa, 
                    Cplx x);

        Accumulator(AutoMPO* pa);

        Accumulator(AutoMPO* pa, 
                    const char* opname);

        Accumulator(AutoMPO* pa, 
                    std::string const& opname);

        ~Accumulator();
        
        Accumulator&
        operator,(Real x);

        Accumulator&
        operator,(Cplx x);

        Accumulator&
        operator,(int i);

        Accumulator&
        operator,(const char* op);

        Accumulator&
        operator,(std::string const& op);
        };

    public:

    AutoMPO() { }

    AutoMPO(abstract_sites const& sites) 
      //: sites_(sites)
        { }

    //abstract_sites const&
    //sites() const { return sites_; }

    storage const&
    terms() const { return terms_; }

    int
    size() const { return terms_.size(); }

    //operator MPO() const { return toMPO<ITensor>(*this); }

    //operator IQMPO() const { return toMPO<IQTensor>(*this); }

    template <typename T>
    Accumulator
    operator+=(T x) { return Accumulator(this,x); }

    void
    add(HTerm & t);

    void
    reset() { terms_.clear(); }
    };

std::ostream& 
operator<<(std::ostream& s, SiteTerm const& t);

std::ostream& 
operator<<(std::ostream& s, HTerm const& t);

std::ostream& 
operator<<(std::ostream& s, AutoMPO const& a);


#endif
