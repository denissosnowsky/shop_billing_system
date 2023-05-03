#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Shopping {
private:
  int pcode;
  float price;
  float dis;
  string pname;

public:
  void menu();
  void administrator();
  void buyer();
  void add();
  void edit();
  void rem();
  void list();
  void receipt();
}