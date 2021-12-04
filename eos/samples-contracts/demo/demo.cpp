#include "demo.hpp"

void demo::create(name user, name mma, name mmb) 
{
   require_auth(user);

   marriage_index marriages(get_self(), user.value);
   auto itr = marriages.find(mma.value);

   check(itr == marriages.end(), "marriage already exists");

   marriages.emplace(user, [&]( auto& row ){
       row.evi = user;
       row.mma = mma;
       row.mmb = mmb;
       row.mmmsg = "注册结婚";
       row.timestamp = current_time_point().to_string();
       row.ismma = false;
       row.ismmb = false;
  });

}

void demo::sign(name user, name mma, name by) 
{
   require_auth(by);

   marriage_index marriages(get_self(), user.value);
   auto itr = marriages.find(mma.value);

   check(itr != marriages.end(), "marriage does not exists");
   check(itr->mma == by || itr->mma == by, "only marriage's person can do");

   marriages.modify(itr, user, [&]( auto& row ){
       if(row.mma == by) {
         row.ismma = true;
       }
       if(row.mmb == by) {
         row.ismmb = true;
       }
       
       
  });

}
