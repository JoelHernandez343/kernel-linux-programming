const { menu, pause } = require('./modules/inquierer');

const app = async () => {
  let option = 0;

  do {
    option = await menu();
    await pause();
  } while (option !== 0);
};

module.exports = app;
