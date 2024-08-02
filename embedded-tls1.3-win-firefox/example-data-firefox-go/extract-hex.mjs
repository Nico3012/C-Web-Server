import { readFile, writeFile, appendFile } from "node:fs/promises";

const data = await readFile("firefox-c-client-hello.bin", "hex");

let hexCode = "";

for (let i = 0; i < data.length; i += 2) {
    // produce c code:
    // hexCode += `0x${data[i]}${data[i + 1]},\n`;

    // write in one line:
    hexCode += `${data[i]}${data[i + 1]} `;
}

// when writing to one line:
hexCode += "\n";

await appendFile("c-go-firefox-client-hello-compare.txt", hexCode, "utf-8");
// await writeFile("firefox-go-client-hello.txt", hexCode, "utf-8");
