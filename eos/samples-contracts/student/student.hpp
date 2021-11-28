#include <eosio/eosio.hpp>

using namespace eosio;
using std::string;

class[[eosio::contract("student")]] student : public contract
{
    public:
        using contract::contract;
        student(name receiver, name code, datastream<const char *> ds) : contract(receiver, code, ds) {beginid = 1;}
        uint64_t beginid = 0;
        struct [[eosio::table]] person
        {
            uint64_t  sid;
            string    sname;
            uint8_t   sage;
            auto primary_key() const { return sid; }
            
            EOSLIB_SERIALIZE( person, (sid)(sname)(sage))
        };

        typedef eosio::multi_index<"persons"_n, person> pernsons;

        [[eosio::action]]
        void add(uint64_t sid, string sname, uint8_t sage);
        [[eosio::action]]
        void get(uint64_t sid);

    private:

};

