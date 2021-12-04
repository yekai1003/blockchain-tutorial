#include <eosio/eosio.hpp>
#include <eosio/system.hpp>

using namespace eosio;

class [[eosio::contract("demo")]] demo : public eosio::contract {
  public:

    demo(name receiver, name code,  datastream<const char*> ds): contract(receiver, code, ds) {}

    [[eosio::action]]
    void create(name user, name mma, name mmb) ;

    [[eosio::action]]
    void sign(name user, name mma, name by) ;


  private:
    struct [[eosio::table]] marriage {
      name evi;
      name  mma;
      name  mmb;
      std::string mmmsg;
      std::string timestamp;
      bool ismma;
      bool ismmb;
      uint64_t primary_key() const { return mma.value; }
    };

    using marriage_index = eosio::multi_index<"marriages"_n, marriage>;
};
