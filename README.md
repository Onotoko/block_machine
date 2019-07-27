### Smart contract for auto payment on blockchain 
----------------------------------------------------------

Example on jungle testnet using cleos
----------------------------------
#### Get started

- Account name: akitamachine

- Endpoint network:
https://jungle2.cryptolions.io:443

- Contract name: autopayment


##### Build & deploy smart contract

Go to block_machine directory then do flowing steps:

1.  Build smart contract

````bash
$ eosio-cpp -abigen -I include -contract autopayment -o autopayment.wasm src/autopayment.cpp
````
2. Deploy to jungle test net

````bash
$ cleos -u https://jungle2.cryptolions.io:443 set contract akitamachine . autopayment.wasm autopayment.abi
````
##### To add permission on the jungle test net

````bash
$ cleos -u https://jungle2.cryptolions.io:443 set account permission akitamachine active '{"threshold": 1,"keys": [{"key": "EOS6KPrGGbXhtBHYdnfW4HchLM2nX9LoVoWRcxnGS8mbwgKZgJn56","weight": 1}],"accounts": [{"permission":{"actor":"akitamachine","permission":"eosio.code"},"weight":1}]}' owner -p akitamachine

$ cleos -u https://jungle2.cryptolions.io:443 set account permission testpayee111 active '{"threshold": 1,"keys": [{"key": "EOS5drLw5nbgfFYSHSfnQyD4XkijpWQjrMCZNgEsUgpAZbzkvghb2","weight": 1}],"accounts": [{"permission":{"actor":"akitamachine","permission":"eosio.code"},"weight":1}]}' owner -p testpayee111
````

#### Testing

1. Prepare input

For example:
- We have two account on EOS network,  `testpayee111` and `receipient12`
- A payment:
```
{
    id: 2019,
    from: `test.payee11`,
    to: `receipient12`,
    fee: 10 EOS,
    memo: "Buy a car"
}
```

2. Push to blockchain

````bash
cleos -u https://jungle2.cryptolions.io:443 push action akitamachine autopay '["2019","testpayee111", "receipient12", "10 EOS", "Buy a car"]' -p testpayee111

````

3. Check the result

[Go to block explorer](https://jungle.bloks.io/transaction/95cff952b90f5941a33ee2be92792a8a74dda768fa6592fca7b98be5cc6fd2d6)

