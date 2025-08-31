const Parser = require('rss-parser');
const fs = require('fs');
const path = require('path');

// ----------------- CONFIGURATION -----------------
const DOWNLOAD = true;
// Radio classic des histoires en musique
const feedUrl = "https://feed.ausha.co/brvl6HgdLxW8";
// ----------------- /CONFIGURATION -----------------

const parser = new Parser();

async function downloadFile(url, filename, filename_2 = null) {
    const res = await fetch(url);
    const buffer = await res.arrayBuffer();
    fs.writeFileSync(filename, Buffer.from(buffer));
    fs.writeFileSync(filename_2, Buffer.from(buffer));
    console.log(`✔️ Téléchargé : ${filename}`);
}


function writeCSV(filename, data) {
    const headers = Object.keys(data[0]);
    const rows = data.map(obj =>
    headers.map(h => JSON.stringify(obj[h] ?? "")).join(",")
    );
    const csv = [headers.join(","), ...rows].join("\n");
    fs.writeFileSync(filename, csv, "utf8");

    console.log(`✅ CSV généré : ${filename}`);
}

async function main() {

    fs.mkdirSync("data/raw", { recursive: true });
    fs.mkdirSync("data/renamed", { recursive: true });

    const feed = await parser.parseURL(feedUrl);
    const result = [];

    for (const item of feed.items) {
        
        const age = (item.content.match(/Âge\s*:\s*(?:dès\s*)?(\d+)\s*ans/i) || [])[1];
        
        const enclosure = item.enclosure?.url;
        const title_formated = item.title
            .replaceAll('/', '-')
            .replaceAll(' – ', ' - ')
            .replaceAll('«', '')
            .replaceAll('»', '')
            .replaceAll('  ', ' ')
            .replace(/[<>:"/\\|?*]+/g, "")
            .trim();

        const id = enclosure.split('/')[3];

        if (enclosure && DOWNLOAD) {
            await downloadFile(
                `https://audio.ausha.co/${id}.mp3`, 
                path.join('data', 'renamed', `${title_formated}.mp3`),
                path.join('data', 'raw', `${id}.mp3`)
            );
        }

        result.push({
            id,
            age: age ? age : '',
            title_formated,
            title: item.title,
            enclosure,
        });
    }
    fs.writeFileSync(path.join('data', 'result.json'), JSON.stringify(result, null, 2));
    console.log('✅ JSON généré : result.json');
    writeCSV(
        path.join('data', 'result.csv'),
        [...result.map((item) => ({
            age: item.age,
            title: item.title,
        }))].sort((a, b) => a.title.localeCompare(b.title, "fr", { sensitivity: "base" }))
    );
}

main().catch(console.error);
