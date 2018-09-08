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


/* Standard C++ includes */
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using std::string;
using std::pair;
using std::vector;
using std::cout;
using std::endl;

class DBConnector {
public:
  DBConnector(string hostname, string username, string password, string database, string tablename);
  virtual int connect();
  virtual int disconnect();
  virtual int testConnection();
  virtual int insertData(string modelName, std::vector < pair < string, double > > args);

  string hostname;
  string username;
  string password;
  string database;
  string tablename;
};
