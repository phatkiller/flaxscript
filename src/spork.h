
// Copyright (c) 2009-2012 The Flaxscript developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef SPORK_H
#define SPORK_H

#include "bignum.h"
#include "sync.h"
#include "net.h"
#include "key.h"
#include "core.h"
#include "util.h"
#include "script.h"
#include "base58.h"
#include "main.h"

using namespace std;
using namespace boost;

// Don't ever reuse these IDs for other sporks
#define SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT               10000
#define SPORK_2_INSTANTX                                      10001
#define SPORK_3_INSTANTX_BLOCK_FILTERING                      10002
#define SPORK_4_NOTUSED                                       10003
#define SPORK_5_MAX_VALUE                                     10004
#define SPORK_6_NOTUSED                                       10005
#define SPORK_7_MASTERNODE_SCANNING                           10006

#define SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT_DEFAULT       1424217600  //2015-2-18
#define SPORK_2_INSTANTX_DEFAULT                              978307200   //2001-1-1
#define SPORK_3_INSTANTX_BLOCK_FILTERING_DEFAULT              1424217600  //2015-2-18
#define SPORK_5_MAX_VALUE_DEFAULT                             1000        //1000 FLAX
#define SPORK_7_MASTERNODE_SCANNING_DEFAULT                   978307200   //2001-1-1

class CSporkMessage;
class CSporkManager;

#include "bignum.h"
#include "net.h"
#include "key.h"
#include "util.h"
#include "protocol.h"
#include "darksend.h"
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

extern std::map<uint256, CSporkMessage> mapSporks;
extern std::map<int, CSporkMessage> mapSporksActive;
extern CSporkManager sporkManager;

void ProcessSpork(CNode* pfrom, std::string& strCommand, CDataStream& vRecv);
int GetSporkValue(int nSporkID);
bool IsSporkActive(int nSporkID);
void ExecuteSpork(int nSporkID, int nValue);

//
// Spork Class
// Keeps track of all of the network spork settings
//

class CSporkMessage
{
public:
    std::vector<unsigned char> vchSig;
    int nSporkID;
    int64_t nValue;
    int64_t nTimeSigned;

    uint256 GetHash(){
        uint256 n = HashC11(BEGIN(nSporkID), END(nTimeSigned));
        return n;
    }

    IMPLEMENT_SERIALIZE(
        READWRITE(nSporkID);
        READWRITE(nValue);
        READWRITE(nTimeSigned);
        READWRITE(vchSig);
    )
};


class CSporkManager
{
private:
    std::vector<unsigned char> vchSig;

    std::string strMasterPrivKey;
    std::string strTestPubKey;
    std::string strMainPubKey;

public:

    CSporkManager() {
        strMainPubKey = "043b2fcaa1149e58bcab5e270fe1ee37690fbe710ad36fabbce89233a6a4842faa6030da06ecda2358066e7dec1045ebcfcba37c8865af23be651ac625c0e008ef";
        strTestPubKey = "0474055bd4aad01c80de5d168922bf0bc1a3dd929c2d5d80e43c31c60802d81306c84a1d424e9103e6c617c186915f4e4a7ad2231af4a456aabef1c8b9350b68f9";
    }

    std::string GetSporkNameByID(int id);
    int GetSporkIDByName(std::string strName);
    bool UpdateSpork(int nSporkID, int64_t nValue);
    bool SetPrivKey(std::string strPrivKey);
    bool CheckSignature(CSporkMessage& spork);
    bool Sign(CSporkMessage& spork);
    void Relay(CSporkMessage& msg);

};

#endif
