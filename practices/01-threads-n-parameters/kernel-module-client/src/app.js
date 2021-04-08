const { menu, pause, askArray, askOption } = require('./modules/inquierer');
const {
  setParameter,
  showParameter,
  showAllParameters,
} = require('./modules/parameters');

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
      showAllParameters();
      break;

    case 'option':
    case 'data':
    case 'evenData':
    case 'average':
      showParameter(option);
      break;

    case 6:
      setParameter('data', await askArray());
      break;

    case 7:
      const opt = await askOption();
      if (opt !== 0) {
        setParameter('option', opt.toString());
      }
      break;

    default:
      break;
  }
};

module.exports = app;
