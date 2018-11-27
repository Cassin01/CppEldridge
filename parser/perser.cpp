#include <iostream>
#include <vector>
#include <string>
#include "ThisIs.cpp"
#include <stack>

static const int MAX_N = 100;

using namespace std;

class Parser {
  private:
    vector<int> code_stack;
    int n;
    int it;
    int root;
  public:
    class SNode {
      public:
        string node;
        string value;
        int right;
        int left;
    };

    SNode snode[1000];

    Parser() {
      n = 0;
    }

    string detect(string str, int it) {
      ThisIs this_is;
      if (isdigit(str[it])) {
        return "num";
      } else if (this_is.is_this(str[it], ' ')) {
        return "space";
      } else if (this_is.is_this(str[it], '*')) {
        return "_*_";
      } else if (this_is.is_this(str[it], '+')) {
        return "_+_";
      } else {
        return "others";
      }
    }

    string stack_top_type() {
      return snode[code_stack.back()].node;
    }

    void show(int r) {
      cout << snode[r].node << " " << snode[r].value;
      cout << " [ ";
      if (snode[r].right >= 0 && snode[r].left >= 0) {
        show(snode[r].right);
        show(snode[r].left);
      } else {
        cout << "null" << " ] ";
        return;
      }
      cout << " ] ";
    }

    void show2(string detected) {
      if (detected != "space") {
        cout << n << "番目 ";
        for (auto a: code_stack) {
          cout << "stack=" << a;
          cout << " right=" << snode[a].right;
          cout << " left="  << snode[a].left;
        }
        cout << endl;
        show(code_stack.back());
        cout << endl << endl;
      }
    }

    int go_left_end(int n) {
      if (snode[n].left == -1) {
        return n;
      } else {
        return go_left_end(snode[n].left);
      }
    }

    void solve(string str) {
      it = 0;
      while (it < str.size()) {
        string detected = detect(str, it);
        if (detected == "num") {
          cout << "num" << endl;
          snode[n].node  = detected;
          snode[n].value = str[it];
          snode[n].right = -1;
          snode[n].left  = -1;
          if (code_stack.size() > 0) {
            snode[go_left_end(code_stack.back())].left = n;
          } else {
            code_stack.push_back(n);
          }
          n++;
        } else if (detected == "space") {
          //cout << "space" << endl;
          // なにもしない。
        } else if (detected == "_*_") {
          cout << "_*_" << endl;
          snode[n].node  = detected;
          snode[n].value = str[it];
          if (stack_top_type() == "num") {
            snode[n].right = code_stack.back();
            snode[n].left  = -1;
            code_stack.pop_back();
            code_stack.push_back(n);
          }
          else if (stack_top_type() == "_+_") {
            snode[n].right = snode[code_stack.back()].left;
            snode[n].left  = -1;
            snode[code_stack.back()].left = n;
          }
          else if (stack_top_type() == "_*_") {
            snode[n].right = code_stack.back();
            snode[n].left  = -1;
            code_stack.pop_back();
            code_stack.push_back(n);
          }
          else {
            cout << "ERR : unkown operator" << endl;
          }
          n++;
        } else if (detected == "_+_") {
          cout << "_+_" << endl;
          snode[n].node  = detected;
          snode[n].value = str[it];
          snode[n].right = code_stack.back();
          snode[n].left  = -1;
          code_stack.pop_back();
          code_stack.push_back(n);
          n++;
        }
        else if (detected == "ohters") {
          cout << "変な文字入ってるよ" << endl;
          return;
        }
        it++;
      }
      show(code_stack.back());
      cout << endl;
    }
};



int main(void) {
  Parser parser;
  parser.solve("2 + 2 * 3");
  return 0;
}
