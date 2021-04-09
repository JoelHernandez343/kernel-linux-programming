const { showAbout } = require('./modules/about');
const { menu, pause, askString, askLetter } = require('./modules/inquierer');
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

    case 'str':
    case 'option':
    case 'letter':
    case 'length':
    case 'coincidences':
      showParameter(option);
      break;

    case '7':
      setParameter('str', await askString());
      break;

    case '8':
      setParameter('letter', await askLetter());
      break;

    //     case 6:
    //       setParameter('data', await askArray());
    //       break;

    //     case 7:
    //       const opt = await askOption();
    //       if (opt !== 0) {
    //         setParameter('option', opt.toString());
    //       }
    //       break;

    case '10':
      showAbout();
      break;

    case '0':
      console.log('Bye :)');
      return;
  }

  await pause();
};

module.exports = app;
