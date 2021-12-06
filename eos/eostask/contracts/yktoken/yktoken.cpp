#include "yktoken.hpp"

void yktoken::ykcreate(name admin, name issuer)
{
   require_auth(admin);
   supplys sly(get_self(), admin.value);

   auto itr = sly.find(issuer.value);

   check(itr == sly.end(), "token already exists");

   sly.emplace(admin, [&](auto &g) {
        g.issuer = issuer;
        g.totalSupply = 0; 
    });
}

void yktoken::ykissue(name admin, name issuer, uint64_t  supply)
{
   require_auth(admin);
   supplys sly(get_self(), admin.value);

   auto itr = sly.find(issuer.value);

   check(itr != sly.end(), "token does not exists");
   check(supply > 0, "supply must > 0");
   
   sly.modify(itr, admin, [&](auto &row) {
      row.totalSupply += supply;
   });

   balances bal(get_self(), issuer.value);
   auto itr2 = bal.find(issuer.value);

   if(itr2 == bal.end()) {

      bal.emplace(admin, [&](auto &g) {
        g.username = issuer;
        g.amount = supply; 
      });

   } else {
      bal.modify(itr2, admin, [&](auto &row) {
         row.amount += supply;
      });
   }

}

void yktoken::yktransfer(name admin, name issuer, name from, name to, uint64_t amount)
{
   //require_auth(admin);
   require_auth("yktask"_n);
   balances bal(get_self(), issuer.value);
   auto itr = bal.find(from.value);

   check(itr != bal.end(), "from's balance does not exists");
   check(itr->amount >= amount, "from's balance not enough");

   bal.modify(itr, admin, [&](auto &row) {
         row.amount -= amount;
   });

   itr = bal.find(to.value);

   if(itr == bal.end()) {
      bal.emplace(admin, [&](auto &g){
         g.username = to;
         g.amount   = amount;
      });
   } else {
      bal.modify(itr, admin, [&](auto &g){
         g.amount   += amount;
      });
   }
   

}
uint64_t yktoken::ykbalanceof(name admin, name issuer, name who)
{
   require_auth(admin);
   balances bal(get_self(), issuer.value);
   auto itr = bal.find(who.value);

   if(itr != bal.end()) {
      return itr->amount;
   }
   return 0;

}
uint64_t yktoken::yksupply(name admin, name issuer)
{
   require_auth(admin);
   supplys sly(get_self(), admin.value);
   auto itr = sly.find(issuer.value);

   if(itr != sly.end()) {
      return itr->totalSupply;
   }

   return 0;
}
