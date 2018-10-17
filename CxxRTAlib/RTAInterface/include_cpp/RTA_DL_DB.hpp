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

#ifndef RTA_DL_DB_H
#define RTA_DL_DB_H


#include "MySqlDBConnector.hpp"
#include "RedisDBConnector.hpp"
#include "RTAThread.hpp"

using std::cout;
using std::endl;
using std::string;

class RTA_DL_DB {
public:

  RTA_DL_DB(string database, string configFilePath = "");

  DBConnector * dbConnector;
  Config * config;
  CTABuffer * eventBuffer;


  int numberofthreads = 0;
  string modelname;

  std::vector<Thread*> thread_array;
  std::vector<ThreadStatistic*> thread_statistics_array;

  void start();
  DBConnector * getConnector(int id,string databaseEngine, string configFilePath);
  int _insertEvent(EVTbase *event);
  bool waitAndClose();

};

#endif
