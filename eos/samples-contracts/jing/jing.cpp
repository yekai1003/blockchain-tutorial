/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include "jing.hpp"

void jing::create( eosio::name host, eosio::name challenger )
{
    print("on create ",name{host},",",name{challenger});
    require_auth(host);
    check(challenger != host, "challenger shouldn't be the same as host");

    // Check if game already exists
    games existing_host_games(get_self(), challenger.value);
    auto itr = existing_host_games.find( challenger.value );
    check(itr == existing_host_games.end(), "game already exists");

    //games.challenger = challenger;
    existing_host_games.emplace(host, [&]( auto& g ) {
        g.challenger = challenger;
        g.host = host;
        g.turn = host;
    });
}
void jing::restart( eosio::name host, eosio::name challenger, eosio::name by )
{
require_auth(by);

    // Check if game exists
    games existing_host_games(host, host.value);
    auto itr = existing_host_games.find( challenger.value );
    check(itr != existing_host_games.end(), "game doesn't exists");

    // Check if this game belongs to the action sender
    check(by == itr->host || by == itr->challenger, "this is not your game!");

    // Reset game
    existing_host_games.modify(itr, itr->host, []( auto& g ) {
        g.reset_game();
    });
}
void jing::move( eosio::name host, eosio::name challenger, eosio::name by, movement mvt )
{
    require_auth(by);

      // Check if game exists
      games existing_host_games(host, host.value);
      auto itr = existing_host_games.find( challenger.value );
      check(itr != existing_host_games.end(), "game doesn't exists");

      // Check if this game hasn't ended yet
      check(itr->winner == "none"_n, "the game has ended!");
      // Check if this game belongs to the action sender
      check(by == itr->host || by == itr->challenger, "this is not your game!");
      // Check if this is the  action sender's turn
      check(by == itr->turn, "it's not your turn yet!");


      // Check if user makes a valid movement
      check(is_valid_movement(mvt, *itr), "not a valid movement!");

      // Fill the cell, 1 for host, 2 for challenger
      const uint8_t cell_value = itr->turn == itr->host ? 1 : 2;
      const auto turn = itr->turn == itr->host ? itr->challenger : itr->host;
      existing_host_games.modify(itr, itr->host, [&]( auto& g ) {
         g.board[mvt.row * 3 + mvt.column] = cell_value;
         g.turn = turn;

         //check to see if we have a winner
         g.winner = get_winner(g);
      });

    
}
void jing::close( eosio::name host, eosio::name challenger )
{
    require_auth(host);

      // Check if game exists
      games existing_host_games(host, host.value);
      auto itr = existing_host_games.find( challenger.value );
      check(itr != existing_host_games.end(), "game doesn't exists");

      // Remove game
      existing_host_games.erase(itr);
}


//EOSIO_ABI(jing,(create)(restart)(close)(move))
