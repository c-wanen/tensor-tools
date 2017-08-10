#ifndef INDEX_CLASS_FOR_QUANTUM_NUMBERED_TENSOR_HEADER
#define INDEX_CLASS_FOR_QUANTUM_NUMBERED_TENSOR_HEADER

#include "../util/types_and_headers.h"

class qtensor_index{
public:
  qtensor_index();
  qtensor_index(arrow_type arrow);
  qtensor_index(arrow_type arrow, string name);
  qtensor_index(arrow_type arrow, string name, index_type type);
  qtensor_index(arrow_type arrow, string name, index_type type, unsigned level);
  qtensor_index(const qtensor_index& other);
  qtensor_index(qtensor_index&& other);

  ~qtensor_index(){}

  inline void addQN(quantum_number qn) {_qn.push_back(qn); _sorted=false; setTag();}
  inline void addQN(vector<int> qn, uint_vec qdim) {
    for (size_t i = 0; i < qn.size(); i++) {
      _qn.push_back(std::make_pair(qn[i], qdim[i]));
    }
    _sorted=false;
    setTag();
  }

  inline void rename(string name) {_name=name; setTag();}
  inline void retype(index_type type) {_type=type; setTag();}
  inline void resize(unsigned i, unsigned size) {_qn.at(i).second=size; setTag();}
  inline void sortQN(){if(!_sorted && _qn.size()>1) std::sort(_qn.begin(), _qn.end(), qnCompare); _sorted=true;}
  inline void setTag(){
    sortQN();
    _tag = _name+" "+to_string(_type)+" ";
    for (size_t i = 0; i < _qn.size(); i++) {
      _tag += ("qn"+to_string(_qn[i].first)+"qdim"+to_string(_qn[i].second)+" ");
    }
  };

  qtensor_index operator = (const qtensor_index& other);
  bool operator == (const qtensor_index& A) const;
  bool operator != (const qtensor_index& A) const;
  bool operator <  (const qtensor_index& A) const;

  inline arrow_type arrow()  {return _arrow;}
  inline unsigned size()     {return _qn.size();}
  inline unsigned level()    {return _level;}
  inline string name()       {return _name;}
  inline index_type type()   {return _type;}
  inline string tag()        {return _arrow+" "+to_string(_level)+" "+_tag;}
  inline int qn(unsigned i) {return _qn.at(i).first;}
  inline unsigned qdim(unsigned i) {return _qn.at(i).second;}

  inline void dag() {
    if(_arrow==Inward)
      _arrow=Outward;
    else
      _arrow=Inward;
  }

  inline bool similar(const qtensor_index& A){
    if(_arrow != A._arrow &&
           _tag    == A._tag   &&
       ((_level== A._level+1)||(_level+1== A._level))
       ){
      return true;
    }else{
      return false;
    }
  }

  inline bool similar(qtensor_index& A){
    if(_arrow != A._arrow &&
           _tag    == A._tag   &&
       ((_level== A._level+1)||(_level+1== A._level))
       ){
      return true;
    }else{
      return false;
    }
  }
  
  inline void prime(int inc=1) {_level+=inc;}
  inline void primeLink(int inc=1) {if(_type==Link) _level+=inc;}
  inline void primeSite(int inc=1) {if(_type==Site) _level+=inc;}
  inline void mapPrime(unsigned from, unsigned to) {if(_level==from) _level=to;}
  inline void mapPrime(unsigned from, unsigned to, index_type type) {if(_level==from&&_type==type) _level=to;}

private:
  bool _sorted;
  arrow_type _arrow;
  string     _name;
  index_type _type;
  unsigned   _level;
  vector< quantum_number > _qn;
  string _tag; // make it hashable
};

#endif