// Copyright anssi.grohn@karelia.fi (c) 2014.
// Licensed under GPLv3.
#include "Game.h"
#include <iostream>
#include <string>
////////////////////////////////////////////////////////////////////////////////
using namespace std;
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
  Game & g = *Game::GetInstance();
  g.Play();

  return 0;
}
////////////////////////////////////////////////////////////////////////////////
