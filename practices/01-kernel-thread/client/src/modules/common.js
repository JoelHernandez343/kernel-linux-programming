require('colors');

const showError = err => console.log(`${'ERR!'.red.bgBlack}`, err);

module.exports = { showError };
