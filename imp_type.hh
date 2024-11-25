#ifndef IMP_TYPE
#define IMP_TYPE

#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <list>
#include <vector>

using namespace std;

class ImpType {
public:
  enum TType { NOTYPE=0, VOID, INT,LONGINT, BOOL, FUN , CONST};
  static const char* type_names[7];
  TType ttype;
  vector<TType> types;
  TType ctype;
  bool match(const ImpType&);
  bool set_basic_type(string s);
  bool set_basic_type(TType tt);
  bool set_fun_type(list<string> slist, string s);
  bool set_const_type(string s);
  bool set_const_type(TType tt);

private:
  TType string_to_type(string s);
};

std::ostream& operator << ( std::ostream& outs, const ImpType & type );


#endif
