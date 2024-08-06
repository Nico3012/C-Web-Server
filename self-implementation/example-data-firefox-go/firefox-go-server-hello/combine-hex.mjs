import { readFile, writeFile } from "node:fs/promises";

const data1 = await readFile("1.bin", "hex");
const data2 = await readFile("2.bin", "hex");
const data3 = await readFile("3.bin", "hex");

// make sure every server-hello dataset has the same length
if (data1.length !== data2.length && data1.length !== data3.length) throw new Error("not every server-hello dataset has the same length!");

/** @type {[string, string, string]} */
const hexContent = ["", "", ""];
let lastHexEqual = false;

for (let i = 0; i < data1.length; i += 2) {
    // compare current hex value:
    if (`${data1[i]}${data1[i + 1]}` === `${data2[i]}${data2[i + 1]}` && `${data1[i]}${data1[i + 1]}` === `${data3[i]}${data3[i + 1]}`) {
        if (!lastHexEqual) {
            // from now on there is a new block of equal values
            hexContent[0] += "------------ ";
            hexContent[1] += "------------ ";
            hexContent[2] += "------------ ";
        }

        lastHexEqual = true;
    } else {
        if (lastHexEqual) {
            // from now on there is a new block of unequal values
            hexContent[0] += ": ";
            hexContent[1] += ": ";
            hexContent[2] += ": ";
        }

        lastHexEqual = false;
    }

    hexContent[0] += `${data1[i]}${data1[i + 1]} `;
    hexContent[1] += `${data2[i]}${data2[i + 1]} `;
    hexContent[2] += `${data3[i]}${data3[i + 1]} `;
}

await writeFile("1-3.txt", hexContent.join("\r\n") + "\r\n", "utf-8");
