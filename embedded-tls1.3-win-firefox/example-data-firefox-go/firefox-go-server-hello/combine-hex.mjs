import { readFile, writeFile, appendFile } from "node:fs/promises";

const data1 = await readFile("1.bin", "hex");
const data2 = await readFile("2.bin", "hex");
const data3 = await readFile("3.bin", "hex");

let hexContent = "";

for (let i = 0; i < data1.length; i += 2) {
    hexContent += `${data1[i]}${data1[i + 1]} `;
}

hexContent += "\r\n";

for (let i = 0; i < data2.length; i += 2) {
    hexContent += `${data2[i]}${data2[i + 1]} `;
}

hexContent += "\r\n";

for (let i = 0; i < data3.length; i += 2) {
    hexContent += `${data3[i]}${data3[i + 1]} `;
}

hexContent += "\r\n";

await writeFile("1-3.txt", hexContent, "utf-8");
