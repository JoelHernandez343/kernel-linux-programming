require('colors');

const inquierer = require('inquirer');

const questions = {
  type: 'list',
  name: 'option',
  message: 'Select an option',
  choices: [
    {
      value: 1,
      name: `${'1.'.bold.green} View all parameters.`,
    },
    {
      value: 2,
      name: `${'2.'.bold.green} Write some parameters.`,
    },
    {
      value: 3,
      name: `${'3.'.bold.green} List completed tasks`,
    },
    {
      value: 4,
      name: `${'4.'.bold.green} List pending tasks`,
    },
    {
      value: 0,
      name: `${'7.'.bold.green} Exit`,
    },
  ],
};

const menu = async () => {
  console.clear();
  console.log('----------------------------------'.yellow.bgBlack);
  console.log('        Kernel module app         '.bold.white.bgBlack);
  console.log('----------------------------------\n'.yellow.bgBlack);

  const { option } = await inquierer.prompt(questions);

  return option;
};

const pause = async () =>
  await inquierer.prompt({
    name: '_',
    message: `Press ${'ENTER'.green} to continue.`,
  });

module.exports = {
  menu,
  pause,
};
