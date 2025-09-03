'use strict';

const Parser = require('rss-parser');
const fs = require('fs');
const path = require('path');


// ----------------- CONFIGURATION -----------------
const DOWNLOAD = true;
// Radio classic - des histoires en musique
const feed_url = 'https://feed.ausha.co/brvl6HgdLxW8';
// Pathes
const path_data = path.join('data');
const path_data_raw = path.join(path_data, 'raw');
const path_data_renamed = path.join(path_data, 'renamed');
// ----------------- /CONFIGURATION -----------------


async function downloadFile(url, filename, filename_2 = null) {
    const res = await fetch(url);
    const buffer = await res.arrayBuffer();
    fs.writeFileSync(filename, Buffer.from(buffer));
    fs.writeFileSync(filename_2, Buffer.from(buffer));
    console.log(`✔️ Téléchargé : ${filename}`);
}


function writeCSV(filename, data) {
    const headers = Object.keys(data[0]);
    const rows = data.map((item) =>
        headers.map(h => JSON.stringify(item[h] ?? '')).join(',')
    );
    const csv = [headers.join(','), ...rows].join('\n');
    fs.writeFileSync(filename, csv, 'utf8');

    console.log(`✅ CSV généré : ${filename}`);
}


function createOutputFolders(folders_list = []) {
    const mkdir_sync_options = {
        recursive: true,
    };
    folders_list.forEach((folder) => {
        fs.mkdirSync(folder, mkdir_sync_options);
    });
}


(async () => {

    createOutputFolders([
        path_data_raw,
        path_data_renamed,
    ]);

    const parser = new Parser();
    const feed = await parser.parseURL(feed_url);
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
            .replace(/[<>:"/\\|?*]+/g, '')
            .trim();

        const id = enclosure.split('/')[3];

        if (enclosure && DOWNLOAD) {
            await downloadFile(
                `https://audio.ausha.co/${id}.mp3`, 
                path.join(path_data_renamed, `${title_formated}.mp3`),
                path.join(path_data_raw, `${id}.mp3`)
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
        path.join(path_data, 'result.csv'),
        [
            ...result.map((item) => ({
                age: item.age,
                title: item.title,
            }))
        ]
            .sort(
                (item_a, item_b) => item_a.title.localeCompare(
                    item_b.title,
                    'fr',
                    {
                        sensitivity: 'base',
                    }
                )
            )
    );

})();
