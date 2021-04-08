require('colors');

const inquirer = require('inquirer');

const questions = {
  type: 'list',
  name: 'option',
  message: 'Select an option',
  loop: false,
  choices: [
    {
      value: 1,
      name: `${'1.'.green.bold} Show all parameters`,
    },
    {
      value: 'option',
      name: `${'2.'.green.bold} Show <${'option'.red.bold}> parameter`,
    },
    {
      value: 'data',
      name: `${'3.'.green.bold} Show <${'data'.red.bold}> parameter`,
    },
    {
      value: 'evenData',
      name: `${'4.'.green.bold} Show <${'even_data'.red.bold}> parameter`,
    },
    {
      value: 'average',
      name: `${'5.'.green.bold} Show <${'average'.red.bold}> parameter`,
    },
    {
      value: 6,
      name: `${'6.'.green.bold} Write array of data`,
    },
    {
      value: 7,
      name: `${'7.'.green.bold} Write option to kernel module`,
    },
    new inquirer.Separator('------------------------------------'),
    {
      value: 8,
      name: `${'8.'.green.bold} About`,
    },
    {
      value: 0,
      name: `${'9.'.green.bold} Exit`,
    },
  ],
};

const menu = async () => {
  console.clear();
  console.log('--------------------------------------'.yellow.bgBlack);
  console.log('          Kernel module app           '.white.bgBlack.bold);
  console.log('--------------------------------------\n'.yellow.bgBlack);

  const { option } = await inquirer.prompt(questions);

  return option;
};

const pause = async () =>
  await inquirer.prompt({
    name: '_',
    message: `Press ${'ENTER'.green} to continue.`,
  });

module.exports = {
  menu,
  pause,
};
