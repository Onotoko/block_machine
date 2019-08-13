#include <autopayment.hpp>

namespace eosio {
  constexpr symbol eos_symbol = symbol("EOS", 4);

  ACTION autopayment::autopay( uint64_t payment_id, 
                                name from, name to, 
                                const asset& fee, 
                                const std::string& memo) 
  {
    /**
     * Require authorize
     * 
    */ 
    require_auth(from);

    /**
     * Check input parameters
     * 
    */
    
    check(is_account(from), "Invalid account name of payeee");
    check(is_account(to), "Invalid account name of recipient");
    check(fee.is_valid(), "invalid reward");
    check(fee.amount > 0, "must input positive total of reward");
    check(fee.symbol == eos_symbol, "symbol precision mismatch");
    check( memo.size() <= 256, "memo has more than 256 bytes" );

    /**
     * Store log of payment
     * 
    */ 
    payments payment_table(get_self(), get_self().value);
      
    auto payment = payment_table.find(payment_id);
      
    
    check(payment == payment_table.end(), "This payment has been existed!");
      
    payment_table.emplace(get_self(), [&](auto & p) {

        p.id        = payment_id;
        p.from      = from;
        p.to        = to;
        p.fee       = fee;
        p.memo      = memo;
    });

    /**
     * Send amount of fee to recipient
    */ 
    action(
      permission_level{ from, "active"_n },
      "eosio.token"_n,"transfer"_n,
      std::make_tuple(from, to, fee, memo)
    ).send();

    
  }
}//end namespace eosio

EOSIO_DISPATCH(autopayment, (autopay))
