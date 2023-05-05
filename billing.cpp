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
};

void Shopping::menu() {
m:
  int choice;
  string email;
  string password;
  string adminEmail = "admin@gmail.com";
  string adminPass = "adminpass";

  cout << "_______________________________________________\n";
  cout << "            Supermarket Menu\n";
  cout << "_______________________________________________\n";
  cout << "\t1) Administrator\n";
  cout << "\t2) Buyer\n";
  cout << "\t3) Exit\n";
  cout << "Please select:";

  cin >> choice;

  switch (choice) {
  case 1:
    cout << "Enter email: \n";
    cin >> email;
    cout << "Enter password: \n";
    cin >> password;

    if (email == adminEmail && password == adminPass) {
      administrator();
    } else {
      cout << "Invalid email/password\n";
    }
    break;
  case 2:
    buyer();
    break;
  case 3:
    exit(0);
    break;
  default:
    cout << "Enter correct option\n";
    goto m;
  };
};

void Shopping::administrator() {
m:
  int choice;

  cout << "_______________________________________________\n";
  cout << "            Administator menu\n";
  cout << "_______________________________________________\n";
  cout << "\t1) Add product\n";
  cout << "\t2) Modify product\n";
  cout << "\t3) Delete product\n";
  cout << "\t4) Back to main menu\n";
  cout << "Please enter your choice: \n";

  cin >> choice;

  switch (choice) {
  case 1:
    add();
    break;
  case 2:
    edit();
    break;
  case 3:
    rem();
    break;
  case 4:
    menu();
    break;
  default:
    cout << "Enter correct option\n";
    goto m;
  }
};

void Shopping::buyer() {
m:
  int choice;

  cout << "_______________________________________________\n";
  cout << "            Buyer menu\n";
  cout << "_______________________________________________\n";
  cout << "\t1) Buy product\n";
  cout << "\t2) Go back\n";
  cout << "Please enter your choice: \n";

  cin >> choice;

  switch (choice) {
  case 1:
    receipt();
    break;
  case 2:
    menu();
    break;
  default:
    cout << "Enter correct option\n";
    goto m;
  }
};

void Shopping::add() {
m:
  fstream data;
  int token = 0;
  int c;
  float p;
  float d;
  string n;

  cout << "Code of the product";
  cin >> pcode;
  cout << "Name of the product";
  cin >> pname;
  cout << "Price of the product";
  cin >> price;
  cout << "Discount on the product";
  cin >> dis;

  data.open("database.txt", ios::in);

  if (!data) {
    data.open("database.txt", ios::app | ios::out);
    data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
    data.close();
  } else {
    data >> c >> n >> p >> d;

    while (!data.eof()) {
      if (c == pcode) {
        token++;
      }
      data >> c >> n >> p >> d;
    }
    data.close();

    if (token == 1) {
      goto m;
    } else {
      data.open("database.txt", ios::app | ios::out);
      data << " " << pcode << " " << pname << " " << price << " " << dis
           << "\n";
      data.close();
    }
  }

  cout << "Data inserted!\n";
  menu();
};

void Shopping::edit() {
  fstream data, data1;
  int pkey;
  int token = 0;
  int c;
  float p;
  float d;
  string n;

  cout << "Modify the record\n";
  cout << "Enter the product code:\n";
  cin >> pkey;

  data.open("database.txt", ios::in);

  if (!data) {
    cout << "File does not exist\n";
  } else {
    data1.open("database1.txt", ios::app | ios::out);

    data >> pcode >> pname >> price >> dis;
    while (!data.eof()) {
      if (pkey == pcode) {
        cout << "Enter product new code: \n";
        cin >> c;
        cout << "Enter product name: \n";
        cin >> n;
        cout << "Enter price: \n";
        cin >> p;
        cout << "Enter discount: \n";
        cin >> d;

        data1 << " " << c << " " << n << " " << p << " " << d << "\n";
        cout << "Record edited";
        token++;

      } else {
        data1 << " " << pcode << " " << pname << " " << price << " " << dis
              << "\n";
      };

      data >> pcode >> pname >> price >> dis;
    }

    data.close();
    data1.close();

    remove("database.txt");
    rename("database1.txt", "database.txt");

    if (token == 0) {
      cout << "Record not found, sorry!";
    }
  }

  menu();
};

void Shopping::rem() {
  fstream data, data1;
  int pkey;
  int token = 0;

  cout << "Delete product \n";
  cout << "Enter code: \n";
  cin >> pkey;

  data.open("database.txt", ios::in);

  if (!data) {
    cout << "File does not exist";
  } else {
    data1.open("database1.txt", ios::app | ios::out);
    data >> pcode >> pname >> price >> dis;

    while (!data.eof()) {
      if (pkey == pcode) {
        cout << "Deleted successfully";
        token++;
      } else {
        data1 << " " << pcode << " " << pname << " " << price << " " << dis
              << "\n";
      };

      data >> pcode >> pname >> price >> dis;
    };

    data.close();
    data1.close();

    remove("database.txt");
    rename("database1.txt", "database.txt");

    if (token == 0) {
      cout << "Product not found";
    }
  }

  menu();
};

void Shopping::list() {
  fstream data;

  data.open("database.txt");

  cout << "\n";
  cout << "ProdNo\t\tName\t\tPrice";
  cout << "\n";

  data >> pcode >> pname >> price >> dis;

  while (!data.eof()) {
    cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
    data >> pcode >> pname >> price >> dis;
  };

  data.close();
}

void Shopping::receipt() {
  fstream data;
  int arrc[100];
  int arrq[100];
  char choice;
  int c = 0;
  float amount = 0;
  float dis = 0;
  float total = 0;

  cout << "-------------- RECEIPT --------------";
  data.open("database.txt", ios::in);
  if (!data) {
    cout << "Empty database";
  } else {
    data.close();

    list();
    cout << "_______________________________________________\n";
    cout << "            Please place the order\n";
    cout << "_______________________________________________\n";
    do {
    m:
      cout << "Enter product code: \n";
      cin >> arrc[c];
      cout << "Enter quantity: \n";
      cin >> arrq[c];

      for (int i = 0; i < c; i++) {
        if (arrc[i] == arrc[c]) {
          cout << "Dublication\n";
          goto m;
        }
      };

      c++;
      cout << "Do you want to add another product? Press y or n: \n";
      cin >> choice;
    } while (choice == 'y');

    cout << "\t\t\t______________RECEIPT_______________\n";
    cout << "\nProduct No\t Product Name\t Product "
            "quantity\tprice\tAmount\tAmount with discount\n";

    for (int i = 0; i < c; i++) {
      data.open("database.txt", ios::in);
      data >> pcode >> pname >> price >> dis;

      while (!data.eof()) {
        if (pcode == arrc[i]) {
          amount = price * arrq[i];
          dis = amount - (amount * dis / 100);
          total = total + dis;
          cout << "\n"
               << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t"
               << price << "\t" << amount << "\t\t"
               << "dis"
               << "\n";
        }

        data >> pcode >> pname >> price >> dis;
      }
      data.close();
    }
  }

  cout << "\n";
  cout << "TOTAL AMOUNT: " << total << "\n";

  menu();
};

int main() {
  Shopping s;
  s.menu();
}