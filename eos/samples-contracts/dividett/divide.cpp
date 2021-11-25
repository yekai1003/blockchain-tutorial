#include "divide.hpp"

void divide::create(const name &challenger, name &host) {
    require_auth(host);
    check(challenger != host, "Challenger should not be the same as the host.");

    // Check if game already exists
    games existingHostGames(get_self(), host.value);
    auto itr = existingHostGames.find(challenger.value);
    check(itr == existingHostGames.end(), "Game already exists.");

    existingHostGames.emplace(host, [&](auto &g) {
        g.challenger = challenger;
        g.host = host;
    });
}

void divide::restart(const name &challenger, const name &host, const name &by)
{
    check(has_auth(by), "Only " + by.to_string() + "can restart the game.");

    // Check if game exists
    games existingHostGames(get_self(), host.value);
    auto itr = existingHostGames.find(challenger.value);
    check(itr != existingHostGames.end(), "Game does not exist.");

    // Check if this game belongs to the action sender
    check(by == itr->host || by == itr->challenger, "This is not your game.");

    // Reset game
    existingHostGames.modify(itr, itr->host, [](auto &g) {
        g.resetGame();
    });
}

void divide::close(const name &challenger, const name &host)
{
    check(has_auth(host), "Only the host can close the game.");

    require_auth(host);

    // Check if game exists
    games existingHostGames(get_self(), host.value);
    auto itr = existingHostGames.find(challenger.value);
    check(itr != existingHostGames.end(), "Game does not exist.");

    // Remove game
    existingHostGames.erase(itr);
}

void divide::showhand(const name &challenger, const name &host, const name &by, const uint8_t &opt)
{
    check(has_auth(by), "The next showhand should be made by " + by.to_string());

    games existingHostGames(get_self(), host.value);
    auto itr = existingHostGames.find(challenger.value);
    check(itr != existingHostGames.end(), "Game does not exist.");

    check(itr->winner == none, "The game has ended.");
    check(by == itr->host || by == itr->challenger, "This is not your game.");

    check(isNext != 2, "the game already end.You can restart it!");

    if(by == itr->host) {
        check(boardHost == 0, "host already showhand");
        existingHostGames.modify(itr, itr->host, [&](auto &g) {
        g.boardHost = opt;
        g.isNext ++;
        if(g.isNext == 2) {
            if(isHostWin(g.boardHost, g.boardCallenger) ) {
                g.winner = g.host;
            } else {
                g.winner = g.challenger;
            }
        }
    });
    if(by == itr->challenger) {
        check(boardCallenger == 0, "challenger already showhand");
        existingHostGames.modify(itr, itr->host, [&](auto &g) {
        g.boardCallenger = opt;
        g.isNext ++;
        if(g.isNext == 2) {
            if(isHostWin(g.boardHost, g.boardCallenger) ) {
                g.winner = g.host;
            } else {
                g.winner = g.challenger;
            }
        }
    });



    }

}

bool divide::isHostWin(uint8_t _host, uint8_t _callenger) {
    return true;
}