'use strict';

const fs = require('fs');
const path = require('path');

const result = JSON.parse(fs.readFileSync(path.join('data', 'result.json'), 'utf8'));

// console.log(result)

const data = {};

result.map(item => item.title_formated).forEach((item) => {
    if (data[item]) {
        data[item] += 1;
    } else {
        data[item] = 1;
    }
})

console.log(data);

Object.keys(data).forEach(key => {
    if (data[key] > 1) {
        console.log(key);
    }
});
