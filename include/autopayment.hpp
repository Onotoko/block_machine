#include <eosio/eosio.hpp>
#include <eosio/system.hpp>
#include <eosio/asset.hpp>


using namespace eosio;
namespace eosio
{
  CONTRACT autopayment : public contract {
    public:
      using contract::contract;
      autopayment(eosio::name receiver, eosio::name code, datastream<const char*> ds):contract(receiver, code, ds) {}

      ACTION autopay(uint64_t payment_id, name from, name to, const asset& fee, const std::string& memo);
    
    private:
      TABLE payment {
        uint64_t    id;
        name        from;
        name        to;
        asset       fee;
        std::string memo;

        uint64_t primary_key() const { return id; }
      };
      typedef eosio::multi_index<"payment"_n, payment> payments;
  };
} // namespace eosio