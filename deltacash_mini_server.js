const express = require("express");
const crypto = require("crypto");

const app = express();
app.use(express.json());

let blockchain = [];
let balances = {};
let pendingTransactions = [];

// Hash function
function hash(data) {
    return crypto.createHash("sha256").update(data).digest("hex");
}

// Create block
function createBlock() {
    const block = {
        index: blockchain.length,
        transactions: pendingTransactions,
        timestamp: Date.now(),
        previousHash: blockchain.length ? blockchain[blockchain.length - 1].hash : "0",
    };

    block.hash = hash(JSON.stringify(block));
    blockchain.push(block);
    pendingTransactions = [];
}

app.get("/", (req, res) => {
    res.send("DeltaCash Mini Server is running 🚀");
});

// Create account
app.post("/create", (req, res) => {
    const address = "dch" + crypto.randomBytes(4).toString("hex");
    balances[address] = 100; // faucet awal
    res.json({ address });
});

// Send transaction
app.post("/send", (req, res) => {
    const { from, to, amount } = req.body;

    if (!balances[from] || balances[from] < amount) {
        return res.json({ error: "Saldo tidak cukup" });
    }

    balances[from] -= amount;
    balances[to] = (balances[to] || 0) + amount;

    pendingTransactions.push({ from, to, amount });

    if (pendingTransactions.length >= 3) {
        createBlock();
    }

    res.json({ success: true });
});

// Check balance
app.get("/balance/:address", (req, res) => {
    res.json({ balance: balances[req.params.address] || 0 });
});

// View blockchain
app.get("/chain", (req, res) => {
    res.json(blockchain);
});

app.listen(3000, () => {
    console.log("Mini DeltaCash server running on port 3000");
});
