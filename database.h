#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>

enum Type { INT, DOUBLE, STRING, ARRAY };

struct Array {
  int size;
  Type type;
  void *items;
};

struct Entry {
  Type type;
  std::string key;
  void *value;
};

struct Database {
  Entry** entryArray;
  int size;
};

// 엔트리를 생성한다.
Entry *create(Type type, std::string key, void *value);

// 데이터베이스를 초기화한다.
void init(Database &database);

// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry);

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry *get(Database &database, std::string &key);

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database &database, std::string &key);

// 데이터베이스를 해제한다.
void destroy(Database &database);

// 데이터베이스의 내용을 모두 출력한다.
void printDB(Database &database);

// 엔트리의 내용을 출력한다.
void printEntry(Entry *entry);

// 배열의 내용을 출력한다.
void printArray(Array *array);

// 배열을 생성한다.
Array *create(int size, Type type, void *items);

#endif