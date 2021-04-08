require('colors');

const inquirer = require('inquirer');
const { validateArray, transformArray } = require('./parameters');

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
      name: `${'6.'.green.bold} Set data`,
    },
    {
      value: 7,
      name: `${'7.'.green.bold} Invoke method of kernel module`,
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
    new inquirer.Separator('------------------------------------'),
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

const askArray = async () => {
  const { array } = await inquirer.prompt({
    name: 'array',
    message: `Input the array's values separated by ",". Limit 8:`,
    validate: validateArray,
  });

  return transformArray(array);
};

const askOption = async () => {
  const { option } = await inquirer.prompt({
    type: 'list',
    name: 'option',
    message: `Select module's method to invoke:`,
    choices: [
      {
        value: 1,
        name: `${'1.'.green.bold} Calculate average`,
      },
      {
        value: 2,
        name: `${'2.'.green.bold} Sort array`,
      },
      {
        value: 3,
        name: `${'3.'.green.bold} Find even numbers`,
      },
      {
        value: 0,
        name: `${'4.'.green.bold} Cancel`,
      },
    ],
  });

  return option;
};

module.exports = {
  menu,
  pause,
  askArray,
  askOption,
};
