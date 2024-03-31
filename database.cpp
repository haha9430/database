#include "database.h"
#include <iostream>
#include <string>
using namespace std;

// 엔트리를 생성한다.
Entry *create(Type type, std::string key, void *value) {
    // 새로운 entry를 동적 할당
    Entry* newEntry = new Entry;
    // 새로운 entry에 parameter 값들을 대입
    newEntry->type = type;
    newEntry->key = key;
    newEntry->value = value;
    // 새로운 entry를 반환
    return newEntry;
}

// 데이터베이스를 초기화한다.
void init(Database &database) {
    database.size = 0;
    database.entryArray = nullptr;
}

// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry) {
    // database의 size를 1만큼 증가
    database.size++; 
    // 새로운 entryArray를 database의 size만큼 동적 할당
    Entry** newEntryArray = new Entry*[database.size];
    // 새로운 entryArray에 기존 entryArray의 값들을 복사
    for (int i = 0; i < database.size-1; i++) {
        newEntryArray[i] = database.entryArray[i];
    }
    // 새로운 entryArray의 마지막에 대입
    newEntryArray[database.size - 1] = entry;
    // 기존 entryArray는 동적 해제
    delete[] database.entryArray;
    // 기존 entryArray에 새로운 entryArray를 대입
    database.entryArray = newEntryArray;
}

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry *get(Database &database, std::string &key) {
    // key값이 같은 entry를 찾아 대입
    for (int i = 0; i < database.size; i++) {
        if (database.entryArray[i]->key.compare(key) == 0) {
            return database.entryArray[i];
        }
    }
    // 해당 entry를 넣은 entry 포인터를 반환
    return nullptr;
}

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database &database, std::string &key) {
    Entry* entry = get(database, key);
    if (entry == nullptr) {
        cout << "Not found" << endl;
    }else {
        // parameter로 받은 key값을 가진 entry의 순서
        int pos;
        // 위의 key값을 가진 entry의 순서를 찾는 과정
        for (int i = 0; i < database.size; i++) {
            if (database.entryArray[i]->key.compare(key) == 0) {
            pos = i;
            }
        }
        // 새로운 entryArray를 database의 size - 1만큼 동적 할당
        Entry** newEntryArray = new Entry*[database.size - 1];
        // 새로운 entryArray에 기존 entryArray[pos]를 뺀 나머지 값들을 복사
        for (int i = 0; i < pos; i++) {
            newEntryArray[i] = database.entryArray[i];
        }
        for (int i = pos; i < database.size - 1; i++) {
            newEntryArray[i] = database.entryArray[i + 1];
        }
        // database의 size를 1만큼 감소
        database.size--;
        // 기존 entryArray는 동적 해제
        delete[] database.entryArray;
        // 기존 entryArray에 새로운 entryArray를 대입
        database.entryArray = newEntryArray;
    }
    
}

// 데이터베이스를 해제한다.
void destroy(Database &database) {
    // database의 size만큼 entryArray를 동적 해제
    for (int i = 0; i > database.size; i++) {
        delete database.entryArray[i];
    }
    delete[] database.entryArray;
}


// 데이터베이스의 내용을 모두 출력한다.
void printDB(Database &database) {
    // database의 size만큼 entryArray를 출력
    for (int i = 0; i < database.size; i++) {
        printEntry(database.entryArray[i]);
    }
}

// 엔트리의 내용을 출력한다.
void printEntry(Entry *entry) {
    if (entry == nullptr) {
        cout << "Not found" << endl;
    }else {
        switch (entry->type) {
            case INT:
                cout << entry->key << ": ";
                cout << *(static_cast<int*>(entry->value)) << endl;
                break;
            case DOUBLE:
                cout << entry->key << ": ";
                cout << *(static_cast<double*>(entry->value)) << endl;
                break;
            case STRING:
                cout << entry->key << ": ";
                cout << "\"" << *(static_cast<string*>(entry->value)) << "\"" << endl;
                break;
            case ARRAY:
                cout << entry->key << ": ";
                printArray(static_cast<Array*>(entry->value));
                cout << endl;
                break;
        }
        
    }
}

// array의 내용을 출력한다.
void printArray(Array *array) {
    cout << "[";

    if (array->type == INT) {
        int* Items = (static_cast<int*>(array->items));
        for (int i = 0; i < (array->size) - 1; i++) {
            cout << Items[i] << ", ";
        }
        cout << Items[(array->size) - 1] << "]";
    }else if (array->type == DOUBLE) {
        double* Items = (static_cast<double*>(array->items));
        for (int i = 0; i < (array->size) - 1; i++) {
            cout << Items[i] << ", ";
        }
        cout << Items[(array->size) - 1] << "]";
    }else if (array->type == STRING) {
        string* Items = (static_cast<string*>(array->items));
        for (int i = 0; i < (array->size) - 1; i++) {
            cout << "\"" << Items[i] << "\", ";
        }
        cout << "\"" << Items[(array->size) - 1] << "\"]";
    }else if (array->type == ARRAY) {
        Array* Items = (static_cast<Array*>(array->items));
        for (int i = 0; i < (array->size); i++) {
            printArray(&Items[i]);
        }
        cout << "]";
    }
}

// 배열을 생성한다.
Array *create(int size, Type type, void *items) {
    // 새로운 array를 동적 할당
    Array* newArray = new Array;
    // 새로운 array에 parameter 값들을 대입
    newArray->size = size;
    newArray->type = type;
    newArray->items = items;
    // 새로운 entry를 반환
    return newArray;
}