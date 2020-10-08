#include "json.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Spending {
  string category;
  int amount;
};

vector<Spending> LoadFromJson(istream& input) {
  vector<Spending> result;
  Document document = Load(input);
  for (const Node& node : document.GetRoot().AsArray()) {
    result.push_back({node.AsMap().at("category").AsString(), node.AsMap().at("amount").AsInt()});
  }
  return result;
}
