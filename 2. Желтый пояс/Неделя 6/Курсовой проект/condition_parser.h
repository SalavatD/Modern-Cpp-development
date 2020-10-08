#pragma once

#include "node.h"

#include <memory>
#include <iostream>

using namespace std;

Date ParseDate(std::istream &is);

shared_ptr<Node> ParseCondition(istream &is);
