/*
 ==========================================================================

 Copyright (C) 2018 Giancarlo Zollino
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ==========================================================================
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "IniParser.hpp"
#include <stdlib.h>     /* getenv */

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::map;

class Config{
public:
  static Config* getIstance(string filepath="");
  static void deleteInstance();
  int setSection(string filepath, string sectionName, vector < map <string, string > > values);
  int setConfFile(string filepath);
  void clearConfFile(string filepath);
  IniFile file;


private:
  Config(string filepath="");
  static Config * _instance;
};

#endif
