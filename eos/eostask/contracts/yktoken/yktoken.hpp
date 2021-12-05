#include <eosio/eosio.hpp>

using namespace eosio;
using std::string;

class[[eosio::contract("yktoken")]] yktoken : public contract
{
    public:
        using contract::contract;
        yktoken(name receiver, name code, datastream<const char *> ds) : contract(receiver, code, ds) {beginid = 1;}

        struct [[eosio::table]] token
        {
            name      username;
            string    password;
            auto primary_key() const { return username.value; }
            
            EOSLIB_SERIALIZE( userinfo, (username)(password))
        };

        typedef eosio::multi_index<"users"_n, userinfo> users;

        [[eosio::action]]
        void register(name admin, name sname, string password);
        [[eosio::action]]
        bool login(name admin, name sname, string password);

    private:

};

