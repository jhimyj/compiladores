#include "imp_type.hh"

const char* ImpType::type_names[7] = { "notype", "procedure", "integer","longint", "boolean", "function","const" };

bool ImpType::match(const ImpType& t) {
  if(t.ttype==ImpType::CONST)
    return t.ctype == this->ttype;
  if(this->ttype==ImpType::CONST)
    return this->ctype == t.ttype;
  if (this->ttype != t.ttype) return false;
  if (this->ttype == ImpType::FUN) {
    if (t.types.size() != this->types.size()) return false;
    for (int i=0; i < this->types.size(); i++)
      if (t.types[i] != this->types[i]) return false;
  }
  return true;
}

bool ImpType::set_basic_type(string s) {
  TType tt;
  bool ret = true;
  tt = string_to_type(s);
  if (tt == ImpType::NOTYPE) ret = false;
  this->ttype = tt;
  return ret;
}

bool ImpType::set_basic_type(TType tt) {
    bool ret = true;
    switch(tt) {
    case ImpType::INT:
    case ImpType::LONGINT:
    case ImpType::BOOL:
    case ImpType::VOID:
      case ImpType::CONST:
      this->ttype = tt; break;
    default:
      ret = false;
    }
    return ret;
}


bool ImpType::set_fun_type(list<string> slist, string s) {
  list<string>::iterator it;
  ttype = ImpType::NOTYPE;
  types.clear();
  for (it = slist.begin(); it != slist.end(); ++it) {
    ImpType type;
    type.set_basic_type(*it);
    if (type.ttype==ImpType::INT || type.ttype==ImpType::BOOL || type.ttype==ImpType::LONGINT)
      types.push_back(type.ttype);
    else {     
      types.clear();
      return false;
    }
  }
  ImpType rtype;
  if (rtype.set_basic_type(s))
    types.push_back(rtype.ttype);
  else {
    types.clear();
    return false;
  }
  ttype = ImpType::FUN;
  return true;
}

bool ImpType::set_const_type(string s) {
  if(!set_basic_type(s)) return false;
  ctype = ttype;
  ttype = ImpType::CONST;
  return true;
}
bool ImpType::set_const_type(TType s) {
  if(!set_basic_type(s)) return false;
  ctype = ttype;
  ttype = ImpType::CONST;
  return true;
}

ImpType::TType ImpType::string_to_type(string s) {
  TType tt;
  if (s.compare("integer")==0) tt = ImpType::INT;
  else if (s.compare("longint")==0) tt = ImpType::LONGINT;
  else if (s.compare("boolean")==0) tt = ImpType::BOOL;
  else if (s.compare("void")==0) tt = ImpType::VOID;
  else if (s.compare("const")==0) tt = ImpType::CONST;
  else tt = ImpType::NOTYPE; 
  return tt;
}

std::ostream& operator << ( std::ostream& outs, const ImpType & type )
{
  outs << ImpType::type_names[type.ttype];
  if (type.ttype == ImpType::FUN) {
    int num_params = type.types.size()-1;
    ImpType::TType rtype = type.types[num_params];
    outs << "(";
    if (num_params > 0) outs << ImpType::type_names[type.types[0]];    
    for(int i=1; i<num_params; i++)
      outs << "," << ImpType::type_names[type.types[i]];
    outs << ")->" << ImpType::type_names[rtype];    
  }
  return outs;
}


