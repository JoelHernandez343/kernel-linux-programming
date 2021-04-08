const { menu, pause } = require('./modules/inquierer');
const { showParameter } = require('./modules/parameters');

const app = async () => {
  let option = 0;

  do {
    option = await menu();

    await switchOpt(option);

    await pause();
  } while (option !== 0);
};

const switchOpt = async option => {
  switch (option) {
    case 1:
      break;

    case 'option':
    case 'data':
    case 'evenData':
    case 'average':
      showParameter(option);
      break;

    default:
      break;
  }
};

module.exports = app;