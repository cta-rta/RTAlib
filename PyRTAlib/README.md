# PyRTAlib
The Python version of the RTAlib.

## Dependencies
The following external dependencies are needed:
* Python 3.6+
* MySql server (Ver 14.14 Distrib 5.7.17, for Linux (x86_64))
* Redis server (4.0.10+)

## Features
The following features are supported:
- inserting data in a MySql/Redis database in a batch (using transactions) or a streaming fashion [A1], using a synchronous single-thread or asynchronous (single or multi-threads) strategies [A2].
- [B] possibility to update other tables at the end of each transaction.
- [C] using the Redis Pub/Sub mechanism to send messages and data into Redis channels to enable asynchronous communication between the RTAlib and other systems.
- [D] specifying the type of data with the implementation of the data model classes.
- [E] a stand alone deamon that uses Redis Pub/Sub mechanism, listens for the RTAlib data messages and forward those data messages to a [https://github.com/IftachSadeh/ctaOperatorGUI] (Graphic User Interface) displaying Data Quality components.

## Who implements the features
- DBConnectors
  - [A1] this module expose an interface that can be used to insert data in a database. Two databases are supported: MySql and Redis. Two types of insertion strategies can be adopted: batch-insert or streaming-insert.
- RTAInterface
  - [A2] the RTA_DL_DB.py base class implements the synchronous or asynchronous (even multi-threading) execution.
  - [B] The code to execute queries after every commit (when a transaction is closed) can be inserted within any class that iherits the RTA_DL_DB.py base class. This is available only in synchronous mode.
  - [C] the RTA_DL_DB.py can send data to a Redis channel specified in the configuration file (Dtr/inputchannel).
- DataModels [D]
  - this module contains all the classes that describe the data types that are stored in the database.

## Installation
* Create a virtualenv:
  ```bash
    conda create --name rtalib python=3.6
  ```
* Activate the virtualenv:
  ```bash
    source activate rtalib
  ```
* Install dependencies with:
  ```Python
    python setup.py install
  ```
* Rename the configuration file from rtalibconfig_default to rtalibconfig.
* Fill in the configuration file's fields.

## Setup the test environment
* Call the following script that takes in input a MySql username with enough privileges to create a database:
  ```bash
    . PyRTAlib/TestEnvironment/setup_test.sh
  ```
  The script will create a database for testing purpose, an associated user and two tables. It will also create a rtalibconfig configuration file for the test environment (located under PyRTAlib/TestEnvironment).
* Set the Redis password in the rtalibconfig configuration file.

## Configuration options
```
[General]
modelname=         # the name of the mysql table or of the redis zset/hashset
mjdref=            # MJDREFI+MJDREFF
debug=             # yes/y/True/'True' or any other value for False
batchsize=         # performance tuning parameter: the input streaming is writed to db with a batch strategy (if batchsize > 1)
numberofthreads=   # performance tuning parameter: more than one thread may help to sustain a high-rate input streaming

[Dtr]
guiname=
active=            # yes/y/True/'True' or any other value for False
debug=             # yes/y/True/'True' or any other value for False
inputchannel=
outputchannel=

[MySql]
host=
username=
password=
dbname=

[Redis]
host=
password=
dbname=
indexon=           # key:value,key:value

[MySqlPipelineDatabase]
active=            # yes/y/True/'True' or any other value for False
debug=             # yes/y/True/'True' or any other value for False
host=
username=
password=
dbname=
```

## General usage
* Specify the location of the configuration file
* Create a RTA_DL_DB object of the right subclass specifying the database type
* Send events to the RTA pipeline with insertEvent()
* Close connection with close()

### Example

```python
from PyRTAlib.RTAInterface import RTA_DL3ASTRI_DB

# The RTACONFIGFILE environment variabile is used to specify the configuration file path.
os.environ['RTACONFIGFILE'] = './path/to/config/file'  

# In the class constructor is specified the database in which the events will be writed.
RTA_DL3ASTRI = RTA_DL3ASTRI_DB('redis-basic')

# The insertEvent(..) method writes the events in the database.
for i in range(10000):
  RTA_DL3ASTRI.insertEvent(..)

# If multithreading has been setted up, the waitAndClose() methods blocks the execution
# until all threads finish their jobs
RTA_DL3ASTRI.waitAndClose()
```

### Example 2
The library can be also used with the following, pythonic syntax:
```python
from PyRTAlib.RTAInterface import RTA_DL3ASTRI_DB

os.environ['RTACONFIGFILE'] = './path/to/config/file'

with RTA_DL3ASTRI_DB('mysql') as RTA_DL3ASTRI:
    RTA_DL3ASTRI.insertEvent( evtid, eventidfits, observationid, datarepositoryid, ra_deg...)
```
the waitAndClose() method is implicitally called as the execution flow exits from the 'with' statement.

## Testing

### Unit testing
The classes under unit testing are:
* Config.py
* MySqlDBConnector.py
* RedisDBConnector.py

In order to run the unit tests you can use the following script:
```bash
  cd TestEnvironment/unit_tests
  . run_unit_tests.sh
```

### performance test (single and multithreading)
This test will print the execution time (sec) and event rate (events/sec) of the library writing to the database a
fixed number of events. It is possibile to configure the runs modifying the configuration section within the source code.

Scripts:
* performance_test.py
* performance_test_multithreading.py

Arguments:
* database
* number of events
* path to the configuration file

```python
python performance_test.py redis-basic 5000 ../
python performance_test_multithreading.py mysql 5000 ../

```

## Test code coverage
The code coverage is measured with a synchronous single-thread execution.

Coverage.py ([docs](https://coverage.readthedocs.io/en/v4.5.x/index.html)) collects execution data in a file called “.coverage”. If need be, you can set a new file name (.coverage.xyz

If you need to collect coverage data from different machines or processes, coverage.py can combine multiple files into one for reporting. Once you have created a number of these files
```bash
coverage combine
coverage combine results_folder/
```
To erase the collected data, use the erase command:
```bash
coverage erase
```

Reporting:
* Coverage.py provides a few styles of reporting, with the report, html, annotate, and xml commands.
* If you provide a --fail-under value, the total percentage covered will be compared to that value. If it is less, the command will exit with a status code of 2, indicating that the t
* The -m flag also shows the line numbers of missing statements.
* The --skip-covered switch will leave out any file with 100% coverage, letting you focus on the files that still need attention.
* The html command creates an HTML report similar to the report summary, but as an HTML file. Each module name links to the source file decorated to show the status of each line. [htm

Configuration file options: https://coverage.readthedocs.io/en/v4.5.x/config.html


### Check installation of Coverage library
The following command:
```python
coverage --version
```
should output:
```
Coverage.py, version 5.0a3 with C extension
Documentation at https://coverage.readthedocs.io/en/coverage-5.0a3
```
If the C extension is not present, you may need to install the python-dev and gcc support files before installing coverage. You can use:
```bash
sudo apt-get install python3-dev gcc
```
or
```bash
sudo yum install python3-devel gcc
```
### Statement coverage

```bash
coverage run my_program.py arg1 arg2
```
If your coverage results seem to be overlooking code that you know has been executed, try running coverage.py again with the --timid flag.

### Branch coverage
```bash
coverage run --branch my_program.py arg1 arg2
```

* Exluding [debug branches](https://coverage.readthedocs.io/en/v4.5.x/excluding.html#excluding-code-from-coverage-py)
* Exluding [structurally partial branches](https://coverage.readthedocs.io/en/v4.5.x/branch.html#structurally-partial-branches)

## DTR
### Starting the DTR deamon
DTR is a standalone python deamon which purpose is to send to the scientific/data quality GUIs the data coming from the RTAlib. The RTAlib stores the DL1/DL2/DL3 events in a database and then, it publish those events in a Redis PubSub channel (the channel's name is specified in the configuration file). The DTR will listen for data on this channel and when an event arrives, the DTR push the event in a queue. An asynchronous thread will consume the queue and each event is transformed (in a data format for GUI visualization) and pushed into another Redis PubSub channel (GUIs channel).

In order to start the DTR, execute the startDTR.py script specifying the path to the configuration file.

```bash
  cd RTAlib/PyRTAlib
  python startDTR.py ./
```



## API
```python
class RTA_DL3ASTRI_DB.RTA_DL3ASTRI_DB(database, configFilePath = '', pure_multithreading = False)
```
Constructor for a RTA_DL3ASTRI_DB object.
Arguments:
* *database* (required) is a string that sets the database type.
* *configFilePath* (optional) is a string that specifies the location of the configuration file (it will be overrided by the RTACONFIGFILE environment variabile, if set)
* *pure_multithreading* (optional) is a boolean that specifies the *pure multithreading* mode. When the number of threads is configured equal to one, a False value means that the execution flow is synchronous i.e. no asynchronous threads are created.
___
```python
class RTA_DL3ASTRI_DB.insertEvent(eventidfits, time, ra_deg, dec_deg, energy, detx, dety, mcid, observationid = 0, datarepositoryid = 0, status = 1)
```
Implements the the *class RTA_DL_DB.insertEvent(°args)* abstract method of the base class.
___
```python
class RTA_DL3ASTRI_DB.waitAndClose()
```
TODO
If the multithreading mode has been set, it returns:
* (totalEvents, executionTime, eventRate)
___
```python
class RTA_DL3ASTRI_DB.forceClose()
```
TODO
___
