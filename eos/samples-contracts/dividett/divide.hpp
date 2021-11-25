#include <eosio/eosio.hpp>

using namespace eosio;

class[[eosio::contract("divide")]] divide : public contract
{
    public:
        using contract::contract;
        divede(name receiver, name code, datastream<const char *> ds) : contract(receiver, code, ds) {}
        //定义2个常量
        static constexpr name none = "none"_n;
        static constexpr name draw = "draw"_n;
        enum UserOption {Zero, Rock, Paper, Scissors};
        struct [[eosio::table]] game
        {

            static constexpr uint16_t boardWidth = 10;
            uint8_t boardHost = Zero;
            uint8_t boardCallenger = Zero;
            game() {}

            name challenger;
            name host;
            name winner = none; // = none/ draw/ name of host/ name of challenger
            uint8_t  isNext = 0;

            // Reset game
            void resetGame()
            {
                winner = "none"_n;
                boardHost = 0;
                boardCallenger = 0;
                isNext = 0;
            }


            auto primary_key() const { return challenger.value; }
            EOSLIB_SERIALIZE( game, (challenger)(host)(winner)(boardHost)(boardCallenger)(isNext))
        };

        // Define the games type which uses the game data structure. 
        typedef eosio::multi_index<"games"_n, game> games;

        // Declare class method.
        [[eosio::action]]
        void create(const name &challenger, name &host);
        
        // Declare class method.
        [[eosio::action]]
        void restart(const name &challenger, const name &host, const name &by);

        // Declare class method.
        [[eosio::action]]
        void close(const name &challenger, const name &host);
        
        // Declare class method.
        [[eosio::action]]   
        void showhand(const name &challenger, const name &host, const name &by, const uint8_t &opt);
    private:
        bool isHostWin(uint8_t _host, uint8_t _callenger);
        
};