#include "userauth.hpp"

void userauth::userreg(name admin, name sname, string password) 
{
   users us(get_self(), admin.value);
   auto itr = us.find(sname.value);
   check(itr == us.end(), "user already exists.");

    us.emplace(admin, [&](auto &g) {
        g.username = sname;
        g.password = password; 
    });
}

string userauth::login(name admin, name sname, string password) 
{
   users us(get_self(), admin.value);
   auto itr = us.find(sname.value);
   check(itr != us.end(), "user does not exists.");
   if(itr->password == password) {
      return "true";
   }

   return "false";
}
