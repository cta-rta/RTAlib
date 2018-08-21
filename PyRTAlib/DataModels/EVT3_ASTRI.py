# ==========================================================================
#
# Copyright (C) 2018 INAF - OAS Bologna
# Author: Leonardo Baroncelli <leonardo.baroncelli26@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# ==========================================================================
import time
from ..Utils import time_mjd_to_tt


class EVT3_ASTRI():
    def __init__(self, eventidfits, timemjd, ra_deg, dec_deg, energy, detx, dety, mcid, mjdref, observationid, datarepositoryid, status):

        ## BUG: TypeError: Object of type 'uint32' is not JSON serializable
        ## -> <class 'numpy.uint32'> I convert those data to int() in order to convert it to json later in RedisDBConnector
        self.eventidfits = float(eventidfits)
        self.ra_deg = float(ra_deg)
        self.dec_deg = float(dec_deg)
        self.energy = float(energy)
        self.detx = float(detx)
        self.dety = float(dety)
        self.mcid = float(mcid)

        self.timerealtt = time_mjd_to_tt(mjdref) + float(timemjd)
        self.insert_time = time.time()

        self.observationid = int(observationid)
        self.datarepositoryid = int(datarepositoryid)
        self.status = int(status)

        pass

    def getData(self):
        """Return the 'dictionary' representation of the object.
        """
        return vars(self)

    """
    def getInsertQuery(self, table):
        query = 'INSERT INTO '+table
        queryK = '(eventidfits, ra_deg, dec_deg, energy, detx, dety, mcid, timerealtt, insert_time, observationid, datarepositoryid, status) '
        queryV = 'VALUES('  +str(self.eventidfits)+', '       \
                            +str(self.ra_deg)+', '            \
                            +str(self.dec_deg)+', '           \
                            +str(self.energy)+', '            \
                            +str(self.detx)+', '              \
                            +str(self.dety)+', '              \
                            +str(self.mcid)+', '              \
                            +str(self.timerealtt)+', '        \
                            +str(self.insert_time)+', '       \
                            +str(self.observationid)+', '     \
                            +str(self.datarepositoryid)+', '  \
                            +str(self.status)+')'
        return query+queryK+queryV
    """
