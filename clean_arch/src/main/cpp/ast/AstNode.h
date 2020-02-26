#pragma once

struct AstLocation {
  const int line;
  const int row;

  AstLocation(int line, int row) : line(line), row(row) {}
};

struct AstNode {
  const AstLocation location;

  AstNode(AstLocation location) : location(location) {}
};
