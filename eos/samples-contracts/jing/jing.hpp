/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eosio/eosio.hpp>

using namespace eosio;

struct movement {
        uint32_t    row;
        uint32_t    column;

        EOSLIB_SERIALIZE( movement, (row)(column) )
    };


const uint32_t board_len = 9;
/// @abi table games i64
struct [[eosio::table]] game {
      eosio::name     challenger;
      uint64_t primary_key() const { return challenger.value; }

      game() { initialize_board(); }
      game(eosio::name challenger_account, eosio::name host_account)
            : challenger(challenger_account), host(host_account), turn(host_account) {
         // Initialize board
         initialize_board();
      }
      
      eosio::name     host;
      eosio::name     turn; // = account name of host/ challenger
      eosio::name     winner; // = none/ draw/ account name of host/ challenger
      std::vector<uint32_t>         board;
      // Initialize board with empty cell
      void initialize_board() {
        board.resize(board_len);
         for (uint32_t i = 0; i < board_len ; i++) {
            board[i] = 0;
         }
      }

      // Reset game
      void reset_game() {
         initialize_board();
         turn = host;
         winner = name("none");
      }

      
      EOSLIB_SERIALIZE( game, (challenger)(host)(turn)(winner)(board) )
};

class [[eosio::contract("jing")]] jing: public contract {
    using contract::contract;
    public:
        
        [[eosio::action]]
        void create( eosio::name host, eosio::name challenger );
        [[eosio::action]]
        void restart( eosio::name host, eosio::name challenger, eosio::name by );
        [[eosio::action]]
        void move( eosio::name host, eosio::name challenger, eosio::name by, movement mvt );
        [[eosio::action]]
        void close( eosio::name host, eosio::name challenger );
    public:
        
    private:
        
    /**
    * @brief Check if cell is empty
    * @param cell - value of the cell (should be either 0, 1, or 2)
    * @return true if cell is empty
    */
   bool is_empty_cell(const uint8_t& cell) {
      return cell == 0;
   }

   /**
    * @brief Check for valid movement
    * @detail Movement is considered valid if it is inside the board and done on empty cell
    * @param mvt - the movement made by the player
    * @param game_for_movement - the game on which the movement is being made
    * @return true if movement is valid
    */
   bool is_valid_movement(const movement& mvt, const game& game_for_movement) {
      uint32_t movement_location = mvt.row * 3 + mvt.column;
      bool is_valid = movement_location < board_len && is_empty_cell(game_for_movement.board[movement_location]);
      return is_valid;
   }


   /**
    * @brief Get winner of the game
    * @detail Winner of the game is the first player who made three consecutive aligned movement
    * @param current_game - the game which we want to determine the winner of
    * @return winner of the game (can be either none/ draw/ account name of host/ account name of challenger)
    */
   eosio::name get_winner(const game& current_game) {
      if((current_game.board[0] == current_game.board[4] && current_game.board[4] == current_game.board[8]) ||
         (current_game.board[1] == current_game.board[4] && current_game.board[4] == current_game.board[7]) ||
         (current_game.board[2] == current_game.board[4] && current_game.board[4] == current_game.board[6]) ||
         (current_game.board[3] == current_game.board[4] && current_game.board[4] == current_game.board[5])) {
         //  x | - | -    - | x | -    - | - | x    - | - | -
         //  - | x | -    - | x | -    - | x | -    x | x | x
         //  - | - | x    - | x | -    x | - | -    - | - | -
         if (current_game.board[4] == 1) {
            return current_game.host;
         } else if (current_game.board[4] == 2) {
            return current_game.challenger;
         }
      } else if ((current_game.board[0] == current_game.board[1] && current_game.board[1] == current_game.board[2]) ||
                 (current_game.board[0] == current_game.board[3] && current_game.board[3] == current_game.board[6])) {
         //  x | x | x       x | - | -
         //  - | - | -       x | - | -
         //  - | - | -       x | - | -
         if (current_game.board[0] == 1) {
            return current_game.host;
         } else if (current_game.board[0] == 2) {
            return current_game.challenger;
         }
      } else if ((current_game.board[2] == current_game.board[5] && current_game.board[5] == current_game.board[8]) ||
                 (current_game.board[6] == current_game.board[7] && current_game.board[7] == current_game.board[8])) {
         //  - | - | x       - | - | -
         //  - | - | x       - | - | -
         //  - | - | x       x | x | x
         if (current_game.board[8] == 1) {
            return current_game.host;
         } else if (current_game.board[8] == 2) {
            return current_game.challenger;
         }
      } else {
         bool is_board_full = true;
         for (uint8_t i = 0; i < board_len; i++) {
            if (is_empty_cell(current_game.board[i])) {
               is_board_full = false;
               break;
            }
         }
         if (is_board_full) {
            return name("draw");
         }
      }
      return name("none");
   }
    /**
    * @brief table definition, used to store existing games and their current state
    */
   typedef eosio::multi_index< "games"_n, game> games;
};
