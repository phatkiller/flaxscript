// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0x12345678
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x01;
        pchMessageStart[1] = 0x07;
        pchMessageStart[2] = 0x02;
        pchMessageStart[3] = 0x03;
        vAlertPubKey = ParseHex("04aaf7dd45e99635296f3c1c3b361b3ec7d3f2003d8dcd5af65ad06bbf3e8c1504f0f22036ae5c286764a363ba615cdc8b7adeaf5fcbf8db51e978ec32c30d317a");
        nDefaultPort = 17235;
        nRPCPort = 23175;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 100000; // 2 years

        // Genesis block
        const char* pszTimestamp = "Never trust a woman or an automatic pistol.";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 16 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1430677023;
        genesis.nBits    = 0x1e0fffff;
        genesis.nNonce   = 571396;

        hashGenesisBlock = genesis.GetHash();
		
        assert(hashGenesisBlock == uint256("0x00000cfc6d06805a3cf598e42c91379bf185fce04cc2759ef53a203aeae676a1"));
        assert(genesis.hashMerkleRoot == uint256("0xe6fbf62ba0bf84cd80fbf65f9a32446143dfc457d83bca1a9e530570ad15e5c8"));

            vSeeds.push_back(CDNSSeedData("seed1.flaxscript.org", "seed1.flaxscript.org"));
	    vSeeds.push_back(CDNSSeedData("seed2.flaxscript.org", "seed2.flaxscript.org"));
	    vSeeds.push_back(CDNSSeedData("seed3.flaxscript.org", "seed3.flaxscript.org"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of( 43);                    // Flaxscript addresses start with 'X'
        base58Prefixes[SCRIPT_ADDRESS] = list_of(  4);                    // Flaxscript script addresses start with '7'
        base58Prefixes[SECRET_KEY] =     list_of(28 + 128);               // Flaxscript private keys start with '7' or 'X'
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x02)(0xFE)(0x52)(0xF8); // Flaxscript BIP32 pubkeys start with 'drkv'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x02)(0xFE)(0x52)(0xCC); // Flaxscript BIP32 prvkeys start with 'drkp'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000005);             // Flaxscript BIP44 coin type is '5'

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0x11;
        pchMessageStart[3] = 0x02;
		
        vAlertPubKey = ParseHex("04d7359ddda87e68d491a7c98a77f658b48e84918c52c7fe1a0716cb34bc96f1c48f79fa421c5fcae6165d678710a683d6eaae61dcadfd840635add91dc65a8cb8");
		
        nDefaultPort = 23990;
        nRPCPort = 23995;
        strDataDir = "testnet3";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1430677000;
        genesis.nNonce = 1555370;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000a8f0d18d66188cbd8ad958b749a6d289e1b17363e98fea0ba4b87330435"));

        vSeeds.push_back(CDNSSeedData("23skidoo.info", "23skidoo.info"));
        //vFixedSeeds.clear();
        //vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of( 105);                    // Testnet flaxscript addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = list_of( 44);                    // Testnet flaxscript script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY]     = list_of(88 + 128);               // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x3a)(0x80)(0x61)(0xa0); // Testnet flaxscript BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x3a)(0x80)(0x58)(0x37); // Testnet flaxscript BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_COIN_TYPE]  = list_of(0x80000001);             // Testnet flaxscript BIP44 coin type is '5' (All coin's testnet default)
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0x1f;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0x56;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1430676999;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 4;
        nDefaultPort = 18444;
        strDataDir = "regtest";

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x302a153d30db8a969b92126f1c6d946a019b228ddc6888084c994f812d115685"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
