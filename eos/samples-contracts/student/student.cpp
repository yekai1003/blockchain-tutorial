#include "student.hpp"

void student::add(uint64_t sid, string sname, uint8_t sage)
{
    pernsons ps(get_self(), "yekai"_n.value);
    //auto itr = existingHostGames.find(challenger.value);
    //check(itr == existingHostGames.end(), "Game already exists.");

    ps.emplace("yekai"_n, [&](auto &g) {
        g.sid = sid;
        g.sname = sname;
        g.sage = sage;
    });
}
void student::get(uint64_t sid)
{
    pernsons ps(get_self(), "yekai"_n.value);
    auto itr = ps.find(sid);
    print("sid = ", itr->sid, ",sname = ", itr->sname, ", sage = ", itr->sage);
}


uint8_t student::getage(uint64_t sid)
{
    pernsons ps(get_self(), "yekai"_n.value);
    auto itr = ps.find(sid);
    return itr->sage;
}
string student::getname(uint64_t sid)
{
    pernsons ps(get_self(), "yekai"_n.value);
    auto itr = ps.find(sid);
    return itr->sname;
}

