const Parser = require('rss-parser');
const fs = require('fs');
const path = require('path');

// Radio classic des histoires en musique
const feedUrl = "https://feed.ausha.co/brvl6HgdLxW8";

const parser = new Parser();

async function downloadFile(url, filename, filename_2 = null) {
  const res = await fetch(url);
  const buffer = await res.arrayBuffer();
  fs.writeFileSync(filename, Buffer.from(buffer));
  fs.writeFileSync(filename_2, Buffer.from(buffer));
  console.log(`✔️ Téléchargé : ${filename}`);
}

async function main() {

    fs.mkdirSync("data/raw", { recursive: true });
    fs.mkdirSync("data/renamed", { recursive: true });

    const feed = await parser.parseURL(feedUrl);
    const result = [];

    for (const item of feed.items) {
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

        if (enclosure) {
            await downloadFile(
                `https://audio.ausha.co/${id}.mp3`, 
                path.join('data', 'renamed', `${title_formated}.mp3`),
                path.join('data', 'raw', `${id}.mp3`)
            );
        }

        result.push({
            id,
            title_formated,
            title: item.title,
            enclosure,
        });
    }
    fs.writeFileSync(path.join('data', 'result.json'), JSON.stringify(result, null, 2));
}

main().catch(console.error);
