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

import unittest
from random import randint, uniform
from time import sleep

from PyRTAlib.DTRInterface.DTR  import DTR
from PyRTAlib.Utils         import Config
from PyRTAlib.DataModels import EVT3_ASTRI

"""
 (            (
 )\ )   *   ) )\ )
(()/( ` )  /((()/(
 /(_)) ( )(_))/(_))
(_))_ (_(_())(_))
 |   \|_   _|| _ \
 | |) | | |  |   /
 |___/  |_|  |_|_\
"""
class DTRTEST(unittest.TestCase):

    def test_dtr(self):
        config = Config('./')
        config.set('Dtr', 'debug', 'yes')
        dtr = DTR('./')

        evt3 = EVT3_ASTRI(*EVT3_ASTRI.getRandomEvent(), 1, 0, 0, 1)

        dtr.publish(evt3)
        sleep(1.5)
        dtr.waitAndClose()

if __name__ == '__main__':
    unittest.main()