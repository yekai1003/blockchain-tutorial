#include "yktask.hpp"
#include <eosio/system.hpp>

void yktask::issuetask(name admin, name issuer, string desc, uint64_t bonus)
{
   require_auth(admin);
   tasks tks(get_self(), admin.value);

   check(bonus > 0, "bonus must > 0");

   tks.emplace(admin, [&](auto &g){
      g.taskid = tks.available_primary_key();
      g.issuer = issuer;
      g.hunter = "none"_n;
      g.status = 0;
      g.desc   = desc;
      g.tasktime = current_block_time().to_string(); 
      g.bonus  = bonus;
   });

}

void yktask::taketask(name admin, uint64_t tid, name hunter)
{
   require_auth(admin);
   tasks tks(get_self(), admin.value);
   auto itr = tks.find(tid);
   check(itr != tks.end(), "task does not exists");
   check(itr->hunter == "none"_n, "task already be taked");
   check(itr->status == 0, "task status can not take");

   tks.modify(itr, admin, [&](auto &row){
      row.hunter = hunter;
      row.status  = 1;
   });
}

void yktask::committask(name admin, uint64_t tid, name hunter)
{
   require_auth(admin);
   tasks tks(get_self(), admin.value);
   auto itr = tks.find(tid);
   check(itr != tks.end(), "task does not exists");
   check(itr->hunter == hunter, "task already be taked");
   check(itr->status == 1, "task status can not commit");

   tks.modify(itr, admin, [&](auto &row){
      row.status  = 2;
   });
}

void yktask::confirmtask(name admin, uint64_t tid, name issuer, uint8_t status, string comment)
{
   require_auth(admin);
   tasks tks(get_self(), admin.value);
   auto itr = tks.find(tid);
   check(itr != tks.end(), "task does not exists");
   check(itr->issuer == issuer, "task already be taked");
   check(itr->status == 2, "task status can not confirm");
   tks.modify(itr, admin, [&](auto &row){
      if(status == 3) {
         // send token
         print("ok3", status, comment);
         row.status  = status;
         row.comment = comment;

         action token = action(
            permission_level{admin,"active"_n},
            "yktoken"_n,
            "yktransfer"_n,
            std::make_tuple(admin, "ykc"_n, row.issuer, row.hunter, row.bonus)
         );

         token.send();

      } else {
         row.status = 1;
      }
      
   });
}

yktask::task yktask::querytask(name admin, uint64_t tid)
{
   require_auth(admin);
   tasks tks(get_self(), admin.value);
   auto itr = tks.find(tid);
   check(itr != tks.end(), "task does not exists");

   return *itr;
}
