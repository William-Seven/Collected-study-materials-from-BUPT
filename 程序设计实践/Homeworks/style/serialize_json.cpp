#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;

// 将字符串根据json的转义要求进行转义，返回一个新的字符串
string escape_json(const string &s) 
{
   ostringstream o;
   for(const char* c = s.c_str(); *c != 0; c++) {
      switch (*c) {
         case '"' : o << "\\\""; break;
         case '\\': o << "\\\\"; break;
         case '\b': o << "\\b"; break;
         case '\f': o << "\\f"; break;
         case '\n': o << "\\n"; break;
         case '\r': o << "\\r"; break;
         case '\t': o << "\\t"; break;
         default:
            if (!('\x00' <= *c && *c <= '\x1f'))
                o << *c;
            else
                o << "\\u" << hex << setw(4) << setfill('0') << (int)*c;
      }
   }
   return o.str();
}

// 将map中的数据序列化为一个json格式的字符串返回
string serialize(map<string, string>& m)
{
   ostringstream o;
   o << "{";
   map<string, string>::iterator i;
   bool not_first = false;
   for(i = m.begin(); i != m.end(); i++){
      if(not_first)
         o << ",";
      else
         not_first = true;
      o << "\"" << escape_json(i->first) << "\":\"" << escape_json(i->second) << "\"";
   }
   o << "}";
   return o.str();
}

int main()
{
   map<string, string> m;
   m["sjdf"] = "sk\ndjfksdf";
   m["hsdhf"] = "sjdgfjsdhgfj sdgfjsd";
   m["sjdh"] = "sjdhfg\x01sjdf sdf";
   m["uery"] = "uerytjfsd";
   m["jsdkf"] = "123456";
   m["sdhs"] = "ksjhdfksf";

   string json = serialize(m);
   cout << json << endl;
   return 0;
}
