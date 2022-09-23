address 0x1 { 
    // use 0x1::Std; 
    module football { 
        use Std::Signer;
        const STAR_ALREADY_EXISTS:u64 = 100;
        struct FootBallStar has key  { 
            name: vector<u8>, 
            country: vector<u8>, 
            position: u8, 
            value: u64, 
        } 
 
        public fun newStar(name:vector<u8>, country:vector<u8>, position:u8):FootBallStar { 
            FootBallStar{ 
                name,country,position, 
                value:0 
            } 
        }

        public fun mint(to:&signer) {
            let star = newStar(b"Ronaldo", b"brazil", 9);
            assert!(!exists<FootBallStar>(Signer::address_of(to)), STAR_ALREADY_EXISTS);
            move_to<FootBallStar>(to, star);
        }

        public fun get(owner:address): (vector<u8>, u64) acquires FootBallStar {
            let star = borrow_global<FootBallStar>(owner);
            (star.name, star.value)
        }
        
        public fun setPrice(owner: address, price: u64) acquires FootBallStar {
            let star = borrow_global_mut<FootBallStar>(owner);
            star.value = price;
        }
    } 
}