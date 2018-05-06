#include "Map.h"
#include "City.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

Map::Map(string filename) {
  ifstream myfile(filename);
  string name;
  int x,y;
  while (myfile >> name >> x >> y) {
    City * temp = new City(name, x, y);
    map.push_back(temp);

  }
  for (auto i: map) {
    findAdjacents(i);
  }
}

// Map::Map(const Map &copy) {
//   vector<City *> temp = copy.getMap();
//   for (auto i : temp) {
//     map.push_back(new City(i.getName(), i.getXCoor(), i.getYCoor()));
//   }
// }

vector<City *> Map::getMap() {
  return map;
}




City * Map::findByName(string cityName) {
  for (auto i : map) {
    if (i->getName() == cityName) {
      return i;
    }
  }
  return nullptr;

}

void Map::findAdjacents(City * temp) {
  int north = 0;
  int south = 0;
  int west = 0;
  int east = 0;
  for (auto i : map) {
    if (i->getXCoor() == temp->getXCoor() && i->getYCoor() - temp->getYCoor() > 0) {
      if (north == 0) {
        temp->addAdjacent(i, "n");
        north = i->getYCoor() - temp->getYCoor();
      } else {
        if (temp->getYCoor() - i->getYCoor() < north) {
          temp->addAdjacent(i, "n");
          north = i->getYCoor() - temp->getYCoor();
        }
      }
    } else if (i->getXCoor() == temp->getXCoor() && i->getYCoor() - temp->getYCoor() < 0) {
      if (south == 0) {
        temp->addAdjacent(i, "s");
        south = temp->getYCoor() - i->getYCoor();
      } else {
        if (i->getYCoor() - temp->getYCoor() < south) {
          temp->addAdjacent(i, "s");
          south = temp->getYCoor() - i->getYCoor();
        }
      }
    } else if (i->getYCoor() == temp->getYCoor() && i->getXCoor() - temp->getXCoor() > 0) {
      if (east == 0) {
        temp->addAdjacent(i, "e");
        east = i->getXCoor() - temp->getXCoor();
      } else {
        if (temp->getYCoor() - i->getYCoor() < east) {
          temp->addAdjacent(i, "e");
          east = temp->getXCoor() - i->getXCoor();
        }
      }
    } else if (i->getYCoor() == temp->getYCoor() && i->getXCoor() - temp->getXCoor() < 0) {
      if (west == 0) {
        temp->addAdjacent(i, "w");
        west = temp->getXCoor() - i->getXCoor();
      } else {
        if (i->getYCoor() - temp->getYCoor() < west) {
          temp->addAdjacent(i, "w");
          west = temp->getXCoor() - i->getXCoor();
        }
      }
    }
  }
}
