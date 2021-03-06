const { showAbout } = require('./modules/about');
const { menu, pause, askArray, askOption } = require('./modules/inquierer');
const {
  setParameter,
  showParameter,
  showAllParameters,
} = require('./modules/parameters');

const app = async () => {
  let option = '1';

  do {
    option = await menu(option);
    await switchOpt(option);
  } while (option !== '0');
};

const switchOpt = async option => {
  switch (option) {
    case '1':
      showAllParameters();
      break;

    case 'option':
    case 'data':
    case 'evenData':
    case 'average':
      showParameter(option);
      break;

    case '6':
      setParameter('data', await askArray());
      break;

    case '7':
      const opt = await askOption();
      if (opt === 0) {
        return;
      }

      setParameter('option', opt.toString());

      break;

    case '8':
      showAbout();
      break;

    case '0':
      console.log('\nBye :)');
      return;
  }

  await pause();
};

module.exports = app;
