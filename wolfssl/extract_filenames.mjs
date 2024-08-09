import { readdirSync } from "node:fs";

const dir = readdirSync("wolfssl-5.7.2/wolfcrypt/src").filter(file => {
    if (file.endsWith(".c")) return true;
    return false;
});

console.log(dir.map(file => "    wolfssl-5.7.2/wolfcrypt/src/" + file + " \\").join("\n"));
