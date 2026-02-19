# DeltaCash-Technologies
GitHub repository for sharing DeltaCash-Technologies Project code

deltacash server command:

CREATE ACCOUNT
curl -X POST http://localhost:3000/create

CHECK BALANCE
curl http://localhost:3000/balance/DELTACASH_ADDRESS

SEND DELTACASH 
curl -X POST http://localhost:3000/send \
-H "Content-Type: application/json" \
-d '{"from":"DELTACASH_ADDRESS","to":"DELTACASH_ADDRESS","amount":ENTER_AMOUNT}'

CHECKING BLOCKCHAIN
curl http://localhost:3000/chain
