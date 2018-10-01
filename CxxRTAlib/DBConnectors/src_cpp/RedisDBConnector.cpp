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

#include"RedisDBConnector.hpp"

int RedisDBConnector::connect(){

  cout << "REDISDBCONNECTOR CONNECT" << endl;

  hostname = config->file["Redis"]["host"].getString();
  username = config->file["Redis"]["username"].getString();
  password = config->file["Redis"]["password"].getString();
  database = config->file["Redis"]["dbname"].getString();
  indexon = config->file["Redis"]["indexon"].getString();
  modelName = config->file["General"]["modelname"].getString();
  batchsize = config->file["General"]["batchsize"].getInt();

  int dp = indexon.find(":");
  indexon_clean = indexon.substr(dp+1,indexon.size());

  cout << "Hostname: " << hostname << endl;
  cout << "Database: " << database << endl;
  cout << "Batchsize: " << batchsize << endl;
  cout << "Indexon: " << indexon << endl;

  connection(hostname.c_str(),password.c_str(),database.c_str());
}

int RedisDBConnector :: disconnect(){

  cout << "REDISDBCONNECTOR DISCONNECT" << endl;

  close_connection();

}

int RedisDBConnector :: testConnection(){

}

int RedisDBConnector :: insertData(map < string, string > args){


  #ifdef DEBUG
  cout << "INSERT DATA FUNCTION" << endl;
  cout << "Batchsize: " << batchsize << endl;
  cout << "Modelname: " << modelName << endl;
  #endif

  string query = buildQuery(modelName, batchsize, args);

  if( batchsize == 1){

    streamingInsert(query);

  }else if(batchsize > 1){

    flagTransaction = 1;

    int commandsSent = batchInsert(query, batchsize);

  }else{
    cout << "[RedisConnector] Error, self.conn is None" << endl;
    return EXIT_FAILURE;
  }

  return commandsSent;

}


int RedisDBConnector :: streamingInsert(string query){

  #ifdef DEBUG
  cout << "STREAMING" << endl;
  #endif

  streamingInsert_c(modelName.c_str(), score.c_str(), query.c_str());



}


int RedisDBConnector :: batchInsert(string query, int batchsize){

  #ifdef DEBUG
  cout << "BATCHSIZE" << endl;
  #endif

  batchInsert_c(modelName.c_str(), score.c_str(),query.c_str(),batchsize);


}


string RedisDBConnector :: buildQuery(string modelName, int batchsize, map <string,string> args){

  #ifdef DEBUG
  cout <<"Tablename: " << modelName << endl;
  #endif

  string query;

  string queryH = "'{";

  for (map<string,string>::iterator it=args.begin(); it!=args.end(); ++it) {

    queryH += it->first + " : " + it->second + ", ";

  }

  queryH = queryH.substr(0,queryH.size()-2);

  // cout << "Indexon cleaned: " << indexon_clean << endl;

  int p = queryH.find(indexon_clean);

  // cout << "p: " << p << endl;

  int q = queryH.find(":", p);

  // cout << "q: " << q << endl;

  // cout << "QueryH size: " << queryH.size()-1 << endl;

  score = queryH.substr(q+2,queryH.size()-1);

  // cout << "score: " << score << endl;

  queryH += "}'";


  return queryH;
}
