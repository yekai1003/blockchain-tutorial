#include <eosio/eosio.hpp>

using namespace eosio;
using std::string;

class[[eosio::contract("userauth")]] userauth : public contract
{
    public:
        using contract::contract;
        userauth(name receiver, name code, datastream<const char *> ds) : contract(receiver, code, ds) {}

        struct [[eosio::table]] userinfo
        {
            name      username;
            string    password;
            auto primary_key() const { return username.value; }
            
            EOSLIB_SERIALIZE( userinfo, (username)(password))
        };

        typedef eosio::multi_index<"users"_n, userinfo> users;

        [[eosio::action]]
        void userreg(name admin, name sname, string password);
        [[eosio::action]]
        string login(name admin, name sname, string password);

    private:

};

