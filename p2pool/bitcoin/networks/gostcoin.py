import os
import platform

from twisted.internet import defer

from .. import data, helper
from p2pool.util import pack

#P2P_PREFIX = 'f9beb4d9'.decode('hex')
P2P_PREFIX = 'fac4a74b'.decode('hex')
P2P_PORT = 9377
ADDRESS_VERSION = 38
RPC_PORT = 9376
RPC_CHECK = defer.inlineCallbacks(lambda bitcoind: defer.returnValue(
            (yield helper.check_genesis_block(bitcoind, '00000dd00df9728558f339d2e034e2c862329d509018b56d699aec5b6fa6ba1f')) and
            not (yield bitcoind.rpc_getinfo())['testnet']
        ))
SUBSIDY_FUNC = lambda height: 50*100000000 >> (height + 1)//210000
POW_FUNC = lambda data: pack.IntType(256).unpack(__import__('gst_gost').getPoWHash(data))
BLOCK_PERIOD = 600 # s
SYMBOL = 'GST'
CONF_FILE_FUNC = lambda: os.path.join(os.path.join(os.environ['APPDATA'], 'Gostcoin') if platform.system() == 'Windows' else os.path.expanduser('~/Library/Application Support/Gostcoin/') if platform.system() == 'Darwin' else os.path.expanduser('~/.gostcoin'), 'gostcoin.conf')
BLOCK_EXPLORER_URL_PREFIX = 'https://blockchain.info/block/'
ADDRESS_EXPLORER_URL_PREFIX = 'https://blockchain.info/address/'
TX_EXPLORER_URL_PREFIX = 'https://blockchain.info/tx/'
SANE_TARGET_RANGE = (2**256//2**32//1000000 - 1, 2**256//2**32 - 1)
DUMB_SCRYPT_DIFF = 1
DUST_THRESHOLD = 0.001e8

