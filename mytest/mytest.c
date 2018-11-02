
#include "BRCrypto.h"
#include "BRBloomFilter.h"
#include "BRMerkleBlock.h"
#include "BRWallet.h"
#include "BRKey.h"
#include "BRBIP38Key.h"
#include "BRKeyECIES.h"
#include "BRAddress.h"
#include "BRBase58.h"
#include "BRBech32.h"
#include "BRBIP39Mnemonic.h"
#include "BRBIP39WordsEn.h"
#include "BRPeer.h"
#include "BRPeerManager.h"
#include "BRChainParams.h"
#include "BRPaymentProtocol.h"
#include "BRInt.h"
#include "BRArray.h"
#include "BRSet.h"
#include "BRTransaction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SKIP_BIP38 1

#if BITCOIN_TESTNET
#define BR_CHAIN_PARAMS BRTestNetParams
#else
#define BR_CHAIN_PARAMS BRMainNetParams
#endif


static void walletBalanceChanged(void *info, uint64_t balance)
{
    printf("balance changed %"PRIu64"\n", balance);
}

static void walletTxAdded(void *info, BRTransaction *tx)
{
    printf("tx added: %s\n", u256hex(tx->txHash));
}

static void walletTxUpdated(void *info, const UInt256 txHashes[], size_t txCount, uint32_t blockHeight,
                            uint32_t timestamp)
{
    for (size_t i = 0; i < txCount; i++) printf("tx updated: %s\n", u256hex(txHashes[i]));
}

static void walletTxDeleted(void *info, UInt256 txHash, int notifyUser, int recommendRescan)
{
    printf("tx deleted: %s\n", u256hex(txHash));
}

void syncStarted(void *info)
{
    printf("sync started\n");
}

void syncStopped(void *info, int error)
{
    printf("sync stopped: %s\n", strerror(error));
}

void txStatusUpdate(void *info)
{
    printf("transaction status updated\n");
}

void saveBlocks(void *info, int replace, BRMerkleBlock *blocks[], size_t blocksCount){


//
//    printf("save blockes --------------- \n");
//
//    printf("%d\n",replace);
//    printf("%d\n",blocksCount);
//    printf("%d\n",(*blocks)->height);
//    printf("save blockes --------------- \n");

}


int main(int argc, const char *argv[])
{





    int err = 0;
    UInt512 seed = UINT512_ZERO;
    BRMasterPubKey mpk = BR_MASTER_PUBKEY_NONE;
    BRWallet *wallet;
    BRPeerManager *manager;

    //BRBIP39DeriveKey(seed.u8, "video tiger report bid suspect taxi mail argue naive layer metal surface", NULL);
    BRBIP39DeriveKey(seed.u8, "axis husband project any sea patch drip tip spirit tide bring belt", NULL);
    mpk = BRBIP32MasterPubKey(&seed, sizeof(seed));

    wallet = BRWalletNew(NULL, 0, mpk);
    BRWalletSetCallbacks(wallet, wallet, walletBalanceChanged, walletTxAdded, walletTxUpdated, walletTxDeleted);
    printf("wallet created with first receive address: %s\n", BRWalletReceiveAddress(wallet).s);

//    manager = BRPeerManagerNew(&BRMainNetParams, wallet, BIP39_CREATION_TIME, NULL, 0, NULL, 0);
    manager = BRPeerManagerNew(&BRMainNetParams, wallet, 1538639362, NULL, 0, NULL, 0);
    BRPeerManagerSetCallbacks(manager, manager, syncStarted, syncStopped, txStatusUpdate, saveBlocks, NULL, NULL, NULL);

    BRPeerManagerConnect(manager);


    while (err == 0 && BRPeerManagerPeerCount(manager) > 0){

       uint32_t height = BRPeerManagerLastBlockHeight(manager);
        double progress = BRPeerManagerSyncProgress(manager,0);
        const char * name = BRPeerManagerDownloadPeerName(manager);

        printf("--- %f,%d,%s ---\n",progress,height,name);


        err = sleep(1);
    }



    if (err != 0) printf("sleep got a signal\n");

    BRPeerManagerDisconnect(manager);
    BRPeerManagerFree(manager);
    BRWalletFree(wallet);
    sleep(5);

}

