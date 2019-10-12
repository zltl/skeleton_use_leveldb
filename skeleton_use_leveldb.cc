#include "skeleton_use_leveldb.h"
#include <assert.h>
#include <leveldb/db.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;

  // open
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
  assert(status.ok());

  string key = "keytest";
  string value = "this is the value of keytest";

  // write
  status = db->Put(leveldb::WriteOptions(), key, value);
  assert(status.ok());

  // read
  status = db->Get(leveldb::ReadOptions(), key, &value);
  assert(status.ok());

  cout << "Read OK: value of " << key << " is " << value << endl;

  // delete
  status = db->Delete(leveldb::WriteOptions(), key);
  assert(status.ok());

  status = db->Get(leveldb::ReadOptions(), key, &value);
  assert(!status.ok());

  // close
  delete db;

  return 0;
}
