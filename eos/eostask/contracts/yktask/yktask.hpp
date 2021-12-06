#include <eosio/eosio.hpp>

using namespace eosio;
using std::string;

class[[eosio::contract("yktask")]] yktask : public contract
{
    public:
        using contract::contract;
        yktask(name receiver, name code, datastream<const char *> ds) : eosio::contract(receiver, code, ds) {}

        struct [[eosio::table]] task
        {
            uint64_t taskid;
            name     issuer;
            name     hunter;
            uint8_t  status;
            string   desc;
            string   comment;
            string  tasktime;
            uint64_t bonus;
            auto primary_key() const { return taskid; }
            
            //EOSLIB_SERIALIZE( task, (username)(amount))
        };

        typedef eosio::multi_index<"tasks"_n, task> tasks;

        [[eosio::action]]
        void issuetask(name admin, name issuer, string desc, uint64_t bonus);
        [[eosio::action]]
        void taketask(name admin, uint64_t tid, name hunter);
        [[eosio::action]]
        void committask(name admin, uint64_t tid, name hunter);
        [[eosio::action]]
        void confirmtask(name admin, uint64_t tid, name issuer, uint8_t status, string comment);
        [[eosio::action]]
        task querytask(name admin, uint64_t tid);

    private:

};

