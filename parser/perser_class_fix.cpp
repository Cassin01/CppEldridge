#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

struct SNode {
  string type;
  string value;
  int right;
  int left;
};

tuple<string, SNode> number(string str, SNode snode) {
  while (str.size() > 0) {
    if (isdigit(str.front())) {
      snode.value += str.front();
      str.erase(str.begin());
    } else {
      return forward_as_tuple(str, snode);
    }
  }
  return forward_as_tuple(str, snode);
}

SNode SNodes_init(string type) {
  SNode snode;
  snode.type  = type;
  snode.right = -1;
  snode.left  = -1;
  return snode;
}

void term(const string str) {
  vector<SNode> snodes;
  string str_table = str;
  if (isdigit(str.front())) {
    std::string str_table;
    SNode snode;
    tie(str_table, snode) = number(str, SNodes_init("num"));
    snodes.push_back(snode);
    cout << snode.value << endl;
  }

  while(str_table.size() > 0) {
    if(str_table.front() == '*') {
      SNode snode = SNodes_init("mf*");
      snode.right = snodes.back();
    }
    str_table.erase(str_table.begin());
  }
}

void test() {
  term("12 * 2");
}

int main(void) {
  test();
  return 0;
}