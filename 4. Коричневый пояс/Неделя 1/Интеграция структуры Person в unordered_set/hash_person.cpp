#include <limits>
#include <random>
#include <unordered_set>

using namespace std;

struct Address {
  string city, street;
  int building;

  bool operator==(const Address& other) const {
    return
      city == other.city && street == other.street && building == other.building;
  }
};

struct Person {
  string name;
  int height;
  double weight;
  Address address;

  bool operator==(const Person& other) const {
    return name == other.name && height == other.height && weight == other.weight && address == other.address;
  }
};

struct AddressHasher {
  size_t operator()(const Address& address) const {
    hash<int> int_hasher;
    hash<string> string_hasher;
    size_t x = 41;
    size_t a = string_hasher(address.city);
    size_t b = string_hasher(address.street);
    size_t c = int_hasher(address.building);
    return x * x * a + x * b + c;
  }
};

struct PersonHasher {
  size_t operator()(const Person& person) const {
    hash<int> int_hasher;
    hash<double> double_hasher;
    hash<string> string_hasher;
    AddressHasher address_hasher;
    size_t coef = 41;
    size_t a = string_hasher(person.name);
    size_t b = int_hasher(person.height);
    size_t c = double_hasher(person.weight);
    size_t d = address_hasher(person.address);
    return a * x * x * x + b * x * x + c * x + d;;
  }
};
