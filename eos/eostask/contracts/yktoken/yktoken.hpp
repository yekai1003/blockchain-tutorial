#include <eosio/eosio.hpp>

using namespace eosio;
using std::string;
//using eosio::name;
//using eosio::contract;

class[[eosio::contract("yktoken")]] yktoken : public contract
{
    public:
        using contract::contract;
        yktoken(name receiver, name code, datastream<const char *> ds) : eosio::contract(receiver, code, ds) {}

        struct [[eosio::table]] balance
        {
            name      username;
            uint64_t    amount;
            auto primary_key() const { return username.value; }
            
            EOSLIB_SERIALIZE( balance, (username)(amount))
        };

        typedef eosio::multi_index<"balances"_n, balance> balances;

        struct [[eosio::table]] supply
        {
            name      issuer;
            uint64_t    totalSupply;
            auto primary_key() const { return issuer.value; }
            
            EOSLIB_SERIALIZE( supply, (issuer)(totalSupply))
        };

        typedef eosio::multi_index<"supplys"_n, supply> supplys;

        [[eosio::action]]
        void ykcreate(name admin, name issuer);
        [[eosio::action]]
        void ykissue(name admin, name issuer, uint64_t  supply);
        [[eosio::action]]
        void yktransfer(name admin, name issuer, name from, name to, uint64_t amount);
        [[eosio::action]]
        uint64_t ykbalanceof(name admin, name issuer, name who);
        [[eosio::action]]
        uint64_t yksupply(name admin, name issuer);

    private:

};

