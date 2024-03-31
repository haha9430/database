#include "database.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

// Database 선언
Database database;
// 대표적으로 쓸 커맨드와 타입들
string command[5] = {"list", "add", "get", "del", "exit"};
string type[4] = {"int", "double", "string", "array"};
// string 타입의 input 함수
string inputS() {
  string s;
  cin >> s;
  return s;
}
// int 타입의 input 함수
int inputI() {
  int i;
  cin >> i;
  return i;
}
// double 타입의 input 함수
double inputD() {
  double d;
  cin >> d;
  return d;
}
// array* 타입의 array를 입력받는 input 함수
Array* inputA(string arrayT) {
  // 반환할 array;
  Array* array;
  // int 타입의 array일 때
  if (arrayT.compare(type[0]) == 0) {
    int arrayS = inputI();
    int* arrayInt = new int[arrayS];
    for (int i = 0; i < arrayS; i++) {
      int item;
      cout << "item[" << i << "]: ";
      cin >> item;
      arrayInt[i] = item;
    }
    array = create(arrayS, INT, arrayInt);
  // double 타입의 array일 때
  }else if (arrayT.compare(type[1]) == 0) {
    int arrayS = inputI();
    double* arrayDouble = new double[arrayS];
    for (int i = 0; i < arrayS; i++) {
      double item;
      cout << "item[" << i << "]: ";
      cin >> item;
      arrayDouble[i] = item;
    }
    array = create(arrayS, DOUBLE, arrayDouble);
  // string 타입의 array일 때
  }else if (arrayT.compare(type[2]) == 0) {
    int arrayS = inputI();
    cin.ignore();
    string* arrayString = new string[arrayS];
    for (int i = 0; i < arrayS; i++) {
      string item;
      cout << "item[" << i << "]: ";
      getline(cin, item);
      arrayString[i] = item;
    }
    array = create(arrayS, STRING, arrayString);
  // Array 타입의 array일 때
  }else if (arrayT.compare(type[3]) == 0) {
    int arrayS = inputI();
    Array* arrayArray = new Array[arrayS];
    for (int i = 0; i < arrayS; i++) {
      cout << "item[" << i << "]: ";
      cout << "type (int, double, string, array): ";
      string arrayT1 = inputS();
      cout << "size: ";
      if (arrayT.compare(type[0]) == 0 || arrayT.compare(type[1]) == 0 || arrayT.compare(type[2]) == 0 || arrayT.compare(type[3]) == 0) {
        arrayArray[i] = *inputA(arrayT1);
      }
    }
    array = create(arrayS, ARRAY, arrayArray);
  }
  return array;
}

// 메인 로직 함수
void logic() {
  // database를 초기화(기본 세팅)
  init(database);
  while (true) {
    // 동적 할당을 위한 변수를 선언
    int* vInt;
    double* vDouble;
    string* vString;
    int* arrayInt;
    // command를 input
    cout << "command (list, add, get, del, exit): ";
    string commandS = inputS();
    // command가 list일 때
    if (commandS.compare(command[0]) == 0){
      // database의 내용을 모두 출력
      printDB(database);
    // command가 add일 때  
    }else if (commandS.compare(command[1]) == 0) {
      // entry의 key를 input
      cout << "key: ";
      string k = inputS();
      // entry의 type을 input
      cout << "type (int, double, string, array): ";
      string t = inputS();
      cout << "value: ";
      // type이 int일 때
      if (t.compare(type[0]) == 0) {
        // vInt를 동적 할당
        vInt = new int;
        *vInt = inputI();
        Entry* entry = create(INT, k, vInt);
        add(database, entry);
      // type이 double일 때
      }else if (t.compare(type[1]) == 0) {
        // vDouble를 동적 할당
        vDouble = new double;
        *vDouble = inputD();
        Entry* entry = create(DOUBLE, k, vDouble);
        add(database, entry);
      // type이 string일 때
      }else if (t.compare(type[2]) == 0) {
        // vString를 동적 할당
        vString = new string;
        cin.ignore();
        getline(cin, *vString);
        Entry* entry = create(STRING, k, vString);
        add(database, entry);
      // type이 array일 때
      }else if (t.compare(type[3]) == 0) {
        // array의 type을 input
        cout << "type (int, double, string, array): ";
        string arrayT = inputS();
        // array의 size를 input
        cout << "size: ";
        // type이 int, double, string, array일 때
        if (arrayT.compare(type[0]) == 0 || arrayT.compare(type[1]) == 0 || arrayT.compare(type[2]) == 0 || arrayT.compare(type[3]) == 0) {
          // array를 input
          Array* array = inputA(arrayT);
          Entry* entry = create(ARRAY, k, array);
          // entry에 array를 넣은 다음 database에 add
          add(database, entry);
        // type이 그 외일 때
        }else {
          // 다시 입력
          cout << "invalid type" << endl;
          continue;
        }
      // type이 그 외일 때
      }else {
        // 다시 입력
        cout << "invalid type" << endl;
        continue;
      }
    // command가 get일 때
    } else if (commandS.compare(command[2]) == 0) {
      // get할 key를 input
      cout << "key: ";
      string k = inputS();
      Entry* entry = get(database, k);
      printEntry(entry);
    // command가 del일 때
    } else if (commandS.compare(command[3]) == 0) {
      // del할 key를 input
      cout << "key: ";
      string k = inputS();
      remove(database, k);
    // command가 exit일 때
    } else if (commandS.compare(command[4]) == 0) {
      // database 동적 해제
      destroy(database);
      break;
    // command가 그 외일 때
    } else {
      // 다시 입력
      cout << "invalid command" << endl;
      cout << endl;
      continue;
    }
    // 줄바꿈
    cout << endl;
  }
}
// 메인 함수
int main() {
  // 로직 함수 실행
  logic();
  return 0;
}