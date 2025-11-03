#include "game.h"
#include <bits/stdc++.h>
int main(){
  Game g(std::cin);
  std::cerr<<"ok: bricksTotal="<<g.bricksTotal()<<" remaining="<<g.bricksRemaining()<<"\n";
  return 0;
}
